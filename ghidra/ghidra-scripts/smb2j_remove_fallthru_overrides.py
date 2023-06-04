# Remove fallthrough overrides created earlier

# Labels indicate what the fallthrough override falls into
# "it" is the fallthrough preceding the label
removal_into = [
    'UpdateScreen',             # because it falls through into the same function
    'LoopCmdE',                 # because it goes to a function that only contains RTS
    'ImposeGravitySprObj',      # because they seem to both be a means to call ImposeGravity similarly
    'StarFlagExit',             # because it goes to a function that only contains RTS
    'BlockBufferColli_Head',    # because they seem to call BlockBufferCollision similarly

    # because they seem to do the same thing, just at different counts
    'DumpFourSpr',
    'DumpThreeSpr',
    'DumpTwoSpr',

    # worry about audio stuff later
]

removals = [getInstructionAt(toAddr(x)).previous.address for x in removal_into]

for addr in removals:
    getInstructionAt(addr).clearFallThroughOverride()
