# Trace through the entire program's Pcode and solve the inputs and outputs of every function it encounters.
# This bloody game - and most 6502 games really - has no consistent "calling convention" to speak of.
#
# The script logs Python code you can choose to use for your own analysis.
#
# This approach assumes there's no recursion in the code.
# If recursion is detected, it'll be logged and the analysis is deemed invalid.
#
# Now, there IS some recursion in SMB. We just fix it up.
# This is done by manually solving the input/output for any function in the cycle formed by the recursion.
# (see presolved_functions_list)

# All valid registers in our program. Also determines the order they appear in function parameters and return structures.
full_set_of_registers_list = ['A', 'X', 'Y', 'N', 'V', 'Z', 'C', 'r00', 'r01', 'r02', 'r03', 'r04', 'r05', 'r06', 'r07']
full_set_of_registers_list = [currentProgram.getRegister(x) for x in full_set_of_registers_list]
full_set_of_registers = set(full_set_of_registers_list)

def is_register_a_flag(reg):
    '''Used to check if a register should be a boolean'''
    return reg.name in 'NVBDIZC'


# (address, inputs, outputs)
# If a label doesn't exist, it'll be ignored
presolved_functions_list = [
    ('Reset',                 [], []),       # Reset
    ('NMI',                   [], []),       # NMI
    ('OperModeExecutionTree', [], []),
    ('ReadPortBits',          ['X'], []),    # Bitshifts accumulator from caller, but the original value becomes completely lost.
    ('CheckpointEnemyID',     ['X'], []),    # Recursive. It's the entrypoint for a call hierarchy that eventually calls itself again.
    ('SoundEngine',           [], []),       # Actually we're ignoring it because this is frightening and we don't want to analyze it right now lol

    ('FDSBIOS_LoadFiles',     [], ['A', 'Y', 'Z']),
    ('FDSBIOS_WriteFile',     ['A'], ['A', 'Z']),
]

# Which functions should be analyze, in order? Note: recurses into calls.
functions_to_analyze = [
    'Reset',
    'NMI',
    'CheckpointEnemyID',
    'OperModeExecutionTree'
]

# Should we apply the solved inputs/outputs? False means we just log them.
applyit = True
log_call_trees = False





presolved_functions = {
    toAddr(x[0]): x[1:3] for x in presolved_functions_list if toAddr(x[0]) is not None
}

# We need a feature to assert that certain calls do not use a register as input or output
# example is ImposeGravity(), which only uses r01 if A is nonzero

def ImposeGravity_excl(addr):
    # the call at this address does not read or write r01
    return (int(addr.offset), ['r01'], ['r01'])

# addresses are of the instruction. applies to all CALL pcode ops within it
calls_register_exclusions_list = [
    ImposeGravity_excl(toAddr('RunFB').add(15)),
    ImposeGravity_excl(toAddr('WhPull').add(13)),
    ImposeGravity_excl(toAddr('ProcHammerObj').add(37)),
    ImposeGravity_excl(toAddr('JCoinRun').add(18)),
    ImposeGravity_excl(toAddr('ImposeGravitySprObj').add(4))
]

calls_register_exclusions = {
    toAddr(x[0]): x[1:] for x in calls_register_exclusions_list
}


def next_paddr_ram(paddr):
    # increment the ram part, and set seq to 0
    ram_addr, seq = paddr
    instr = getInstructionAt(ram_addr)
    next_addr = instr.getFallThrough()
    if next_addr is None:
        raise Exception('No fallthrough exists for the instruction at {}'.format(ram_addr))
    return (next_addr, 0)

def canonical_paddr(paddr):
    ram_addr, seq = paddr
    instr = getInstructionAt(ram_addr)
    ops = instr.getPcode(java.lang.Boolean(True))
    if seq > len(ops):
        raise Exception('Seq out of bounds')
    if seq == len(ops):
        next_addr = instr.getFallThrough()
        if next_addr is None:
            raise Exception('No fallthrough exists for the instruction at {}'.format(ram_addr))
        return (next_addr, 0)
    return (ram_addr, seq)

def add_paddr(paddr, n):
    ram_addr, seq = paddr
    return canonical_paddr((ram_addr, seq+n))

def inc_paddr(paddr):
    return add_paddr(paddr, 1)

def at(paddr):
    ram_addr, seq = paddr
    instr = getInstructionAt(ram_addr)
    if not instr:
        print('NOPE')
        print(ram_addr)
    # Get the pcodeops, with overrides enabled.
    # Allows for nice things like CALL_RETURN (tail calls for branches).
    ops = instr.getPcode(java.lang.Boolean(True))
    if len(ops) == 0 and seq == 0:
        # NOP, or another do-nothing instruction
        return None

    return ops[seq]

def is_instr_relative_branch(instr):
    return instr.mnemonicString in ['BPL', 'BMI', 'BVC', 'BVS', 'BRA', 'BCC', 'BCS', 'BNE', 'BEQ']

def parse_paddr_from_pcodeop(current_paddr, pcodeop, input_num):
    '''Returns the "paddr" (ram,seq tuple) referred to at the given input parameter for the pcode op'''
    varnode = pcodeop.getInputs()[input_num]
    addr = varnode.getAddress()
    if addr.isConstantAddress():
        # The branch is a pcode seq offset relative to the current pcode op
        # This stays within the instruction, or directly fallthroughs the instruction
        return add_paddr(current_paddr, addr.getOffset())
    else:
        # assume RAM

        current_ram_addr = current_paddr[0]
    
        # Workaround: Assume we're in the same address space for relative branches
        # Ghidra uses the RAM address space and ignores the actual one for all branches unfortunately :/
        instr = getInstructionAt(current_ram_addr)
        if pcodeop.mnemonic == 'CBRANCH' and is_instr_relative_branch(instr):
            addr = instr.getPrimaryReference(0).toAddress
        if instr.mnemonicString in ['JMP', 'BRA']:
            # Also workaround JMPs entirely
            addr = instr.getPrimaryReference(0).toAddress

        return (addr, 0)

def parse_call_addr_from_pcodeop(current_paddr, pcodeop, input_num):
    current_ram_addr = current_paddr[0]
    addr = pcodeop.getInputs()[input_num].getAddress()
    instr = getInstructionAt(current_ram_addr)
    if pcodeop.mnemonic == 'CBRANCH' and is_instr_relative_branch(instr):
        addr = instr.getPrimaryReference(0).toAddress
    if instr.mnemonicString in ['JMP', 'BRA']:
        # Also workaround JMPs entirely
        addr = instr.getPrimaryReference(0).toAddress
    return addr

def find_pcode_blocks(start_ram_addr):
    '''Returns the entrypoint block, and all the block objects'''
    ram_addr = start_ram_addr

    start_of_blocks = set()
    start_of_blocks.add((start_ram_addr, 0))

    visited = set()

    # 1. Find the starting address of each block
    q = [(start_ram_addr, 0)]
    while q:
        paddr = q[0]
        q = q[1:]
        if paddr in visited:
            continue
        visited.add(paddr)
        pcodeop = at(paddr)
        if not pcodeop:
            # NOP-like
            q.append(next_paddr_ram(paddr))
            continue
        
        mn = pcodeop.mnemonic
        if mn == 'CBRANCH':
            dest = parse_paddr_from_pcodeop(paddr, pcodeop, 0)
            start_of_blocks.add(dest)
            start_of_blocks.add(inc_paddr(paddr))
            q.append(dest)
            q.append(inc_paddr(paddr))
        elif mn == 'BRANCH':
            dest = parse_paddr_from_pcodeop(paddr, pcodeop, 0)
            start_of_blocks.add(dest)
            q.append(dest)
        elif mn == 'BRANCHIND':
            raise Exception('Indirect branch not supported')
        elif mn == 'RETURN':
            pass
        else:
            q.append(inc_paddr(paddr))
    
    # 2. Collect the pcode for each block and the relationships between blocks,
    # once we know where they are

    start_of_blocks = sorted(start_of_blocks)
    block_edges = {}
    blocks = {}
    for block_paddr in start_of_blocks:
        paddr = block_paddr
        pcodes = []
        block_edges[block_paddr] = []
        while True:
            pcodeop = at(paddr)
            if not pcodeop:
                # NOP-like
                paddr = next_paddr_ram(paddr)
                continue
            pcodes.append((pcodeop, paddr))
            mn = pcodeop.mnemonic
            if mn == 'CBRANCH':
                dest = parse_paddr_from_pcodeop(paddr, pcodeop, 0)
                block_edges[block_paddr].append(inc_paddr(paddr))
                block_edges[block_paddr].append(dest)
                break
            elif mn == 'BRANCH':
                dest = parse_paddr_from_pcodeop(paddr, pcodeop, 0)
                block_edges[block_paddr].append(dest)
                break
            elif mn == 'RETURN':
                break
            else:
                paddr = inc_paddr(paddr)
        b = Block()
        b.paddr = block_paddr
        b.pcodes = pcodes
        blocks[block_paddr] = b

    for srcpaddr,dstpaddrs in block_edges.items():
        for dstpaddr in dstpaddrs:
            blocks[srcpaddr].add_dest(blocks[dstpaddr])

    return (blocks[(start_ram_addr, 0)], blocks.values())

class Fresh:
    def __init__(self, fninput=None, fnoutput=None, reg=None):
        self._from = set()
        self._effects = set()
        if fninput is not None:
            self._effects.add(('fninput', fninput, reg))
        if fnoutput is not None:
            self._effects.add(('fnoutput', fnoutput, reg))

    def link(self, tofresh):
        tofresh._from.add(self)
    
    # can't override __eq__, because it messes up hashing
    def semantically_equal(self, other):
        return self._from == other._from and self._effects == other._effects

    def clone_as_orphan(self):
        x = Fresh()
        x._from = set()
        x._effects = set(self._effects)
        return x

    def traverse_backwards_all(freshes, visit):
        # After being linked, the Fresh objects form a directed graph.
        # Traverse backwards from these ones.
        visited = set()
        q = list(freshes)
        while len(q) > 0:
            x = q[0]
            q = q[1:]
            if x in visited: continue
            visited.add(x)
            result = visit(x)
            if result != 'STOP':
                q = q + list(x._from)
    traverse_backwards_all = staticmethod(traverse_backwards_all)

    def traverse_backwards(self, visit):
        return Fresh.traverse_backwards_all([self], visit)
    
    def get_roots(self):
        '''Returns a set of Fresh objects that have no parents'''
        rs = set()

        def visit(x):
            if len(x._from) == 0:
                rs.add(x)

        self.traverse_backwards(visit)

        return rs

    def clone_backwards_all(freshes):
        old_to_new = {}
        def visit(x):
            old_to_new[x] = x.clone_as_orphan()
        Fresh.traverse_backwards_all(freshes, visit)

        for old,new in old_to_new.items():
            new._from = {old_to_new[x] for x in old._from}

        return old_to_new
    clone_backwards_all = staticmethod(clone_backwards_all)

    def simplify_all(inputs, outputs, reads):
        '''Create a new graph of freshes'''
        old_to_new = {}
        for fresh in outputs+reads:
            newfresh = Fresh()
            def visit(x):
                newfresh._effects.update(x._effects)
                if x in inputs:
                    x.link(newfresh)
                    return 'STOP'
            fresh.traverse_backwards(visit)

            if len(fresh.get_roots()) > 1:
                # add a dummy Fresh as an additional parent, to indicate the new fresh can be multiple values
                # otherwise the analysis think registers are passthrus when they're not
                Fresh().link(newfresh)

            old_to_new[fresh] = newfresh

        # Remove duplicate reads
        newreads = []
        for x in reads:
            x = old_to_new[x]
            skip = False
            for y in newreads:
                if x.semantically_equal(y):
                    skip = True
                    break
            if not skip:
                newreads.append(x)
        
        newoutputs = [old_to_new[x] for x in outputs]

        return (newoutputs, newreads)
    simplify_all = staticmethod(simplify_all)

    def get_fn_inputs_and_outputs(freshes):
        ins = set()
        outs = set()

        def visit(x):
            for typ, fn, reg in x._effects:
                if typ == 'fninput':
                    ins.add((fn, reg))
                if typ == 'fnoutput':
                    outs.add((fn, reg))

        Fresh.traverse_backwards_all(freshes, visit)

        return (ins, outs)
    get_fn_inputs_and_outputs = staticmethod(get_fn_inputs_and_outputs)

from ghidra.program.model.lang import Register

def coerce_to_reg(x):
    '''Returns None if not a register'''
    if type(x) is Register:
        return x
    else:
        return currentProgram.getRegister(x)

def sorted_registers(regs):
    regs = [coerce_to_reg(r) for r in regs]
    # Use a specific order
    return [r for r in full_set_of_registers_list if r in regs]

def is_valid_reg(reg):
    reg = coerce_to_reg(reg)
    return reg in full_set_of_registers

class Function:
    def __init__(self, addr):
        self.presolved = False
        self.addr = addr
        self.input_regs = set()
        self.output_regs = set()

        entrypoint_block, blocks = find_pcode_blocks(addr)
        self.entrypoint_block = entrypoint_block
        self.blocks = blocks

    def __repr__(self):
        return 'F@{}'.format(self.addr)

    def add_input_reg(self, reg):
        self.input_regs.add(coerce_to_reg(reg))
    def add_output_reg(self, reg):
        self.output_regs.add(coerce_to_reg(reg))
    
    def __cmp__(self, other):
        # note: only works in python 2, which is what Ghidra uses as of writing
        return cmp(str(self), str(other))
    
    def __hash__(self):
        return hash(str(self))


class BlockPorts:
    def __init__(self, clonefrom=None, value=None, **kwargs):
        if value:
            self._regs = value
        elif clonefrom:
            self._regs = {r: x for r,x in clonefrom._regs.items()}
        else:
            self._regs = {r: Fresh(reg=r, **kwargs) for r in full_set_of_registers}
    
    def clone(self):
        return BlockPorts(clonefrom=self)
    
    def freshes(self):
        return [x for r,x in self]
    
    def deepclone_freshes_all(blockportses, additional_freshes=None):
        # makes deep clones of all the freshes
        freshes = list({x for b in blockportses for x in b._regs.values()}) + (additional_freshes or [])
        freshes_old_to_new = Fresh.clone_backwards_all(freshes)

        out = [BlockPorts(value={r: freshes_old_to_new[fresh] for r,fresh in b._regs.items()}) for b in blockportses]
        if additional_freshes is not None:
            out.append([freshes_old_to_new[fresh] for fresh in additional_freshes])
        return out
    deepclone_freshes_all = staticmethod(deepclone_freshes_all)

    def simplify_all(fninputs, fnoutputs, reads):
        outs = fnoutputs.freshes()
        newouts, newreads = Fresh.simplify_all(fninputs.freshes(), outs, reads)
        old_to_new = {a:b for a,b in zip(outs, newouts)}

        return BlockPorts(value={r: old_to_new[x] for r,x in fnoutputs}), newreads
    simplify_all = staticmethod(simplify_all)

    def __getitem__(self, reg):
        reg = coerce_to_reg(reg)
        return self._regs[reg]
    
    def __setitem__(self, reg, fresh):
        reg = coerce_to_reg(reg)
        if reg in self._regs:
            self._regs[reg] = fresh
    
    def __iter__(self):
        for reg,fresh in self._regs.items():
            yield reg,fresh

    def fresh(self, reg, **kwargs):
        self[reg] = Fresh(**kwargs)

    def link(self, toblockports):
        for r in self._regs.keys():
            self[r].link(toblockports[r])

class Block:
    def __init__(self):
        self._to = set()
        self.processed = False
    def add_dest(self, toblock):
        self._to.add(toblock)
    def dest_blocks(self):
        return list(self._to)
    def is_terminating(self):
        return len(self._to) == 0

ADDR_TO_FUNCTION_LOOKUP = {}

def find_function_from_addr(addr):
    f = ADDR_TO_FUNCTION_LOOKUP.get(addr)
    if f is None:
        f = Function(addr)
        presolved = presolved_functions.get(addr)
        if presolved:
            inp,out = presolved
            f.presolved = True
            for reg in inp: f.add_input_reg(reg)
            for reg in out: f.add_output_reg(reg)
        ADDR_TO_FUNCTION_LOOKUP[addr] = f
    return ADDR_TO_FUNCTION_LOOKUP[addr]

def debug_freshes(freshes, highlight=[]):
    def visit(fresh):
        for p in fresh._from:
            print('{} -> {}'.format(id(p), id(fresh)))
        
        in_list = fresh in freshes

        extra_str = ', style=filled, fillcolor=red' if in_list else ''
        if fresh in highlight:
            extra_str += ', penwidth=16'

        label = []
        for typ, fn, reg in fresh._effects:
            label.append('{}: {} {}'.format(typ, fn, reg))
        label = '\\n'.join(label)
        
        print('{}[label="{}"{}]'.format(id(fresh), label, extra_str))
    Fresh.traverse_backwards_all(freshes, visit)

def create_multireg_struct(regs):
    regs = [coerce_to_reg(x) for x in regs]
    from ghidra.program.model.data import StructureDataType
    from ghidra.program.model.data import DataTypeConflictHandler
    from ghidra.program.model.data import BooleanDataType, ByteDataType, VoidDataType, ArrayDataType
    ByteType = ByteDataType()
    BooleanType = BooleanDataType()
    def data_type_for_reg(reg):
        return BooleanType if is_register_a_flag(reg) else ByteType
    
    structname_post = ''.join([reg.name.lower() for reg in regs])
    structname = 'struct_' + structname_post

    data_type_manager = currentProgram.getDataTypeManager()
    dt = StructureDataType(structname, 0, data_type_manager)
    for reg in regs:
        dt.add(data_type_for_reg(reg), 1, reg.name.lower(), '')
    # Add the data type. If it already exists, don't replace the one that's there
    return data_type_manager.addDataType(dt, DataTypeConflictHandler.KEEP_HANDLER)
    # return data_type_manager.addDataType(dt, DataTypeConflictHandler.REPLACE_HANDLER)

def set_function_io(fn, input_regs, output_regs):
    # fn is a Ghidra function

    input_regs = [coerce_to_reg(x) for x in input_regs]
    output_regs = [coerce_to_reg(x) for x in output_regs]

    from ghidra.program.model.listing.Function import FunctionUpdateType
    from ghidra.program.model.symbol import SourceType
    from ghidra.program.model.listing import ParameterImpl, VariableStorage
    from ghidra.program.model.data import BooleanDataType, ByteDataType, VoidDataType, ArrayDataType
    ByteType = ByteDataType()
    BooleanType = BooleanDataType()

    def byte_array(n):
        return ArrayDataType(ByteType, n, 1)
    
    def data_type_for_reg(reg):
        return BooleanType if is_register_a_flag(reg) else ByteType

    params = [ParameterImpl(None, data_type_for_reg(reg), reg, currentProgram) for reg in input_regs]
    fn.replaceParameters(params, FunctionUpdateType.CUSTOM_STORAGE, True, SourceType.USER_DEFINED)
    if len(output_regs) == 0:
        fn.setReturnType(VoidDataType.dataType, SourceType.USER_DEFINED)
    elif len(output_regs) == 1:
        fn.setReturn(data_type_for_reg(output_regs[0]), VariableStorage(currentProgram, output_regs[0]), SourceType.USER_DEFINED)
    else:
        # variable storage registers are in reverse order, because the processor is little-endian
        # (registers occur in order when laid out in memory)

        if len(output_regs) == 2:
            # this is dumb, but let's add another one.
            # ghidra decompiles these a lot better and doesn't convert them to shorts
            # use "I", because nothing writes to it
            output_regs = output_regs + [coerce_to_reg('I')]

        fn.setReturn(create_multireg_struct(output_regs), VariableStorage(currentProgram, output_regs[::-1]), SourceType.USER_DEFINED)
        # fn.setReturn(byte_array(len(output_regs)), VariableStorage(currentProgram, output_regs[::-1]), SourceType.USER_DEFINED)
    
    fn.setCallingConvention('__stdcall')

def apply_function_inputs_outputs_to_the_real_thing(f):
    # for now, multiple outputs are a byte array.
    # should probably be a struct later.

    fn = getFunctionAt(f.addr)
    if not fn:
        raise Exception('What? How is there no function here? at {}'.format(f.addr))
    
    ins, outs = sorted_registers(f.input_regs), sorted_registers(f.output_regs)
    set_function_io(fn, ins, outs)
    fn.setComment('SMB:{}\nSignature: {} -> {}'.format(fn.getEntryPoint(), ins, outs))

def decompose_varnode_to_regs(varnode):
    '''Meant to convert 16-bit registers to 8-bit ones'''
    if not varnode.isRegister():
        return []
    
    reg = coerce_to_reg(varnode)
    regs = list(reg.getChildRegisters())
    if len(regs) > 0:
        return regs
    else:
        return [reg]

def process_block(callstack, block, visit_fn):
    pcodeops = block.pcodes

    readlist = []

    def flag_read(fresh):
        readlist.append(fresh)

    def clone_io():
        # block.inputs, block.outputs = block.cached_inputs, block.cached_outputs
        block.inputs, block.outputs, block.readlist = BlockPorts.deepclone_freshes_all([block.cached_inputs, block.cached_outputs], block.cached_readlist)

    if block.processed:
        # just clone the existing BlockPorts
        clone_io()
        return

    block.cached_inputs = BlockPorts()
    cur = block.cached_inputs.clone()

    def input_is_reg(op, n):
        return is_valid_reg(op.getInputs()[n])
    def output_is_reg(op):
        return is_valid_reg(op.getOutput())
    for op,paddr in pcodeops:
        mn = op.mnemonic
        if mn == 'COPY' and input_is_reg(op, 0) and output_is_reg(op):
            # if copying between two registers, treat it specially
            cur[op.getOutput()] = cur[op.getInputs()[0]]
        else:
            for varnode in op.getInputs():
                for v in decompose_varnode_to_regs(varnode):
                    if is_valid_reg(v):
                        flag_read(cur[v])
            outvarnode = op.getOutput()
            if outvarnode is not None:
                for v in decompose_varnode_to_regs(outvarnode):
                    if is_valid_reg(v):
                        cur[v] = Fresh()

        if mn == 'CALL':
            call_addr = parse_call_addr_from_pcodeop(paddr, op, 0)
            f = find_function_from_addr(call_addr)

            instr_addr = paddr[0]
            exclude_inputs, exclude_outputs = calls_register_exclusions.get(instr_addr, [[], []])

            exclude_inputs  = [coerce_to_reg(x) for x in exclude_inputs]
            exclude_outputs = [coerce_to_reg(x) for x in exclude_outputs]

            cur_f = cur.clone()
            for reg in exclude_inputs:
                cur_f[reg] = Fresh()
            
            cur_f, readlist_f = analyze_fn(callstack, f, cur_f, visit_fn)
            readlist += readlist_f

            for reg in exclude_outputs:
                cur_f[reg] = cur[reg]
            
            cur = cur_f

    block.cached_readlist = readlist
    block.cached_outputs = cur
    clone_io()
    block.processed = True


def analyze_fn(callstack, f, caller_cur, visit_fn):
    visit_fn(f, callstack[-1] if len(callstack) > 0 else None)
    # presolved functions are a way to prevent recursion issues, so it comes before the recursion check
    if len(callstack) > 0:
        if f.presolved:
            print('# NOTE: encountered presolved function: {}'.format(f))
            fnoutputs = caller_cur.clone()
            for reg in f.output_regs:
                fnoutputs[reg] = Fresh(fnoutput=f, reg=reg)
            readlist = []
            for reg in f.input_regs:
                fresh = Fresh()
                caller_cur[reg].link(fresh)
                readlist.append(fresh)
            return fnoutputs, readlist

    if f in callstack:
        print('# WARNING: recursion detected at {}! {}'.format(f, callstack + [f]))
        print('# Analysis can no longer be assumed valid. You need to fix this by presolving a function in the recursion cycle!')
        print('# Assuming no in/outs for function {}'.format(f))
        return caller_cur.clone(), []

    callstack = callstack + [f]

    blocks = f.blocks
    entrypoint_block = f.entrypoint_block

    readlist = []

    for block in blocks:
        process_block(callstack, block, visit_fn)
        readlist += block.readlist

    for block in blocks:
        for nextblock in block.dest_blocks():
            block.outputs.link(nextblock.inputs)
    
    fninputs  = BlockPorts(fninput=f)
    fnoutputs = BlockPorts(fnoutput=f)

    for block in blocks:
        if block.is_terminating():
            block.outputs.link(fnoutputs)

    fninputs.link(entrypoint_block.inputs)

    fnoutputs, readlist = BlockPorts.simplify_all(fninputs, fnoutputs, readlist)

    for reg,fresh in list(fnoutputs):
        roots = fresh.get_roots()
        if roots == set([fninputs[reg]]):
            # yup, a passthru
            fnoutputs[reg] = caller_cur[reg]
    
    caller_cur.link(fninputs)

    return fnoutputs, readlist

def analyze_start(f):
    print('# Analyze start: 0x{}'.format(f.addr))

    inputs = BlockPorts()
    cur = inputs.clone()
    visited_fns = set()
    def visit_fn(f, caller_f):
        if log_call_trees:
            if caller_f:
                print('calls(0x{}, 0x{})'.format(caller_f.addr, f.addr))
            tags = [str(x.name) for x in getFunctionAt(f.addr).getTags()]
            if tags:
                print('tags(0x{}, {})'.format(f.addr, tags))
        visited_fns.add(f)
    cur,readlist = analyze_fn([], f, cur, visit_fn)
    for reg in f.output_regs:
        readlist.append(cur[reg])
    
    ins,outs = Fresh.get_fn_inputs_and_outputs(readlist)

    ins_m = {}
    outs_m = {}

    for f,r in ins:
        s = ins_m.get(f, set())
        ins_m[f] = s
        s.add(r)
    for f,r in outs:
        s = outs_m.get(f, set())
        outs_m[f] = s
        s.add(r)
    

    for f in sorted(set(ins_m.keys()).union(set(outs_m.keys()))):
        i = sorted_registers(ins_m.get(f, []))
        o = sorted_registers(outs_m.get(f, []))
        for r in i:
            f.add_input_reg(r)
        for r in o:
            f.add_output_reg(r)
        print('function_io(0x{}, {}, {})'.format(f.addr, [str(x) for x in i], [str(x) for x in o]))
    
    def chunks(xs, n):
        n = max(1, n)
        return (xs[i:i+n] for i in range(0, len(xs), n))
    for vf in chunks(sorted(['0x' + str(f.addr) for f in visited_fns]), 32):
        print('visited_functions([{}])'.format(', '.join(vf)))

    return visited_fns


for addr in functions_to_analyze:
    visited_fns = set()
    f = find_function_from_addr(toAddr(addr))
    visited_fns.update(analyze_start(f))
    if applyit:
        for f in visited_fns:
            apply_function_inputs_outputs_to_the_real_thing(f)
