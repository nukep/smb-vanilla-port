cc = meson.get_compiler('c')

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

if get_option('use_poison_debug')
  smbcore_args += ['-DUSE_POISON_DEBUG']
endif

# Define signed integer wraparound
# Require it for now, until other compilers are supported
if cc.get_id() == 'msvc'
  # Note: I only tested this on Visual Studio 2022 (msvc 19.38)
  smbcore_args += cc.get_supported_arguments('/UndefIntOverflow-', checked: 'require')
else
  # GCC-like and Clang
  smbcore_args += cc.get_supported_arguments('-fwrapv', checked: 'require')
endif

# Turn on warnings for implicit sign conversions
smbcore_args += cc.get_supported_arguments('-Wsign-conversion')

force_cpp_args = []

if force_cpp
  # Note: may not work for MSVC or other compilers
  force_cpp_args += ['-x', 'c++']
endif

smb1core = library('smb1core',
  'common.c',
  'common_sound.c',
  'area.c',
  'smb1only.c',
  c_args: smbcore_args + force_cpp_args + ['-DSMB1_MODE'],
)

smb2jcore = library('smb2jcore',
  'common.c',
  'common_sound.c',
  'area.c',
  'smb2jonly.c',
  c_args: smbcore_args + force_cpp_args + ['-DSMB2J_MODE'],
)

smbcore = library('smbcore',
  'smbcore.c',
  include_directories: ['..'],
  c_args: smbcore_args,
  link_with: [smb1core, smb2jcore],
)
