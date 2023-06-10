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
    toAddr('NoStopSfx').add(21),

    # smb1 soundengine stuff
    # holy crap, there's a lot!
    toAddr('PTone1F').add(2),
    toAddr('SkipPIn').add(5),
    toAddr('PlayFlagpoleSlide').add(12),
    toAddr('PlaySmallJump').add(2),
    toAddr('PlayFireballThrow').add(4),
    toAddr('BranchToDecLength1').add(0),
    toAddr('PlayCoinGrab').add(4),
    toAddr('N2Tone').add(0),
    toAddr('PlayBlast').add(9),
    toAddr('SBlasJ').add(0),
    toAddr('BlstSJp').add(0),
    toAddr('EL_LRegs').add(0),
    toAddr('DivLLoop').add(14),
    toAddr('PlayGrowPowerUp').add(2),
    toAddr('HandleAreaMusicLoopB').add(23),
    toAddr('FetchSqu1MusicData').add(21),
    toAddr('FetchNoiseBeatData').add(16),
    toAddr('LoadControlRegs').add(9)
]

for addr in addrs:
    setByte(addr, 0x80)
