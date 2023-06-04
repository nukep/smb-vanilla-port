# smb-vanilla-port

A C++ decompilation of the NES games "Super Mario Bros" and "Super Mario Bros 2 Japan" (aka Lost Levels).

This program only reimplements the code, and does not come with level data or graphical assets.

Progress made:

- [x] Super Mario Bros runs, is beatable
- [ ] Super Mario Bros 2J (Lost Levels) runs, is beatable
- [ ] Unit and regression tests
- [ ] Audio for SMB1
- [ ] Audio for SMB2J (uses 2C33 audio chip)
- [ ] Refactor of code
- [ ] A decent UI/UX, customizable controls

## What's supported

You must provide your own copy of the original games, otherwise they will not run.

The ROM is required to load level, audio, and graphical assets. As such, simple modifications to level, audio, and graphical data should work.

Romhacks that modify code or other types of data are not supported.

## The vision of this project

The main goal of this project is to behave as identically to the original game as possible (including bugs).

The secondary goal is to provide an accessible, high-level reference for the logic of Super Mario Bros.

It's reasonable for retro enthusiasts to cross-reference this with assembly listings. For this reason, code comments that make reference to "how the original did it" are encouraged (within reason).

This is a "Vanilla" Super Mario Bros port. A non-goal is for this to be an "uber-engine" in its own right. However, when this is stable, a fork of this project that has non-vanilla enhancements is encouraged (some ideas include modding, widescreen support, etc).

We also shouldn't get too wild with refactoring, in the spirit of being a good cross-reference.
It's okay to simplify loops and expressions, to separate things out for unit-testing, and even inline trivial functions - but I wouldn't stray too far. There may be a temptation to make this object-oriented or to reduce the use of global variables, but that should be done in a fork, not here.


## Special Thanks

Shoutout to doppelganger, for creating the go-to Super Mario Bros disassembly. Their work has been immensely helpful, and the diassembly is the basis for the label names used in this project:
https://www.romhacking.net/documents/344/
