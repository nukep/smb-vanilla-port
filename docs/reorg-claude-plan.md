(technically an AI-generated doc)

# Reorg Plan: Two Independent Game Libraries

## Context

The current codebase compiles SMB1 and SMB2J into a single `libsmbcore` by namespacing all functions with `smb1_`/`smb2j_` prefixes and using `#define` aliases to let shared `.c` files call the right version at compile time. All game code is tied to a global `SMB_STATE` singleton accessed via macros in `smbcore.h`. This makes the library hard to use on embedded targets, prevents dynamic loading of a single game, and leaves `.c` files as `#include`d fragments rather than real translation units.

The goal is two self-contained libraries — `libsmb1` and `libsmb2j` — each exposing the same `mario.h` public API, with an interface layer that decouples game code from the callback/state mechanism.

### Key facts about the current build (verified against the code)

These facts drive several decisions below. Get them wrong and the build breaks.

1. **The shared "`.c`" files are actually C++.** `src/smbcore/common.c`, `area.c`, `common_sound.c`, `smb1only.c`, `smb2jonly.c` are named `.c` but compiled as C++. They are **never** listed as meson sources today — they are `#include`d textually into `smb1.cpp`/`smb2j.cpp`. They use C++-only constructs reachable via `smbcore.h` (`class RamByteArray`, `thread_local`, aggregate assignment `*buttons = {0};`). Meson selects the compiler **by file extension**, so listing them as `.c` sources (as the original Phase 4 did) would invoke the C compiler and fail. They must either be renamed to `.cpp` or compiled as C++ explicitly. **This plan renames them to `.cpp`** (see Phase 1d).

2. **Everything is currently one translation unit per game.** Because the `.c` files are `#include`d into `smb1.cpp`, all of SMB1's code is a single TU; likewise SMB2J. This is why `static` functions and inline glue forward-declarations work across "files" today. Splitting into real TUs (the entire point of Phase 1d) breaks every cross-file `static` reference and every implicit forward declaration. The two confirmed cross-TU `static` cases and the glue functions are enumerated below — they must be handled or the link fails.

3. **`smbcore.h` and `smbcommon.h` have no include guards.** The `-include` injection approach plus any redundant direct `#include` will double-include them. Phase 1 must add include guards (or `#pragma once`) to every header that will be pulled in via context, and remove the now-redundant direct includes from the `.cpp` files.

---

## Cross-TU symbols that must be declared in a header (the critical gap)

Today these resolve because the caller and definition land in the same TU. Once files are real TUs, each needs a real declaration in a shared header. Verified call sites:

| Symbol | Defined in | Called from (other TU) | Currently declared? |
|---|---|---|---|
| `SoundEngine` | `common_sound.cpp` (`static`!) | `smb1.cpp`, `smb2j.cpp` NMI | No — and it's `static` |
| `DrawTitleScreen` (SMB1) | `smb1.cpp` | `common.cpp` (`ScreenRoutines`) | No |
| `TransposePlayers` (SMB1) | `smb1.cpp` | `common.cpp` | No |
| `ScrollScreen` (SMB2J) | `smb2j.cpp` | `common.cpp` (3×) | No |
| `LoadFiles` (SMB2J) | `smb2j.cpp` | `smb2jonly.cpp` (4×) | No (locally declared in smb2j.cpp) |
| `UpdateGamesBeaten` (SMB2J) | `smb2j.cpp` | `smb2jonly.cpp` | No (locally declared) |
| `FDS_drive_status` (SMB2J) | `smb2j.cpp` | `smb2jonly.cpp` (2×) | No |
| `LoadAreaPointer`, `GetAreaDataAddrs`, `AltHard_GetAreaDataAddrs` (SMB2J-only), `AreaParserTaskControl`, `AreaParserTaskHandler` | `area.cpp` (`static`) | `common.cpp` | declared `static` in `area.h` |

Action: make `SoundEngine` non-`static` and declare it in `smbcommon.h` (it is game-agnostic). Move the inline glue forward-decls currently at the tops of `smb1.cpp`/`smb2j.cpp` (`DrawTitleScreen`, `TransposePlayers`, `ScrollScreen`, `LoadFiles`, `UpdateGamesBeaten`, `FDS_drive_status`, etc.) into the appropriate per-game header (`smb1.h`/`smb2j.h`) so the shared TUs can see them. Drop `static` from the five `area.h` functions (the original plan only listed four — `AltHard_GetAreaDataAddrs` was missed; it is `SMB2J_MODE`-only).

The two real cross-TU `static` cases were found by scanning; one is a false positive worth noting so a future reader doesn't re-flag it:
- `common_sound.c::SoundEngine` — **real**, must be de-`static`ed and declared.
- `smb2jonly.c::LoadLuigiPhysics` referenced in `common.c` — **false positive**; the two references in `common.c` are inside comments only. No action.

---

## Phase 1 — Context headers, interface layer, standalone TUs

### 1a. Split `smbcore.h`

- **Keep in `smbcore.h`**: game-agnostic utilities only — `byte`/`ushort`/`u8`/`u16`/`i8`/`i16`/`i32` typedefs, the `NOINLINE`/`NORETURN`/`likely`/`unlikely` and `error`/`warning` macros, math macros (`LOAD_16`, `ADD_16_16`, etc.), `ppureg`/`ppu_state`/`sprite` structs, `assert_*`/`assume_weak_original`/`jmpengine_overflow` helpers, `RamByteArray`/`ConstRamByteArray` and the `RAMARRAY` macros, `CONCAT11`, `CARRY1`, `NEGATE`, `SWAP`, `ABS_DIFF`, `find_first_bit_position`. No reference to `SMB_STATE` or callbacks.
  - **Caveat:** `RamByteArray` uses the `RAM()` macro, which is an interface concern (it expands to `SMB_STATE->rammem[...]`). So `smbcore.h` cannot fully avoid depending on `RAM()`. Resolve by having `smbcore.h` (or the context header) include the interface header *before* the `RamByteArray` definitions, or keep `RamByteArray`/`RAMARRAY` in the interface layer with the other `RAM`-dependent code. Decide explicitly; do not leave `RAM` undefined at the point `RamByteArray` is parsed.
- **Move to `smbcore/interface_callbacks.h`**: everything that goes through `SMB_STATE` — the `SMB_state`/`SMB_callbacks` wiring, `RAM`, `PPURAM`, `CHRROM`, `RAM_CONST`, `AreaData`, `EnemyData`, `MusicData`, `PatchCurrentPlayer`, `read_rom_bytes`, `seek_rom`, `draw_tile`, `can_draw_tile`, `apu_write_register`, `apu_end_frame`, `joy1`, `joy2`, `announce_main_scroll`, `transfer_sprite_data`, `smb2j_load_games_beaten`, `smb2j_save_games_beaten`, `update_pattern_tables`, `PPU_STATE` macro + `#include "ppu.h"`, `rom_ptr`, `joystick_strobe`, all `APU_REG` inlines, the `SMB_STATE` extern declaration, and the `SMB1_ONLY`/`SMB2J_ONLY`/`SMB1_2J_SWITCH`/`ssw` macros.
- **Add include guards** to `smbcore.h` (and to the new headers). It currently has none.

### 1b. Create interface selector and alternate implementation

- **`smbcore/interface.h`**: thin selector — `#include`s `interface_callbacks.h` by default, or `interface_globals.h` when `SMB_INTERFACE_GLOBALS` is defined at build time.
- **`smbcore/interface_globals.h`**: new file. Same macro/function names as `interface_callbacks.h` but backed by bare globals (`extern byte smbglobals_ram[0x10000]`, etc.) and `extern` function declarations. No `SMB_STATE` struct. Intended for embedded targets.
  - This file is a **stub for now** and is only smoke-tested (see Verification). It must provide: `RAM`/`PPURAM`/`CHRROM`/`RAM_CONST`, `AreaData`/`EnemyData`/`MusicData`/`PatchCurrentPlayer`, the PPU state hook, the APU/joy/draw/scroll/sprite functions, and the `SMB1_ONLY`/`SMB2J_ONLY` constants (which become compile-time `true`/`false` per library — see Phase 3c). Getting the full surface right is deferred; the goal in Phase 1 is that it *exists and the selector compiles*.

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
#include "smbcore/consts.h"   // smb1only/common/area all #include "consts.h"
#include "smbcommon.h"
```

**`smbcore/smb2j_context.h`** — same shape with SMB2J equivalents (`smb2j_romarrays.h`, `smb2j.h`) and `#define SMB2J_MODE`.

Notes:
- These extract what is already at the tops of `smb1.cpp` / `smb2j.cpp`, **plus** the per-file includes currently inside the `.c` files (`types.h`, `vars.h`, `consts.h`, `area.h`). Since injection happens once per TU and the `.c` files also `#include` these directly, **include guards make the duplication harmless** — but only if guards exist (they do for `vars.h`/`types.h`/`consts.h`/`area.h`/romarrays; they do **not** yet for `smbcore.h`/`smbcommon.h`). Add the missing guards in 1a.
- The glue forward-declarations and `#define GameTimerDisplay GameTimerDisplaySMB1` (resp. SMB2J), and SMB2J's `#define AreaAddrOffsets RAMARRAY_CONST(0xC360, 0x28)`, currently sit in the `.cpp` files. Decide where each lands: game-specific `#define`s like `GameTimerDisplay` and `AreaAddrOffsets` belong in the context header (or the per-game romarrays header); the cross-TU function decls belong in `smb1.h`/`smb2j.h` (see the table above). `AreaAddrOffsets` already has an SMB1 definition in `smb_romarrays.h` but the SMB2J one is a manual `#define` in `smb2j.cpp` — consolidate it into `smb2j_romarrays.h` for symmetry.

### 1d. Make shared files proper translation units

- **Rename** `common.c`, `area.c`, `common_sound.c`, `smb1only.c`, `smb2jonly.c` → `.cpp` (they are already C++; this lets meson compile them directly). Update `area.h`'s include and any references.
- Build system injects context via `-include src/smbcore/smb1_context.h` (etc.) for each library's source list — no per-file edits for context.
- **Remove `static`** from `LoadAreaPointer`, `GetAreaDataAddrs`, `AltHard_GetAreaDataAddrs` (SMB2J-only), `AreaParserTaskControl`, `AreaParserTaskHandler` in `area.h` (existing TODO comment) — and update the definitions in `area.cpp` to match.
- **De-`static` and declare `SoundEngine`** (in `common_sound.cpp`); add a declaration to `smbcommon.h`.
- **Hoist the cross-TU glue declarations** from the tops of `smb1.cpp`/`smb2j.cpp` into `smb1.h`/`smb2j.h` (see table). Remove the now-redundant local forward-decls.
- Remove all `#include "*.c"` lines from `smb1.cpp` and `smb2j.cpp`, and remove the per-file `#include "types.h"`/`"vars.h"`/`"consts.h"` from the (renamed) shared `.cpp` files if relying on the context injection — *or* leave them and rely on include guards. Pick one approach and apply it consistently.

---

## Phase 2 — Drop `smb1_`/`smb2j_` prefixes and aliases

- Definitions in all game TUs use plain names (`GameMode`, `ScrollHandler`, etc.).
- Delete every `#define Foo smb1_Foo` / `#define Foo smb2j_Foo` line from `smbcore/smb1.h` and `smbcore/smb2j.h` (~330 and ~430 lines respectively — this is mechanical but large; consider a script).
- Rename `smb1_Foo`/`smb2j_Foo` declarations to plain `Foo` in those headers.
- Extract the identical struct definitions (`struct_ycr07`, `struct_axyz`, `blockbuffer_colli_result`, etc., plus the `#pragma pack(push,1)`/`pop` framing) shared by both headers into a new `smbcore/game.h`; include it from both context headers. Keep game-specific structs in the respective header (note: `struct_ayz` and `struct_axyz` appear in **both** headers today, so they go in `game.h`; verify the final per-game remainder is genuinely game-specific before leaving it behind).

After this phase the two libraries have conflicting symbols and **cannot be linked together**. The single `smbcore` library and the testrunner-against-both-games setup no longer work as-is (see Phase 4 / Verification). Verify each game binary builds and runs independently.

---

## Phase 3 — Absorb `smbcore.cpp`, fold in `smbcommon.cpp`

### 3a. Move ROM loading into game files

- `load_smb1` and the SMB1 branch of `detect_and_load_rom` move into `smb1.cpp`.
- `smb2j_load_file` + `load_smb2j` + the SMB2J branch of `detect_and_load_rom` (currently split across `smbcore.cpp`/`smb2j.cpp` via `extern "C"`) consolidate entirely into `smb2j.cpp`. The `extern "C"` indirection for `smb2j_load_file` can then be dropped.
- Each game file exposes a private loader; `detect_and_load_rom` becomes per-library (each only knows its own format). Note SMB1 currently only handles the iNES path and SMB2J handles the two FDS paths — keep that behavior, just split it.

### 3b. Move public API into each game file

Move from `smbcore.cpp` into `smb1.cpp` / `smb2j.cpp`:
- `SMB_state_size`, `SMB_state_init`, `SMB_start_on_level`, `SMB_which_game`, `SMB_ram`, `SMB_ppuram`, `SMB_ram_finishwrite`, `SMB_tick`, and the `draw_graphics` + `draw_nametable_tile`/`draw_nametable_rect` helpers.
- `SMB_STATE` `thread_local` definition.
- `SMB1_Reset`/`SMB1_NMI` → renamed to `SMB_Reset`/`SMB_NMI` (plain names, no prefix); same for SMB2J side. Drop the `extern "C"` wrappers that only existed to bridge `smbcore.cpp` ↔ the uber-modules.
- `SMB_tick` no longer dispatches on `which_game` — it calls this library's `SMB_Reset`/`SMB_NMI` directly. The SMB1-only `set_world_and_level` hack in `SMB_tick` stays in `smb1.cpp` (it's already SMB1-only — the SMB2J branch has it commented out).
- The `SMB_STATE` definition and `SMB_state_init`'s assignment of it are `interface_callbacks.h` concerns; the `interface_globals.h` build has no `SMB_STATE` and will need its own trivial `SMB_state_init`/`SMB_state_size` (deferred with the rest of the globals stub).

`draw_graphics`/`draw_nametable_*` are byte-identical between the two games. To avoid divergence, consider leaving them in a shared file (`smbcommon.cpp`) rather than copying into both game files. Flag this as a judgment call; copying is acceptable if the duplication is documented.

`smbcore.cpp` is now empty — delete it, and remove it from the build.

Note: `SMB_which_game` is used by the testrunner. Keep it in each library returning a compile-time constant (`GAME_SMB1` or `GAME_SMB2J`).

### 3c. Compile `smbcommon.cpp` into each library

Add `src/smbcommon.cpp` to both library source lists. Compiled under each context header, `SMB1_ONLY`/`SMB2J_ONLY` in `set_world_and_level` and `InitializeMemory` become compile-time constants (`true`/`false`), so dead branches can be removed at leisure. (Today `SMB1_ONLY` is `SMB_STATE->which_game == GAME_SMB1`; under each per-game build it should resolve to a constant — define it that way in each interface header, keyed off `SMB1_MODE`/`SMB2J_MODE`.)

`sync_data`, `set_world_and_level`, `update_screen`, `WriteNTAddr`, `InitializeMemory`, `ReadJoypads`, `ReadPortBits`, `dectimers`, `update_prng` all live here and are game-agnostic — they stay in `smbcommon.cpp`, now compiled twice (once per library) instead of `#include`d.

---

## Phase 4 — Build system (`meson.build`)

Replace the single `smbcore` library and its two executables with two libraries and two executables. Because the shared files are now `.cpp`, list them directly:

```meson
smb1_args  = ['-include', 'src/smbcore/smb1_context.h']
smb2j_args = ['-include', 'src/smbcore/smb2j_context.h']
# Note: SMB1_MODE/SMB2J_MODE are #defined inside the context headers,
# so -D flags for them are redundant. Keep mode defines in ONE place
# (the context header) to avoid drift.

libsmb1 = library('smb1',
  ['src/smb1.cpp', 'src/smbcommon.cpp',
   'src/smbcore/common.cpp', 'src/smbcore/area.cpp',
   'src/smbcore/common_sound.cpp', 'src/smbcore/smb1only.cpp'],
  cpp_args: smbcore_args + smb1_args)

libsmb2j = library('smb2j',
  ['src/smb2j.cpp', 'src/smbcommon.cpp',
   'src/smbcore/common.cpp', 'src/smbcore/area.cpp',
   'src/smbcore/common_sound.cpp', 'src/smbcore/smb2jonly.cpp'],
  cpp_args: smbcore_args + smb2j_args)
```

Open question — **executables and the testrunner**:
- The original plan implied a single `smbvanilla` linking `libsmb1`. But the current `smbvanilla` plays *either* game depending on the ROM you hand it (`detect_and_load_rom`). After the split, one executable can only contain one game's symbols. Decide:
  - (a) Two executables, `smbvanilla` (SMB1) and `smbvanilla2j` (SMB2J), each linking one library; OR
  - (b) One executable that links *both* libraries — **not possible** after Phase 2 because of symbol collisions (`SMB_tick`, etc. exist in both). Would require either keeping the public API symbols namespaced/versioned, or `dlopen`ing one library at runtime.
- The **testrunner** currently runs both SMB1 and SMB2J movies through one binary and branches on `SMB_which_game`. After the split it must become two testrunner binaries (one per library) — or one that `dlopen`s. Update `main_testrunner.c` invocation accordingly; the `SMB_which_game`-based range selection stays but each binary only ever returns one value.
- `libsmb1`/`libsmb2j` may also be built as shared libraries for `dlopen`.

This executable/testrunner question should be resolved (probably option a: two of each) before starting Phase 4.

---

## Verification

- After Phase 1: each game still builds (now as separate TUs rather than one `#include` blob) and the existing test runner passes for both games; neither binary changes behavior. This is the riskiest phase for link errors — watch for undefined references from the cross-TU `static`/glue symbols enumerated above.
- After Phase 2: build each game target separately and run the test runner against each. The combined `smbcore` library no longer exists.
- After Phase 3: `smbcore.cpp` is gone; both game binaries still pass tests; `SMB_which_game` returns a compile-time constant in each.
- After Phase 4: `smbvanilla` and `smbvanilla2j` both build, run their respective ROMs, and a (per-game) test runner works against each. Confirm `wasm` build (`build-wasm/`) is updated too — it currently builds `libsmbcore` and `smb_testrunner`.
- Embedded path: build with `-DSMB_INTERFACE_GLOBALS` and confirm `interface_globals.h` is selected and compiles cleanly against a stub environment. (This stub is intentionally incomplete in Phase 1; the verification is "selector + globals header compile," not "embedded target runs.")

## Suggested ordering / risk notes

- Do 1a–1d as one mechanical-but-careful unit and get *one* game (SMB1, the simpler/smaller glue surface) building as real TUs before touching SMB2J. SMB2J has more glue (`LoadFiles`, `UpdateGamesBeaten`, FDS shims, `AreaAddrOffsets`, `AltHard_GetAreaDataAddrs`).
- Phase 2's prefix/alias deletion is large and mechanical; script it and diff carefully. It's also the point of no return for "one library" — keep the repo bisectable by ensuring each phase builds.
- The `RamByteArray`-depends-on-`RAM` layering (1a) and the no-include-guard issue (1a) are the two things most likely to cause confusing compile errors; settle both before writing the new headers.
