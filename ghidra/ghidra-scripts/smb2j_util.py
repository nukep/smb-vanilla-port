# Some common code that's useful for SMB2J scripts
# Not meant to be run directly!

def get_mmap_addr(mmap, offset):
    '''Returns an Address object that exists in the memory map.
    Helpful function to use when parsing data files.

    mmap is a prefix of the memory map's name.
    e.g. sm2main will match sm2main_a, sm2main_b, etc.'''
    if mmap is None:
        mmap = 'sm2main'

    for addr_range in currentProgram.getMemory():
        space_name = str(addr_range.addressSpace.name)
        if space_name.startswith(mmap) or (space_name == 'RAM' and mmap == 'sm2main'):
            test_addr = addr_range.addressSpace.getAddress(offset)
            if addr_range.contains(test_addr):
                return test_addr
    raise Exception('Offset not in memory map: {}, {:04x}'.format(mmap, offset))

from ghidra.program.model.symbol import FlowType

def update_call_mmap(instaddr, dest_mmap, opidx=0, flowtype=None):
    '''Update the instruction's reference to point to its address in the provided memory map'''
    instr = getInstructionAt(instaddr)
    ref = instr.getPrimaryReference(opidx)
    original_dst = ref.toAddress
    destaddr = get_mmap_addr(dest_mmap, int(original_dst.offset))

    # we gotta disassemble and make it a function, otherwise the decompiler won't recognize the new function call
    disassemble(destaddr)
    createFunction(destaddr, None)

    if flowtype is None:
        flowtype = instr.getFlowType()

    setReferencePrimary(addInstructionXref(instaddr, destaddr, opidx, flowtype))

    # Remove "Bad Instruction" bookmarks if they were there from disassembling the previously-bad function address
    for b in currentProgram.getBookmarkManager().getBookmarks(instaddr):
        if b.category == 'Bad Instruction':
            removeBookmark(b)


# Beginning at $3000...
__PATCHES_AT = toAddr(0x3000)
# start at the next available undefined address
__PATCHES_AT = getUndefinedDataAfter(__PATCHES_AT.subtract(1)).address

def current_patch_start():
    return __PATCHES_AT

def add_patch(patch):
    global __PATCHES_AT
    start = __PATCHES_AT
    setBytes(__PATCHES_AT, bytes(bytearray(patch)))
    __PATCHES_AT = __PATCHES_AT.add(len(patch))
    return start
