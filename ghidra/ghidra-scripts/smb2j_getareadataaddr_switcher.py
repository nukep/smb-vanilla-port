runScript('smb2j_util.py')

# Create a switcher function for GetAreaDataAddrs

patch_addr = add_patch([
    0xAD, 0xF7, 0x07,   # lda FileListNumber
    0xC9, 0x03,         # cmp #3
    0xF0, 0x04,         # beq +
    0x20, 0xC3,0xC2,    # jsr $c2c3
    0x60,               # rts
# +
    0x20, 0xC3,0xC2,    # jsr $c2c3
    0x60,               # rts
])

lo = patch_addr.offset&0xFF
hi = (patch_addr.offset>>8)&0xFF

# Patch the JSR address to GetAreaDataAddrs
setByte(toAddr(0x6e85), lo)
setByte(toAddr(0x6e86), hi)

disassemble(patch_addr)
update_call_mmap(patch_addr.add(7), 'sm2main')
update_call_mmap(patch_addr.add(11), 'sm2data4')
