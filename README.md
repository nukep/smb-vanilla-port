# smb-vanilla-port

A C (and some C++) decompilation of the NES games "Super Mario Bros" and "Super Mario Bros 2 Japan" (aka Lost Levels).

This program only reimplements the code, and does not come with level data or graphical assets.

Progress made:

- [x] Super Mario Bros runs, is beatable
- [x] Super Mario Bros 2J (Lost Levels) runs, is beatable
- [x] Audio for SMB1 and (excluding the ending) SMB2J
- [ ] Audio for SMB2J ending (uses 2C33 audio chip)
- [ ] Unit and regression tests
- [ ] Refactor of code
- [ ] A decent UI/UX, customizable controls
- [ ] Get the core games compiling in C (to make sure it's portable to older and embedded systems)

## Running the game

Provide a copy of "smb.nes" and put in the same directory as the executable. Alternatively, modify the file paths in smbport.ini.

smbport.ini also has options to change key bindings if they're not tasteful for you.

When all is set up, run smbport.exe (or smbport on *nix). The first CLI argument can be the ROM filename to override the value in smbport.ini. On Windows you can also drag the ROM onto the executable.

To play SMB2J (Lost Levels), modify smbport.ini.

Known-to-work hashes:
- SHA-1 hashes for smb.nes (NTSC): ea343f4e445a9050d4b4fbac2c77d0693b1d0922
- SHA-1 hashes for smb2j.fds: 3b8c8998b4887d6dd676965943d69a320738ab9c or 20e50128742162ee47561db9e82b2836399c880c

## Build instructions

You'll need a C and C++ compiler and Meson.

This project depends on SDL2 (required) and GLEW (optional). These are available as packages on most Linux distros.

If GLEW is missing, the project will be built without OpenGL support.

On Ubuntu 22.04:

```sh
sudo apt install build-essential meson libsdl2-dev libglew-dev
```

On Fedora 39 or Rocky Linux 9:
```sh
sudo dnf install gcc gcc-c++ meson SDL2-devel glew-devel
```


Build:

```sh
mkdir build
cd build

meson ..
meson compile
```

Run:

```sh
./build/smbport
```

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
