#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "mario.h"
#include "movie.h"


struct testrunner_userdata {
    FILE *romfile;
    struct SMB_state *smb_state;
    struct SMB_buttons joy1_buttons;
};

bool open_rom(struct testrunner_userdata *userdata, const char *filename) {
    FILE *f = fopen(filename, "rb");
    userdata->romfile = f;
    return f != 0;
}

bool read_rom_bytes(struct testrunner_userdata *userdata, byte *buf, size_t size) {
    return fread(buf, size, 1, userdata->romfile) == 1;
}

bool seek_rom(struct testrunner_userdata *userdata, size_t offset) {
    fseek(userdata->romfile, offset, SEEK_SET);
    return true;
}

void joy1(struct testrunner_userdata *userdata, struct SMB_buttons *buttons) {
    *buttons = userdata->joy1_buttons;
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

    while (movie_next(movie, &movie_buttons, ram)) {

        if (framecounter != 0) {
            // Don't compare the first frame, because the movie's ramseq's first frame occurs after Reset and before the first NMI.
            // SMB_tick calls Reset if it hasn't been called before. If we're here, then Reset has never been called.
            // Additionally, we can go without comparing it, as memory before the first NMI is not very interesting.

            byte *compareto = SMB_ram(userdata->smb_state);

            // RAM errors start at frame 16600, when we go underwater

            #define mem_eq_range(from, upto) do { \
                const byte *a = ram; \
                const byte *b = compareto; \
                size_t len = (upto) + 1 - (from); \
                for (size_t i = (from); i <= (upto); i++) { \
                    if (a[i] != b[i]) { \
                        if (printerrors) { \
                            fprintf(stderr, "Caused by frame %05d: RAM not equal: At %04lX: %02X expected vs %02X actual\n", framecounter-1, i, a[i], b[i]); \
                            errorcount += 1; \
                            if (errorcount >= 1000) { \
                                printerrors = false; \
                                fprintf(stderr, "Too many errors. Not printing any more...\n"); \
                            } \
                            success = false; \
                        } \
                    } \
                } \
            } while (0)

            // Missing ranges:
            // $160-$1FF is the stack (this port doesn't use this)

            if (SMB_which_game(userdata->smb_state) == GAME_SMB1) {
                mem_eq_range(0x0008, 0x00FF);
                mem_eq_range(0x0100, 0x015F);
                mem_eq_range(0x0200, 0x07FF);
            } else if (SMB_which_game(userdata->smb_state) == GAME_SMB2J) {
                // FDS may modify $00-$0F and $F5-$FF with BIOS subroutines, so they're unreliable
                mem_eq_range(0x0010, 0x00EF);
                mem_eq_range(0x0109, 0x015F);
                mem_eq_range(0x0200, 0x07FF);
            }
        }

        if (upto_frame != 0 && framecounter == upto_frame+1) {
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

    if (argc > 3) {
        if (sscanf(argv[3], "%" SCNd32, &upto_frame) != 1) {
            upto_frame = 0;
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

    if (success) {
        printf("✅ Movie passed RAM tests\n");
    } else {
        printf("❌ Movie failed RAM tests\n");
    }

    movie_fini(&movie);

    return success ? 0 : 1;
}
