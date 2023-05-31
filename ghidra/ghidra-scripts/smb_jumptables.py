# addresses are the locations of the "JSR JumpEngine" instructions.
tables = [(0x8215,4),
          (0x8234,4),
          (0x83a3,5),
          (0x856a,15),
          (0x921b,3),
          (0x92c8,8),
          (0x9664,47),
          (0x9743,3),
          (0xaedf,4),
          (0xb04c,13),
          (0xb34e,4),
          (0xbdbd,9),
          (0xc27f,55),
          (0xc7a8,6),
          (0xc88f,34),
          (0xc907,21),
          (0xc987,7),
          (0xd2e5,5)]


from ghidra.program.model.address import AddressSet
from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.program.model.listing import FlowOverride

# Beginning at $3000...
patches_at = toAddr(0x3000)
# start at the next available undefined address
patches_at = getUndefinedDataAfter(patches_at.subtract(1)).address

def add_patch(patch):
    global patches_at
    setBytes(patches_at, bytes(bytearray(patch)))
    patches_at = patches_at.add(len(patch))

def create_jsrengine_patch(jsr_addr, count):
    start_patch_at = patches_at

    # Patching with our own custom instructions
    # JMPENGINE_INIT
    lo = int(jsr_addr.offset + 3) & 0xFF
    hi = (int(jsr_addr.offset + 3) >> 8) & 0xFF
    add_patch([0x07, lo, hi])
    for index in range(count):
        lo = getByte(jsr_addr.add(3 + index*2))&0xFF
        hi = getByte(jsr_addr.add(3 + index*2 + 1))&0xFF
        # JMPENGINE_JSRIF
        add_patch([0x17, index, lo, hi])
    # JMPENGINE_JSRELSE
    add_patch([0x27])

    # replace JSR JmpEngine with a JMP to the patched code
    lo = int(start_patch_at.offset) & 0xFF
    hi = (int(start_patch_at.offset) >> 8) & 0xFF
    setBytes(jsr_addr, bytes(bytearray([0x4c, lo, hi])))

from ghidra.program.model.data import ArrayDataType

for addr_raw,count in tables:
    create_jsrengine_patch(toAddr(addr_raw), count)

for addr_raw,count in tables:
    # disassemble and create all functions in the tables
    for i in range(count):
        fn_addr_raw = getShort(toAddr(addr_raw+3 + i*2))&0xFFFF
        addr = toAddr(fn_addr_raw)
        disassemble(addr)
        createFunction(addr, None)
