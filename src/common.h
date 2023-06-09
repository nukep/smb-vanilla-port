void Reset();
void NMI();

void UpdateScreen(const byte*);
void WriteNTAddr(byte);
byte InitializeMemory(byte);
void ReadJoypads();
void ReadPortBits(byte joynum);

void SoundEngine() {
    // Stubbed out for now
    // Sound code is horrifying, so we're dealing with it later
}

static inline void dectimer(byte& timer) {
    if (timer != 0) {
        timer--;
    }
}

static inline void dectimers() {
    if (TimerControl >= 2) {
        TimerControl -= 1;
    } else {
        // If TimerControl is 0 or 1...
        // decrement the timers.

        TimerControl = 0;

        // We unrolled a loop on the timers here
        // The NES version decrements in reverse order as listed here, but the order doesn't really matter

        dectimer(SelectTimer);      dectimer(PlayerAnimTimer);    dectimer(JumpSwimTimer);   dectimer(RunningTimer);
        dectimer(BlockBounceTimer); dectimer(SideCollisionTimer); dectimer(JumpspringTimer); dectimer(GameTimerCtrlTimer);
        dectimer(ClimbSideTimer);
        for (int i = 0; i < 5; i++) {
            dectimer(EnemyFrameTimer[i]);
        }
        dectimer(FrenzyEnemyTimer); dectimer(BowserFireBreathTimer); dectimer(StompTimer); dectimer(AirBubbleTimer);
        dectimer(UnusedTimer1);     dectimer(UnusedTimer2);
        // up to and including the timer at $0794

        IntervalTimerControl -= 1;
        if (IntervalTimerControl >= 0x80) {
            IntervalTimerControl = 20;
            dectimer(ScrollIntervalTimer);
            for (int i = 0; i < 7; i++) {
                dectimer(EnemyIntervalTimer[i]);
            }
            dectimer(BrickCoinTimer); dectimer(InjuryTimer); dectimer(StarInvincibleTimer); dectimer(ScreenTimer);
            dectimer(WorldEndTimer);  dectimer(DemoTimer);   dectimer(UnusedTimer3);
            // up to and including the timer at $07A3
        }
    }
}


// This is the only subroutine in all of SMB that writes to the PPU! (aside from WriteNTAddr, which blanks a nametable)
// Each draw buffer item has the format: <ppu_hi> <ppu_lo> <count> <data...>
// 
// SMB:8edd, SM2MAIN:6d56
// Signature: [r00, r01] -> []
void UpdateScreen(const byte* buf) {
    while (buf[0] != 0) {
        // Start writing to the PPU address
        ppustatus();
        ppuaddr(buf[0]);
        ppuaddr(buf[1]);

        if (buf[2] & 0x80) {
            // Draw vertically
            Mirror_PPU_CTRL_REG1 |= 0x04;
        } else {
            // Draw horizontally
            Mirror_PPU_CTRL_REG1 &= ~0x04;
        }
        ppuctrl(Mirror_PPU_CTRL_REG1);

        int count = buf[2] & 0x3F;
        if (count == 0) {
            // The original SMB does a do-while loop, and so a count of 0 is actually 256
            count = 256;
        }

        if (buf[2] & 0x40) {
            // Run-length encoding
            for (int i = 0; i < count; i++) {
                ppudata(buf[3]);
            }
            buf += 3 + 1;
        } else {
            // Variable-length
            for (int i = 0; i < count; i++) {
                ppudata(buf[3 + i]);
            }
            buf += 3 + count;
        }

        // The original SMB does these extra, seemingly pointless assignments to the ppuaddr register
        ppuaddr(0x3f);
        ppuaddr(0);
        ppuaddr(0);
        ppuaddr(0);
    }
    ppustatus();
    ppuscroll(0);
    ppuscroll(0);
}

// SMB:8e2d, SM2MAIN:6ca6
// Signature: [A] -> []
void WriteNTAddr(byte ppu_page) {
    ppuaddr(ppu_page);
    ppuaddr(0);

    // Fill the nametable with blank tiles
    for (int i = 0; i < 0x3C0; i++) {
        ppudata(0x24);
    }
    // ... and clear the colors of all metatiles to the first palette
    for (int i = 0; i < 0x40; i++) {
        ppudata(0x00);
    }

    VRAM_Buffer1_Offset = 0;
    VRAM_Buffer1[0] = 0;
    HorizontalScroll = 0;
    VerticalScroll = 0;
    ppuscroll(0);
    ppuscroll(0);
    return;
}

// SMB:8e5c, SM2MAIN:6cd5
// Signature: [] -> []
void ReadJoypads() {
    joystick_strobe(1);
    joystick_strobe(0);
    ReadPortBits(0);
    ReadPortBits(1);
}


// SMB:8e6a, SM2MAIN:6ce3
// Signature: [X] -> []
void ReadPortBits(byte joynum) {
    byte bits = 0;

    struct SMB_buttons buttons = {0};

    if (joynum == 0) {
        joy1(&buttons);
    } else {
        joy2(&buttons);
    }

    bits |= buttons.a       ?0x80:0;
    bits |= buttons.b       ?0x40:0;
    bits |= buttons.select  ?0x20:0;
    bits |= buttons.start   ?0x10:0;
    bits |= buttons.u       ?0x08:0;
    bits |= buttons.d       ?0x04:0;
    bits |= buttons.l       ?0x02:0;
    bits |= buttons.r       ?0x01:0;

    SavedJoypadBits[joynum] = bits;

    // If Select or Start were pressed last time this was called, then "unpress" them.
    if ((bits & (0x20 | 0x10) & JoypadBitMask[joynum]) != 0) {
        SavedJoypadBits[joynum] = bits & ~(0x20 | 0x10);
    } else {
        JoypadBitMask[joynum] = bits;
    }
}