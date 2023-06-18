// Functions to render SMB with OpenGL.
// Designed to be called anywhere an OpenGL context exists. The caller is responsible for managing the context.
// Requires at least OpenGL 3.3.
// Uses GLEW. Avoids platform-specific libraries such as SDL, by design.

#include "mario.h"
#include "render_opengl.h"

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#define log_error(msg, ...) fprintf(stderr, "ERROR: " msg "\n", ##__VA_ARGS__)
#define log_info(msg, ...)  fprintf(stdout, "INFO: " msg "\n", ##__VA_ARGS__)

static bool gl_initshaders(struct SMBgl *gl);

// The OpenGL texture for the pattern table is 128x256 pixels (16x32 tiles, each tile is 8x8)
struct pattern_buffer {
  byte data[256][128];
};

struct RGB {
  byte r, g, b;
};

#define ATTRIB_POS_LOCATION 0
#define ATTRIB_ST_LOCATION 1
#define ATTRIB_PALIDX_LOCATION 2

struct gl_vbo_item {
  GLfloat pos[3];
  GLfloat st[2];
  GLbyte pal;
};

// On the NES, there's a limit of 1024 tiles on the screen at a time (32x30 bg tiles, plus 64 sprites = 960+64 = 1024).
// We render a tile with 4 vertices each.
// 1024 is an okay limit, but we wanna add more tiles for contingency.
#define MAX_VBO_ITEMS (8192*4)

struct SMBgl {
  struct RGB palette[0x40];
  byte palette_indices[0x20];
  GLuint gltexture;
  GLuint glvao;
  GLuint glvbo;
  GLuint gl_shader_program;
  GLint gl_pos_attrib;
  struct pattern_buffer *gl_update_texture;
  struct gl_vbo_item *vbo_buffer;
  size_t vbo_cur;
};

size_t SMBgl_size(void) {
  return sizeof(struct SMBgl);
}

bool SMBgl_init(struct SMBgl *gl) {
  memset(gl, 0, sizeof(struct SMBgl));

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    return false;
  }

  if (!gl_initshaders(gl)) {
    return false;
  }

  gl->vbo_buffer = malloc(sizeof(struct gl_vbo_item) * MAX_VBO_ITEMS);
  gl->vbo_cur = 0;

  glGenTextures(1, &gl->gltexture);
  glGenVertexArrays(1, &gl->glvao);
  glGenBuffers(1, &gl->glvbo);

  size_t stride = sizeof(struct gl_vbo_item);
  glBindVertexArray(gl->glvao);
  glBindBuffer(GL_ARRAY_BUFFER, gl->glvbo);
  glEnableVertexAttribArray(ATTRIB_POS_LOCATION);
  glVertexAttribPointer(ATTRIB_POS_LOCATION, 3, GL_FLOAT, GL_FALSE, stride, offsetof(struct gl_vbo_item, pos));
  glEnableVertexAttribArray(ATTRIB_ST_LOCATION);
  glVertexAttribPointer(ATTRIB_ST_LOCATION, 2, GL_FLOAT, GL_FALSE, stride, offsetof(struct gl_vbo_item, st));
  glEnableVertexAttribArray(ATTRIB_PALIDX_LOCATION);
  glVertexAttribIPointer(ATTRIB_PALIDX_LOCATION, 1, GL_BYTE, stride, offsetof(struct gl_vbo_item, pal));

  return true;
}

void SMBgl_fini(struct SMBgl *gl) {
  glDeleteBuffers(1, &gl->glvbo);
  glDeleteVertexArrays(1, &gl->glvao);
  glDeleteTextures(1, &gl->gltexture);
  free(gl->vbo_buffer);
  glDeleteProgram(gl->gl_shader_program);
}

void SMBgl_update_pattern_tables(struct SMBgl *gl, const unsigned char *chrrom) {
  // every time we update the pattern table, we queue an upload of a GL texture
  // (this practically only happens when the game loads, and during the SMB2J ending)

  // This might run before OpenGL is initialized, so queue up the buffer to be uploaded later
  if (gl->gl_update_texture) {
    free(gl->gl_update_texture);
  }

  struct pattern_buffer *p = malloc(sizeof(struct pattern_buffer));
  gl->gl_update_texture = p;

  for (int tileidx = 0; tileidx < 512; tileidx++) {
    const byte *buf = chrrom + tileidx * 0x10;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        const byte hibit = (buf[i + 8] >> (7 - j)) & 1;
        const byte lobit = (buf[i + 0] >> (7 - j)) & 1;

        int x = (tileidx%16)*8 + j;
        int y = (tileidx/16)*8 + i;

        p->data[y][x] = (hibit << 1) | lobit;
        p->data[y][x] <<= 6;
      }
    }
  }
}

void SMBgl_provide_palette_lookup(struct SMBgl *gl, const unsigned char *rgb) {
  memcpy(gl->palette, rgb, sizeof(gl->palette));
}

void SMBgl_update_palette(struct SMBgl *gl, const byte *palette_indices) {
  memcpy(gl->palette_indices, palette_indices, sizeof(gl->palette_indices));
}


void SMBgl_draw_tile(struct SMBgl *gl, const struct SMB_tile tile) {
  float z = 0.0f;
  if (tile.extra_type == TILE_TYPE_BG) {
    if (tile.tileidx == 0x124) {
      // blank bg tile
      return;
    }
    if (tile.tileidx >= 0x1b0 && tile.tileidx < 0x1b8) {
      z = 8.0f;
    }
  } else {
    if (tile.tileidx == 0xFC) {
      // blank sprite tile
      return;
    }
    if (tile.y > 240) {
      return;
    }
    z = 0.0f;
  }

  // texture coordinate values
  float s1 = (float)(tile.tileidx%16)*8.0f/128.0f;
  float s2 = (float)(tile.tileidx%16 + 1)*8.0f/128.0f;
  float t1 = (float)(tile.tileidx/16)*8.0f/256.0f;
  float t2 = (float)(tile.tileidx/16 + 1)*8.0f/256.0f;

  if (tile.flip_horz) {
    float tmp = s2;
    s2 = s1;
    s1 = tmp;
  }
  if (tile.flip_vert) {
    float tmp = t2;
    t2 = t1;
    t1 = tmp;
  }

  const struct gl_vbo_item items[4] = {
    {{tile.x,      tile.y,      z}, {s1, t1}, tile.paletteidx},
    {{tile.x+8.0f, tile.y,      z}, {s2, t1}, tile.paletteidx},
    {{tile.x,      tile.y+8.0f, z}, {s1, t2}, tile.paletteidx},
    {{tile.x+8.0f, tile.y+8.0f, z}, {s2, t2}, tile.paletteidx}
  };

  if (gl->vbo_cur+4 <= MAX_VBO_ITEMS) {
    memcpy(gl->vbo_buffer + gl->vbo_cur, &items[0], sizeof(items));

    gl->vbo_cur = gl->vbo_cur+4;
  } else {
    log_error("Too many VBO items");
  }
}

bool SMBgl_render_frame(struct SMBgl *gl) {

  // opengl
  const struct RGB bgcolor = gl->palette[gl->palette_indices[0]];

  if (gl->gl_update_texture) {
    // Upload a texture if there's data queued to upload
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gl->gltexture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // "GL_RED" just means a single channel
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 128, 256, 0, GL_RED, GL_UNSIGNED_BYTE, gl->gl_update_texture->data);

    free(gl->gl_update_texture);
    gl->gl_update_texture = 0;
  }

  // update the palette in the fragment shader
  float palbuf[32][4];
  for (int i = 0; i < 32; i++) {
    struct RGB *p = gl->palette + gl->palette_indices[i];
    if (i%4 == 0) {
      palbuf[i][0] = palbuf[i][1] = palbuf[i][2] = palbuf[i][3] = 0.0f;
    } else {
      palbuf[i][0] = (float)p->r/255.0f;
      palbuf[i][1] = (float)p->g/255.0f;
      palbuf[i][2] = (float)p->b/255.0f;
      palbuf[i][3] = 1.0f;
    }
  }
  GLint palette_location = glGetUniformLocation(gl->gl_shader_program, "palette");
  glUniform4fv(palette_location, 32, palbuf);

  glClearColor((float)bgcolor.r/255.0f, (float)bgcolor.g/255.0f, (float)bgcolor.b/255.0f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // row-major view matrix
  // transform the 2D 256x240 coordinate space to NDC
  static const float view_matrix[4][4] = {
    {2.0f/256.0f,        0.0f, 0.0f, -1.0f},
    {       0.0f,-2.0f/240.0f, 0.0f,  1.0f},
    {       0.0f,        0.0f, 0.0f,  0.0f},
    {       0.0f,        0.0f, 0.0f,  1.0f}
  };

  glUniformMatrix4fv(glGetUniformLocation(gl->gl_shader_program, "viewmat"), 1, 1, &view_matrix);

  // enable alpha blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glUseProgram(gl->gl_shader_program);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, gl->gltexture);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(gl->gl_shader_program, "patterntable"), 0);

  glBindBuffer(GL_ARRAY_BUFFER, gl->glvbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(gl->vbo_buffer[0])*gl->vbo_cur, gl->vbo_buffer, GL_STREAM_DRAW);

  glBindVertexArray(gl->glvao);
  for (size_t i = 0; i < gl->vbo_cur; i+=4) {
    glDrawArrays(GL_TRIANGLE_STRIP, i, 4);
  }

  gl->vbo_cur = 0;

  return true;
}

#define makethunk(prefix, st, field, fnname, args, params) \
static void prefix##_##fnname(void *userdata, args) { \
  void **newuserdata_ptr = ((unsigned char*)userdata) + offsetof(st, field); \
  void *newuserdata = *newuserdata_ptr; \
  return gl_update_pattern_tables(newuserdata, params); \
}

#define makeit(prefix, st, field) \
static void prefix##_update_pattern_tables(void *userdata, const byte *chrrom) { \
  void **newuserdata_ptr = ((unsigned char*)userdata) + offsetof(st, field); \
  void *newuserdata = *newuserdata_ptr; \
  return gl_update_pattern_tables(newuserdata, chrrom); \
} \
static void prefix##_add_to_callback(struct SMB_callbacks *cb) { \
  cb->update_pattern_tables = prefix##_update_pattern_tables; \
}

struct test_userdata {
  int foo;
  void *gl_userdata;
};

static bool gl_initshaders(struct SMBgl *gl) {
  // Vertex shader. Straight-forward stuff.
  // Transforms the vertex using the view matrix.
  // Passes the texture coordinates and palette index to fragment shader.
  static const GLchar *vertex_shader_source[1] = {
    "#version 330\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec2 st;\n"
    "layout(location = 2) in int palidx_in;\n"
    "flat out int palidx;\n"
    "out vec2 texcoord;\n"
    "uniform mat4 viewmat;\n"
    "void main() { palidx = int(palidx_in); texcoord = st; gl_Position = viewmat * vec4( position, 1.0 ); }"};

  // Fragment shader.
  // Performs a lookup of the correct palette color.
  static const GLchar *fragment_shader_source[1] = {
    "#version 330\n"
    "layout(location = 0) out vec4 color;\n"
    "flat in int palidx;\n"
    "in vec2 texcoord;\n"
    "uniform vec4 palette[32];\n"
    "uniform sampler2D patterntable;\n"
    "void main() { vec4 idx = texture(patterntable, texcoord); int n = int(idx.x*4.0); color = palette[palidx*4+n]; }"};


  GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vshader, 1, vertex_shader_source, 0);
  glCompileShader(vshader);

  GLint vertex_compiled;
  glGetShaderiv(vshader, GL_COMPILE_STATUS, &vertex_compiled);
  if (vertex_compiled != GL_TRUE) {
    char message[1024];
    glGetShaderInfoLog(vshader, sizeof(message), 0, message);
    log_error("GLSL vertex shader: %s", message);
    return false;
  }

  GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fshader, 1, fragment_shader_source, 0);
  glCompileShader(fshader);

  GLint fragment_compiled;
  glGetShaderiv(fshader, GL_COMPILE_STATUS, &fragment_compiled);
  if (fragment_compiled != GL_TRUE) {
    char message[1024];
    glGetShaderInfoLog(fshader, sizeof(message), 0, message);
    log_error("GLSL fragment shader: %s", message);
    return false;
  }

  GLuint program = glCreateProgram();

  glAttachShader(program, vshader);
  glAttachShader(program, fshader);
  glLinkProgram(program);

  GLint program_linked;
  glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
  if (program_linked != GL_TRUE) {
    char message[1024];
    glGetProgramInfoLog(program, sizeof(message), 0, message);
    log_error("GLSL program: %s", message);
    return false;
  }

  gl->gl_shader_program = program;

  return true;
}
