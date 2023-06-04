# SMB2J (aka Lost Levels) has a more complex memory layout than SMB1.
# FDS will load files from disk and write to sections of memory (PRG RAM).
# Most of these files overwrite existing data and code (such as loading Worlds 5-8, Worlds A-D, or the ending with World 9).
# We can model this in Ghidra with memory map overlays.

currentProgram = state.getCurrentProgram()
memory = currentProgram.getMemory()

def resolve_path(name):
    import os
    CUR_PATH = os.path.dirname(os.path.realpath(__file__))
    return os.path.realpath(os.path.join(CUR_PATH, '../../bin', name))

def create(name, fromaddr, toaddr, filename, origin, overlay=False):
    with open(resolve_path(filename), 'rb') as f:
        filebytes = memory.createFileBytes(filename, 0, 0x8000, f, monitor)
        memblock = memory.createInitializedBlock(name, toAddr(fromaddr), filebytes, fromaddr-origin, toaddr+1-fromaddr, overlay)
    r,w,x = True,True,True

    # Yes, we can actually write because the FDS loads the program into RAM
    memblock.setPermissions(r, w, x)

# Create the memory maps
# When execution happens within an overlay, the entire range of that overlay is unambiously within the overlay.
# i.e. if sm2data4 is loaded, an access from sm2data4 to c300 is unambiguously within sm2data4.

# Memory layout (not to scale)
# 6000            8000            a000            c000            d000            e000
# | sm2main                                                                      || fds bios |
#                                                       | sm2data2     |
#                                                          | sm2data3  |
#                                                    | sm2data4      |

# we split up SM2MAIN, because accessing from 6000 to say, c300, is ambiguous.
# There are two non-overlay memory maps, because they can always be accessed unambiguously no matter where.
create('sm2main_a', 0x6000, 0xc2c2, 'SM2MAIN .bin', origin=0x6000)
create('sm2main_b', 0xc2c3, 0xc46d, 'SM2MAIN .bin', origin=0x6000, overlay=True)
# c46e instead of c470, because code crosses through it
create('sm2main_c', 0xc46e, 0xd29e, 'SM2MAIN .bin', origin=0x6000, overlay=True)
create('sm2main_z', 0xd29f, 0xdfff, 'SM2MAIN .bin', origin=0x6000)

create('sm2data2', 0xc5d0, 0xd29e, 'SM2DATA2.bin', origin=0xc470, overlay=True)
create('sm2data3', 0xc5d0, 0xd29e, 'SM2DATA3.bin', origin=0xc5d0, overlay=True)
# c2b4-c2c2 in sm2main and sm2data4 are identical. 
create('sm2data4_a', 0xc2c3, 0xc46f, 'SM2DATA4.bin', origin=0xc2b4, overlay=True)
create('sm2data4_z', 0xc5d0, 0xd1ff, 'SM2DATA4.bin', origin=0xc2b4, overlay=True)

# sm2data2 and sm2data4 share the same data here
create('sm2data_24_common', 0xc470, 0xc5cf, 'SM2DATA2.bin', origin=0xc470, overlay=True)
