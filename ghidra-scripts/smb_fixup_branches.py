# There are some conditional branches, that always branch unconditionally in practice.
# It creates issues with analysis when the fallthrough is to data.
# Other times we just wanna clean up analysis a bit.
# Patch them with a custom "BRA" opcode.
# It doesn't exist on the 6502, but we define it in the processor for convenience.

setByte(toAddr(0x81bb), 0x80)

# in BlockObjectsCore, decompilation gets confused and throws off the stack depth
setByte(toAddr(0xbeb1), 0x80)

setByte(toAddr(0xbf8a), 0x80)
setByte(toAddr(0xbf90), 0x80)
setByte(toAddr(0xc348), 0x80)
setByte(toAddr(0xc719), 0x80)
setByte(toAddr(0xd963), 0x80)
setByte(toAddr(0xe234), 0x80)
setByte(toAddr(0xf3ab), 0x80)
setByte(toAddr(0xf3af), 0x80)
setByte(toAddr(0xf419), 0x80)
setByte(toAddr(0xf6c6), 0x80)

