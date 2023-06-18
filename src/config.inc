/* Defines the layout of smbport.ini */

section(general,
        cstr(rom_filename)
        cstr(palette_filename)

        cbool(maxspeed));

section(debug,
        cstr(dump_ram_filename)
        cstr(dump_ppu_filename));

section(graphics,
        cbool(opengl)
        cbool(software));

section(audio,
        cbool(enabled)
        cint(samplerate)
        cint(maxlatency_ms));

section(bindings,
        clist(keys, read_key_binding, SDL_Scancode, 8));

#undef section
#undef cstr
#undef cbool
#undef cint
#undef clist
