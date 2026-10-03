# Build instructions

You'll need a C and C++ compiler and Meson.

This project depends on SDL2 or SDL3 (one of them is required). These are available as packages on most Linux distros.

SDL3 is preferred. If SDL3 is missing, then SDL2 will be used.

## Check out this project, submodules

Using git:

```
git clone https://codeberg.org/dannysp/SMB-Vanilla.git
git submodule update --init --recursive
```


## Rocky Linux 10

Install Meson, using `pip install meson` or `sudo dnf install meson`.

Install SDL3 and dependencies:

```
sudo dnf --enablerepo=devel install gcc gcc-c++ SDL3-devel
```

If you wish to use SDL2, replace `SDL3-devel` with `sdl2-compat-devel`.

Build:

```sh
meson setup build/
meson compile -C build/
```

Run:

```sh
./build/src/platform/smbvanilla
```

## Windows, MSVC 64-bit

TODO: make these build steps more robust

Building in Windows is a bit tricker, but it's doable. I'll refrain from documenting specific environment paths. But the gist of it is:

Download Meson, ensure it and the Python environment are on your PATH: https://mesonbuild.com/

Download the built devel libraries for SDL3. It'll be named something like "SDL3-devel-3.4.18-VC.zip": https://github.com/libsdl-org/SDL/releases


These build flags work for me:

```
meson setup build/  --cmake-prefix-path="C:\path\to\SDL3-3.4.18" --buildtype=debugoptimized
```
