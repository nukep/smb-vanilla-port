# There are some conditional branches, that always branch unconditionally in practice.
# It creates issues with analysis when the fallthrough is to data.
# Other times we just wanna clean up analysis a bit.
# Patch them with a custom "BRA" opcode.
# It doesn't exist on the 6502, but we define it in the processor for convenience.

# All shared between SMB1 and SMB2J
addrs = [
    toAddr('ChkStart').add(30),

    # in BlockObjectsCore, decompilation gets confused and throws off the stack depth
    toAddr('ChkTop').add(7),

    toAddr('MoveDropPlatform').add(2),
    toAddr('SetMdMax').add(2),
    toAddr('SmallBBox').add(2),
    toAddr('FireBulletBill').add(8),
    toAddr('KillPlayer').add(11),
    toAddr('GetFireballBoundBox').add(7),
    toAddr('SetFreq_Squ2').add(2),
    toAddr('SetFreq_Tri').add(2),
    toAddr('DecJpFPS').add(0),
    toAddr('NoStopSfx').add(21)
]

for addr in addrs:
    setByte(addr, 0x80)
