runScript('smb2j_util.py')

# addresses are the locations of the "JSR JumpEngine" instructions.
tables = [
    (0x627C,4),
    (0x62C6,6),
    (0x62D8,14),
    (0x64C8,16),
    (0x705A,3),
    (0x70D9,8),
    (0x7475,55),
    (0x759A,3),
    (0x7A3A,5),
    (0x7BA4,13),
    (0x7EB5,4),
    (0x897E,13),
    (0x8E63,55),
    (0x93DD,6),
    (0x94C4,34),
    (0x953C,21),
    (0x95BC,7),
    (0x9F1A,5),
    (0xBFB3,6),
    (0xBFC5,5),
    (0xC009,5),
    (0xC050,5),
    (0xC091,5),
    
    (0xC601,7, 'sm2data3'),
    (0xC73B,5, 'sm2data3')
]

tables = [(x[0],x[1],'sm2main' if len(x) == 2 else x[2]) for x in tables]
tables = [(get_mmap_addr(mmap, addr), count, mmap) for addr,count,mmap in tables]

def is_in_sm2main_a_or_z(offset):
    return (offset >= 0x6000 and offset <= 0xc2c2) or (offset >= 0xd29f and offset <= 0xdfff)

def is_in_24_common(offset):
    return offset >= 0xc470 and offset <= 0xc5cf

# Most entries in the jump tables point to sm2main (the non-overlapping parts)
# However, some don't, and we have to tell Ghidra to reference addresses at specific locations.

which_map = {
    # in jumptable at $62d8
    0xC5FE: 'sm2data3',
    0xC642: 'sm2data3',
    0xC686: 'sm2data3',
    0xC6CA: 'sm2data3',
    0xC710: 'sm2data3',
    0xC727: 'sm2data3',
    0xC738: 'sm2data3',

    # in jumptable $64c8
    0xC573: 'sm2main_c',
    0xC58A: 'sm2main_c',

    # in jumptable at $64d8
    0xC5D0: 'sm2main_c',

    # in jumptable at $7475
    0xC470: 'sm2data_24_common',
    0xC475: 'sm2data_24_common',
    0xC5BE: 'sm2data_24_common',
    0xC5C2: 'sm2data_24_common',

    # in jumptable at $953c
    0xC4C0: 'sm2data_24_common',

    # in jumptable at $bfb3
    0xC5DB: 'sm2main_c',
    0xC46E: 'sm2main_c',
    0xC592: 'sm2main_c',

    # in jumptable at sm2data3 $c601
    0xC612: 'sm2data3',
    0xC61E: 'sm2data3',

    # in jumptable at sm2data3 $c73b
    0xC759: 'sm2data3',
}


def create_jsrengine_patch(jsr_addr, count):
    start_patch_at = current_patch_start()

    # Patching with our own custom instructions
    # JMPENGINE_INIT
    lo = int(jsr_addr.offset + 3) & 0xFF
    hi = (int(jsr_addr.offset + 3) >> 8) & 0xFF
    add_patch([0x07, lo, hi])

    addr_offsets = [getShort(jsr_addr.add(3 + index*2))&0xFFFF for index in range(count)]

    index = 0
    for addroff in addr_offsets:
        lo = addroff&0xFF
        hi = (addroff>>8)&0xFF
        # JMPENGINE_JSRIF
        add_patch([0x17, index, lo, hi])
        index += 1

    add_patch([0x27])

    # replace JSR JmpEngine with a JMP to the patched code
    lo = int(start_patch_at.offset) & 0xFF
    hi = (int(start_patch_at.offset) >> 8) & 0xFF
    setBytes(jsr_addr, bytes(bytearray([0x4c, lo, hi])))

    return start_patch_at, addr_offsets

patches = []

for jsr_addr,count,mmap in tables:
    patch_at,addr_offsets = create_jsrengine_patch(jsr_addr, count)
    patches.append((mmap,patch_at,addr_offsets))
    # for i in range(count):
    #     a = getShort(jsr_addr.add(3+i*2))&0xFFFF
    #     if is_in_sm2main_a_or_z(a):
    #         fn_addr = toAddr(a)
    #     else:
    #         fn_addr = toAddr('{}::{:04X}'.format(which_map[a], a))
        
    #     disassemble(fn_addr)
    #     createFunction(fn_addr, None)

for mmap,patch_at,addr_offsets in patches:
    disassemble(patch_at)
    # Update the references so they call the function at the correct memory map
    for i in range(len(addr_offsets)):
        addroff = addr_offsets[i]
        instr_addr = patch_at.add(3 + 4*i)
        if addroff in which_map:
            dest_mmap = which_map[addroff]
            update_call_mmap(instr_addr, dest_mmap, opidx=1, flowtype=FlowType.CONDITIONAL_CALL)
            instr = getInstructionAt(instr_addr)
        else:
            createFunction(get_mmap_addr('sm2main', addroff), None)
