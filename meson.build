project('smbport', ['c', 'cpp'],
        default_options: 'default_library=static')

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

opengl_sources = glew.found() ? ['src/render_opengl.c'] : []

cdata = configuration_data()
configure_file(output: 'smbport_config.h', configuration: cdata)

smbcore = library('smbcore',
        'src/smbcore.cpp',
        'src/smbcommon.cpp',
        'src/smb1.cpp',
        'src/smb2j.cpp'
)

nessndemu = library('nessndemu',
        'Nes_Snd_Emu/emu2413/emu2413.c',
        'Nes_Snd_Emu/nes_apu/Blip_Buffer.cpp',
        'Nes_Snd_Emu/nes_apu/Multi_Buffer.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Apu.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Fds_Apu.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Fme7_Apu.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Mmc5_Apu.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Namco_Apu.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Oscs.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Vrc6_Apu.cpp',
        'Nes_Snd_Emu/nes_apu/Nes_Vrc7_Apu.cpp',
        include_directories: ['Nes_Snd_Emu/emu2413']
)

executable('smb_testrunner',
           ['src/main_testrunner.c', 'src/movie.c'],
           link_with: smbcore)

if use_sdl3
  executable('smbport',
             ['src/main_sdl3.c',
              'src/audio_sdl3.cpp',
              'src/time.c',
              'src/movie.c',
              'src/render_raster.c',
              'src/thirdparty/ini.c'] + opengl_sources,

             include_directories: ['Nes_Snd_Emu'],
             link_with: [smbcore, nessndemu],
             dependencies: [sdl, glew])
else
  executable('smbport',
             ['src/main_sdl2.c',
              'src/audio_sdl2.cpp',
              'src/time.c',
              'src/movie.c',
              'src/render_raster.c',
              'src/thirdparty/ini.c'] + opengl_sources,

             include_directories: ['Nes_Snd_Emu'],
             link_with: [smbcore, nessndemu],
             dependencies: [sdl, glew],
             c_args:   ['-DUSE_SDL2'],
             cpp_args: ['-DUSE_SDL2'])
endif

