runScript('smb2j_util.py')

def data_filename(name):
    import os
    CUR_PATH = os.path.dirname(os.path.realpath(__file__))
    return os.path.realpath(os.path.join(CUR_PATH, '../../data', name))

from ghidra.program.model.address import AddressSet
from ghidra.app.cmd.data import CreateArrayCmd
from ghidra.program.model.data import ByteDataType, PointerDataType, VoidDataType
ByteType = ByteDataType()
BytePointerType = PointerDataType(ByteType)

def getaddr(addr_str):
    # format: 0x1234
    offset = int(addr_str[2:], 16)
    if offset < 0x2000:
        offset += 0x5000

    return toAddr(offset)

def create_byte_array(addr, count):
    cmd = CreateArrayCmd(addr, count, ByteType, 1)
    cmd.applyTo(currentProgram)

def create_byte_pointer(addr):
    createData(addr, BytePointerType)

with open(data_filename('smb2j_ram.csv'), 'r') as f:
    contents = f.read().strip()

items = [item.split(',') for item in contents.split()]
# Skip items we don't want the decompiler to use (start with ---)
items = [x for x in items if '---' not in x[0]]
items.append(('dummy',0x0800,'n/a'))

for (name,addr,typ),(nextname,nextaddr,nexttyp) in zip(items,items[1:]):
    addr = getaddr(addr)
    if typ == 'byte':
        createLabel(addr, name, True)
        createByte(addr)
    elif typ == 'pointer':
        createLabel(addr, name, True)
        create_byte_pointer(addr)
        pass
    elif typ == 'array':
        nextaddr = getaddr(nextaddr)
        count = int(nextaddr.offset - addr.offset)
        createLabel(addr, name, True)
        create_byte_array(addr, count)
    else:
        pass

with open(data_filename('smb2j_romarrays.csv'), 'r') as f:
    contents = f.read().strip()
for item in contents.split('\n'):
    if not item: continue
    name,mmap,addr,count = [x.strip() for x in item.split(',')]
    addr = get_mmap_addr(mmap, addr)
    count = int(count)
    createLabel(addr, name, True)
    create_byte_array(addr, count)

if True:
    with open(data_filename('smb2j_code_labels.csv'), 'r') as f:
        contents = f.read().strip()
    for item in contents.split('\n'):
        if not item: continue

        name,mmap,addr = [x.strip() for x in item.split(',')]
        addr = int(addr, 16)
        addr = get_mmap_addr(mmap, addr)
        createLabel(addr, name, True)
