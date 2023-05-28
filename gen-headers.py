with open('./src/generated/smb_romarrays.h', 'w') as out:
    with open('./data/smb_romarrays.csv') as f:
        contents = f.read()
    for item in contents.split():
        name,addr,count = item.split(',')
        print(f'''static const ConstRamByteArray {name} = ConstRamByteArray({addr}, {count});''', file=out)

with open('./src/generated/smb_vars.h', 'w') as out:
    with open('./data/smb_ram.csv') as f:
        contents = f.read()
    for item in contents.split():
        name,addr,typ = item.split(',')

        # Include the variables that are unpreferred by the decompiler
        name = name.replace('---', '')

        if typ == 'byte':
            print(f'''static byte &{name} = RAM({addr});''', file=out)
        elif typ == 'pointer':
            print(f'''static RamPtr &{name} = RAMPtr({addr});''', file=out)
        elif typ == 'array':
            print(f'''static const RamByteArray {name} = RamByteArray({addr});''', file=out)
        else:
            print('unknown!!!', file=out)
