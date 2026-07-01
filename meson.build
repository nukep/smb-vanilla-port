project('smbvanilla', ['c', 'cpp'],
        default_options: 'default_library=static')

cdata = configuration_data()
configure_file(output: 'smbvanilla_config.h', configuration: cdata)

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

imgui = library('imgui',
        'imgui/imgui.cpp',
        'imgui/imgui_demo.cpp',
        'imgui/imgui_draw.cpp',
        'imgui/imgui_tables.cpp',
        'imgui/imgui_widgets.cpp',
        'imgui/backends/imgui_impl_sdl3.cpp',
        'imgui/backends/imgui_impl_sdlrenderer3.cpp',
        include_directories: ['imgui/', 'imgui/backends/']
)

subdir('src/smbcore')
subdir('src/platform')
