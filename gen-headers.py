with open('./src/generated/smb_romarrays.h', 'w') as out:
    with open('./data/smb_romarrays.csv') as f:
        contents = f.read()
    for item in contents.split():
        name,addr,count = item.split(',')
        print(f'''#define {name:32} RAMARRAY_CONST({addr}, {count})''', file=out)

with open('./src/generated/smb2j_romarrays.h', 'w') as out:
    with open('./data/smb2j_romarrays.csv') as f:
        contents = f.read()
    for item in contents.split('\n'):
        if not item: continue
        name,mmap,addr,count = [x.strip() for x in item.split(',')]
        # we're going to ignore the memory map

        # Everything's writable (for now)
        print(f'''#define {name:32} RAMARRAY({addr}, {count})''', file=out)

for prefix in ['smb', 'smb2j']:
    with open(f'./src/generated/{prefix}_vars.h', 'w') as out:
        with open(f'./data/{prefix}_ram.csv') as f:
            contents = f.read()
        for item in contents.split():
            name,addr,typ = item.split(',')

            # Include the variables that are unpreferred by the decompiler
            name = name.replace('---', '')

            if typ == 'byte':
                print(f'''#define {name:32} RAM({addr})''', file=out)
            elif typ == 'pointer':
                print(f'''#define {name:32} RAMPTR({addr})''', file=out)
            elif typ == 'array':
                print(f'''#define {name:32} RAMARRAY({addr}, 0)''', file=out)
            else:
                print('unknown!!!', file=out)
