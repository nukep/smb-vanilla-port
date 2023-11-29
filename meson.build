project('smbport', ['c', 'cpp'],
        default_options: 'default_library=static')

sdl2 = dependency('sdl2')
glew = dependency('glew', required: get_option('opengl'))

if glew.found()
endif

cdata = configuration_data()

cdata.set('FOO', true)
cdata.set('FOO', false)

configure_file(output: 'smbport_config.h', configuration: cdata)

smbcore = library('smbcore', 'src/smbcore.cpp', 'src/smbcommon.cpp', 'src/smb1.cpp', 'src/smb2j.cpp')

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

executable('smbport',
           ['src/main_sdl.c',
            'src/movie.c',
            'src/audio.cpp',
            'src/time.c',
            'src/render_opengl.c',
            'src/render_raster.c',
            'src/thirdparty/ini.c'],

           include_directories: ['Nes_Snd_Emu'],
           link_with: [smbcore, nessndemu],
           dependencies: [sdl2, glew])
