# Sometimes the disassembly doesn't know which memory map an address belongs to.

runScript('smb2j_util.py')

def fixcall(src_mmap_addr, destinations):
    # the destination is selected based on which file number is loaded
    # if there's just one, assume the file it belongs to is loaded

    instaddr = get_mmap_addr(*src_mmap_addr)

    if len(destinations) == 1:
        dest_mmap = destinations[0]
        update_call_mmap(instaddr, dest_mmap)

fixcall(('sm2main', 0x6e84), ['sm2main', 'sm2data4'])
fixcall(('sm2main', 0x7a94), ['sm2data_24_common'])
fixcall(('sm2main', 0x7ed8), ['sm2data_24_common'])
fixcall(('sm2main', 0xbfee), ['sm2data4'])

# This one's a bit of a problem, because it's a JMP.
# Even if the flow override is CALL_RETURN, the pcode for the instruction doesn't even show the new address space
# Workaround (not implemented yet) is to turn the instruction to a JSR and set CALL_RETURN.
fixcall(('sm2main', 0xc0c7), ['sm2data3'])
