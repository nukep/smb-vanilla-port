# Behavioral differences from the original games

This document describes known differences in behavior in the original games.
They will not be fixed or worked-around in this port.


## Limited ability to play out-of-bounds worlds

Luckily, the minus world (36-1) for SMB1 NES is playable. But many out-of-bounds worlds aren't playable.

This is because the level data might resolve to an address in RAM, I/O registers, or another unmapped memory address.
Arbitrary reads from these are undefined.

The minus world is 36-1, which is within the PRG ROM in SMB1 NES. Its AreaData is AE45, and EnemyData is A171.

A non-exhaustive list of worlds where the AreaData pointer is not in PRG ROM:

14-1 52-1 56-1 70-1 126-1 130-1 132-1 134-1 143-1 148-1 154-1 190-1 191-1 196-1 203-1 224-1 225-1 226-1 236-1 250-1 251-1

A non-exhaustive list of worlds where the EnemyData pointer is not in PRG ROM:

9-1 11-1 12-1 13-1 14-1 19-1 20-1 25-1 26-1 30-1 34-1 35-1 49-1 52-1 55-1 56-1 64-1 68-1 70-1 71-1 72-1 73-1 80-1 122-1 123-1 125-1 126-1 127-1 130-1 132-1 134-1 135-1 137-1 138-1 139-1 140-1 143-1 146-1 148-1 153-1 154-1 189-1 190-1 191-1 192-1 193-1 196-1 197-1 198-1 201-1 203-1 205-1 213-1 214-1 220-1 221-1 222-1 224-1 225-1 226-1 227-1 230-1 232-1 236-1 246-1 248-1 249-1 250-1 251-1 252-1 255-1 256-1


## No lag frames, other timing artifacts

This port eliminates lag frames. This is mostly a good thing.

In the original SMB1 and SMB2J, if a frame took too long to process, the NMI would be missed and cause a lag frame.

This port has no mechanism to count elapsed 6502 clock cycles, and doing so would overcomplicate matters.
So the easiest thing is to just not do it!

However, this difference means that pre-recorded gameplay from emulators and authentic hardware can't be directly played.
A workaround for porting movies is to run it through an emulator and get the state at each encountered NMI. The `fceux_movie_dump.lua` script does this.

Some other consequences of not counting clock cycles:

- APU emulation is not 100% accurate. This port elapses the emulated APU uniformly, instead of by the exact amount of cycles. It doesn't sound noticably different in practice, however.
- The status bar doesn't flicker like it does on the NES. Most would consider this a feature.

