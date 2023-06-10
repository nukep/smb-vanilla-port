# We reimplement functions gradually.
# Give these tags so we can omit them from the decompiled output.

reimplemented = [
    'Reset',
    'NMI',
    'WriteNTAddr',
    'DrawTitleScreen',
    'UpdateScreen',
    'InitializeMemory',
    'TransposePlayers',
    'ReadJoypads',
    'ReadPortBits',
    'Dump_Freq_Regs',
]

unused = [
    'InitScroll'
]

for name in reimplemented + unused:
    getFunction(name).addTag('skip')
