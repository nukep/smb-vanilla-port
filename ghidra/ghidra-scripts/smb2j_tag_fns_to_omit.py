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

# Skip all functions at and after SoundEngine. They're all sound related.
fn = getFunction('SoundEngine')
while fn and fn.entryPoint.offset < 0xe000:
    fn.addTag('skip')
    fn = getFunctionAfter(fn)
