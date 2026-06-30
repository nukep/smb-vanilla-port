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

use_sdl_args = []
if not use_sdl3
  use_sdl_args += ['-DUSE_SDL2']
endif

executable('smbvanilla',
           ['main_sdl.c',
            'audio_sdl.cpp',
            'timer_sdl.c',
            'movie.c',
            'render_raster.c',
            'thirdparty/ini.c'] + opengl_sources,

           install: true,
           include_directories: ['../../Nes_Snd_Emu', '..'],
           link_with: [smbcore, nessndemu],
           dependencies: [sdl, glew],
           c_args:   use_sdl_args + opengl_args,
           cpp_args: use_sdl_args + opengl_args)


executable('smbvanilla_testrunner',
           ['main_testrunner.c', 'movie.c'],
           include_directories: ['..'],
           link_with: smbcore)
