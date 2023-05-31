## Reset
disassemble(toAddr(0x8000))
createFunction(toAddr(0x8000), None)
# Skip the TXS instruction
getInstructionAt(toAddr(0x8007)).setFallThrough(toAddr(0x800a))


## NMI
disassemble(toAddr(0x8082))
createFunction(toAddr(0x8082), None)
