# The Ghidra decompilation is really grody.
#
# It does quite well with what it knows, and we do what we can in Ghidra itself.
# But sometimes, search-replacing the decompiled output is the best way to fix some problems.
#
# run without arguments: python3 <this-script>

import re

# As outputted by Ghidra
INPUT_C_FILE = 'rawsmb.c'
INPUT_H_FILE = 'rawsmb.h'

# As finessed by this script
TARGET_CPP_FILE = 'smb.cpp'
TARGET_H_FILE = 'smb.h'


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

    pattern = r'\*\((char|byte|undefined)\s*\*\)\((.+?)\s*{}\)'.format(offset_str)
    replacement = array_str.format(r'\2')
    output_string = re.sub(pattern, replacement, input_string)
    return output_string

# We get mangled array accesses in the decompiled output, usually because some arrays "start" in the middle of instructions.
# (it's really just that the index is assumed to be offset)
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

mangled_array_fixups = []
for line in mangled_array_fixups_str.strip().split('\n'):
    lhs,rhs = line.split('=>')
    lhs = lhs.strip().split()
    rhs = rhs.strip().replace('[A', '[{}')
    offset = int(lhs[1]+lhs[2], 16)
    mangled_array_fixups.append((offset, rhs))

with open(INPUT_C_FILE, 'r') as f:
    outstr = f.read()

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

# Very specific hack on reading the player controller
# Yes, there's actually only one read on $4016 or $4017 despite the decompilation showing it twice.
outstr = outstr.replace(
    r'bVar3 = ((&BYTE_4016)[param_1] >> 1 | (&BYTE_4016)[param_1]) & 1;',
    r'byte j; if (param_1 == 0) { j = joy1(); } else { j = joy2(); } bVar3 = (j >> 1 | j & 1) & 1;'
)

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

writable_hw_registers = [
    ('2000', 'ppuctrl'),
    ('2001', 'ppumask'),
    ('2003', 'oamaddr'),
    ('2005', 'ppuscroll'),
    ('2006', 'ppuaddr'),
    ('2007', 'ppudata'),

    ('4016', 'joystick_strobe'), 

    ('4000', 'apu_sq1_vol'), ('4001', 'apu_sq1_sweep'), ('4002', 'apu_sq1_lo'),    ('4003', 'apu_sq1_hi'),
    ('4004', 'apu_sq2_vol'), ('4005', 'apu_sq2_sweep'), ('4006', 'apu_sq2_lo'),    ('4007', 'apu_sq2_hi'),
    ('4008', 'apu_tri_linear'),                         ('400a', 'apu_tri_lo'),    ('400b', 'apu_tri_hi'),
    ('400c', 'apu_noise_vol'),                          ('400e', 'apu_noise_lo'),  ('400f', 'apu_noise_hi'),
    ('4010', 'apu_dmc_freq'), ('4011', 'apu_dmc_raw'),  ('4012', 'apu_dmc_start'), ('4013', 'apu_dmc_len'),
    ('4014', 'apu_oamdma'),
    ('4015', 'apu_snd_chn'),
    ('4017', 'apu_framecounter_ctrl'),
]

readable_hw_registers = [
    ('2002', 'ppustatus'),
    ('2007', 'ppudata'),

    ('4016', 'joy1'), ('4017', 'joy2')
]

for name,replacement in writable_hw_registers:
    outstr = re.sub(r'BYTE_{} = (.*?);'.format(name), '{}(\\1);'.format(replacement), outstr)

for name,replacement in readable_hw_registers:
    outstr = re.sub(r'BYTE_{}'.format(name), '{}()'.format(replacement), outstr)

outstr = re.sub(r'undefined in_I;', '', outstr)
# things might try to assign to in_I if another function had returned it and the current one also returns it
outstr = re.sub(r'in_I \=.*', '', outstr)
outstr = outstr.replace('in_I', '0')

outstr = outstr.replace(INPUT_H_FILE, TARGET_H_FILE)

# break the infinite loop in Start
outstr = outstr.replace('// WARNING: Do nothing block with infinite loop', 'break;')

with open(TARGET_CPP_FILE, 'w') as f:
    f.write(outstr)


# Header file

with open(INPUT_H_FILE, 'r') as f:
    outstr = f.read()

# C++ has a bool type. Don't redefine it!
outstr = outstr.replace('typedef unsigned char    bool;', '')

# Add more stuff to the data structures, so we can cast integers to/from them (just like Ghidra)
outstr = re.sub(r'struct (.*?) {', r'''struct \1 {
    inline \1() {}
    inline \1(uint64_t v) {
        memcpy(this, &v, sizeof(*this));
    }
    inline operator uint64_t() const {
        uint64_t v = 0;
        memcpy(&v, this, sizeof(*this));
        return v;
    }
''', outstr)

with open(TARGET_H_FILE, 'w') as f:
    f.write('#pragma pack(push, 1)')
    f.write('\n')
    f.write(outstr)
    f.write('#pragma pack(pop)')
    f.write('\n')
