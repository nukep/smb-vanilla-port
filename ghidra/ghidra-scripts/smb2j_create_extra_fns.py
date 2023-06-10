function_names = [
    'ModifyPhysics',

    'PlaySkidSfx',
    'PlayWindSfx',
    'ContinueSkidSfx',
    'ContinueWindSfx',
]

addrs = [toAddr(x) for x in function_names]

for addr in addrs:
    print('creating {}'.format(addr))
    createFunction(addr, None)
