function_names = [
    'ContinueGame',
    'ChkPOffscr',
    'InitChangeSize',
    'NextArea',
    'LRAir',
    'MoveBubl',
    'JCoinC',
    'SPBBox',
    'MoveHammerBroXDir',
    'MoveD_Bowser',
    'BowserGfxHandler',
    'EndAreaPoints',
    'ChkYPCollision',
    'EnemySmackScore',
    'RXSpd',
    'DoEnemySideCheck',
    'GetMaskedOffScrBits',
    'SetupEOffsetFBBox',
    'MoveBoundBoxOffscreen',
    'SprObjectOffscrChk',
    'PlayerGfxProcessing',
    'AnimationControl',
    'GetOffScreenBitsSet',
    'ContinueMusic',
    'LoadEventMusic',
    'LoadAreaMusic',
    'HandleAreaMusicLoopB',
    'FindEventMusicHeader',
    'LoadHeader'
]

addrs = [toAddr(x) for x in function_names]

for addr in addrs:
    print('creating {}'.format(addr))
    createFunction(addr, None)
