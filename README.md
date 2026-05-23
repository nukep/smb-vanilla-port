# SMB Vanilla

A C/C++ reconstruction compatible with the NES games "Super Mario Bros" and "Super Mario Bros 2 Japan" (aka Lost Levels).

This project intends to support most non-gamebreaking glitches from the original games (e.g. the minus world, collision and clipping bugs).

A legally obtained ROM dump is required to play the game. Otherwise, it will not run. This project only reimplements the gameplay, and does not come with level data or graphical assets.

Progress made:

- [x] Super Mario Bros runs, is beatable
- [x] Super Mario Bros 2J (Lost Levels) runs, is beatable
- [x] Audio for SMB1 and (excluding the ending) SMB2J
- [ ] Refactor of Ghidra-produced code (in progress)
- [ ] Audio for SMB2J ending (uses 2C33 audio chip)
- [ ] Unit and regression tests
- [ ] A decent UI/UX, customizable controls
- [ ] Get the core games compiling in C only (to make sure it's portable to older and embedded systems)


## Running the game

Provide a copy of "smb.nes" and put in the same directory as the executable. Alternatively, modify the file paths in smbvanilla.ini.

smbvanilla.ini also has options to change key bindings if they're not tasteful for you.

When all is set up, run smbvanilla.exe (or smbvanilla on *nix). The first CLI argument can be the ROM filename to override the value in smbvanilla.ini. On Windows you can also drag the ROM onto the executable.

```
./smbvanilla
```

To play SMB2J (Lost Levels), provide the ROM path as a CLI argument, or modify smbvanilla.ini.

To play a specific level (SMB1 only right now), you can do so from the command line. For example, to play World 8-1:

```
./smbvanilla --level 8-1
```

Known-to-work hashes:
- SHA-1 hashes for smb.nes (NTSC): ea343f4e445a9050d4b4fbac2c77d0693b1d0922
- SHA-1 hashes for smb2j.fds: 3b8c8998b4887d6dd676965943d69a320738ab9c or 20e50128742162ee47561db9e82b2836399c880c

Romhacks that modify code or other types of data are not supported.


## Building from source

See [BUILDING.md](./BUILDING.md) for details.


## Contributing

See [CONTRIBUTING.md](./CONTRIBUTING.md) for details.


## Goals for this project

The main goal of this project is to behave as identically to the original game as possible (including bugs).

The secondary goal is to provide an accessible, high-level reference for the logic of Super Mario Bros. It's reasonable for retro enthusiasts to cross-reference this with disassembly listings.


## Special Thanks

Shoutout to doppelganger, for creating the go-to Super Mario Bros disassembly. Their work has been immensely helpful, and the diassembly is the basis for the label names used in this project:
https://www.romhacking.net/documents/344/

## Legal disclaimer

This project has no affiliation with Nintendo. No ROMs are included in this project.

