#include <stdbool.h>

struct cli_args {
  const char *rom_filename;
  const char *movie_prefix;
  unsigned int movie_skip_to_before_frame;
  bool movie_readram;
  int world;
  int level;
};

#define PEEK_EQ(s) (i < argc && (strcmp(argv[i], s) == 0))
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

bool parse_cli_args(int argc, char *argv[], struct cli_args *out) {
  char *ptr = 0;
  int i = 1;
  int last_i;

  out->world = 1;
  out->level = 1;

  // The rom is the first argument by default
  if (!out->rom_filename) {
    POP_IF_EXISTS();
    out->rom_filename = ptr;
  }

  do {
    last_i = i;
    if (PEEK_EQ("--rom")) {
      POP();
      POP();
      out->rom_filename = ptr;
    }
    if (PEEK_EQ("--movie") || PEEK_EQ("-m")) {
      POP();
      POP();
      out->movie_prefix = ptr;
    }
    if (PEEK_EQ("--movie-skip") || PEEK_EQ("-ms")) {
      POP();
      POP();
      unsigned int val;
      if (sscanf(ptr, "%u", &val) == 1) {
        out->movie_skip_to_before_frame = val;
      } else {
        return false;
      }
    }
    if (PEEK_EQ("--movie-readram")) {
      POP();
      out->movie_readram = true;
    }
    if (PEEK_EQ("--level") || PEEK_EQ("-l")) {
      int world = 0;
      int level = 0;
      POP();
      POP();
      if (sscanf(ptr, "%d-%d", &world, &level) == 2) {
        out->world = world;
        out->level = level;
      } else {
        return false;
      }
    }
  } while (last_i != i);

  return true;
}

#undef POP
#undef POP_IF_EXISTS
#undef PEEK_EQ
