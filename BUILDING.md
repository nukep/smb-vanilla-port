# Build instructions

You'll need a C and C++ compiler and Meson.

This project depends on SDL2 or SDL3 (one of them is required) and GLEW (optional). These are available as packages on most Linux distros.

SDL3 is preferred. If SDL3 is missing, then SDL2 will be used.

If GLEW is missing, the project will be built without OpenGL support.

## Rocky Linux 10

Install Meson, using `pip install meson` or `sudo dnf install meson`.

Install SDL3 and dependencies:

```
sudo dnf --enablerepo=devel install gcc gcc-c++ SDL3-devel glew-devel
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

