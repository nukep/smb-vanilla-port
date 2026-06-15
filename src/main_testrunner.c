#include "mario.h"
#include "movie.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct testrunner_userdata {
  FILE *romfile;
  struct SMB_state *smb_state;
  struct SMB_buttons joy1_buttons;

  bool mode_failframe;
  int failframe_result;
};

bool open_rom(struct testrunner_userdata *userdata, const char *filename) {
  FILE *f = fopen(filename, "rb");
  userdata->romfile = f;
  return f != 0;
}

bool read_rom_bytes(void *userdata, byte *buf, size_t size) {
  struct testrunner_userdata *ud = userdata;
  return fread(buf, size, 1, ud->romfile) == 1;
}

bool seek_rom(void *userdata, size_t offset) {
  struct testrunner_userdata *ud = userdata;
  fseek(ud->romfile, offset, SEEK_SET);
  return true;
}

void joy1(void *userdata, struct SMB_buttons *buttons) {
  struct testrunner_userdata *ud = userdata;
  *buttons = ud->joy1_buttons;
}

byte smb2j_load_games_beaten(void *userdata) {
  // A decent test value - lets us test Worlds A-D
  return 8;
}
bool smb2j_save_games_beaten(void *userdata, byte games_beaten) {
  printf("Pretending to save game...");
  printf("Games beaten: %d\n", games_beaten);
  return true;
}

bool run_movie(struct Movie *movie, struct testrunner_userdata *userdata, uint32_t upto_frame) {
  byte ram[0x800];
  struct MovieButtons movie_buttons;
  uint32_t framecounter = 0;
  bool success = true;

  int errorcount = 0;
  bool printerrors = true;

  const int max_errorcount = 100;

  while (movie_next(movie, &movie_buttons, ram)) {

    if (framecounter != 0) {
      // Don't compare the first frame, because the movie's ramseq's first frame occurs after Reset and before the first
      // NMI. SMB_tick calls Reset if it hasn't been called before. If we're here, then Reset has never been called.
      // Additionally, we can go without comparing it, as memory before the first NMI is not very interesting.

      byte *compareto = SMB_ram(userdata->smb_state);

#define RANGE_N 64

#define mem_eq_range(from, upto) { \
        if (range_curidx >= RANGE_N) { fprintf(stderr, "FATAL: too many memory ranges\n"); return false; } \
        range_from[range_curidx] = from; \
        range_upto[range_curidx] = upto; \
        range_curidx += 1; \
      }

      int range_curidx = 0;
      int range_from[RANGE_N] = {};
      int range_upto[RANGE_N] = {};

      // Missing ranges:
      // $00-$08 are temporary registers
      // $E7-$EA are pointers
      // $EB-$EF are temporary registers
      // $F5-F6 is a pointer
      // $109 is a temporary variable
      // $160-$1FF is the stack (this port doesn't use this)
      // $3C4-$3CA is SprObject_Attrib. It's mostly unused except for power-ups, and has some glitchy values from cheep-cheeps that are best not compared
      // $735 is a temporary variable

      if (SMB_which_game(userdata->smb_state) == GAME_SMB1) {
        mem_eq_range(0x0009, 0x00E6);
        mem_eq_range(0x00F0, 0x00F4);
        mem_eq_range(0x00F7, 0x00FF);
        mem_eq_range(0x0100, 0x0108);
        mem_eq_range(0x010a, 0x015F);
        mem_eq_range(0x0200, 0x03C3);
        mem_eq_range(0x03CB, 0x0734);
        mem_eq_range(0x0736, 0x07FF);
      } else if (SMB_which_game(userdata->smb_state) == GAME_SMB2J) {
        // FDS may modify $00-$0F and $F5-$FF with BIOS subroutines, so they're unreliable
        mem_eq_range(0x0010, 0x00E6);
        mem_eq_range(0x010a, 0x015F);
        mem_eq_range(0x0200, 0x03C3);
        mem_eq_range(0x03CB, 0x0734);
        mem_eq_range(0x0736, 0x07FF);
      }

      for (int j = 0; j < range_curidx; j++) {
        const byte *a = ram;
        const byte *b = compareto;
        const int from = range_from[j];
        const int upto = range_upto[j];

        for (int i = from; i <= upto; i++) {
          if (a[i] != b[i]) {

            if (userdata->mode_failframe) {
              userdata->failframe_result = framecounter - 1;
              return false;
            }

            if (printerrors) {
              fprintf(stderr, "Caused by frame %05d: RAM not equal: At %04X: %02X expected vs %02X actual\n",
                      framecounter - 1, i, a[i], b[i]);
              errorcount += 1;
              if (errorcount >= max_errorcount) {
                printerrors = false;
                fprintf(stderr, "Too many errors. Not printing any more...\n");
              }
              success = false;
            }
          }
        }
      }
    }

    if (upto_frame != 0 && framecounter == upto_frame + 1) {
      break;
    }

    userdata->joy1_buttons.u = movie_buttons.u;
    userdata->joy1_buttons.d = movie_buttons.d;
    userdata->joy1_buttons.l = movie_buttons.l;
    userdata->joy1_buttons.r = movie_buttons.r;
    userdata->joy1_buttons.a = movie_buttons.a;
    userdata->joy1_buttons.b = movie_buttons.b;
    userdata->joy1_buttons.select = movie_buttons.select;
    userdata->joy1_buttons.start = movie_buttons.start;

    SMB_tick(userdata->smb_state);
    framecounter += 1;
  }

  printf("Ran %d frames\n", framecounter);

  return success;
}

#ifdef WIN32
#include <Windows.h>
#endif

int main(int argc, char *argv[]) {
#ifdef WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  const char *rom_filename = argv[1];
  const char *movie_prefix = argv[2];
  uint32_t upto_frame = 0;
  bool mode_failframe = false;

  if (argc > 3) {
    // Support a mode to print the failed frame, if any
    if (strcmp(argv[3], "--print-failframe") == 0) {
      mode_failframe = true;
    } else {
      if (sscanf(argv[3], "%" SCNd32, &upto_frame) != 1) {
        upto_frame = 0;
      }
    }
  }

  printf("Movie: %s\n", movie_prefix);
  if (upto_frame == 0) {
    printf("Up to frame: entire movie\n");
  } else {
    printf("Up to frame: %d\n", upto_frame);
  }

  struct SMB_state *smb_state = malloc(SMB_state_size());
  struct testrunner_userdata userdata = {0};

  if (!smb_state) {
    return 1;
  }

  userdata.smb_state = smb_state;
  userdata.mode_failframe = mode_failframe;

  struct SMB_callbacks callbacks = {0};
  callbacks.userdata = &userdata;
  callbacks.read_rom_bytes = read_rom_bytes;
  callbacks.seek_rom = seek_rom;
  callbacks.joy1 = joy1;
  callbacks.smb2j_load_games_beaten = smb2j_load_games_beaten;
  callbacks.smb2j_save_games_beaten = smb2j_save_games_beaten;

  open_rom(&userdata, rom_filename);
  SMB_state_init(smb_state, &callbacks);

  struct Movie movie;
  char buttons_filename[1024];
  char ram_filename[1024];
  snprintf(buttons_filename, sizeof(buttons_filename), "%smovie-buttons.txt", movie_prefix);
  snprintf(ram_filename, sizeof(ram_filename), "%smovie-ram.bin", movie_prefix);
  if (!movie_init(&movie, buttons_filename, ram_filename)) {
    return 1;
  }
  bool success = run_movie(&movie, &userdata, upto_frame);

  if (mode_failframe) {
    printf("failframe result: %d\n", userdata.failframe_result);
    success = true;
  }

  if (!mode_failframe) {
    if (success) {
      printf("✅ Movie passed RAM tests\n");
    } else {
      printf("❌ Movie failed RAM tests\n");
    }
  }

  movie_fini(&movie);

  return success ? 0 : 1;
}
