# We reimplement functions gradually.
# Give these tags so we can omit them from the decompiled output.

reimplemented = [
    'Start',
    'NonMaskableInterrupt',
    'WriteNTAddr',
    'DrawTitleScreen',
    'UpdateScreen',
    'InitializeMemory',
    'TransposePlayers',
    'ReadJoypads',
    'ReadPortBits'
]

unused = [
    'InitScroll'
]

for name in reimplemented + unused:
    getFunction(name).addTag('skip')

# Skip all functions at and after SoundEngine. They're all sound related.
fn = getFunction('SoundEngine')
while fn:
    fn.addTag('skip')
    fn = getFunctionAfter(fn)
