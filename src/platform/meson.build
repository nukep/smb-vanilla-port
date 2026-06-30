if get_option('sdl2')
  sdl = dependency('sdl2')
  use_sdl3 = false
else
  sdl3 = dependency('sdl3', required: false)
  if sdl3.found()
    sdl = sdl3
    use_sdl3 = true
  else
    sdl = dependency('sdl2')
    use_sdl3 = false
  endif
endif

glew = dependency('glew', required: get_option('opengl'))

opengl_sources = glew.found() ? ['render_opengl.c'] : ['render_opengl_noop.c']
opengl_args = glew.found() ? ['-DOPENGL_ENABLED'] : []


if use_sdl3
  executable('smbvanilla',
             ['main_sdl3.c',
              'audio_sdl3.cpp',
              'time.c',
              'movie.c',
              'render_raster.c',
              'thirdparty/ini.c'] + opengl_sources,

             install: true,
             include_directories: ['../../Nes_Snd_Emu', '..'],
             link_with: [smbcore, nessndemu],
             dependencies: [sdl, glew],
             c_args:   opengl_args,
             cpp_args: opengl_args)
else
  executable('smbvanilla',
             ['main_sdl2.c',
              'audio_sdl2.cpp',
              'time.c',
              'movie.c',
              'render_raster.c',
              'thirdparty/ini.c'] + opengl_sources,

             include_directories: ['../../Nes_Snd_Emu', '..'],
             link_with: [smbcore, nessndemu],
             dependencies: [sdl, glew],
             c_args:   ['-DUSE_SDL2'] + opengl_args,
             cpp_args: ['-DUSE_SDL2'] + opengl_args)
endif


executable('smbvanilla_testrunner',
           ['main_testrunner.c', 'movie.c'],
           include_directories: ['..'],
           link_with: smbcore)
