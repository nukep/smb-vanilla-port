# Remove fallthrough overrides created earlier

removals = [
    0x8eda, # because it falls through into the same function
    0x92ac, # because it goes to a function that only contains RTS
    0x9643, # because it goes to a function that only contains RTS
    0xbfaa, # because they seem to both be a means to call ImposeGravity similarly
    0xd30e, # because it goes to a function that only contains RTS
    0xe3e8, # because they seem to call BlockBufferCollision similarly
    0xe5b8, 0xe5bb, 0xe5be, # because they seem to do the same thing, just at different counts

    # worry about audio stuff later
    # 0xf6d1, # because it falls through into the same function
]

for addr in removals:
    getInstructionAt(toAddr(addr)).clearFallThroughOverride()
