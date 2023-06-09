# The Ghidra decompilation is really grody.
#
# It does quite well with what it knows, and we do what we can in Ghidra itself.
# But sometimes, search-replacing the decompiled output is the best way to fix some problems.
#
# run without arguments: python3 <this-script>
# for smb2j: python3 <this-script> 2

import shutil
import re
import sys

IS_SMB2J = len(sys.argv) > 1 and sys.argv[1] == '2'

IS_SMB1 = not IS_SMB2J

if IS_SMB1:
    # As outputted by Ghidra
    INPUT_C_FILE = 'rawsmb.c'
    INPUT_H_FILE = 'rawsmb.h'

    # As finessed by this script
    TARGET_DIR = 'src/generated/'
    TARGET_CPP_FILE = 'smb1.c'
    TARGET_H_FILE = 'smb1.h'
else:
    # As outputted by Ghidra
    INPUT_C_FILE = 'rawsmb2j.c'
    INPUT_H_FILE = 'rawsmb2j.h'

    # As finessed by this script
    TARGET_DIR = 'src/generated/'
    TARGET_CPP_FILE = 'smb2j.c'
    TARGET_H_FILE = 'smb2j.h'

# Replaces a pattern like:
# *(byte *)(A + 0x1234) => FooBar[A - 1]
#
# The offset is a positive or negative number. e.g. 0x1234
# The array_str is a formatted string. e.g. 'FooBar[{} - 1]'
# Returns a string with all occurrences replaced.
def fixup_manged_array_access(input_string, offset, array_str):
    if offset < 0:
        offset_str = r'\-\s*0x{:x}'.format(-offset)
    else:
        offset_str = r'\+\s*0x{:x}'.format(offset)

    pattern = r'\*\(([a-zA-Z]+)\s*\*\)\((.+?)\s*{}\)'.format(offset_str)
    replacement = array_str.format(r'\2')
    output_string = re.sub(pattern, replacement, input_string)
    return output_string

# We get mangled array accesses in the decompiled output, usually because some arrays "start" in the middle of instructions.
# (it's really just that the index is assumed to be offset)
if IS_SMB1:
    mangled_array_fixups_str = '''
A + 0x833f => DemoActionData[A - 1]
A + 0x85c7 => BGColorCtrl_Addr[A - 4]
A + 0x92f6 => BSceneDataOffsets[A - 1]
A + 0x9720 => FrenzyIDData[A - 8]
A + 0xdc16 => PlayerPosSPlatData[A - 1]
A + 0xde24 => ClimbXPosAdder[A - 1]
A + 0xe1ff => BoundBoxCtrlData[A + 2]
A - 0xff => FreqRegLookupTbl[A + 1]
A - 0x100 => FreqRegLookupTbl[A]
A - 0xb2d => ExtraLifeFreqData[A - 1]
A - 0x6f4 => MusicHeaderData[A - 1]
'''
else:
    mangled_array_fixups_str = ''

mangled_array_fixups = []
for line in mangled_array_fixups_str.strip().split('\n'):
    if not line: continue
    lhs,rhs = line.split('=>')
    lhs = lhs.strip().split()
    rhs = rhs.strip().replace('[A', '[{}')
    offset = int(lhs[1]+lhs[2], 16)
    mangled_array_fixups.append((offset, rhs))

with open(INPUT_C_FILE, 'r') as f:
    outstr = f.read()
shutil.copyfile(INPUT_C_FILE, INPUT_C_FILE+'.bak')

# Replace mangled arrays
# e.g. *(byte *)(A + 0x1234) => FooBar[A - 1]
for offset, array_str in mangled_array_fixups:
    outstr = fixup_manged_array_access(outstr, offset, array_str)

# Replace *(byte *)(A) and similar with RAM(A)
outstr = re.sub(r'\*\((char|byte|undefined)\s*\*\)\(', 'RAM(', outstr)

# horrible
outstr = outstr.replace('*(byte *)param_1', 'RAM(param_1)')

# Okay, we can get rid of all other (byte *)s
outstr = outstr.replace('(byte *)', '')

# We're gonna replace the (&A)[B] pattern with (&A)[force_byte(B)].
# MSVC likes to "optimize" away the underflow-wrapping behavior of bytes when used in this specific context.
# (even though this is defined behavior!!!!!)
#     byte B = 0;
#     do {
#         (&A)[B] = 0; B--;
#     } while (B != 0);
# It doesn't like that!
# Anyway, I'll stop complaining. Time to pull my sleeves up and fix this
outstr = re.sub(r'\(\&(.*?)\)\[(.*?)\]', r'(&\1)[force_byte(\2)]', outstr)

# Replace character literals with numbers
def replace_character_literals(code):
    pattern = r"'(.+?)'"

    lookup = {
        r'\0': 0x00,
        r'\a': 0x07,
        r'\b': 0x08,
        r'\e': 0x1B,
        r'\f': 0x0C,
        r'\n': 0x0A,
        r'\r': 0x0D,
        r'\t': 0x09,
        r'\v': 0x0B,
        r'\\': 0x5C,
        r'\'': 0x27,
        r'\"': 0x22,
        r'\?': 0x3F
    }

    def replace(match):
        literal = match.group(1)
        if literal.startswith('\\x'):
            value = int(literal[2:], 16)
        elif literal in lookup:
            value = lookup[literal]
        else:
            value = ord(literal)

        if value > 10: value = f'0x{value:02X}'
        else: value = f'{value}'

        return value

    replaced_code = re.sub(pattern, replace, code)
    return replaced_code

outstr = replace_character_literals(outstr)

# Another very specific hack
# Decompiler tries to index a function :(
outstr = outstr.replace(
    r'(byte)RowOfCoins[param_1 + 7]',
    r'C_ObjectRow[param_1 - 2]'
)

# Another one. There's no statement after this label, and clang hates that.
outstr = outstr.replace('WrongChk:', 'WrongChk: 0;')

# Another. We're comparing with an unsigned byte, but Ghidra doesn't know that.
outstr = outstr.replace('-0x3e', '0xc2')
outstr = outstr.replace('-0x3d', '0xc3')

writable_hw_registers = [
    ('2000', 'ppuctrl'),
    ('2001', 'ppumask'),
    ('2003', 'oamaddr'),
    ('2005', 'ppuscroll'),
    ('2006', 'ppuaddr'),
    ('2007', 'ppudata'),
    
    ('4014', 'oamdma'),
    ('4016', 'joystick_strobe'), 

    ('4000', 'apu_sq1_vol'), ('4001', 'apu_sq1_sweep'), ('4002', 'apu_sq1_lo'),    ('4003', 'apu_sq1_hi'),
    ('4004', 'apu_sq2_vol'), ('4005', 'apu_sq2_sweep'), ('4006', 'apu_sq2_lo'),    ('4007', 'apu_sq2_hi'),
    ('4008', 'apu_tri_linear'),                         ('400a', 'apu_tri_lo'),    ('400b', 'apu_tri_hi'),
    ('400c', 'apu_noise_vol'),                          ('400e', 'apu_noise_lo'),  ('400f', 'apu_noise_hi'),
    ('4010', 'apu_dmc_freq'), ('4011', 'apu_dmc_raw'),  ('4012', 'apu_dmc_start'), ('4013', 'apu_dmc_len'),
    ('4015', 'apu_snd_chn'),
    ('4017', 'apu_framecounter_ctrl'),
]

readable_hw_registers = [
    ('2002', 'ppustatus'),
    ('2007', 'ppudata'),

    ('4016', 'joy1'), ('4017', 'joy2'),
    
    ('4032', 'FDS_drive_status')
]

for name,replacement in writable_hw_registers:
    outstr = re.sub(r'BYTE_{} = (.*?);'.format(name), '{}(\\1);'.format(replacement), outstr)

for name,replacement in readable_hw_registers:
    outstr = re.sub(r'BYTE_{}'.format(name), '{}()'.format(replacement), outstr)


outstr = outstr.replace('EnemyData._0_1_', 'EnemyData.lo')
outstr = outstr.replace('EnemyData._1_1_', 'EnemyData.hi')

# Since Ghidra 10.3, these appear in the structures
outstr = re.sub(r'([a-zA-Z0-9]+)\._([0-9])_([0-9])_', r'SUBPIECE(\1,\2,\3)', outstr)

# Replace integer casts 
outstr = re.sub(r'\(uint.\)(sVar.)', r'CAST_TO_INT(\1)', outstr)

# Ack! This is so weird! Appeared since Ghidra 10.3
#   register0x06 = (char)((uint3)uVar1 >> 8);
#   register0x07 = (char)((uint3)uVar1 >> 0x10);
#   return sVar2;
outstr = re.sub(r'register0x06 = (.*?);\n\s*register0x07 = (.*?);\n\s*return (.*?);',
                r'\3.r06 = \1;\n  \3.r07 = \2;\n  return \3;',
                outstr)

if 'register0x' in outstr:
    raise Exception('Leftover register0x... usage is still there!')

outstr = re.sub(r'undefined in_I;', '', outstr)
# things might try to assign to in_I if another function had returned it and the current one also returns it
outstr = re.sub(r'in_I \=.*', '', outstr)
outstr = outstr.replace('in_I', '0')

outstr = outstr.replace(INPUT_H_FILE, TARGET_H_FILE)

# Set all undefined "in" variables to 0
outstr = re.sub(r'byte (in_.*?);', r'byte \1 = 0;', outstr)
outstr = re.sub(r'bool (in_.*?);', r'bool \1 = false;', outstr)

# Fix "byte abVar1 [1]" and "abVar1[0]", which aren't ever truly accessed as multi-item arrays
outstr = re.sub(r'(abVar.) \[1\]', r'\1', outstr)
outstr = re.sub(r'(abVar.)\[0\]', r'\1', outstr)

if IS_SMB1:
    # SMB1 doesn't replace the opcode of a particular instruction
    outstr = outstr.replace('DAT_2100', '0x0e')
else:
    outstr = outstr.replace('DAT_2100', 'RAM(0xb585)')

if IS_SMB2J:
    outstr = outstr.replace('func_0xc858()', 'WriteNameToVictoryMsg()')
    # The lo address byte of the JSR SoundEngine call. Used to patch it.
    outstr = outstr.replace('DAT_2101', 'RAM(0x611d)')
    # The operand for a comparison in MovePiranhaPlant
    outstr = outstr.replace('uRAM9ffe', 'RAM(0x9ffe)')
    # this comparison:
    outstr = outstr.replace('< 0x21) goto PutinPipe;', '< RAM(0x9ffe)) goto PutinPipe;')

if IS_SMB2J:
    outstr = re.sub(r'SMB:sm2main_.::', 'SM2MAIN:', outstr)
    outstr = re.sub(r'SMB:sm2data2::', 'SM2DATA2:', outstr)
    outstr = re.sub(r'SMB:sm2data3::', 'SM2DATA3:', outstr)
    outstr = re.sub(r'SMB:sm2data4_.::', 'SM2DATA4:', outstr)
    outstr = re.sub(r'SMB:sm2data_24_common::', 'SM2DATA2+SM2DATA4:', outstr)
    outstr = re.sub(r'SMB:', 'SM2MAIN:', outstr)

outstr = re.sub(r'\(struct_(.*)\)', r'CAST_INT_TO_struct_\1', outstr)

with open(TARGET_DIR + TARGET_CPP_FILE, 'w') as f:
    f.write(outstr)

# Header file

with open(INPUT_H_FILE, 'r') as f:
    outstr = f.read()
shutil.copyfile(INPUT_H_FILE, INPUT_H_FILE+'.bak')

# Find all function declarations and prefix them
# This is a crude way to avoid linker collisions between the two games
function_prefix = 'smb1_' if IS_SMB1 else 'smb2j_'
outstr = re.sub(r'^(.+?) (.+?)\((.*)\);$', rf'\1 {function_prefix}\2(\3);\n#define \2 {function_prefix}\2\n', outstr, flags=re.MULTILINE);

# C++ has a bool type. Don't redefine it!
outstr = outstr.replace('typedef unsigned char    bool;', '')

# Add integer casting functions
outstr = re.sub(r'^struct (.*?) {(.*?)};',
r'''struct \1 {\2};
static inline \1 CAST_INT_TO_\1(uint64_t v) {
    \1 a;
    memcpy(&a, &v, sizeof(a));
    return a;
};''', outstr, flags=re.DOTALL|re.MULTILINE)

with open(TARGET_DIR + TARGET_H_FILE, 'w') as f:
    f.write('#pragma once\n')
    f.write('#pragma pack(push, 1)\n')
    f.write(outstr)
    f.write('#pragma pack(pop)\n')
