currentProgram = state.getCurrentProgram()
memory = currentProgram.getMemory()

def create(name, fromaddr, toaddr, init=None, mirror=None, r=True, w=True, x=False, volatile=False):
    if init is not None:
        memblock = memory.createInitializedBlock(name, toAddr(fromaddr), toaddr+1-fromaddr, init, None, False)
    elif mirror is not None:
        memblock = memory.createByteMappedBlock(name, toAddr(fromaddr), toAddr(mirror), toaddr+1-fromaddr, None, False)
    else:
        memblock = memory.createUninitializedBlock(name, toAddr(fromaddr), toaddr+1-fromaddr, False)
    
    memblock.setPermissions(r, w, x)
    memblock.setVolatile(volatile)

# Create the memory maps

# REGS_1 is PPU related
# REGS_2 is APU (and FDS for SMB2) related

create('VARS',      0x0000, 0x07FF)
create('mirror1',   0x0800, 0x0FFF, mirror=0x0000)
create('mirror2',   0x1000, 0x17FF, mirror=0x0000)
create('mirror3',   0x1800, 0x1FFF, mirror=0x0000)
create('REGS_1',    0x2000, 0x200F, volatile=True)
create('unused_1',  0x2010, 0x2FFF)
create('PATCHES',   0x3000, 0x3FFF, init=0x60, w=False, x=True)
create('REGS_2',    0x4000, 0x40FF, volatile=True)
create('unused_2',  0x4100, 0x4FFF)
create('FAKEVARS',  0x5000, 0x5FFF)

# SMB1 code is at 0x8000-0xFFFF
# SMB2 code is at 0x6000-0xDFFF (with some regions reloaded from disk)

# Make sure all the hardware registers are byte types

for i in range(0x2000, 0x200F+1):
    createByte(toAddr(i))
for i in range(0x4000, 0x40FF+1):
    createByte(toAddr(i))
