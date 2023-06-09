import re

def should_skip_romarray(name):
    return name.startswith('E_') or name.startswith('L_') or re.match(r'World.Areas', name)

with open('./src/generated/smb_romarrays.h', 'w') as out:
    with open('./data/smb_romarrays.csv') as f:
        contents = f.read()
    for item in contents.split():
        name,addr,count = item.split(',')
        if should_skip_romarray(name): continue
        print(f'''#define {name:32} RAMARRAY_CONST({addr}, {count})''', file=out)

with open('./src/generated/smb2j_romarrays.h', 'w') as out:
    with open('./data/smb2j_romarrays.csv') as f:
        contents = f.read()
    for item in contents.split('\n'):
        if not item: continue
        name,mmap,addr,count = [x.strip() for x in item.split(',')]
        if should_skip_romarray(name): continue
        # we're going to ignore the memory map

        # Everything's writable (for now)
        addr = addr.upper()
        if addr[:2] == '0X': addr = '0x'+addr[2:]
        print(f'''#define {name:32} RAMARRAY({addr}, {count})''', file=out)

allvars = []

for prefix in ['smb', 'smb2j']:
    with open(f'./data/{prefix}_ram.csv') as f:
        contents = f.read()
    for item in contents.split():
        name,addr,typ = item.split(',')

        # Include the variables that are unpreferred by the decompiler
        name = name.replace('---', '')

        allvars.append((prefix, name, addr, typ))

from itertools import groupby
common_list = []
smb1_list = []
smb2j_list = []

for name, v in groupby(sorted(allvars, key=lambda x: x[1]),
                       key=lambda x: x[1]):
    v = list(v)
    games = {x[0] for x in v}
    addr = {x[2] for x in v}
    typ = {x[3] for x in v}

    if len(addr) > 1 or len(typ) > 1:
        print('uh oh!')
        print(f'collision for {name}')
        sys.exit(1)
    addr = list(addr)[0]
    typ = list(typ)[0]

    thelist = None
    if len(games) > 1: thelist = common_list
    elif games == {'smb'}: thelist = smb1_list
    elif games == {'smb2j'}: thelist = smb2j_list

    thelist.append((addr, name, typ))

with open(f'./src/generated/vars.h', 'w') as out:
    for game,l in [('common',common_list), ('smb1',smb1_list), ('smb2j',smb2j_list)]:
        print(f'/* {game} ----------------------- */', file=out)
        for addr,name,typ in sorted(l):
            if typ == 'byte':
                print(f'''#define {name:32} RAM({addr})''', file=out)
            elif typ == 'pointer':
                print(f'''#define {name:32} RAMPTR({addr})''', file=out)
            elif typ == 'array':
                print(f'''#define {name:32} RAMARRAY({addr}, 0)''', file=out)
            else:
                print('unknown!!!', file=out)
