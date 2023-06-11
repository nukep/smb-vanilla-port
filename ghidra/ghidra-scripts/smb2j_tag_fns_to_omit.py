# We reimplement functions gradually.
# Give these tags so we can omit them from the decompiled output.

reimplemented = [
    'Reset',
    'NMI',
    'IRQHandler',
    'WriteNTAddr',
    'UpdateScreen',
    'InitializeMemory',
    'ReadJoypads',
    'ReadPortBits',
    'Dump_Freq_Regs',
    'NoiseSfxHandler',

    'LoadFiles',
    'ScrollScreen',
    'UpdateGamesBeaten'
]

unused = [
    'InitScroll',
    'FDSBIOS_LoadFiles',
    'FDSBIOS_WriteFile'
]

for name in reimplemented + unused:
    getFunction(name).addTag('skip')
