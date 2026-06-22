(technically an AI-generated doc)

# Reorg Plan: Two Independent Game Libraries

## Context

The current codebase compiles SMB1 and SMB2J into a single `libsmbcore` by namespacing all functions with `smb1_`/`smb2j_` prefixes and using `#define` aliases to let shared `.c` files call the right version at compile time. All game code is tied to a global `SMB_STATE` singleton accessed via macros in `smbcore.h`. This makes the library hard to use on embedded targets, prevents dynamic loading of a single game, and leaves `.c` files as `#include`d fragments rather than real translation units.

The goal is two self-contained libraries — `libsmb1` and `libsmb2j` — each exposing the same `mario.h` public API, with an interface layer that decouples game code from the callback/state mechanism.

---

## Phase 1 — Context headers, interface layer, standalone TUs

### 1a. Split `smbcore.h`

- **Keep in `smbcore.h`**: game-agnostic utilities only — `byte`/`ushort` typedefs, math macros (`LOAD_16`, `ADD_16_16`, etc.), `ppureg`/`ppu_state`/`sprite` structs, `assert_*` macros, `RamByteArray`, `CONCAT11`, `CARRY1`, `NEGATE`, `SWAP`, `find_first_bit_position`. No reference to `SMB_STATE` or callbacks.
- **Move to `smbcore/interface_callbacks.h`**: everything that goes through `SMB_STATE` — `RAM`, `PPURAM`, `CHRROM`, `AreaData`, `EnemyData`, `MusicData`, `draw_tile`, `can_draw_tile`, `apu_write_register`, `apu_end_frame`, `joy1`, `joy2`, `announce_main_scroll`, `transfer_sprite_data`, `smb2j_load_games_beaten`, `smb2j_save_games_beaten`, `update_pattern_tables`, `PPU_STATE` macro, `rom_ptr`, `joystick_strobe`, all `APU_REG` inlines, `SMB_STATE` extern declaration, `SMB1_ONLY`/`SMB2J_ONLY`/`ssw` macros.

### 1b. Create interface selector and alternate implementation

- **`smbcore/interface.h`**: thin selector — `#include`s `interface_callbacks.h` by default, or `interface_globals.h` when `SMB_INTERFACE_GLOBALS` is defined at build time.
- **`smbcore/interface_globals.h`**: new file. Same macro/function names as `interface_callbacks.h` but backed by bare globals (`extern byte smbglobals_ram[0x10000]`, etc.) and `extern` function declarations. No `SMB_STATE` struct. Intended for embedded targets.

### 1c. Create per-game context headers

**`smbcore/smb1_context.h`**:
```c
#define SMB1_MODE
#include "smbcore.h"
#include "smbcore/interface.h"
#include "smbcore/smb_romarrays.h"
#include "smbcore/vars.h"
#include "smbcore/smb1.h"
#include "smbcore/types.h"
#include "smbcommon.h"
```

**`smbcore/smb2j_context.h`** — same shape with SMB2J equivalents.

These extract what is already at the top of `smb1.cpp` / `smb2j.cpp`.

### 1d. Make shared `.c` files proper translation units

- Build system injects context via `-include src/smbcore/smb1_context.h` (etc.) for each library's source list — no changes to the `.c` files themselves.
- Remove `static` from `LoadAreaPointer`, `GetAreaDataAddrs`, `AreaParserTaskControl`, `AreaParserTaskHandler` in `smbcore/area.h` (existing TODO comment).
- Remove all `#include "*.c"` lines from `smb1.cpp` and `smb2j.cpp`.

---

## Phase 2 — Drop `smb1_`/`smb2j_` prefixes and aliases

- Definitions in all game TUs use plain names (`GameMode`, `ScrollHandler`, etc.).
- Delete every `#define Foo smb1_Foo` / `#define Foo smb2j_Foo` line from `smbcore/smb1.h` and `smbcore/smb2j.h`.
- Rename `smb1_Foo`/`smb2j_Foo` declarations to plain `Foo` in those headers.
- Extract the identical struct definitions (`struct_ycr07`, `struct_axyz`, `blockbuffer_colli_result`, etc.) from both headers into a new `smbcore/game.h`; include it from both context headers. Keep any game-specific structs (e.g. `struct_ayz` only in smb2j) in the respective header.

After this phase the two libraries have conflicting symbols and **cannot be linked together**. Verify each game binary builds and runs independently.

---

## Phase 3 — Absorb `smbcore.cpp`, fold in `smbcommon.cpp`

### 3a. Move ROM loading into game files

- `load_smb1` and the SMB1 branch of `detect_and_load_rom` move into `smb1.cpp`.
- `smb2j_load_file` + `load_smb2j` (currently split across `smbcore.cpp`/`smb2j.cpp` via `extern "C"`) consolidate entirely into `smb2j.cpp`.
- Each game file exposes `SMB_load_rom(struct SMB_state *)` handling its own format.

### 3b. Move public API into each game file

Move from `smbcore.cpp` into `smb1.cpp` / `smb2j.cpp`:
- `SMB_state_size`, `SMB_state_init`, `SMB_tick`, `SMB_start_on_level`, `SMB_which_game`, `SMB_ram`, `SMB_ppuram`, `SMB_ram_finishwrite`, `draw_graphics`
- `SMB_STATE` thread_local definition
- `SMB1_Reset`/`SMB1_NMI` → renamed to `SMB_Reset`/`SMB_NMI` (plain names, no prefix); same for SMB2J side.
- `SMB_tick` no longer dispatches on `which_game` — calls `SMB_Reset`/`SMB_NMI` directly.
- `SMB_STATE` definition and `SMB_state_init`'s assignment of it are `interface_callbacks.h` concerns; `interface_globals.h` has no `SMB_STATE`.

`smbcore.cpp` is now empty — delete it.

Note: `SMB_which_game` is used by the testrunner. Keep it in `mario.h` returning a compile-time constant per library (`GAME_SMB1` or `GAME_SMB2J`).

### 3c. Compile `smbcommon.cpp` into each library

Add `src/smbcommon.cpp` to both library source lists. Compiled under each context header, `SMB1_ONLY`/`SMB2J_ONLY` in `set_world_and_level` and `InitializeMemory` become compile-time constants; dead branches can be removed at leisure.

---

## Phase 4 — Build system (`meson.build`)

```meson
smb1_args  = ['-include', 'src/smbcore/smb1_context.h',  '-DSMB1_MODE']
smb2j_args = ['-include', 'src/smbcore/smb2j_context.h', '-DSMB2J_MODE']

libsmb1 = library('smb1',
  ['src/smb1.cpp', 'src/smbcommon.cpp',
   'src/smbcore/common.c', 'src/smbcore/area.c',
   'src/smbcore/common_sound.c', 'src/smbcore/smb1only.c'],
  c_args: smb1_args, cpp_args: smb1_args)

libsmb2j = library('smb2j',
  ['src/smb2j.cpp', 'src/smbcommon.cpp',
   'src/smbcore/common.c', 'src/smbcore/area.c',
   'src/smbcore/common_sound.c', 'src/smbcore/smb2jonly.c'],
  c_args: smb2j_args, cpp_args: smb2j_args)

executable('smbvanilla',   [...], link_with: libsmb1)
executable('smbvanilla2j', [...], link_with: libsmb2j)
# libsmb1/libsmb2j may also be built as shared libraries for dlopen
```

---

## Verification

- After Phase 1: existing test runner still passes with both games; neither binary changes behavior.
- After Phase 2: build each game target separately and run the test runner against each.
- After Phase 3: `smbcore.cpp` is gone; both game binaries still pass tests; `SMB_which_game` returns a compile-time constant in each.
- After Phase 4: `smbvanilla` and `smbvanilla2j` both build, run their respective ROMs, and the test runner works against each.
- Embedded path: build with `-DSMB_INTERFACE_GLOBALS` and confirm `interface_globals.h` is selected and compiles cleanly against a stub environment.
