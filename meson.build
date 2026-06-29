project('smbvanilla', ['c', 'cpp'],
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

opengl_sources = glew.found() ? ['src/render_opengl.c'] : ['src/render_opengl_noop.c']
opengl_args = glew.found() ? ['-DOPENGL_ENABLED'] : []

smbcore_args = []

if get_option('optimize_aggressively')
  smbcore_args += ['-DASSUME_EXPECTS']
else
  smbcore_args += ['-DPRINT_WARNINGS_AND_ERRORS']
endif

if get_option('thread_local_smbstate')
  smbcore_args += ['-DTHREAD_LOCAL_SMBSTATE']
endif

# For testing, at the moment
force_cpp = false

if get_option('check_array_bounds')
  force_cpp = true
  smbcore_args += ['-DCHECK_ARRAY_BOUNDS']
endif

force_cpp_args = []

if force_cpp
  # Note: may not work for MSVC or other compilers
  force_cpp_args += ['-x', 'c++']
endif

cdata = configuration_data()
configure_file(output: 'smbvanilla_config.h', configuration: cdata)

smb1core = library('smb1core',
  'src/smbcore/common.c',
  'src/smbcore/common_sound.c',
  'src/smbcore/area.c',
  'src/smbcore/smb1only.c',
  c_args: smbcore_args + force_cpp_args + ['-DSMB1_MODE'],
)

smb2jcore = library('smb2jcore',
  'src/smbcore/common.c',
  'src/smbcore/common_sound.c',
  'src/smbcore/area.c',
  'src/smbcore/smb2jonly.c',
  c_args: smbcore_args + force_cpp_args + ['-DSMB2J_MODE'],
)

smbcore = library('smbcore',
  'src/smbcore.c',
  c_args: smbcore_args,
  link_with: [smb1core, smb2jcore],
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
  executable('smbvanilla',
             ['src/main_sdl3.c',
              'src/audio_sdl3.cpp',
              'src/time.c',
              'src/movie.c',
              'src/render_raster.c',
              'src/thirdparty/ini.c'] + opengl_sources,

             include_directories: ['Nes_Snd_Emu'],
             link_with: [smbcore, nessndemu],
             dependencies: [sdl, glew],
             c_args:   opengl_args,
             cpp_args: opengl_args)
else
  executable('smbvanilla',
             ['src/main_sdl2.c',
              'src/audio_sdl2.cpp',
              'src/time.c',
              'src/movie.c',
              'src/render_raster.c',
              'src/thirdparty/ini.c'] + opengl_sources,

             include_directories: ['Nes_Snd_Emu'],
             link_with: [smbcore, nessndemu],
             dependencies: [sdl, glew],
             c_args:   ['-DUSE_SDL2'] + opengl_args,
             cpp_args: ['-DUSE_SDL2'] + opengl_args)
endif

