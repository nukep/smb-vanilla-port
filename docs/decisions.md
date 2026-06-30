# Decisions

This document lists the rationale for decisions made for this port


## Registers, temporary variables, and the stack, are all abstracted away

The 6502 code operates using registers, temporary variables, and the stack.

Registers include:
- 8-bit: A X Y
- 1-bit (flags): N V Z C

Temporary variables include:
- Addresses `$00` to `$07` inclusive. These are essentially treated as general-purpose registers.
- Address `$08` (ObjectOffset)
  - This is loaded/restored by many subroutines, but explicit inclusion as a global varaible created too much noise in the code.
- Addresses `$EB` to `$EF` inclusive. These are used the Gfx drawing code.

These are all converted to parameters and local variables.

This results in much more readable code, but it also means that some classes of glitches are impossible (or very impractical) to implement.

Glitches that buffer-overflow into the stack, or into temporary variables, are usually not implemented.
Some implementions for glitches that occur in casual gameplay do however exist, such as reading `$EF` in `Setup_Vine`.


## Some data is hard-coded, some data is not

The guiding philosophy is: If a basic level editor can make changes, they should be playable in this port. That is: level, text, CHRROM, and music data.
Note that this is currently not likely to work _right now_, because the port doesn't account for shifted-around addresses of arrays in the ROM. But it should work in theory once there's a system for it.

Another philosophy is: If the data is "sufficiently code-like", then it's brought in and treated as code.

Sometimes the line of "sufficiently code-like" is blurred. In those cases, the choice is to load the data from ROM.

What's hard-coded (not read from ROM):
- Constants, such as identifiers or how fast a goomba moves
- Trivially-calculatable lookups
  - `Bitmasks` at `$c68a`, which is just `1 << n`
  - `FirebarTblOffsets` at `$cd2e`, which is just `n * 9`, and used as an offset for an 11 x 9 2d lookup
- Lookups for tiles and metatiles
- (Most) lookups that are only used in one function. Exceptions are traditionally level-editable data.

An upshot to bringing in data this way, is we can eliminate edge-cases that we know can't happen with the given data.


## Many function signatures correspond to the 6502, others do not

For the most part, function signatures correspond to the 6502 code.
One parameter might be register "A", another is register "X", and so on.

Example: `MoveObjectHorizontally` shows that `param_1` is register X, and that the return value is register A.
Unlisted registers (such as `Y`) are either modified or unmodified by the function.

```c
// Signature: [X] -> [A]
byte MoveObjectHorizontally(const byte param_1) { ...
```

Sometimes we have to change these signatures for code clarity. Such cases:
- When a function always returns a constant, such as 0. The constant is moved to the caller.
- When a function always returns a parameter. The parameter is treated as a pass-thru, and is moved to the caller.
- When function parameters are equivalent to each other. These are merged.


## The Block Buffer pointer is decomposed into x/y metatile coordinates

Whenever you see `mt_x` and `mt_y` in the code, it usually refers to a decomposed metatile buffer pointer.

The original SMB accesses the metatile buffer (aka the Block Buffer) by building a 16-bit pointer at addresses `$06` and `$07`.

The pointer would point to an address ranging from `$0500 - $05CF` and `$05D0 - $069F` (not counting overflow bugs). The `$0500` portion would be used for even pages, and the `$05D0` portion for odd pages. Each page is 16 metatiles wide by 13 metatiles tall, so the entire buffer spans 32x13 metatiles (0x1A0 bytes).

This had to be refactored for a few reasons:
- To make the intent clearer
- To not hardcode the `$0500` origin calculated by `GetBlockBufferAddr`
- To bounds-check accessess to the buffer
- To cleanly reimplement out-of-bounds bugs with this buffer (they're common!)
- To not translate NES pointers at runtime
- To avoid pointer arithmetic
  - Example 1: `CheckTopOfBlock`: To calculate the above block, our port passes `mt_y - 1`. The original subtracts 16 from the pointer.
  - Example 2: `PutBlockMetatile` (inlined): To calculate the PPU address of the metatile, our port relies on `mt_x` to determine the page. In the original, the comparison `$06 < #$d0` is made to determine if the pointer is for an even or odd page.

As a bonus, `mt_x` is an area-wide coordinate, and not confined to the wrapping behavior of the buffer. The resolved buffer offset is the same as the original because the calculation takes `mt_x % 32` - but this can be changed. This should make it more amenable to enhancement ports.


## State machine increments are made explicit

The original game implements global state machines in integer variables such as
OperMode, OperMode_Task, and ScreenRoutineTask.
The game would advance the state machines by incrementing the values for these variables.

This port replaces increments of these variables with explicit assignments, to make searching for states possible.

e.g. Instead of `OperMode_Task += 1`, we might have `OperMode_Task = OMT_GAMEOVER_RUNGAMEOVER`.

To do this, the assignment usually has to happen at the caller or the caller's caller.


## Compile-time modes for SMB1 and SMB2J

Early on, I had hoped that differences in behavior between SMB1 and SMB2J could be configured at runtime.
Later on, as the complexity became evident, I settled on compile-time with `#ifdef SMB1_MODE` and `#ifdef SMB2J_MODE`.

There are jumptables and enumerations that have different values for SMB1 and SMB2J (e.g. area parsing).
As these are tied into the functions that use them, it makes less sense to have a mix of both
run-time and compile-time switches for SMB1 and SMB2J.

Right now I want to keep the literal enumation values equivalent to the original respective games,
and to not abstract them or create indirection to the "real" values.

