# SMB Vanilla 0.1.0

To run, make sure `smb.nes` exists in the same directory.
This file should be a legally-obtained ROM of Super Mario Bros or Super Mario Bros 2 Japan (The Lost Levels).

Then run: `./smbvanilla`

The default key bindings are WSAD + JK + Enter.

Note that the defaults can be changed in smbvanilla.ini.


# Troubleshooting

error while loading shared libraries: libSDL3.so.0
--------------------------------------------------

This build requires SDL3 on your system. Obtaining it depends on your distro.

On Debian-based distros (tested on Ubuntu 26.04, Debian Trixie):

```
sudo apt install libsdl3-0
```

On Fedora-based distros (tested on Fedora 43, Rocky 10):

```
sudo dnf install SDL3
```

On Arch-based distros (tested on Arch Linux as of October 2026):

```
sudo pacman -S sdl3
```


# Credits

https://github.com/nukep/SMB-Vanilla
https://codeberg.org/dannysp/SMB-Vanilla

Port by Danny Spencer


SDL 3
-----
https://www.libsdl.org/

By Sam Lantinga, et al: https://github.com/libsdl-org/SDL/blob/main/CREDITS.md

Nes_Snd_Emu
-----------
https://github.com/jamesathey/Nes_Snd_Emu

Based on code by blargg, adapted to C++ by James Athey

