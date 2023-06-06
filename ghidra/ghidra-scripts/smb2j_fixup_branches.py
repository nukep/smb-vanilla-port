runScript('smb2j_util.py')

# There are some conditional branches, that always branch unconditionally in practice.
# It creates issues with analysis when the fallthrough is to data.
# Other times we just wanna clean up analysis a bit.
# Patch them with a custom "BRA" opcode.
# It doesn't exist on the 6502, but we define it in the processor for convenience.

# SMB2J only
addrs = [
    toAddr('StartVMDelay').add(5),
    toAddr('UpsideDownPipe_High').add(3),
    toAddr('WindOn').add(2)
]

for addr in addrs:
    setByte(addr, 0x80)


# we're just gonna nop out the payload after some of the "JSR FDSBIOS..." instructions
addr = get_mmap_addr('sm2data3', 0xc75e)
for i in range(4):
    setByte(addr.add(i), 0xEA)
addr = get_mmap_addr('sm2main', 0xc106)
for i in range(4):
    setByte(addr.add(i), 0xEA)
