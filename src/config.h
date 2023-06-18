#ifndef CONFIG_H
#define CONFIG_H

#include "thirdparty/ini.h"
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

struct strbufs {
  char *buf;
  size_t cur;
  size_t limit;
};

static const char *strbufs_alloc(struct strbufs *sb, const char *str) {
  size_t len = strlen(str);
  size_t newcur = sb->cur + len + 1;

  if (newcur > sb->limit) {
    return 0;
  }

  char *p = sb->buf + sb->cur;

  memcpy(p, str, len+1);
  sb->cur = newcur;

  return p;
}


#define section(section, ...) struct cfgsection_##section { __VA_ARGS__ } section
#define cstr(key) const char *key;
#define cbool(key) bool key;
#define cint(key) int32_t key;
#define clist(key, f, dtype, count) dtype key[count]; bool key##_present;

struct config {
  struct strbufs _strbufs;

  // strings can have any "lifetime" that lasts as long as the config itself
  // e.g. static const-char's, argv's in main(), and data in _strbufs

  const char *movie_prefix;
  unsigned int movie_skip_to_before_frame;
  bool movie_readram;
  int world;
  int level;

#include "config.inc"
};

static bool config_init(struct config *cfg) {
  memset(cfg, 0, sizeof(struct config));
  size_t strbufs_limit = 4096;
  cfg->_strbufs.buf = malloc(strbufs_limit);
  cfg->_strbufs.cur = 0;
  cfg->_strbufs.limit = cfg->_strbufs.buf ? strbufs_limit : 0;
  return true;
}


#define PEEK_EQ(s) (i < argc && (strcmp(argv[i], s) == 0))
#define PEEK_IS_NONFLAG() (i < argc && (argv[i][0] != '-'))
#define POP_IF_EXISTS() \
  if (i >= argc) {      \
    ptr = 0;            \
  }                     \
  ptr = argv[i++]
#define POP()      \
  if (i >= argc) { \
    return false;  \
  }                \
  ptr = argv[i++]

static bool parse_cli_args(int argc, char *argv[], struct config *cfg) {
  char *ptr = 0;
  int i = 1;
  int last_i;

  cfg->world = 1;
  cfg->level = 1;

  // The rom is the first argument by default
  if (PEEK_IS_NONFLAG()) {
    POP();
    cfg->general.rom_filename = ptr;
  }

  do {
    last_i = i;
    if (PEEK_EQ("--rom")) {
      POP();
      POP();
      cfg->general.rom_filename = ptr;
    }
    if (PEEK_EQ("--movie") || PEEK_EQ("-m")) {
      POP();
      POP();
      cfg->movie_prefix = ptr;
    }
    if (PEEK_EQ("--movie-skip") || PEEK_EQ("-ms")) {
      POP();
      POP();
      unsigned int val;
      if (sscanf(ptr, "%u", &val) == 1) {
        cfg->movie_skip_to_before_frame = val;
      } else {
        return false;
      }
    }
    if (PEEK_EQ("--movie-readram")) {
      POP();
      cfg->movie_readram = true;
    }
    if (PEEK_EQ("--level") || PEEK_EQ("-l")) {
      int world = 0;
      int level = 0;
      POP();
      POP();
      if (sscanf(ptr, "%d-%d", &world, &level) == 2) {
        cfg->world = world;
        cfg->level = level;
      } else {
        return false;
      }
    }
  } while (last_i != i);

  return true;
}

#undef POP
#undef POP_IF_EXISTS
#undef PEEK_IS_NONFLAG
#undef PEEK_EQ

static bool read_i32(const char *s, int32_t *v) {
  int read = 0;
  if (sscanf(s, "%" SCNd32 "%n", v, &read) != 1) {
    return false;
  }
  if (s[read] != 0) {
    // partially read the number - there was more non-number stuff after
    return false;
  }
  return true;
}


static size_t parse_whitespace_delimited(const char *input, void* (*map)(const char*, void*), void *output, size_t max_count) {
  char buf[16] = {0};
  const char *s = input;
  bool done = false;
  size_t i;
  size_t off = 0;
  while (!done) {
    // trim whitespace from the beginning
    while (*s == ' ') {
      s += 1;
    }

    for (i = 0; ; i++) {
      char c = *s++;
      if (c == ' ') {
        break;
      }
      if (c == 0) {
        done = true;
        break;
      }
      if (i < sizeof(buf)-1) {
        buf[i] = c;
      }
    }
    buf[i] = 0;
    if (i > 0) {
      output = map(&buf[0], output);
      off += 1;
    }
    if (off >= max_count) {
      done = true;
    }
  }
  return off;
}

static void *read_key_binding(const char *key, void *buf) {
  SDL_Scancode *sc = buf;
  *sc = SDL_GetScancodeFromName(key);
  return sc+1;
}

#define section(sectionname, ...)                           \
  if (strcmp(section, #sectionname) == 0) {                 \
    struct cfgsection_##sectionname *p = &cfg->sectionname; \
    __VA_ARGS__                                             \
  }

#define cstr(key)                                  \
  if (strcmp(name, #key) == 0) {                   \
    p->key = strbufs_alloc(&cfg->_strbufs, value); \
    if (!p->key) { return 0; }                     \
  }

// i.e. true if "not false"
#define cbool(key)                                                                                                            \
  if (strcmp(name, #key) == 0) {                                                                                              \
    p->key = !(strcmp(value, "") == 0 || strcmp(value, "0") == 0 || strcmp(value, "false") == 0 || strcmp(value, "no") == 0); \
  }

#define cint(key)                           \
  if (strcmp(name, #key) == 0) {            \
    int32_t v = 0;                          \
    if (!read_i32(value, &v)) { return 0; } \
    p->key = v;                             \
  }

#define clist(key, f, dtype, count)                            \
  if (strcmp(name, #key) == 0) {                               \
    p->key##_present = true;                                   \
    parse_whitespace_delimited(value, f, &p->key[0], (count)); \
  }

static int get_ini_entry(void *user, const char *section, const char *name, const char *value) {
  struct config *cfg = user;

#include "config.inc"

  return 1;
}

static bool parse_options(const char *config_file, int argc, char *argv[], struct config *cfg) {
  int ini_ret = ini_parse(config_file, get_ini_entry, cfg);
  if (ini_ret != 0) {
    log_error("Could not parse configuration file");
    return false;
  }

  if (!parse_cli_args(argc, argv, cfg)) {
    log_error("Could not parse args");
    return false;
  }
  return true;
}

#endif
