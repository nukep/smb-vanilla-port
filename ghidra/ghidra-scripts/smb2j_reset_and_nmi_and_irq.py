## Reset
disassemble(toAddr('Reset'))
createFunction(toAddr('Reset'), None)

## NMI
disassemble(toAddr('NMI'))
createFunction(toAddr('NMI'), None)

## IRQ
disassemble(toAddr('IRQHandler'))
createFunction(toAddr('IRQHandler'), None)

# Skip the PHP and PLP instructions
getInstructionAt(toAddr('IRQHandler').add(0)).setFallThrough(toAddr('IRQHandler').add(2))
getInstructionAt(toAddr('ExitIRQ').add(4)).setFallThrough(toAddr('ExitIRQ').add(6))
