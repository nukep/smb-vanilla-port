(technically an AI-generated doc)

# Reorg Plan: Two Independent Game Libraries

## Context

The current codebase compiles SMB1 and SMB2J into a single `libsmbcore` by namespacing all functions with `smb1_`/`smb2j_` prefixes and using `#define` aliases to let shared game files call the right version at compile time. All game code reaches RAM/PPU/APU and the host through a global `SMB_STATE` singleton accessed via macros in `smbcore.h`. The shared game files are `#include`d as text fragments into `smb1.cpp`/`smb2j.cpp` rather than compiled as real translation units.

The goal is two self-contained libraries — `libsmb1` and `libsmb2j` — each exposing the same `mario.h` public API, with a swappable **interface layer** that decouples the game core from the host (RAM storage, callbacks, drawing, audio, input).

## Design goals (decided — these drive every choice below)

1. **The game core compiles as C.** This is the headline goal and an *enforced invariant*, because embedded targets may have no C++ compiler. "Core" = the two libraries that compile the SMB1/SMB2J game logic (`common`, `area`, `common_sound`, the `*only` files, the shared engine glue, and the per-game top layer of `Reset`/`NMI`/`tick`/`draw_graphics`). Host-side libraries (audio via `Nes_Snd_Emu`, SDL frontends, GL renderer) may stay C++ — an embedded build will swap those out anyway and they are out of scope here.

2. **C++ is an optional luxury layer, not a requirement.** The core must *also* be compilable as C++, so that opt-in C++ features still work — today that means the `RamByteArray`/`ConstRamByteArray` bounds-checker (enabled only under `CHECK_ARRAY_BOUNDS`, debug builds). The bounds-checker stays a C++-only debug luxury: C builds use plain pointer arrays and simply don't get it. We do **not** reimplement it for C.

3. **The core must compile as C against *either* interface implementation.** There are two interface impls (see below): the existing callback/`SMB_STATE` one, and a new bare-globals one for embedded. *Both* must be C-clean. This is stricter than it sounds: it makes the callback interface's current C++-isms (`thread_local`, a C++ reference in `ppu.h`) into debt that this reorg must clear, not just the bulk game files.

4. **Each library embeds one interface implementation at build time.** Selection is a compile-time switch (e.g. `-DSMB_INTERFACE_GLOBALS`); there is no runtime interface indirection and no separately-linked interface object. This matches the current single-binary shape: choosing an interface means recompiling the library.

### What this means concretely (the load-bearing consequence)

Meson picks the compiler **by file extension**. So the simplest, self-enforcing way to guarantee "the core compiles as C" is: **the core game files keep the `.c` extension and are compiled by the C compiler in the default build.** The C invariant is then proven continuously by the normal build, for free.

This *inverts* a tempting move (renaming the shared files to `.cpp`). Renaming to `.cpp` would quietly destroy the invariant — it must not happen. Instead:

- **Default build: core is C.** `.c` files → C compiler. No `thread_local`, no `class`, no references; bounds-checker compiles out to plain pointers.
- **Opt-in C++ build: same `.c` files, force-compiled as C++** (`-x c++` / meson override) under `CHECK_ARRAY_BOUNDS`, to light up `RamByteArray`. This is the luxury path.

Everything below serves making those two statements true.

---

## The central problem: `smbcore.h` mixes three concerns

`smbcore.h` today is one file doing three jobs, and the C++ leakage all comes from blending them:

| Concern | Examples | C-clean? |
|---|---|---|
| **A. Pure utility** (game-agnostic, no host) | int typedefs, math macros (`LOAD_16`…), `CONCAT11`/`NEGATE`/`SWAP`, `find_first_bit_position`, the `ppureg`/`ppu_state`/`sprite` structs, assert/warn macros | Yes, trivially |
| **B. Interface surface** (how the core reaches the host) | `RAM`/`PPURAM`/`CHRROM`, `AreaData`/…, `draw_tile`, APU regs, `joy1/2`, `announce_main_scroll`, `transfer_sprite_data`, `rom_ptr`, `ppu.h` hookup, `SMB1_ONLY`/`SMB2J_ONLY` | This is the seam — must be C-clean in *both* impls |
| **C. Callback-impl internals** | `struct SMB_state`, `thread_local SMB_STATE`, the callback-dispatch inline funcs, `RamByteArray` (the C++ luxury) | Currently C++-only; **the debt** |

The reorg is fundamentally about **separating A / B / C** so that the core depends only on A and the *declared interface* of B, while C (and its C++-isms) is confined to one swappable implementation.

### The three C++-isms in B/C, and where each must go

1. **`thread_local struct SMB_state *SMB_STATE`** — pure callback-impl internal (concern C). Not C-clean (`thread_local` is a C++ keyword; C's spelling is `_Thread_local`/`thread_local` via `<threads.h>`). Goal #3 says the callback impl must be C-compilable, so this needs the C spelling (or a macro that resolves per-language). Lives only in the callback interface impl; the globals impl has no such pointer.

2. **`ppu.h`'s `ushort &v = PPU_STATE.v.value;`** — a C++ reference, inside the PPU register helpers that are part of the interface surface (B). Must be de-referenced (rewrite to a pointer or direct expression) so `ppu.h` is C-clean regardless of interface. This is independent of which impl is chosen.

3. **`RamByteArray`/`ConstRamByteArray` + the `*buttons = {0}` aggregate assignment** — the bounds-checker is the sanctioned C++ luxury (concern C, debug-only); it stays C++-only and the C build uses the plain-pointer `RAMARRAY`. The `{0}` aggregate assignments in the callback inlines (`joy1`/`joy2`) must be written C-compatibly (`*buttons = (struct SMB_buttons){0};`) since those inlines live in the interface impl that must be C-clean.

Settling these three is the *real* work of Phase 1; the file-splitting is bookkeeping around it.

---

## Phase 1 — Carve the interface seam; make the core C-clean

The objective of Phase 1 is: **the existing single combined build still produces identical behavior, but the core game files now compile as C and reach the host only through a declared interface.** No library split yet — minimize moving parts.

### 1a. Split `smbcore.h` by concern (A / B / C above)

- **`smbcore.h` keeps concern A only** — pure utilities, no host, no `SMB_STATE`. Add include guards (it has none today). Verify it is C-clean.
- **`smbcore/interface.h`** declares concern B as a contract: the macros/functions the core calls to reach the host (`RAM`, `draw_tile`, APU, input, `rom_ptr`, the PPU hookup, `SMB1_ONLY`/`SMB2J_ONLY`, …). It is a *selector*: include `interface_callbacks.h` by default, or `interface_globals.h` under `-DSMB_INTERFACE_GLOBALS`.
- **`smbcore/interface_callbacks.h`** is concern C: the `SMB_state` struct, the `SMB_STATE` pointer, and the callback-dispatch inlines — the existing behavior, now isolated and made **C-clean** (items 1 & 3 above). The `RamByteArray` luxury can live here or alongside the `RAMARRAY` macro definition; wherever it lands, it must be `#ifdef __cplusplus`-gated so the C build never sees it.
- **`smbcore/interface_globals.h`** is the embedded impl: same names backed by bare `extern` globals (`extern byte smbglobals_ram[0x10000]`, …), no `SMB_state`, no callbacks. **Stub for now** — its job in this reorg is to *exist and compile as C* (smoke-test), proving the seam is real. Full embedded semantics are deferred.

**Layering caveat to settle explicitly:** `RamByteArray` and the `RAMARRAY` macros depend on `RAM()`, which is defined by the interface impl. So the bounds-checker can't sit "above" the interface. Decide the include order (interface impl defines `RAM` *before* the array wrappers are parsed) and document it; don't leave `RAM` undefined where the wrappers expand.

### 1b. Make `ppu.h` C-clean

De-reference item 2. `ppu.h` is part of the interface surface and is included by every core TU, so it must compile as C under either impl.

### 1c. Make the core game files real C translation units

Today `common.c`, `area.c`, `common_sound.c`, `smb1only.c`, `smb2jonly.c` are `#include`d into the uber-modules, so the whole game is one TU and the C compiler never sees them. To compile them as C TUs:

- Inject the per-game context (the interface selector + per-game headers) via a build-system `-include` of a small `*_context.h`, rather than each file `#include`-ing a pile of headers. Keep the files `.c`.
- **Cross-TU breakage is the main hazard.** Because everything is one TU today, `static` functions and implicit forward-decls reach across "files." Real TUs break that. The fix is purely mechanical — give every cross-TU symbol a real declaration in a shared header and drop `static` where it crosses — but it must be *complete* or the link fails. The specific symbols found by scanning are listed in the Appendix; treat that as a worklist, not as design.
- This is also where the C-cleanliness of the core gets *proven*: once the files compile as C TUs in the default build, any remaining C++-ism is a hard compile error, not a latent risk.

### 1d. Keep the combined build working

At the end of Phase 1 there is still one `smbcore` library and the existing executables/testrunner, behavior unchanged. Only the internal structure (C core + isolated interface) has changed. This keeps the riskiest step (language-cleanliness) decoupled from the library split.

---

## Phase 2 — Drop the `smb1_`/`smb2j_` prefixes and aliases

With the core compiling per-game already (via context injection), the namespacing scheme is now dead weight:

- Game files define plain names (`GameMode`, `ScrollHandler`, …); delete the `#define Foo smb1_Foo` alias walls and the prefixes from `smb1.h`/`smb2j.h`. This is large and mechanical — script it and diff.
- Hoist the struct definitions shared by both per-game headers (`struct_ycr07`, `struct_axyz`, `blockbuffer_colli_result`, the `#pragma pack` framing, …) into a shared `smbcore/game.h`. Leave only genuinely game-specific declarations behind (verify the remainder actually differs).

After this phase the two games have colliding symbols and **cannot be linked into one binary**. That is the point of no return for "one combined library," and it forces the executable/testrunner decision in Phase 4. Keep each commit building.

---

## Phase 3 — Dissolve `smbcore.cpp` into the two libraries

`smbcore.cpp` currently holds the public API and dispatches `SMB_tick` on `which_game`. Split it so each game owns its own:

- **ROM loading** moves into the respective game file (SMB1 iNES path → `smb1`; the FDS paths + `smb2j_load_file` → `smb2j`, dropping the `extern "C"` bridge that only existed to span the uber-modules).
- **Public API** (`SMB_state_*`, `SMB_tick`, `SMB_ram[_finishwrite]`, `SMB_ppuram`, `SMB_which_game`, `draw_graphics`) moves into each game file. `SMB_tick` stops dispatching on `which_game` and calls this library's `Reset`/`NMI` directly. `SMB_which_game` returns a compile-time constant per library.
- The `SMB_STATE` definition and its assignment are **callback-interface concerns** — they belong with `interface_callbacks.h`'s world, not in shared code. The globals build supplies its own trivial `SMB_state_size`/`SMB_state_init`. (Deferred with the rest of the globals stub.)
- **Shared, game-agnostic code stays shared.** `draw_graphics`/`draw_nametable_*` are byte-identical across the two games, as is `smbcommon.cpp` (`set_world_and_level`, `InitializeMemory`, `update_screen`, etc.). Prefer compiling one shared source into both libraries over copy-pasting into each, to prevent divergence. Under each library's context, `SMB1_ONLY`/`SMB2J_ONLY` become compile-time constants, so the dead branches can be pruned later at leisure.

`smbcore.cpp` ends up empty — delete it.

---

## Phase 4 — Build system

Two libraries, each = shared core `.c` files + that game's `*only.c` + `smbcommon` + the per-game top file, built **as C by default** with the context header injected and the interface selected:

- Default config: C compiler on the core; callback interface; this is the C invariant, tested by simply building.
- Luxury config: same core files force-compiled as C++ under `CHECK_ARRAY_BOUNDS` for `RamByteArray`.
- Embedded smoke-test config: core + `-DSMB_INTERFACE_GLOBALS`, compiled as C, must compile cleanly against the globals stub. This is what continuously proves Goal #3 (core is C-clean against *either* interface).

**Open decision to settle before starting Phase 4 — executables & testrunner.** Today one `smbvanilla` plays either game by ROM detection, and the testrunner branches on `SMB_which_game`. After Phase 2 the symbols collide, so one binary can hold only one game. Options:
- (a) Two executables (`smbvanilla` SMB1, `smbvanilla2j` SMB2J) and two testrunner binaries — straightforward, recommended.
- (b) One binary that `dlopen`s a chosen library at runtime — preserves "one app, either game" but needs the public API kept loadable and is more wiring.

Also update the `wasm` build (`build-wasm/`, currently builds `libsmbcore` + `smb_testrunner`).

---

## Verification (per phase)

- **Phase 1:** combined build still passes the testrunner for both games, behavior unchanged. **New, decisive check:** the core game files now compile as **C** in the default build — this is the moment the C invariant becomes real. Also build the C++/`CHECK_ARRAY_BOUNDS` config to confirm the luxury path still works, and compile the core as C against the globals stub to confirm Goal #3.
- **Phase 2:** each game builds separately and passes; the combined library is gone.
- **Phase 3:** `smbcore.cpp` deleted; both libraries pass; `SMB_which_game` is a per-library constant.
- **Phase 4:** both executables build/run their ROMs; a per-game testrunner works against each; wasm build updated.

## Sequencing / risk

- Phase 1 is the hard one and the C-cleanliness work is its spine: do the three C++-ism fixes (thread_local, ppu.h reference, aggregate-init/bounds-checker gating) **first**, then the file-as-TU split, then prove C compilation — before any library split. Land SMB1 first (smaller interface/glue surface) before SMB2J (more FDS glue).
- Keep every commit building; Phase 2's alias deletion is the irreversible step.
- The two layering pitfalls most likely to cause confusing errors: `RamByteArray`-depends-on-`RAM` include order, and the missing include guards on `smbcore.h`/`smbcommon.h`. Settle both while writing the new headers.

---

## Appendix — cross-TU symbol worklist (mechanical, not design)

Splitting the uber-modules into real TUs breaks symbols that currently resolve only because everything is one TU. Each needs a real declaration in a shared header (and `static` dropped where it crosses). Verified against the code; provided so the implementer doesn't have to re-derive it:

| Symbol | Defined in | Called from (other TU) | Fix |
|---|---|---|---|
| `SoundEngine` | `common_sound` (`static`) | `smb1`/`smb2j` NMI | de-`static`, declare in `smbcommon.h` |
| `DrawTitleScreen`, `TransposePlayers` (SMB1) | `smb1` | `common` | declare in `smb1.h` |
| `ScrollScreen` (SMB2J) | `smb2j` | `common` | declare in `smb2j.h` |
| `LoadFiles`, `UpdateGamesBeaten`, `FDS_drive_status` (SMB2J) | `smb2j` | `smb2jonly` | declare in `smb2j.h` |
| `LoadAreaPointer`, `GetAreaDataAddrs`, `AltHard_GetAreaDataAddrs` (SMB2J-only), `AreaParserTaskControl`, `AreaParserTaskHandler` | `area` (`static`) | `common` | drop `static` (existing TODO in `area.h`); note all **five**, not four |

False positive (do not chase): `smb2jonly`'s `static LoadLuigiPhysics` appears in `common.c` only inside comments.

Also relocate the small per-game glue that currently sits inline in the uber files: the `GameTimerDisplay` alias and SMB2J's `AreaAddrOffsets` `#define` belong in each game's context/romarrays header (SMB1's `AreaAddrOffsets` already lives in `smb_romarrays.h`; consolidate SMB2J's there too for symmetry).
