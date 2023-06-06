-- record the controller inputs at the start of each nmi call
-- this is the way to provide movies to our port
-- we can't simply use fc2 movie files, because they don't describe lag frames.
-- our vanilla port doesn't have lag frames (this is usually a feature, but it's a real problem when importing fc2 files)
-- as a bonus, this also records the RAM before each nmi so we can do fun things like regression tests

-- Instructions:
-- 1. Load a movie into FCEUX with the game loaded. The game should be paused on the first frame.
-- 2. Load this script (File -> Lua -> New Lua Script Window)
-- 3. Unpause the game.
-- 4. Watch the playthrough, then pause when it's done. Stop the script.
-- 5. You have two new files!

GAME = 'SMB1'
-- GAME = 'SMB2J'

file = io.open("movie-buttons.txt", "w")
fileram = io.open("movie-ram.bin", "wb")
io.output(file)

function write_button(chr, v)
    if v then
        io.write(chr)
    else
        io.write('.')
    end;
end;
function write_zeros(n)
    fileram:write(string.rep("\0", n));
end

-- called at the beginning of NMI
function on_nmi()
    buttons = joypad.get(1);

    write_button("U", buttons.up);
    write_button("D", buttons.down);
    write_button("L", buttons.left);
    write_button("R", buttons.right);
    write_button("B", buttons.B);
    write_button("A", buttons.A);
    write_button("S", buttons.select);
    write_button("T", buttons.start);
    io.write('\n');

    rambytes = memory.readbyterange(0, 0x800);
    -- zero out $00-$07 (internal temporary "registers")
    write_zeros(8);
    fileram:write(rambytes:sub(0x0008+1,0x160));
    -- and $160-$1FF (stack).
    write_zeros(0x200-0x160);
    fileram:write(rambytes:sub(0x0200+1,0x800));
end;

emu.speedmode("turbo");
if GAME == 'SMB1' then
    memory.registerexecute(0x8082, on_nmi);
else
    memory.registerexecute(0x60a0, on_nmi);
end;

while (true) do
  emu.frameadvance();
end;