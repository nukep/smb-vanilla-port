# Once all functions are defined, run through them and redefine their coverage.

from ghidra.program.model.address import AddressSet
from ghidra.app.cmd.disassemble import DisassembleCommand
from ghidra.program.model.listing import FlowOverride

# Beginning at $3000...
patches_at = toAddr(0x3000)
# start at the next available undefined address
patches_at = getUndefinedDataAfter(patches_at.subtract(1)).address


def create_fallthrough_patch(inst, fnaddr):
    global patches_at
    # create JMP, set flow override to CALL_RETURN
    inst.setFallThrough(patches_at)

    lo = (fnaddr.offset) & 0xFF
    hi = ((fnaddr.offset) >> 8) & 0xFF
    # Patch with a JMP instruction
    patch = bytes(bytearray([0x4c, lo, hi]))

    setBytes(patches_at, patch)
    cmd = DisassembleCommand(patches_at, AddressSet(patches_at, patches_at.add(2)), True)
    cmd.applyTo(currentProgram, monitor)

    jmpinst = getInstructionAt(patches_at)

    # Ensure the primary reference is in the same address space
    setReferencePrimary(addInstructionXref(patches_at, fnaddr, 0, jmpinst.getFlowType()))

    # Set a flow override so the JMP acts as a tail call
    jmpinst.setFlowOverride(FlowOverride.CALL_RETURN)

    patches_at = patches_at.add(3)

def fixup_fallthroughs():
    fns = currentProgram.functionManager.getFunctions(True)
    addrs = AddressSet()
    for fn in fns:
        fnaddr = fn.entryPoint
        # Get instruction right before this one, if one exists
        inst = getInstructionContaining(fnaddr.subtract(1))
        # if the instruction flows into the entrypoint, set a fallthrough override
        if inst and inst.fallThrough == fnaddr:
            addrs.add(inst.address)
            create_fallthrough_patch(inst, fnaddr)
    
    # Display fallthroughs to the user
    show('Fallthroughs', addrs)

# pseudocode:
# if instruction A is branched to, not RTS, and if tracing backwards we encounter multiple function entrypoints, then instruction A should be a function entrypoint.
# (we can trace backwards at an instruction-level using xrefs. no pcode required.)

def getFallFrom(addr):
    # If we're at a function entrypoint, we'll claim that nothing falls through to it
    fn = getFunctionAt(addr)
    if fn:
        return None
    inst = getInstructionAt(addr)
    if inst:
        return inst.fallFrom
    return None

# 1. Get AddressSet of EVERY function. We calculate this ourselves because Ghidra doesn't support overlapping functions.

def calculate_reachable_addresses(addr):
    '''Returns an AddressSet of all addresses reachable from the provided one.
    Accounts for branches, but not calls'''
    q = [addr]
    visited = AddressSet()
    while len(q) > 0:
        addr = q[0]
        q = q[1:]
        if visited.contains(addr): continue

        inst = getInstructionAt(addr)
        if inst:
            visited.addRange(inst.minAddress, inst.maxAddress)
            if inst.fallThrough:
                q.append(inst.fallThrough)
            if inst.flowType.isJump():
                if str(inst.flowOverride) in ['NONE', 'BRANCH']:
                    q = q + list(inst.flows)
        else:
            print('WARNING: Expecting instruction at {}'.format(addr))
    return visited

def get_overlapping_addresses():
    fns = currentProgram.functionManager.getFunctions(True)
    reachable = {}
    for fn in fns:
        fnaddr = fn.entryPoint
        reachable[fnaddr] = calculate_reachable_addresses(fnaddr)

    reachable_l = list(reachable.items())

    # It's O(n^2), but SMB doesn't have a lot of functions (there are about 500).

    overlapping = AddressSet()

    for i in range(len(reachable_l)):
        for j in range(i+1, len(reachable_l)):
            fi, ai = reachable_l[i]
            fj, aj = reachable_l[j]
            a = ai.intersect(aj)
            if not a.isEmpty():
                overlapping.add(a)

    return overlapping


from ghidra.program.model.listing import FlowOverride

def set_callreturn_to_branches_to_functions():
    insts_to_flow_override = set()
    addrs_to_make_fn = set()
    flowtypes = set()

    for inst in list(currentProgram.listing.getInstructions(True)):
        addr = inst.address
        if 'JMPENGINE' in inst.mnemonicString:
            # Workaround - don't apply to our custom instructions...
            continue
        for flowaddr in inst.flows:
            flowinst = getInstructionAt(flowaddr)
            if flowinst:
                if flowinst.mnemonicString == 'RTS':
                    # Leave it alone! Branching to a return...
                    pass
                else:
                    fn = getFunctionContaining(addr)
                    flowfn = getFunctionAt(flowaddr)
                    if flowfn:
                        # only work if we're flowing FROM a function
                        if fn != flowfn:
                            if str(inst.flowType) != 'UNCONDITIONAL_CALL':
                                flowtypes.add(str(inst.flowType))
                                insts_to_flow_override.add(inst)
                                addrs_to_make_fn.add(flowaddr)
            elif False:
                flowinst_inside = getInstructionContaining(flowaddr)
                if flowinst_inside:
                    print('FLOWS TO THE MIDDLE OF AN INSTRUCTION')
                else:
                    print('FLOWS TO NOTHING')
                print('  ', inst.address, flowaddr)

    
    insts_to_flow_override = [inst for inst in insts_to_flow_override if inst.flowOverride != FlowOverride.CALL_RETURN]

    print('Done!')
    print('Setting {} flow overrides:'.format(len(insts_to_flow_override)))
    for inst in insts_to_flow_override:
        # Note: This creates a function automatically if one isn't there
        inst.setFlowOverride(FlowOverride.CALL_RETURN)
    print('Done!')

set_callreturn_to_branches_to_functions()
fixup_fallthroughs()

overlapping = get_overlapping_addresses()

from ghidra.app.tablechooser import AddressableRowObject, ColumnDisplay
class Row(AddressableRowObject):
    def __init__(self, address, data):
        self._address = address
        self._data = data
    def getAddress(self):
        return self._address

class Column(ColumnDisplay):
    def __init__(self, colname, nth, clazz):
        self._colname = colname
        self._nth = nth
        self._clazz = clazz
    def getColumnValue(self, rowObject):
        return rowObject._data[self._nth]
    def getColumnName(self):
        return self._colname
    def getColumnClass(self):
        return self._clazz
    def compare(self, o1, o2):
        o1 = o1._data[self._nth]
        o2 = o2._data[self._nth]
        if o1 < o2: return -1
        if o1 > o2: return 1
        return 0

def address_table_helper(title, cols, rowdata):
    tc = createTableChooserDialog(title, None)
    nth = 0
    for colname, clazz in cols:
        tc.addCustomColumn(Column(colname, nth, clazz))
        nth += 1

    for d in rowdata:
        rowobj = Row(d[0], d[1:])
        tc.add(rowobj)
    tc.show()
    return tc

table_data = []
for ar in overlapping.getAddressRanges():
    table_data.append((ar.minAddress, int(ar.length)))

address_table_helper('Overlapping', [('Size', int)], table_data)
