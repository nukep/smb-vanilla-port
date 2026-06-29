const std = @import("std");

fn hasPkgConfig(b: *std.Build, pkg: []const u8) bool {
    const result = std.process.run(b.allocator, b.graph.io, .{
        .argv = &.{ "pkg-config", "--exists", pkg },
    }) catch return false;
    b.allocator.free(result.stdout);
    b.allocator.free(result.stderr);
    return switch (result.term) {
        .exited => |code| code == 0,
        else => false,
    };
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const use_sdl2_opt = b.option(bool, "sdl2", "Use SDL2 instead of SDL3") orelse false;
    const OpenGlFeature = enum { auto, enabled, disabled };
    const opengl_feature = b.option(OpenGlFeature, "opengl", "Build with OpenGL support") orelse .auto;
    const optimize_aggressively = b.option(bool, "optimize_aggressively", "Enable aggressive optimizations (not recommended)") orelse false;
    const thread_local_smbstate = b.option(bool, "thread_local_smbstate", "Use thread-local singleton for SMB_STATE") orelse false;

    // Mirror meson: prefer SDL3 unless -Dsdl2=true or SDL3 not found.
    const use_sdl3 = !use_sdl2_opt and hasPkgConfig(b, "sdl3");
    const sdl_pkg = if (use_sdl3) "sdl3" else "sdl2";

    const has_glew = switch (opengl_feature) {
        .enabled => true,
        .disabled => false,
        .auto => hasPkgConfig(b, "glew"),
    };

    // Shared compile flags for the smbcore family of libraries.
    var smbcore_flags = std.ArrayList([]const u8).empty;
    defer smbcore_flags.deinit(b.allocator);
    if (optimize_aggressively) {
        smbcore_flags.append(b.allocator, "-DASSUME_EXPECTS") catch @panic("OOM");
    } else {
        smbcore_flags.append(b.allocator, "-DPRINT_WARNINGS_AND_ERRORS") catch @panic("OOM");
        if (optimize == .Debug) {
            smbcore_flags.append(b.allocator, "-DCHECK_ARRAY_BOUNDS") catch @panic("OOM");
        }
    }
    if (thread_local_smbstate) {
        smbcore_flags.append(b.allocator, "-DTHREAD_LOCAL_SMBSTATE") catch @panic("OOM");
    }

    // Build per-library flag slices: base smbcore flags + mode define.
    var smb1_flags = std.ArrayList([]const u8).empty;
    defer smb1_flags.deinit(b.allocator);
    smb1_flags.appendSlice(b.allocator, smbcore_flags.items) catch @panic("OOM");
    smb1_flags.append(b.allocator, "-DSMB1_MODE") catch @panic("OOM");

    var smb2j_flags = std.ArrayList([]const u8).empty;
    defer smb2j_flags.deinit(b.allocator);
    smb2j_flags.appendSlice(b.allocator, smbcore_flags.items) catch @panic("OOM");
    smb2j_flags.append(b.allocator, "-DSMB2J_MODE") catch @panic("OOM");

    // smb1core static library
    const smb1core = b.addLibrary(.{
        .name = "smb1core",
        .linkage = .static,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    smb1core.root_module.addCSourceFiles(.{
        .files = &.{
            "src/smbcore/common.c",
            "src/smbcore/common_sound.c",
            "src/smbcore/area.c",
            "src/smbcore/smb1only.c",
        },
        .flags = smb1_flags.items,
    });

    // smb2jcore static library
    const smb2jcore = b.addLibrary(.{
        .name = "smb2jcore",
        .linkage = .static,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    smb2jcore.root_module.addCSourceFiles(.{
        .files = &.{
            "src/smbcore/common.c",
            "src/smbcore/common_sound.c",
            "src/smbcore/area.c",
            "src/smbcore/smb2jonly.c",
        },
        .flags = smb2j_flags.items,
    });

    // smbcore static library (C++ wrapper)
    const smbcore = b.addLibrary(.{
        .name = "smbcore",
        .linkage = .static,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
            .link_libcpp = true,
        }),
    });
    smbcore.root_module.addCSourceFiles(.{
        .files = &.{"src/smbcore.cpp"},
        .flags = smbcore_flags.items,
    });
    smbcore.root_module.linkLibrary(smb1core);
    smbcore.root_module.linkLibrary(smb2jcore);

    // nessndemu static library
    const nessndemu = b.addLibrary(.{
        .name = "nessndemu",
        .linkage = .static,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
            .link_libcpp = true,
        }),
    });
    nessndemu.root_module.addIncludePath(b.path("Nes_Snd_Emu/emu2413"));
    nessndemu.root_module.addCSourceFiles(.{
        .files = &.{
            "Nes_Snd_Emu/emu2413/emu2413.c",
            "Nes_Snd_Emu/nes_apu/Blip_Buffer.cpp",
            "Nes_Snd_Emu/nes_apu/Multi_Buffer.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Apu.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Fds_Apu.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Fme7_Apu.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Mmc5_Apu.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Namco_Apu.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Oscs.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Vrc6_Apu.cpp",
            "Nes_Snd_Emu/nes_apu/Nes_Vrc7_Apu.cpp",
        },
    });

    // smb_testrunner executable
    const testrunner = b.addExecutable(.{
        .name = "smb_testrunner",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });
    testrunner.root_module.addCSourceFiles(.{
        .files = &.{ "src/main_testrunner.c", "src/movie.c" },
    });
    testrunner.root_module.linkLibrary(smbcore);
    b.installArtifact(testrunner);

    // smbvanilla executable
    const opengl_src: []const []const u8 = if (has_glew)
        &.{"src/render_opengl.c"}
    else
        &.{"src/render_opengl_noop.c"};

    var app_flags = std.ArrayList([]const u8).empty;
    defer app_flags.deinit(b.allocator);
    if (!use_sdl3) app_flags.append(b.allocator, "-DUSE_SDL2") catch @panic("OOM");
    if (has_glew) app_flags.append(b.allocator, "-DOPENGL_ENABLED") catch @panic("OOM");

    const main_src: []const u8 = if (use_sdl3) "src/main_sdl3.c" else "src/main_sdl2.c";
    const audio_src: []const u8 = if (use_sdl3) "src/audio_sdl3.cpp" else "src/audio_sdl2.cpp";

    const smbvanilla = b.addExecutable(.{
        .name = "smbvanilla",
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
            .link_libcpp = true,
        }),
    });
    smbvanilla.root_module.addIncludePath(b.path("Nes_Snd_Emu"));
    smbvanilla.root_module.addCSourceFiles(.{
        .files = &.{
            "src/time.c",
            "src/movie.c",
            "src/render_raster.c",
            "src/thirdparty/ini.c",
        },
        .flags = app_flags.items,
    });
    smbvanilla.root_module.addCSourceFiles(.{
        .files = &.{main_src},
        .flags = app_flags.items,
    });
    smbvanilla.root_module.addCSourceFiles(.{
        .files = &.{audio_src},
        .flags = app_flags.items,
    });
    smbvanilla.root_module.addCSourceFiles(.{
        .files = opengl_src,
        .flags = app_flags.items,
    });
    smbvanilla.root_module.linkLibrary(smbcore);
    smbvanilla.root_module.linkLibrary(nessndemu);
    smbvanilla.root_module.linkSystemLibrary(sdl_pkg, .{});
    if (has_glew) smbvanilla.root_module.linkSystemLibrary("glew", .{});

    b.installArtifact(smbvanilla);
}
