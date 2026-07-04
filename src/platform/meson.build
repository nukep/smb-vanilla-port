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

use_opengl = glew.found()

imgui_src = []
if not use_sdl3
  imgui_src += ['../../imgui/backends/imgui_impl_sdl2.cpp']
  imgui_src += ['../../imgui/backends/imgui_impl_sdlrenderer2.cpp']
else
  imgui_src += ['../../imgui/backends/imgui_impl_sdl3.cpp']
  imgui_src += ['../../imgui/backends/imgui_impl_sdlrenderer3.cpp']
endif

if use_opengl
  imgui_src += ['../../imgui/backends/imgui_impl_opengl3.cpp']
endif

imgui = library('imgui',
                ['../../imgui/imgui.cpp',
                 '../../imgui/imgui_demo.cpp',
                 '../../imgui/imgui_draw.cpp',
                 '../../imgui/imgui_tables.cpp',
                 '../../imgui/imgui_widgets.cpp'] + imgui_src,
                dependencies: [sdl],
                include_directories: ['../../imgui/', '../../imgui/backends/']
)

opengl_sources = use_opengl ? ['render_opengl.c'] : ['render_opengl_noop.c']
opengl_args = use_opengl ? ['-DOPENGL_ENABLED'] : []

use_sdl_args = []
if not use_sdl3
  use_sdl_args += ['-DUSE_SDL2']
endif

executable('smbvanilla',
           ['main_sdl.c',
            'windowing_sdl.c',
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
           cpp_args: use_sdl_args + opengl_args,
)

executable('smbvanilla_imgui',
           ['main_imgui_sdl.cpp',
            'ui.cpp',
            'smbsession.cpp',
            'windowing_sdl.c',
            'audio_sdl.cpp',
            'timer_sdl.c',
            'movie.c',
            'render_raster.c',
            'thirdparty/ini.c'] + opengl_sources,
           include_directories: ['../../Nes_Snd_Emu', '../../imgui', '../../imgui/backends', '..'],
           link_with: [smbcore, nessndemu, imgui],
           dependencies: [sdl, glew],
           c_args:   use_sdl_args + opengl_args,
           cpp_args: use_sdl_args + opengl_args,
)


executable('smbvanilla_testrunner',
           ['main_testrunner.c', 'movie.c'],
           include_directories: ['..'],
           link_with: smbcore)
