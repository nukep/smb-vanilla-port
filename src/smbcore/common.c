#include "ctx.h"

#include <string.h>


void sync_data(void) {
  // The engine defines some internal data structures
  // Synchronize them by reading the game RAM

  AreaData  = rom_ptr(LOAD_16(AreaData_addr_hi, AreaData_addr_lo));
  EnemyData = rom_ptr(LOAD_16(EnemyData_addr_hi, EnemyData_addr_lo));
  MusicData = rom_ptr(LOAD_16(MusicData_addr_hi, MusicData_addr_lo));
  PatchCurrentPlayer = CurrentPlayer;
}


// Custom feature for this port :)
void set_world_and_level(u8 world, u8 level) {
  // This hack only works in SMB1 right now
  // TODO: implement for SMB2J

#ifdef SMB1_MODE
  WorldNumber = world;
  LevelNumber = level;

  u8 off = 0;
  for (int i = 0; i < level; i++) {
    // skip "intermission" areas
    if (AreaAddrOffsets[WorldAddrOffsets[world] + off] == 0x29) {
      off += 1;
    }
    off += 1;
  }
  AreaNumber = off;
#endif
}



// Set 0's in memory.
// The provided number is up to which address in the $0700 page to set to zero.
// e.g. if i=0x14, then clear up to $0714 inclusive.
// Doesn't set the stack, between $0160 and $01FF inclusive.
// On SMB2J, doesn't set $0100 to $0108 inclusive.
// Note that this port, which doesn't target the 6502, doesn't use the stack at $0160-$1FFF at all.
//
// SMB:90cc
// SM2MAIN:6f08
// Signature: [Y] -> []
void InitializeMemory(u8 i) {
#ifdef SMB1_MODE
    memset(&RAM(0x000), 0, 0x160);
    memset(&RAM(0x200), 0, (usize)0x700 - 0x200);
    memset(&RAM(0x700), 0, (u8)(i + 1));
#endif
#ifdef SMB2J_MODE
    memset(&RAM(0x000), 0, 0x100);
    memset(&RAM(0x109), 0, (usize)0x160 - 0x109);
    memset(&RAM(0x200), 0, (usize)0x700 - 0x200);
    memset(&RAM(0x700), 0, (u8)(i + 1));
#endif

  // Note: the original sets register "A" to 0. some callers use it.
}

void dectimers(void) {

#define DECTIMER(x) if ((x) != 0) { (x)--; }

  if (TimerControl >= 2) {
    TimerControl -= 1;
  } else {
    // If TimerControl is 0 or 1...
    // decrement the timers.

    TimerControl = 0;

    // We unrolled a loop on the timers here
    // The NES version decrements in reverse order as listed here, but the order doesn't really matter


    DECTIMER(SelectTimer);
    DECTIMER(PlayerAnimTimer);
    DECTIMER(JumpSwimTimer);
    DECTIMER(RunningTimer);
    DECTIMER(BlockBounceTimer);
    DECTIMER(SideCollisionTimer);
    DECTIMER(JumpspringTimer);
    DECTIMER(GameTimerCtrlTimer);
    DECTIMER(ClimbSideTimer);
    for (int i = 0; i < 5; i++) {
      DECTIMER(EnemyFrameTimer[i]);
    }
    DECTIMER(FrenzyEnemyTimer);
    DECTIMER(BowserFireBreathTimer);
    DECTIMER(StompTimer);
    DECTIMER(AirBubbleTimer);
    DECTIMER(UnusedTimer1);
    DECTIMER(UnusedTimer2);
    // up to and including the timer at $0794

    IntervalTimerControl -= 1;
    if (IntervalTimerControl >= 0x80) {
      IntervalTimerControl = 20;
      DECTIMER(ScrollIntervalTimer);
      for (int i = 0; i < 7; i++) {
        DECTIMER(EnemyIntervalTimer[i]);
      }
      DECTIMER(BrickCoinTimer);
      DECTIMER(InjuryTimer);
      DECTIMER(StarInvincibleTimer);
      DECTIMER(ScreenTimer);
      DECTIMER(WorldEndTimer);
      DECTIMER(DemoTimer);
      DECTIMER(UnusedTimer3);
      // up to and including the timer at $07A3
    }
  }

#undef DECTIMER

}

// This is the only subroutine in all of SMB that writes to the PPU! (aside from WriteNTAddr, which blanks a nametable)
// Each draw buffer item has the format: <ppu_hi> <ppu_lo> <count> <data...>
//
// SMB:8edd
// SM2MAIN:6d56
void update_screen(const u8 *buf, const u16 buf_length) {
  // Original signature: [r00, r01] -> []
  // Added a maximum buffer length parameter, for memory safety

  u16 vram_idx = 0;

#define READ(var) { if (vram_idx >= buf_length) { return; } var = buf[vram_idx++]; }

  while (vram_idx < buf_length) {
    u8 ppuhi;
    u8 ppulo;
    u8 data_header;

    READ(ppuhi);
    READ(ppulo);
    READ(data_header);

    if (ppuhi == 0) {
      return;
    }

    // Start writing to the PPU address
    ppustatus();
    ppuaddr(ppuhi);
    ppuaddr(ppulo);

    if (data_header & DRAW_FLAG_VERTICAL) {
      // Draw vertically
      Mirror_PPU_CTRL_REG1 |= 0x04;
    } else {
      // Draw horizontally
      Mirror_PPU_CTRL_REG1 &= ~0x04;
    }
    ppuctrl(Mirror_PPU_CTRL_REG1);

    int count = data_header & 0x3F;
    if (count == 0) {
      // The original SMB does a do-while loop, and so a count of 0 is actually 256
      count = 256;
    }

    if (data_header & DRAW_FLAG_RLE) {
      // Run-length encoding

      u8 val;
      READ(val);
      for (int i = 0; i < count; i++) {
        ppudata(val);
      }
    } else {
      // Variable-length
      for (int i = 0; i < count; i++) {
        u8 val;
        READ(val);
        ppudata(val);
      }
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

#undef READ
}

// SMB:8e2d, SM2MAIN:6ca6
// Signature: [A] -> []
void WriteNTAddr(u8 ppu_page) {
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
void ReadJoypads(void) {
  // joystick_strobe(1);
  // joystick_strobe(0);
  ReadPortBits(0);
  ReadPortBits(1);
}

// SMB:8e6a, SM2MAIN:6ce3
// Signature: [X] -> []
void ReadPortBits(u8 joynum) {
  u8 bits = 0;

  struct SMB_buttons buttons = {0};

  if (joynum == 0) {
    joy1(&buttons);
  } else {
    joy2(&buttons);
  }

  bits |= buttons.a      ? BUTTON_A : 0;
  bits |= buttons.b      ? BUTTON_B : 0;
  bits |= buttons.select ? BUTTON_SELECT : 0;
  bits |= buttons.start  ? BUTTON_START : 0;
  bits |= buttons.u      ? BUTTON_U : 0;
  bits |= buttons.d      ? BUTTON_D : 0;
  bits |= buttons.l      ? BUTTON_L : 0;
  bits |= buttons.r      ? BUTTON_R : 0;

  SavedJoypadBits[joynum] = bits;

  // If Select or Start were pressed last time this was called, then "unpress" them.
  if ((bits & (BUTTON_SELECT | BUTTON_START) & JoypadBitMask[joynum]) != 0) {
    SavedJoypadBits[joynum] = bits & ~(BUTTON_SELECT | BUTTON_START);
  } else {
    JoypadBitMask[joynum] = bits;
  }
}

// SMB1 and SMB2J's Pseudo-Random Number Generator
//
// How it works, in plain language:
// The PRNG is a 56-bit string (7 * 8 bits) that's shifted to the right each iteration.
// A new bit is fed in from the left depending on the following:
//     If two specific bits in the string are equal, then the new bit is 0. Otherwise the new bit is 1.
//     (you can also interpret this as XORing the two bits to get the new bit).
//
// The seed value is A5 00 00 00 00 00 00.
//
// Example iterations:
//       >     a       b
// 61st: 00100010101101001111000110011000011110110100101110111101  (a=1, b=0. new bit for 62 is 1)
// 62nd: 10010001010110100111100011001100001111011010010111011110  (a=0, b=1. new bit for 63 is 1)
// 63rd: 11001000101011010011110001100110000111101101001011101111  (a=0, b=0. new bit for 64 is 0)
// 64th: 01100100010101101001111000110011000011110110100101110111  (a=0, b=1. new bit for 65 is 1)
//
// For iteration 61, a=1 and b=0, which are not equal, so the new bit to be used for iteration 62 is 1.
//
// Fun fact: This PRNG has a period of 32767 iterations. The cycle starts at the 40th iteration.
// That's about 546.1 seconds or 9.1 minutes at 60fps!
// After which, it'll generate the same values on loop.
// 1st iteration (seed):       A5 00 00 00 00 00 00 (10100101000000000000000000000000000000000000000000000000)
// 40th and 32807th iteration: 33 0F 69 77 A5 4A 00 (00110011000011110110100101110111101001010100101000000000)
void update_prng(u8 *prng) {
  u8 a = prng[0] & 2;
  u8 b = prng[1] & 2;
  bool newbit = a != b;

  for (int i = 0; i < 7; i++) {
    bool next = (prng[i] & 1) != 0;
    prng[i] = (newbit ? 0x80 : 0x00) | (prng[i] >> 1);
    newbit = next;
  }
}


// SMB:8325
// SM2MAIN:c51b
// Signature: [] -> []
void DrawMushroomIcon(void) {
  // This is called DrawMenuCursor in the SMB2J disassembly.

#ifdef SMB1_MODE
  // NES note: Inlined MushroomIconData table, and the effective writes to the VRAM buffer.

  VRAM_Buffer1_Offset = 0;

  if (NumberOfPlayers == 0) {
    VRAM1_DRAW_VERTICAL(PPU_ADDR_NT0_XY(9, 18),
                        0xce, 0x24, 0x24);
  } else {
    VRAM1_DRAW_VERTICAL(PPU_ADDR_NT0_XY(9, 18),
                        0x24, 0x24, 0xce);
  }

  VRAM_Buffer1[VRAM_Buffer1_Offset++] = 0;
#endif
#ifdef SMB2J_MODE
  VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_MENUCURSORTEMPLATE;
  // Inlined: SetupMenuCursor
  MenuCursorTemplate[3] = MenuCursorTiles[CurrentPlayer];
  MenuCursorTemplate[5] = MenuCursorTiles[CurrentPlayer + 1];
#endif
}


static inline void GameMenuRoutine_ResetTitle() {
  OperMode = OM_TITLESCREEN;
  OperMode_Task = OMT_TITLESCREEN_START;

#ifdef SMB1_MODE
  Sprite0HitDetectFlag = 0;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag = 0;
#endif

  DisableScreenFlag += 1;
}

#ifdef SMB1_MODE
// SMB:830e
// Signature: [A] -> [X]
static inline u8 GoContinue(const u8 param_1) {
  WorldNumber = param_1;
  OffScr_WorldNumber = param_1;
  AreaNumber = 0;
  OffScr_AreaNumber = 0;
  return 0;
}
#endif

// SMB:8245
// SM2MAIN:c46e
// Signature: [] -> []
void GameMenuRoutine(void) {
#ifdef SMB1_MODE
  const u8 buttons = SavedJoypadBits[0] | SavedJoypadBits[1];
#endif
#ifdef SMB2J_MODE
  const u8 buttons = SavedJoypadBits[0];
#endif

  const bool button_a_pushed = (buttons & BUTTON_A) != 0;
  const bool button_select_pushed_only = buttons == BUTTON_SELECT;

#ifdef SMB1_MODE
  // Either just the Start button, or just the A + Start button.
  const bool button_activate = (buttons == BUTTON_START) || (buttons == (BUTTON_A | BUTTON_START));
#endif
#ifdef SMB2J_MODE
  // The Start button, with other buttons possibly pushed.
  const bool button_activate = (buttons & BUTTON_START) != 0;;
#endif

  // NES note: This port inverts the comparison order of DemoTimer and the button pushes.
  // (in the orignal NES versions, the button presses are checked first, then DemoTimer).
  // IMO this is easier to understand.

  // if the demo is running...
  if (DemoTimer == 0) {
    if (button_activate) {
      // then reset to the title
#ifdef SMB2J_MODE
      CompletedWorlds = 0;
      DiskIOTask = 0;
      HardWorldFlag = ((GamesBeatenCount >= 8) && button_a_pushed) ? 1 : 0;
#endif
      GameMenuRoutine_ResetTitle();
      return;
    }

    if (button_select_pushed_only) {
      // then reset to the title
      GameMenuRoutine_ResetTitle();
      return;
    }

    // not really sure why this is done. seems pointless
    SelectTimer = buttons;

    if (DemoEngine()) {
      // when the demo is finished, then reset to the title
      GameMenuRoutine_ResetTitle();
      return;
    }

    GameCoreRoutine();
    if (GameEngineSubroutine == GR_PLAYERLOSELIFE) {
      GameMenuRoutine_ResetTitle();
    }
    return;
  }

  // demo is not running

  if (button_activate) {
    // Let'sa go!
    // (start the game)

#ifdef SMB1_MODE
    if (button_a_pushed) {
      GoContinue(ContinueWorld);
    }
    LoadAreaPointer();
    Hidden1UpFlag += 1;
    OffScr_Hidden1UpFlag += 1;
    FetchNewGameTimerFlag += 1;

    expect(OperMode == OM_TITLESCREEN);
    OperMode = OM_GAME;
    OperMode_Task = OMT_GAME_INITIALIZEAREA;

    PrimaryHardMode = WorldSelectEnableFlag;
    DemoTimer = 0;
    for (int i = 0; i < 12*2; i++) {
      DisplayDigits[i + 6] = 0;
    }
#endif
#ifdef SMB2J_MODE
    CompletedWorlds = 0;
    DiskIOTask = 0;
    HardWorldFlag = ((GamesBeatenCount >= 8) && button_a_pushed) ? 1 : 0;

    expect(OperMode == OM_TITLESCREEN);
    expect(OperMode_Task == OMT_TITLESCREEN_GAMEMENUROUTINE);
    OperMode_Task = OMT_TITLESCREEN_HARDWORLDSCHECKPOINT;

    PatchPlayerNamePal();
    WorldNumber = 0;
    LevelNumber = 0;
    AreaNumber = 0;
    for (int i = 0; i < 12; i++) {
      DisplayDigits[i + 6] = 0;
    }
#endif
    return;
  }

  if (button_select_pushed_only) {
    DemoTimer = 0x18;
#ifdef SMB2J_MODE
    FrameCounter &= 0xfe;
#endif
    if (SelectTimer == 0) {
      SelectTimer = 0x10;
#ifdef SMB1_MODE
      NumberOfPlayers ^= 1;
#endif
#ifdef SMB2J_MODE
      CurrentPlayer ^= 1;
#endif
      DrawMushroomIcon();
    }
  }

#ifdef SMB1_MODE
  if ((buttons == BUTTON_B) && (WorldSelectEnableFlag != 0)) {
    DemoTimer = 0x18;
    if (SelectTimer == 0) {
      SelectTimer = 0x10;
      WorldSelectNumber = (WorldSelectNumber + 1) & 7;
      GoContinue(WorldSelectNumber);

      VRAM_Buffer1_Offset = 0;

      // Draw digit for the world number
      VRAM1_DRAW(PPU_ADDR_NT0_XY(19, 3),
                 WorldNumber + 1);
    }
  }
#endif

  SavedJoypadBits[0] = 0;

  GameCoreRoutine();
  if (GameEngineSubroutine == GR_PLAYERLOSELIFE) {
    GameMenuRoutine_ResetTitle();
  }
}


// SMB:8182
// SM2MAIN:61e9
// Signature: [] -> []
void PauseRoutine(void) {
  if ((OperMode == OM_VICTORY) || ((OperMode == OM_GAME && (OperMode_Task == OMT_GAME_GAMECOREROUTINE)))) {
    if (GamePauseTimer != 0) {
      GamePauseTimer -= 1;
      return;
    }
    if ((SavedJoypadBits[0] & BUTTON_START) == 0) {
      GamePauseStatus &= 0x7f;
    } else if ((GamePauseStatus & 0x80) == 0) {
      GamePauseTimer = 0x2b;
      PauseSoundQueue = GamePauseStatus + 1;
      GamePauseStatus = (GamePauseStatus ^ 1) | 0x80;
    }
  }
}


// SMB:81c6
// SM2MAIN:622d
// Signature: [] -> []
void SpriteShuffler(void) {
  for (int j = 0; j < 15; j++) {
    const int i = 14 - j;

    if (SprDataOffset[i] >= 0x28) {
      int amount = (int)SprDataOffset[i] + (int)SprShuffleAmt[SprShuffleAmtOffset];
      if (amount >= 256) {
        amount = (amount % 256) + 40;
      }
      SprDataOffset[i] = (u8)amount;
    }
  }

  SprShuffleAmtOffset += 1;
  if (SprShuffleAmtOffset == 3) {
    SprShuffleAmtOffset = 0;
  }
  for (int i = 0; i < 3; i++) {
    FBall_SprDataOffset[i*3 + 2]     = Enemy_SprDataOffset[i + 4];
    FBall_SprDataOffset[i*3 + 2 + 1] = Enemy_SprDataOffset[i + 4] + 8;
    Misc_SprDataOffset[i*3 + 2]      = Enemy_SprDataOffset[i + 4] + 16;
  }
}


// SMB:8212
// SM2MAIN:6279
// Signature: [] -> []
void OperModeExecutionTree(void) {
  switch (OperMode) {
  case OM_TITLESCREEN:
    TitleScreenMode();
    return;

  case OM_GAME:
    GameMode();
    return;

  case OM_VICTORY:
    VictoryMode();
    return;

  case OM_GAMEOVER:
    GameOverMode();
    return;

  default:
    jmpengine_overflow(OperMode);
    return;
  }
}


// SMB:8220
// SM2MAIN:6287
// Signature: [] -> []
void MoveAllSpritesOffscreen(void) {
  for (int i = 0; i < 64; i++) {
    SPRITE_Y(0, i) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:8223
// SM2MAIN:628a
// Signature: [] -> []
void MoveSpritesOffscreen(void) {
  for (int i = 1; i < 64; i++) {
    SPRITE_Y(0, i) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:8231
// SM2MAIN:bfb0
// Signature: [] -> []
void TitleScreenMode(void) {
  // Note: In the SMB2J disassembly, this is called "AttractModeSubs".
  // We consolidated it into SMB1's "TitleScreenMode" for clarity.

  switch (OperMode_Task) {
  case OMT_TITLESCREEN_INITIALIZEGAME:
    InitializeGame();
    expect(OperMode == OM_TITLESCREEN);
    OperMode_Task = OMT_TITLESCREEN_SCREENROUTINES;
    return;

  case OMT_TITLESCREEN_SCREENROUTINES:
    ScreenRoutines();
    return;

  case OMT_TITLESCREEN_PRIMARYGAMESETUP:
    PrimaryGameSetup();
    expect(OperMode == OM_TITLESCREEN);
    OperMode_Task = OMT_TITLESCREEN_GAMEMENUROUTINE;
    return;

  case OMT_TITLESCREEN_GAMEMENUROUTINE:
    GameMenuRoutine();
    return;

#ifdef SMB2J_MODE
  case OMT_TITLESCREEN_ATTRACTMODEDISKROUTINES:
    AttractModeDiskRoutines();
    return;

  case OMT_TITLESCREEN_HARDWORLDSCHECKPOINT:
    HardWorldsCheckpoint();
    return;
#endif

  default:
    jmpengine_overflow(OperMode_Task);
  }
}


// SMB:836b
// SM2MAIN:c553
// Signature: [] -> [C]
bool DemoEngine(void) {
  if (DemoActionTimer == 0) {
    DemoActionTimer = DemoTimingData[DemoAction];
    DemoAction += 1;
    if (DemoActionTimer == 0) {
      return true;
    }
  }
  DemoActionTimer -= 1;
  SavedJoypadBits[0] = DemoActionData[DemoAction - 1];
  return false;
}

// SMB:838b
// SM2MAIN:6298
// Signature: [] -> []
void VictoryMode(void) {
  expect(OperMode == OM_VICTORY);
  VictoryModeSubroutines();
  if (OperMode_Task != OMT_VICTORY_BRIDGECOLLAPSE) {
#ifdef SMB2J_MODE
    if (WorldNumber == 7) {
      if (OperMode_Task == OMT_VICTORY_W8SMB2J_VICTORYMODEDISKROUTINES) {
        return;
      }
      if (OperMode_Task == OMT_VICTORY_W8SMB2J_ENDINGDISKROUTINES) {
        return;
      }
    }
#endif
    EnemiesAndLoopsCore(0);
  }
  RelativePlayerPosition();
  PlayerGfxHandler();
}


// SMB:83a0
// SM2MAIN:62bc
// Signature: [] -> []
void VictoryModeSubroutines(void) {
#ifdef SMB2J_MODE
  if (WorldNumber == 7) {
    jumptable_VictoryModeSubroutines_forW8(OperMode_Task);
    return;
  }
#endif

  switch (OperMode_Task) {
  case OMT_VICTORY_BRIDGECOLLAPSE:
    BridgeCollapse();
    return;

  case OMT_VICTORY_SETUPVICTORYMODE:
    SetupVictoryMode();
    return;

  case OMT_VICTORY_PLAYERVICTORYWALK:
    PlayerVictoryWalk();
    return;

  case OMT_VICTORY_PRINTVICTORYMESSAGES:
    PrintVictoryMessages();
    return;

  case OMT_VICTORY_PLAYERENDWORLD:
    PlayerEndWorld();
    return;

#ifdef SMB2J_MODE
  case OMT_VICTORY_ENDCASTLEAWARD:
    EndCastleAward();
    return;
#endif

  default:
    jmpengine_overflow(OperMode_Task);
  }
}


// SMB:83b0
// SM2MAIN:62ff
// Signature: [] -> []
void SetupVictoryMode(void) {
  VictoryDestPageLoc = ScreenRight_PageLoc + 1;
  #ifdef SMB2J_MODE
    CompletedWorlds |= 1 << WorldNumber;
    if ((HardWorldFlag != 0) && (WorldNumber > 2)) {
      WorldNumber = 7;
    }
  #endif
  EventMusicQueue = MUSIC_EVENT_BOWSERVICTORY;

  expect(OperMode_Task == OMT_VICTORY_SETUPVICTORYMODE);
  OperMode_Task = OMT_VICTORY_PLAYERVICTORYWALK;
}


// SMB:83bd
// SM2MAIN:6334
// Signature: [] -> []
void PlayerVictoryWalk(void) {
  if ((Player_PageLoc == VictoryDestPageLoc) && (Player_X_Position >= 0x60)) {
    // Stop walking
    VictoryWalkControl = 0;
    AutoControlPlayer(0);
  } else {
    // Keep going right
    VictoryWalkControl = 1;
    AutoControlPlayer(1);
  }

  if (ScreenLeft_PageLoc != VictoryDestPageLoc) {
    const bool bVar1 = ScrollFractional >= 0x80;
    ScrollFractional += 0x80;
    ScrollScreen(bVar1 + 1);
    UpdScrollVar();
    VictoryWalkControl += 1;
  }
  if (VictoryWalkControl == 0) {
    expect(OperMode == OM_VICTORY);
    expect(OperMode_Task == OMT_VICTORY_PLAYERVICTORYWALK);
    OperMode_Task = OMT_VICTORY_PRINTVICTORYMESSAGES;
  }
}


// SMB:8461
// SM2MAIN:63d2
// Signature: [] -> []
void PlayerEndWorld(void) {
  // For SMB2J, only used for worlds 1 thru 7
  if (WorldEndTimer == 0) {
    if (SMB1_ONLY && WorldNumber >= 7) {
      if (((SavedJoypadBits[0] | SavedJoypadBits[1]) & BUTTON_B) != 0) {
        WorldSelectEnableFlag = 1;
        NumberofLives = 0xff;
        TerminateGame();
      }
      return;
    }
    AreaNumber = 0;
    LevelNumber = 0;
    WorldNumber += 1;
    if (SMB2J_ONLY && WorldNumber >= 8) {
      WorldNumber = 8;
    }
    LoadAreaPointer();
    FetchNewGameTimerFlag += 1;
    OperMode = OM_GAME;
    OperMode_Task = OMT_GAME_START;
  }
}


// SMB:84c3
// SM2MAIN:6421
// Signature: [X] -> []
void FloateyNumbersRoutine(const u8 objoff) {
  if (FloateyNum_Control[objoff] == 0) {
    return;
  }

  u8 bVar2 = FloateyNum_Control[objoff];
  if (bVar2 >= 0xb) {
    bVar2 = 0xb;
  }
  FloateyNum_Control[objoff] = bVar2;

  const u8 timer = FloateyNum_Timer[objoff];
  if (timer == 0) {
    FloateyNum_Control[objoff] = 0;
    return;
  }
  FloateyNum_Timer[objoff] -= 1;

  if (timer == 0x2b) {
    if (bVar2 == 0xb) {
      NumberofLives += 1;
      Square2SoundQueue = SOUND_SQ2_1UP;
    }

    static const u8 digit_to_add_to[12] = { 15,4,4,4,4,4,3,3,3,3,3,0 };
    static const u8 add_by[12]          = { 15,1,2,4,5,8,1,2,4,5,8,0 };

    DigitModifier[digit_to_add_to[bVar2]] = add_by[bVar2];
    AddToScore();
  }

  const u8 enemy_id = Enemy_ID[objoff];

  bool cond = false;

  switch (enemy_id) {
  case A_GREEN_KOOPA:
  case A_RED_KOOPA_GREENLIKE:
  case A_BUZZY_BEETLE:
  case A_RED_KOOPA:
  case A_PIRANHA_PLANT_SMB2J:
  case A_GOOMBA:
  case A_BLOOBER:
  case A_BULLET_BILL:
    cond = Enemy_State[objoff] < 2;
    break;

  case A_HAMMER_BRO:
    cond = true;
    break;

  case A_CHEEPCHEEP_GRAY:
  case A_CHEEPCHEEP_RED:
  case A_PIRANHA_PLANT:
  case A_SPINY:
    cond = false;
    break;

  default:
    cond = true;
    break;
  }

  const u8 offset = cond ? Alt_SprDataOffset[BlockOffsetToggle] : Enemy_SprDataOffset[objoff];

  const u8 ypos = FloateyNum_Y_Pos[objoff];
  if (ypos >= 0x18) {
    FloateyNum_Y_Pos[objoff] -= 1;
  }

  // Inlined: DumpTwoSpr
  SPRITE_Y(offset, 0) = ypos - 9;
  SPRITE_Y(offset, 1) = ypos - 9;

  const u8 xpos = FloateyNum_X_Pos[objoff];
  SPRITE_X(offset, 0) = xpos;
  SPRITE_X(offset, 1) = xpos + 8;
  SPRITE_ATTR(offset, 0) = 2;
  SPRITE_ATTR(offset, 1) = 2;

  static const u8 tiles[24] = {
    0xff, 0xff, // dummy
    0xf6, 0xfb, //  "100"
    0xf7, 0xfb, //  "200"
    0xf8, 0xfb, //  "400"
    0xf9, 0xfb, //  "500"
    0xfa, 0xfb, //  "800"
    0xf6, 0x50, //  "1000"
    0xf7, 0x50, //  "2000"
    0xf8, 0x50, //  "4000"
    0xf9, 0x50, //  "5000"
    0xfa, 0x50, //  "8000"
    0xfd, 0xfe, //  "1-UP"
  };

  const u8 ctrl = FloateyNum_Control[objoff];
  SPRITE_TILE(offset, 0) = tiles[ctrl*2];
  SPRITE_TILE(offset, 1) = tiles[ctrl*2 + 1];
}


// SMB:8567
// SM2MAIN:64c5
// Signature: [] -> []
void ScreenRoutines(void) {
  switch (ScreenRoutineTask) {
  case SRT_INITSCREEN:
    InitScreen();
    ScreenRoutineTask = SRT_SETUPINTERMEDIATE;
    return;

  case SRT_SETUPINTERMEDIATE:
    SetupIntermediate();
    ScreenRoutineTask = SRT_WRITETOPSTATUSLINE;
    return;

  case SRT_WRITETOPSTATUSLINE:
    WriteGameText(0);
    ScreenRoutineTask = SRT_WRITEBOTTOMSTATUSLINE;
    return;

  case SRT_WRITEBOTTOMSTATUSLINE:
    WriteBottomStatusLine();
    ScreenRoutineTask = SRT_DISPLAYTIMEUP;
    return;

  case SRT_DISPLAYTIMEUP:
    if (GameTimerExpiredFlag != 0) {
      GameTimerExpiredFlag = 0;
      WriteGameText(2);
      // Inlined: ResetScreenTimer
      ScreenTimer = 7;
      ScreenRoutineTask = SRT_RESETSPRITESANDSCREENTIMER_1;
      DisableScreenFlag = 0;
    } else {
      ScreenRoutineTask = SRT_DISPLAYINTERMEDIATE;
    }
    return;

  case SRT_RESETSPRITESANDSCREENTIMER_1:
    if (ScreenTimer == 0) {
      MoveAllSpritesOffscreen();
      // Inlined: ResetScreenTimer
      ScreenTimer = 7;
      ScreenRoutineTask = SRT_DISPLAYINTERMEDIATE;
    }
    return;

  case SRT_DISPLAYINTERMEDIATE:
    DisplayIntermediate();
    return;

  case SRT_RESETSPRITESANDSCREENTIMER_2:
    if (ScreenTimer == 0) {
      MoveAllSpritesOffscreen();
      // Inlined: ResetScreenTimer
      ScreenTimer = 7;
      ScreenRoutineTask = SRT_AREAPARSERTASKCONTROL;
    }
    return;

  case SRT_AREAPARSERTASKCONTROL:
    DisableScreenFlag += 1;
    do {
      AreaParserTaskHandler();
    } while (AreaParserTaskNum != 0);
    ColumnSets -= 1;
    if (ColumnSets >= 0x80) {
      ScreenRoutineTask = SRT_GETAREAPALETTE;
    }
    VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER2;
    return;

  case SRT_GETAREAPALETTE:
    GetAreaPalette();
    ScreenRoutineTask = SRT_GETBACKGROUNDCOLOR;
    return;

  case SRT_GETBACKGROUNDCOLOR:
    GetBackgroundColor();
    ScreenRoutineTask = SRT_GETALTERNATEPALETTE1;
    return;

  case SRT_GETALTERNATEPALETTE1:
    if (AreaStyle == 1) {
      VRAM_Buffer_AddrCtrl = ADDRCTRL_MUSHROOMPALETTEDATA;
    }
    ScreenRoutineTask = SRT_DRAWTITLESCREEN;
    return;

  case SRT_DRAWTITLESCREEN:
    if (OperMode == OM_TITLESCREEN) {
#ifdef SMB1_MODE
      // The drawing data for the title screen is stored in CHR ROM!
      for (int i = 0; i < 0x13A; i++) {
        VRAM_SMB1_TitleScreen[i] = CHRROM(0x1EC0 + i);
      }
      VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB1_VRAM_PAGE;
#endif
#ifdef SMB2J_MODE
      VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_TITLESCREENGFXDATA;
#endif
      ScreenRoutineTask = SRT_CLEARBUFFERSDRAWICON;
    } else {
      expect(OperMode == OM_GAME);
      expect(OperMode_Task == OMT_GAME_SCREENROUTINES);
      OperMode_Task = OMT_GAME_SECONDARYGAMESETUP;
    }
    return;

  case SRT_CLEARBUFFERSDRAWICON:
    if (OperMode != OM_TITLESCREEN) {
      unreachable();

      // Note: The original game increments the opermode task on non-titlescreen opermodes.
      // However, it seems to never be encountered
      // OperMode_Task += 1;
    }

    // NES note: Zeros out pages $0300 and $0400
    for (int i = 0; i < 256; i++) {
      VRAM_Page[i] = 0;
      Objects_Page[i] = 0;
    }
    DrawMushroomIcon();
    ScreenRoutineTask = SRT_WRITETOPSCORE;
    return;

  case SRT_WRITETOPSCORE:
    expect(OperMode == OM_TITLESCREEN);
    expect(OperMode_Task == OMT_TITLESCREEN_SCREENROUTINES);
    WriteDigits(0xfa);
    OperMode_Task = OMT_TITLESCREEN_PRIMARYGAMESETUP;
    return;

#ifdef SMB2J_MODE
  case SRT_DEMORESET:
    DemoTimer = 0x18;
    LoadAreaPointer();
    InitializeArea();

    // TODO: figure out for sure which opermode this is in
    switch (OperMode) {
    case OM_TITLESCREEN: OperMode_Task = OMT_TITLESCREEN_PRIMARYGAMESETUP; break;
    case OM_GAME: OperMode_Task = OMT_GAME_SECONDARYGAMESETUP; break;
    case OM_GAMEOVER: OperMode_Task = OMT_GAMEOVER_RUNGAMEOVER; break;
    default: unreachable(); break;
    }
    return;
#endif

  default:
    jmpengine_overflow(ScreenRoutineTask);
  }
}


// SMB:858b
// SM2MAIN:64eb
// Signature: [] -> []
void InitScreen(void) {
  MoveAllSpritesOffscreen();
  InitializeNameTables();
  if (OperMode != OM_TITLESCREEN) {
    VRAM_Buffer_AddrCtrl = ADDRCTRL_UNDERGROUNDPALETTEDATA;
  }
  // Note: Moved ScreenRoutineTask increment to caller
}


// SMB:859b
// SM2MAIN:64fb
// Signature: [] -> []
void SetupIntermediate(void) {
  const u8 bVar1 = PlayerStatus;
  const u8 bStack0000 = BackgroundColorCtrl;
  PlayerStatus = PLAYERSTATUS_SMALL;
  BackgroundColorCtrl = 2;
  GetPlayerColors();
  PlayerStatus = bVar1;
  BackgroundColorCtrl = bStack0000;
  // Note: Moved ScreenRoutineTask increment to caller
}


// SMB:85bf
// SM2MAIN:651f
// Signature: [] -> []
void GetAreaPalette(void) {
  switch (AreaType) {
  case AREA_WATER:       VRAM_Buffer_AddrCtrl = ADDRCTRL_WATERPALETTEDATA; break;
  case AREA_GROUND:      VRAM_Buffer_AddrCtrl = ADDRCTRL_GROUNDPALETTEDATA; break;
  case AREA_UNDERGROUND: VRAM_Buffer_AddrCtrl = ADDRCTRL_UNDERGROUNDPALETTEDATA; break;
  case AREA_CASTLE:      VRAM_Buffer_AddrCtrl = ADDRCTRL_CASTLEPALETTEDATA; break;
  default: unreachable(); break;
  }

  // Note: Moved ScreenRoutineTask increment to caller
}


// SMB:85e3
// SM2MAIN:653f
// Signature: [] -> []
void GetBackgroundColor(void) {
  if (BackgroundColorCtrl != 0) {
    expect(BackgroundColorCtrl >= 4 && BackgroundColorCtrl < 8);

    u8 addrctrl;

    switch (BackgroundColorCtrl) {
    case 4: addrctrl = ADDRCTRL_VRAM_BUFFER1; break;
    case 5: addrctrl = ADDRCTRL_DAYSNOWPALETTEDATA; break;
    case 6: addrctrl = ADDRCTRL_NIGHTSNOWPALETTEDATA; break;
    case 7: addrctrl = ADDRCTRL_CASTLEPALETTEDATA; break;
    }

    VRAM_Buffer_AddrCtrl = addrctrl;
  }

  // Note: Moved ScreenRoutineTask increment to caller
  GetPlayerColors();
}


// SMB:85f1
// SM2MAIN:654d
// Signature: [] -> []
void GetPlayerColors(void) {
  static const u8 BackgroundColors[] = {
    0x22, 0x22, 0x0f, 0x0f, // used by area type if bg color ctrl not set,
    0x0f, 0x22, 0x0f, 0x0f, // used by background color control if set,
  };

  // Note: The original SMB2J has slightly different lookups here, because
  // the PlayerColors table would be overwritten depending on if Mario or Luigi was playing.
  // This has been unified to check the current player, which more closely resembles how SMB1 does it.

  // PatchCurrentPlayer captures what the value of CurrentPlayer was when PatchPlayerNamePal was called.
  // We currently have to do it this way in SMB2J, otherwise this may fail RAM tests.
  // This is demonstrated in SMB2J:
  // - Frame 0: first frame
  // - Frame 28: press SELECT to select Luigi
  //   - updates CurrentPlayer
  //   - DOESN'T call PatchPlayerNamePal
  //   - calls GetPlayerColors
  //
  // Frame 28 is the earliest frame the player can press SELECT.
  // This issue doesn't happen if SELECT is pressed on frame 29.
#ifdef SMB1_MODE
  const bool mario = CurrentPlayer == 0;
#endif
#ifdef SMB2J_MODE
  const bool mario = PatchCurrentPlayer == 0;
#endif

  const u8 idx = BackgroundColorCtrl != 0 ? BackgroundColorCtrl : AreaType;
  const u8 bgpal = BackgroundColors[idx];

  u8 pal1;
  u8 pal2;
  u8 pal3;

  if (mario) {
    // Mario
    pal1 = 0x16; pal2 = 0x27; pal3 = 0x18;
  } else {
    // Luigi
    pal1 = 0x30; pal2 = 0x27; pal3 = 0x19;
  }

  if (PlayerStatus == PLAYERSTATUS_FIREFLOWER) {
    // Fire flower (both Mario and Luigi)
    pal1 = 0x37; pal2 = 0x27; pal3 = 0x16;
  }

  VRAM1_DRAW(PPU_ADDR_PALETTE_SPR(0, 0),
             bgpal, pal1, pal2, pal3);
}


// SMB:865a
// SM2MAIN:65af
// Signature: [] -> []
void WriteBottomStatusLine(void) {
  WriteScoreAndCoinTally();

#ifdef SMB1_MODE
  const u8 world_number_display = WorldNumber + 1;
#endif
#ifdef SMB2J_MODE
  // Inlined: GetWorldNumForDisplay
  const u8 world_number_display = HardWorldFlag == 0 ? WorldNumber + 1 : (WorldNumber & 3) + 10;
#endif

  const u8 level_number_display = LevelNumber + 1;

  VRAM1_DRAW(PPU_ADDR_NT0_XY(19, 3),
             world_number_display,
             0x28,
             level_number_display);

  // Note: Moved ScreenRoutineTask increment to caller
}


// SMB:86a8
// SM2MAIN:6617
// Signature: [] -> []
void DisplayIntermediate(void) {
  if (OperMode == OM_GAMEOVER) {

    expect(OperMode_Task == OMT_GAMEOVER_SCREENROUTINES);
#ifdef SMB1_MODE
    ScreenTimer = 0x12;
    WriteGameText(3);
    OperMode_Task = OMT_GAMEOVER_RUNGAMEOVER;
#endif
#ifdef SMB2J_MODE
    WriteGameText(3);
    if (WorldNumber != 8) {
      OperMode_Task = OMT_GAMEOVER_RUNGAMEOVER;
    } else {
      ScreenRoutineTask = SRT_DEMORESET;
    }
#endif

  } else if (OperMode == OM_TITLESCREEN) {

    expect(OperMode_Task == OMT_TITLESCREEN_SCREENROUTINES);
    ScreenRoutineTask = SRT_AREAPARSERTASKCONTROL;

  } else if (OperMode == OM_GAME) {

    expect(OperMode_Task == OMT_GAME_SCREENROUTINES);

    if (AltEntranceControl != 0 || (AreaType != AREA_CASTLE && DisableIntermediate != 0)) {
      ScreenRoutineTask = SRT_AREAPARSERTASKCONTROL;
      return;
    }

    DrawPlayer_Intermediate();
    WriteGameText(1);
    // Inlined: ResetScreenTimer
    ScreenTimer = 7;
    DisableScreenFlag = 0;

    ScreenRoutineTask = SRT_RESETSPRITESANDSCREENTIMER_2;

#ifdef SMB2J_MODE
    if (WorldNumber == 8) {
      ScreenRoutineTask = SRT_DEMORESET;
      DisableScreenFlag += 1;
    }

#endif
  } else {
    unreachable();
  }
}


// SMB:89e1
// SM2MAIN:68be
// Signature: [] -> []
void ColorRotation(void) {
  if ((FrameCounter & 7) != 0) {
    return;
  }

  if (VRAM_Buffer1_Offset > 0x30) {
    return;
  }

  static const u8 coin_palettes[6] = {
    0x27, 0x27, 0x27, 0x17, 0x07, 0x17
  };

  static const u8 palette_0[16] = { 0x0f, 0x0f, 0x0f, 0x0f, };
  static const u8 palette_2[16] = { 0x12, 0x17, 0x17, 0x17, };
  static const u8 palette_3[16] = { 0x0f, 0x0f, 0x1c, 0x00, };

  expect(ColorRotateOffset < 6);
  expect(is_areatype_valid(AreaType));

  // Rotate the second palette color in particular. This is the coin/block color.
  VRAM1_DRAW(PPU_ADDR_PALETTE_BG(3, 0),
             palette_0[AreaType],
             coin_palettes[ColorRotateOffset],
             palette_2[AreaType],
             palette_3[AreaType]);

  ColorRotateOffset += 1;

  if (ColorRotateOffset >= 6) {
    ColorRotateOffset = 0;
  }
}


// Draw a 2x2 block at the position at x,y, where x is 0 to 15, and y is 0 to 14.
// If nt = 0, then draw on the first nametable. Otherwise draw on the second.
static inline void draw_block_metatile(const u8 vramoff, const u8 blockgfxidx, const u8 x, const u8 y, const u8 nt) {
  const u16 nametable = nt == 0 ? 0x2000 : 0x2400;
  const u16 addr = nametable + (y*2*32) + x*2;

  static const u8 block_tiles[5][4] = {
    { 0x45, 0x45, 0x47, 0x47 },
    { 0x47, 0x47, 0x47, 0x47 },
    { 0x57, 0x58, 0x59, 0x5a },
    { 0x24, 0x24, 0x24, 0x24 },
    { 0x26, 0x26, 0x26, 0x26 }
  };

  VRAM_Page[vramoff + 0] = addr >> 8;
  VRAM_Page[vramoff + 1] = addr & 0xff;
  VRAM_Page[vramoff + 2] = 2;
  VRAM_Page[vramoff + 3] = block_tiles[blockgfxidx][0];
  VRAM_Page[vramoff + 4] = block_tiles[blockgfxidx][1];

  VRAM_Page[vramoff + 5] = addr >> 8;
  VRAM_Page[vramoff + 6] = (addr & 0xff) + 32;
  VRAM_Page[vramoff + 7] = 2;
  VRAM_Page[vramoff + 8] = block_tiles[blockgfxidx][2];
  VRAM_Page[vramoff + 9] = block_tiles[blockgfxidx][3];

  VRAM_Page[vramoff + 10] = 0;
}


// SMB:8a4d
// SM2MAIN:692a
void RemoveCoin_Axe(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06] -> []
  // Reworked to use metatile coordinates instead of pointer
  //
  // Replaces the coin or axe metatile with a blank one
  // The blank one is different if underwater
  const u8 blockgfxidx = AreaType != AREA_WATER ? 3 : 4;
  const u8 vramoff = 0x41;

  const u8 x  = mt_x % 16;
  const u8 y  = mt_y + MT_Y_TOP_MARGIN;
  const u8 nt = (mt_x & 0x10) == 0 ? 0 : 1;

  // Inlined: PutBlockMetatile
  draw_block_metatile(vramoff, blockgfxidx, x, y, nt);

  VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER2;
}


// SMB:8a61
// SM2MAIN:693e
void ReplaceBlockMetatile(const u8 param_1, const u8 param_2, const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [A, X, r02, r06] -> []
  // Reworked to use metatile coordinates instead of pointer

  WriteBlockMetatile(param_1, mt_x, mt_y);
  Block_ResidualCounter += 1;
  Block_RepFlag[param_2] = Block_RepFlag[param_2] - 1;
}


// SMB:8a6b
// SM2MAIN:6948
void DestroyBlockMetatile(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06] -> []
  // Reworked to use metatile coordinates instead of pointer

  WriteBlockMetatile(0, mt_x, mt_y);
}


// SMB:8a6d
// SM2MAIN:694a
void WriteBlockMetatile(const u8 param_1, const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [A, r02, r06] -> []
  // Reworked to use metatile coordinates instead of pointer

  u8 blockgfxidx;
  if (param_1 == 0) {
    blockgfxidx = 3;
  } else if (param_1 == MT_BRICK_2) {
    blockgfxidx = 0;
  } else if (param_1 == MT_BRICK) {
    blockgfxidx = 1;
  } else if (param_1 == MT_BRICK_2_COINS) {
    blockgfxidx = 0;
  } else if (param_1 == MT_BRICK_COINS) {
    blockgfxidx = 1;
  } else {
    blockgfxidx = 2;
  }

  const u8 vramoff = VRAM_Buffer1_Offset + 1;

  const u8 x  = mt_x % 16;
  const u8 y  = mt_y + MT_Y_TOP_MARGIN;
  const u8 nt = (mt_x & 0x10) == 0 ? 0 : 1;

  // Inlined: PutBlockMetatile
  draw_block_metatile(vramoff, blockgfxidx, x, y, nt);

  // Inlined: MoveVOffset
  VRAM_Buffer1_Offset += 10;
}


// SMB:8e19
// SM2MAIN:6c92
// Signature: [] -> []
void InitializeNameTables(void) {
  ppustatus();
  WritePPUReg1((Mirror_PPU_CTRL_REG1 & 0xf0) | 0x10);
  WriteNTAddr(0x24);
  WriteNTAddr(0x20);
}


// SMB:8eed
// SM2MAIN:6d66
// Signature: [A] -> []
void WritePPUReg1(const u8 param_1) {
  ppuctrl(param_1);
  Mirror_PPU_CTRL_REG1 = param_1;
}


// SMB:8f06
// SM2MAIN:6d79
// Signature: [A] -> []
void PrintStatusBarNumbers(const u8 param_1) {
  OutputNumbers(param_1);
  OutputNumbers(param_1 >> 4);
}


// SMB:8f11
// SM2MAIN:6d84
// Signature: [A] -> []
void OutputNumbers(const u8 param_1) {
  const u8 sbtype = (param_1 + 1) & 0xf;

  if (sbtype >= 6) {
    return;
  }

  // NES note: SMB2J bounds-checks for sbtype < 6, even though the lookups aren't that long anymore.
#ifdef SMB2J_MODE
  expect(sbtype < 4);
#endif

  //        SMB1  SMB2J
  // sbtype 0     0      Top score display on title screen
  // sbtype 1,2   1      Player score
  // sbtype 3,4   2      Coin tally
  // sbtype 5     3      Game timer

#ifdef SMB1_MODE
  static const u8 xpos[6] = { 16, 2, 2, 13, 13, 26 };
  static const u8 ypos[6] = { 23, 3, 3, 3, 3, 3 };
  static const u8 sbdata_length[6] = { 6, 6, 6, 2, 2, 3 };
#endif
#ifdef SMB2J_MODE
  static const u8 xpos[6] = { 15, 2, 13, 26 };
  static const u8 ypos[6] = { 23, 3, 3, 3 };
  static const u8 sbdata_length[4] = { 6, 6, 2, 3 };
#endif

  const u8 length = sbdata_length[sbtype];
  const u16 ppuaddr = PPU_ADDR_NT0_XY(xpos[sbtype], ypos[sbtype]);

  VRAM_Buffer1[VRAM_Buffer1_Offset + 0] = ppuaddr >> 8;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 1] = ppuaddr & 0xff;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 2] = length;

  static const u8 sboffset_lookup[6] = { 0x06, 0x0c, 0x12, 0x18, 0x1e, 0x24 };

  const u8 sboffset = sboffset_lookup[sbtype];

  for (int i = length; i > 0; i--) {
    VRAM_Buffer1[VRAM_Buffer1_Offset + 3] = DisplayDigits[sboffset - i];
    VRAM_Buffer1_Offset += 1;
  }

  VRAM_Buffer1[VRAM_Buffer1_Offset + 3] = 0;

  VRAM_Buffer1_Offset += 3;
}


// SMB:8f5f
// SM2MAIN:6dd2
// Signature: [Y] -> []
void DigitsMathRoutine(const u8 param_1) {
  // In SMB1 and SMB2J, DigitModifier is often accessed as DigitModifier-1.

  if (OperMode != OM_TITLESCREEN) {
    for (int i = 6; i >= 1; i--) {
      u8 bVar1 = DigitModifier_Minus1[i] + DisplayDigits[param_1 + i - 6];
      if (bVar1 < 0x80) {
        if (bVar1 >= 10) {
          bVar1 -= 10;
          DigitModifier_Minus1[i-1] += 1;
        }
        DisplayDigits[param_1 + i - 6] = bVar1;
      } else {
        DigitModifier_Minus1[i-1] -= 1;
        DisplayDigits[param_1 + i - 6] = 9;
      }
    }
  }

  // Zero out DigitModifier_Minus1

  for (int i = 0; i <= 6; i++) {
    DigitModifier_Minus1[i] = 0;
  }
}


// SMB:8f97
// SM2MAIN:6e08
// Signature: [] -> []
void UpdateTopScore(void) {
  TopScoreCheck(5);
  if (SMB1_ONLY) {
    TopScoreCheck(11);
  }
}


// SMB:8f9e
// SM2MAIN:6e0a
// Signature: [X] -> []
void TopScoreCheck(const u8 last_digit_offset) {
  // last_digit_offset is 5 or 11

  // scan the digits from left to right
  for (int i = 0; i < 6; i++) {
      const u8 player_digit = DisplayDigits[i + last_digit_offset + 1];
      const u8 top_digit = DisplayDigits[i];
      if (player_digit < top_digit) {
          // definitely below than top score
          return;
      }
      if (player_digit > top_digit) {
          // definitely above top score
          break;
      }
  }

  // new (or equal) top score!
  for (int i = 0; i < 6; i++) {
    DisplayDigits[i] = DisplayDigits[i + last_digit_offset + 1];
  }
}


// SMB:8fcf
// SM2MAIN:c592
// Signature: [] -> []
void InitializeGame(void) {
#ifdef SMB2J_MODE
  CompletedWorlds = 0;
  HardWorldFlag = 0;
  CurrentPlayer = 0;
  PatchPlayerNamePal();

  // Inlined: SetupMenuCursor
  MenuCursorTemplate[3] = MenuCursorTiles[0];
  MenuCursorTemplate[5] = MenuCursorTiles[1];

  // Draw a star for each beaten game on the title screen

  for (int i = 0; i < 12; i++) {
    TitleScreenGfxData[0x33 + i] = i < GamesBeatenCount ? 0xf1 : 0x26;
  }
  for (int i = 12; i < 24; i++) {
    TitleScreenGfxData[0x4d + i-12] = i < GamesBeatenCount ? 0xf1 : 0x26;
  }
#endif

  InitializeMemory(0x6f);
  for (int i = 0; i < 0x20; i++) {
    SoundMemory[i] = 0;
  }
  DemoTimer = 0x18;
  LoadAreaPointer();
  InitializeArea();
}


// SMB:8fe4
// SM2MAIN:6e39
// Signature: [] -> []
void InitializeArea(void) {
  InitializeMemory(0x4b);
  for (int i = 0; i < 34; i++) {
    Timers[i] = 0;
  }
  ScreenLeft_PageLoc = HalfwayPage;
  if (AltEntranceControl != 0) {
    ScreenLeft_PageLoc = EntrancePage;
  }
  CurrentPageLoc = ScreenLeft_PageLoc;
  BackloadingFlag = ScreenLeft_PageLoc;
  const u8 bVar1 = GetScreenPosition();
  CurrentNTAddr_High = ((bVar1 & 1) == 0) ? 0x20 : 0x24;
  CurrentNTAddr_Low = 0x80;
  BlockBufferColumnPos = (bVar1 & 1) << 4;
  AreaObjectLength[0] -= 1;
  AreaObjectLength[1] -= 1;
  AreaObjectLength[2] -= 1;
  ColumnSets = 0xb;
#ifdef SMB1_MODE
  GetAreaDataAddrs();
  if ((PrimaryHardMode != 0) || ((WorldNumber >= 4 && ((WorldNumber != 4 || LevelNumber >= 2))))) {
    SecondaryHardMode += 1;
  }
#endif
#ifdef SMB2J_MODE
  if (FileListNumber != 3) {
    GetAreaDataAddrs();
  } else {
    AltHard_GetAreaDataAddrs();
  }
  if ((HardWorldFlag != 0) || ((WorldNumber >= 3 && ((WorldNumber != 3 || LevelNumber >= 3))))) {
    SecondaryHardMode += 1;
  }
#endif
  if (HalfwayPage != 0) {
    PlayerEntranceCtrl = 2;
  }
  AreaMusicQueue = MUSIC_AREA_SILENCE;
  DisableScreenFlag = 1;
#ifdef SMB2J_MODE
  LoadPhysicsData();
#endif

  // Note: Moved OperMode_Task assignment to caller
}


// SMB:9061
// SM2MAIN:c5db
// Signature: [] -> []
void PrimaryGameSetup(void) {
  FetchNewGameTimerFlag = 1;
  PlayerSize = 1;
  NumberofLives = 2;
#ifdef SMB1_MODE
  OffScr_NumberofLives = 2;
#endif
  SecondaryGameSetup();
}


// SMB:9071
// SM2MAIN:6eb9
// Signature: [] -> []
void SecondaryGameSetup(void) {
  DisableScreenFlag = 0;
#ifdef SMB2J_MODE
  WindFlag = 0;
  FlagpoleMusicFlag = 0;
#endif
  for (int i = 0; i < 256; i++) {
    VRAM_Page[i] = 0;
  }
  GameTimerExpiredFlag = 0;
  DisableIntermediate = 0;
  BackloadingFlag = 0;
  BalPlatformAlignment = 0xff;
#ifdef SMB1_MODE
  Mirror_PPU_CTRL_REG1 = (Mirror_PPU_CTRL_REG1 & 0xfe) | (ScreenLeft_PageLoc & 1);
#endif
#ifdef SMB2J_MODE
  NameTableSelect = ScreenLeft_PageLoc & 1;
#endif
  GetAreaMusic();
  SprShuffleAmt[2] = 0x38;
  SprShuffleAmt[1] = 0x48;
  SprShuffleAmt[0] = 0x58;

  static const u8 default_spr_indices[15] = {
    1, 12, 18, 24, 30, 36, 42, 48, 54, 58, 9, 62, 63, 10, 11
  };

  for (int i = 0; i < 15; i++) {
    SprDataOffset[i] = default_spr_indices[i]*4;
  }

#ifdef SMB1_MODE
  SPRITE_Y(0, 0)    = 24;
  SPRITE_TILE(0, 0) = 0xff;
  SPRITE_ATTR(0, 0) = SPRATTR_DRAWBEHIND | 3;
  SPRITE_X(0, 0)    = 88;

  // NES note: there was a call here to "DoNothing2", which, well, does nothing

  Sprite0HitDetectFlag += 1;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag += 1;
#endif

  // NES note: there was a call here to "DoNothing1" ("DoNothing" in SMB2J), which appears to set an unused variable
  // The disassembly by doppelganger claims it's residual code
  // We'll inline it here
  Misc_Collision_Flag[11] = 0xff;

  // Note: Moved OperMode_Task assignment to caller
}

// SMB:90ed
// SM2MAIN:6f2d
// Signature: [] -> []
void GetAreaMusic(void) {
  if (OperMode == OM_TITLESCREEN) {
    return;
  }

  if ((AltEntranceControl != 2) && ((PlayerEntranceCtrl == 6) || (PlayerEntranceCtrl == 7))) {
    AreaMusicQueue = MUSIC_AREA_PIPEINTRO;
    return;
  }

  if (CloudTypeOverride != 0) {
    AreaMusicQueue = MUSIC_AREA_CLOUD;
    return;
  }

  switch (AreaType) {
  case 0: AreaMusicQueue = MUSIC_AREA_WATER; break;
  case 1: AreaMusicQueue = MUSIC_AREA_GROUND; break;
  case 2: AreaMusicQueue = MUSIC_AREA_UNDERGROUND; break;
  case 3: AreaMusicQueue = MUSIC_AREA_CASTLE; break;
  default: unreachable(); break;
  }
}


// SMB:9131
// SM2MAIN:6f71
// Signature: [] -> []
void Entrance_GameTimerSetup(void) {
  // NES Note: $07 is technically an input to this function. However, it's a bug.
  // This function is always called from a jumptable, which sets $07 to the high byte of the function (0x91 or 0x6f depending on SMB1 or SMB2J)
  // It's eventually passed to SetupBubble.

  Player_PageLoc = ScreenLeft_PageLoc;
  VerticalForceDown = 0x28;
  PlayerFacingDir = 1;
  Player_Y_HighPos = 1;
  Player_State = PLAYERSTATE_ONGROUND;
  Player_CollisionBits -= 1;
  HalfwayPage = 0;
  SwimmingFlag = AreaType == AREA_WATER;

  expect(PlayerEntranceCtrl < 8);
  expect(AltEntranceControl < 4);

  switch (AltEntranceControl) {
  case 0:
  case 1:
  {
    static const u8 starting_xpos[2] = {0x28,0x18};
    static const u8 starting_ypos[8] = {0x00,0x20,0xb0,0x50,0x00,0x00,0xb0,0xb0};
    static const bool bg_priority[8]   = {0,1,0,0,0,0,0,0};

    Player_X_Position = starting_xpos[AltEntranceControl];
    Player_Y_Position = starting_ypos[PlayerEntranceCtrl];
    Player_SprAttrib = bg_priority[PlayerEntranceCtrl] ? 0x20 : 0;
    break;
  }

  case 2:
    Player_X_Position = 0x38;
    Player_Y_Position = 0xf0;
    Player_SprAttrib = 0x20;
    break;

  case 3:
    Player_X_Position = 0x28;
    Player_Y_Position = 0;
    Player_SprAttrib = 0;
    break;
  }

  // NES note: The GetPlayerColors subroutine sets the X register to the vram offset.
  // The eventual call to SetupBubble is the only place that indirectly uses it.
  // We've extracted it out to the caller because it's a bug.
  // This always seems to be 0 (TODO: verify this)
  u8 buggy_argument_1 = VRAM_Buffer1_Offset;

  GetPlayerColors();

  if ((GameTimerSetting != 0) && (FetchNewGameTimerFlag != 0)) {
    // Initialize the game timer

    // NES note: inlined from GameTimerData
    static const u16 times[] = {0, 401, 301, 201};

    expect(GameTimerSetting <= sizeof(times)/sizeof(times[0]));

    const u16 time = times[GameTimerSetting];

    GameTimerDisplay[0] = (time / 100) % 10;
    GameTimerDisplay[1] = (time / 10) % 10;
    GameTimerDisplay[2] = (time) % 10;

    FetchNewGameTimerFlag = 0;
    StarInvincibleTimer = 0;
  }

  if (JoypadOverride != 0) {
    Player_State = PLAYERSTATE_CLIMBING;
    InitBlock_XY_Pos(0);
    Block_Y_Position[0] = 0xf0;
    Setup_Vine(5, 0);

    // The X register was set to 5 as an argument to Setup_Vine. It becomes the new buggy argument.
    // I'm unsure if this could ever be used, unless a modded ROM has Mario climbing a vine underwater or something.
    buggy_argument_1 = 5;
  }

  if (AreaType == AREA_WATER) {
    // $07 is passed here.
    const u8 buggy_argument_2 = ssw(0x91, 0x6f);
    SetupBubble_buggy(buggy_argument_1, buggy_argument_2);
  }

  GameEngineSubroutine = GR_PLAYERENTRANCE;
}


// SMB:91cd
// SM2MAIN:700f
// Signature: [] -> []
void PlayerLoseLife(void) {
  DisableScreenFlag += 1;
#ifdef SMB1_MODE
  Sprite0HitDetectFlag = 0;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag = 0;
#endif
  EventMusicQueue = MUSIC_EVENT_STOP;
  NumberofLives -= 1;
  if (NumberofLives >= 0x80) {
    OperMode = OM_GAMEOVER;
    OperMode_Task = OMT_GAMEOVER_SETUPGAMEOVER;
    return;
  }
  u8 bVar1 = WorldNumber * 2;
  if ((LevelNumber & 2) != 0) {
    bVar1 += 1;
  }
  bVar1 = HalfwayPageNybbles[bVar1];
  if ((LevelNumber & 1) == 0) {
    bVar1 >>= 4;
  }
  HalfwayPage = bVar1 & 0xf;
  if ((HalfwayPage != ScreenLeft_PageLoc) && (ScreenLeft_PageLoc <= HalfwayPage)) {
    HalfwayPage = 0;
  }
#ifdef SMB1_MODE
  TransposePlayers();
#endif
  ContinueGame();
}


// SMB:9218
// SM2MAIN:7057
// Signature: [] -> []
void GameOverMode(void) {
  switch (OperMode_Task) {
  case OMT_GAMEOVER_SETUPGAMEOVER:
    SetupGameOver();
    return;

  case OMT_GAMEOVER_SCREENROUTINES:
    ScreenRoutines();
    return;

  case OMT_GAMEOVER_RUNGAMEOVER:
    RunGameOver();
    return;

  default:
    jmpengine_overflow(OperMode_Task);
  }
}


// SMB:9224
// SM2MAIN:7063
// Signature: [] -> []
void SetupGameOver(void) {
  ScreenRoutineTask = SRT_INITSCREEN;
#ifdef SMB1_MODE
  Sprite0HitDetectFlag = 0;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag = 0;
  ContinueMenuSelect = 0;
#endif
  EventMusicQueue = MUSIC_EVENT_GAMEOVER;
  DisableScreenFlag += 1;
  expect(OperMode_Task == OMT_GAMEOVER_SETUPGAMEOVER);
  OperMode_Task = OMT_GAMEOVER_SCREENROUTINES;
}


// SMB:9237
// SM2MAIN:7079
// Signature: [] -> []
void RunGameOver(void) {
  DisableScreenFlag = 0;
#ifdef SMB1_MODE
  if ((SavedJoypadBits[0] & BUTTON_START) != 0) {
    TerminateGame();
    return;
  }
#endif
#ifdef SMB2J_MODE
  if (WorldNumber != 8) {
    GameOverMenu();
    return;
  }
#endif
  if (ScreenTimer == 0) {
    TerminateGame();
  }
}


// SMB:9248
// SM2MAIN:708d
// Signature: [] -> []
void TerminateGame(void) {
  EventMusicQueue = MUSIC_EVENT_STOP;
#ifdef SMB1_MODE
  if (!TransposePlayers()) {
    ContinueGame();
    return;
  }
  ContinueWorld = WorldNumber;
#endif
  ScreenTimer = 0;
  OperMode = OM_TITLESCREEN;
  OperMode_Task = OMT_TITLESCREEN_START;
}


// SMB:9264
// SM2MAIN:709d
// Signature: [] -> []
void ContinueGame(void) {
  LoadAreaPointer();
  PlayerSize = 1;
  FetchNewGameTimerFlag += 1;
  TimerControl = 0;
  PlayerStatus = PLAYERSTATUS_SMALL;
  GameEngineSubroutine = GR_ENTRANCE_GAMETIMERSETUP;
  OperMode = OM_GAME;
  OperMode_Task = OMT_GAME_START;
}


// SMB:9716
// SM2MAIN:756d
// Signature: [A] -> []
void KillEnemies(const u8 param_1) {
  for (int i = 0; i < 5; i++) {
    if (Enemy_ID[i] == param_1) {
      Enemy_Flag[i] = 0;
    }
  }
}


// SMB:aedc
// SM2MAIN:7a37
// Signature: [] -> []
void GameMode(void) {
  switch (OperMode_Task) {
  case OMT_GAME_INITIALIZEAREA:
    InitializeArea();
    expect(OperMode == OM_GAME);
    OperMode_Task = OMT_GAME_SCREENROUTINES;
    return;

  case OMT_GAME_SCREENROUTINES:
    ScreenRoutines();
    return;

  case OMT_GAME_SECONDARYGAMESETUP:
    SecondaryGameSetup();
    expect(OperMode == OM_GAME);
    OperMode_Task = OMT_GAME_GAMECOREROUTINE;
    return;

  case OMT_GAME_GAMECOREROUTINE:
    GameCoreRoutine();
    return;

#ifdef SMB2J_MODE
  case OMT_GAME_GAMEMODEDISKROUTINES:
    GameModeDiskRoutines();
    return;
#endif

  default:
    jmpengine_overflow(OperMode_Task);
  }
}


// SMB:aeea
// SM2MAIN:7a47
// Signature: [] -> []
void GameCoreRoutine(void) {
#ifdef SMB1_MODE
  SavedJoypadBits[0] = SavedJoypadBits[CurrentPlayer];
#endif
  GameRoutines();

  expect(is_opermodetask_valid());

  // NES note: this would compare OperMode_Task < 3, or OperMode_Task < 4 for SMB2J.
  // This is changed to be more explicit.
  // TODO: trim this down to eliminate needless checks.

#define CONTINUE_ON(opermode, opermodetask) \
    if (OperMode == (opermode) && OperMode_Task == (opermodetask)) { doreturn = false; }

  bool doreturn = true;

  CONTINUE_ON(OM_TITLESCREEN, OMT_TITLESCREEN_GAMEMENUROUTINE);
  CONTINUE_ON(OM_GAME, OMT_GAME_GAMECOREROUTINE);
  CONTINUE_ON(OM_VICTORY, OMT_VICTORY_PRINTVICTORYMESSAGES);
  CONTINUE_ON(OM_VICTORY, OMT_VICTORY_PLAYERENDWORLD);

#ifdef SMB2J_MODE
  CONTINUE_ON(OM_TITLESCREEN, OMT_TITLESCREEN_HARDWORLDSCHECKPOINT);
  CONTINUE_ON(OM_VICTORY, OMT_VICTORY_ENDCASTLEAWARD);
#endif

  if (doreturn) {
    return;
  }

#undef CONTINUE_ON

  ProcFireball_Bubble();

  for (int i = 0; i < 6; i++) {
    EnemiesAndLoopsCore(i);
    FloateyNumbersRoutine(i);
  }

  GetPlayerOffscreenBits();
  RelativePlayerPosition();
  PlayerGfxHandler();
  BlockObjMT_Updater();
  BlockObjectsCore(1);
  BlockObjectsCore(0);
  MiscObjectsCore();
  ProcessCannons();
  ProcessWhirlpools();
  FlagpoleRoutine();
  RunGameTimer();
  ColorRotation();
#ifdef SMB2J_MODE
  if (FileListNumber != 0) {
    SimulateWind();
  }
#endif

  bool do_cycle = true;

  // Note: comparison to 0x82 is because this is a signed comparison

  if (Player_Y_HighPos < 2 || Player_Y_HighPos >= 0x82) {
    if (StarInvincibleTimer == 0) {
      ResetPalStar();
      do_cycle = false;
    } else if ((StarInvincibleTimer == 4) && (IntervalTimerControl == 0)) {
      GetAreaMusic();
    }
  }

  if (do_cycle) {
    if (StarInvincibleTimer < 8) {
      CyclePlayerPalette(FrameCounter >> 3);
    } else {
      CyclePlayerPalette(FrameCounter >> 1);
    }
  }

  PreviousA_B_Buttons = A_B_Buttons;
  Left_Right_Buttons = 0;
  UpdScrollVar();
}


// SMB:af6f
// SM2MAIN:7acb
// Signature: [] -> []
void UpdScrollVar(void) {
  if (VRAM_Buffer_AddrCtrl == ADDRCTRL_VRAM_BUFFER2) {
    return;
  }

  if (AreaParserTaskNum == 0) {
    if (ScrollThirtyTwo < 32) {
      return;
    }

    // NES note: The comparison to 128+32 is because of the way CMP + BMI works on the 6502
    // This case isn't likely or intentional (it might not even be possible)
    if (ScrollThirtyTwo >= 128+32) {
      return;
    }

    ScrollThirtyTwo -= 32;
    VRAM_Buffer2_Offset = 0;
  }

  AreaParserTaskHandler();
}


// SMB:af93
// SM2MAIN:7aef
// Signature: [] -> []
void ScrollHandler(void) {
  Player_X_Scroll += Platform_X_Scroll;
  if ((((ScrollLock != 0) || (Player_Pos_ForScroll < 0x50)) || (SideCollisionTimer != 0))
      || (0x7f < (u8)(Player_X_Scroll - 1))) {
    ScrollAmount = 0;
    ChkPOffscr();
    return;
  }
  u8 bVar1 = Player_X_Scroll;
  if (Player_X_Scroll > 1) {
    bVar1 = Player_X_Scroll - 1;
  }
  if (Player_Pos_ForScroll < 0x70) {
    ScrollScreen(bVar1);
    return;
  }
  ScrollScreen(Player_X_Scroll);
}


// SMB:b000
// SM2MAIN:7b58
// Signature: [] -> []
void ChkPOffscr(void) {
  const u8 bits = GetXOffscreenBits(0);

  const bool b1 = (bits & 0x80) != 0;
  const bool b2 = (bits & 0x20) != 0;

  if (b1) {
    const u8 xsubtracterdata = 0;

    Player_X_Position = ScreenLeft_X_Pos - xsubtracterdata;
    Player_PageLoc = ScreenLeft_PageLoc - (ScreenLeft_X_Pos < xsubtracterdata);

    if (Left_Right_Buttons != BUTTON_R) {
      Player_X_Speed = 0;
    }
  } else if (b2) {
    const u8 xsubtracterdata = 0x10;

    Player_X_Position = ScreenRight_X_Pos - xsubtracterdata;
    Player_PageLoc = ScreenRight_PageLoc - (ScreenRight_X_Pos < xsubtracterdata);

    if (Left_Right_Buttons != BUTTON_L) {
      Player_X_Speed = 0;
    }
  }

  Platform_X_Scroll = 0;
}


// SMB:b038
// SM2MAIN:7b90
// Signature: [] -> [A]
u8 GetScreenPosition(void) {
  ScreenRight_X_Pos = ScreenLeft_X_Pos - 1;
  ScreenRight_PageLoc = ScreenLeft_PageLoc + (ScreenLeft_X_Pos != 0);
  return ScreenRight_PageLoc;
}



// SMB:b04a
// SM2MAIN:7ba2
// Signature: [] -> []
void GameRoutines(void) {
  switch (GameEngineSubroutine) {
  case GR_ENTRANCE_GAMETIMERSETUP:
    Entrance_GameTimerSetup();
    return;

  case GR_VINE_AUTOCLIMB:
    Vine_AutoClimb();
    return;

  case GR_SIDEEXITPIPEENTRY:
    SideExitPipeEntry();
    return;

  case GR_VERTICALPIPEENTRY:
    VerticalPipeEntry();
    return;

  case GR_FLAGPOLESLIDE:
    FlagpoleSlide();
    return;

  case GR_PLAYERENDLEVEL:
    PlayerEndLevel();
    return;

  case GR_PLAYERLOSELIFE:
    PlayerLoseLife();
    return;

  case GR_PLAYERENTRANCE:
    PlayerEntrance();
    return;

  case GR_PLAYERCTRLROUTINE:
    PlayerCtrlRoutine();
    return;

  case GR_PLAYERCHANGESIZE:
    PlayerChangeSize();
    return;

  case GR_PLAYERINJURYBLINK:
    PlayerInjuryBlink();
    return;

  case GR_PLAYERDEATH:
    PlayerDeath();
    return;

  case GR_PLAYERFIREFLOWER:
    PlayerFireFlower();
    return;

  default:
    jmpengine_overflow(GameEngineSubroutine);
  }
}


// SMB:b069
// SM2MAIN:7bc1
// Signature: [] -> []
void PlayerEntrance(void) {
  u8 bVar1;

  if (AltEntranceControl == 2) {
    if (JoypadOverride == 0) {
      MovePlayerYAxis(0xff);
      if (Player_Y_Position > 0x90) {
        return;
      }
    } else {
      if (VineHeight != 0x60) {
        return;
      }
      DisableCollisionDet = Player_Y_Position > 0x98;
      bVar1 = 1;
      if (DisableCollisionDet != 0) {
        Player_State = PLAYERSTATE_CLIMBING;
        bVar1 = 8;
        set_metatile(4, 11, MT_MOUNTAIN_R);
      }
      AutoControlPlayer(bVar1);
      if (Player_X_Position < 0x48) {
        return;
      }
    }
  } else {
    if (Player_Y_Position < 0x30) {
      AutoControlPlayer(0);
      return;
    }
    if ((PlayerEntranceCtrl == 6) || (PlayerEntranceCtrl == 7)) {
      if (Player_SprAttrib == 0) {
        AutoControlPlayer(1);
        return;
      }
      EnterSidePipe();
      ChangeAreaTimer -= 1;
      if (ChangeAreaTimer != 0) {
        return;
      }
      DisableIntermediate += 1;
      NextArea();
      return;
    }
  }
  JoypadOverride = 0;
  AltEntranceControl = 0;
  DisableCollisionDet = 0;
  PlayerFacingDir = 1;
  GameEngineSubroutine = GR_PLAYERCTRLROUTINE;
}


// SMB:b0e6
// SM2MAIN:7c3e
// Signature: [A] -> []
void AutoControlPlayer(const u8 param_1) {
  SavedJoypadBits[0] = param_1;
  PlayerCtrlRoutine();
}


// SMB:b0e9
// SM2MAIN:7c41
// Signature: [] -> []
void PlayerCtrlRoutine(void) {
  char cVar1;
  char cVar2;

  if (GameEngineSubroutine != GR_PLAYERDEATH) {
    if ((AreaType == AREA_WATER) && ((Player_Y_HighPos != 1 || (Player_Y_Position >= 0xd0)))) {
      SavedJoypadBits[0] = 0;
    }
    A_B_Buttons = SavedJoypadBits[0] & (BUTTON_A | BUTTON_B);
    Up_Down_Buttons = SavedJoypadBits[0] & (BUTTON_U | BUTTON_D);
    Left_Right_Buttons = SavedJoypadBits[0] & (BUTTON_L | BUTTON_R);
    if ((((SavedJoypadBits[0] & BUTTON_D) != 0) && (Player_State == PLAYERSTATE_ONGROUND)) && (Left_Right_Buttons != 0)) {
      Left_Right_Buttons = 0;
      Up_Down_Buttons = 0;
    }
  }
  PlayerMovementSubs();
  Player_BoundBoxCtrl = 1;
  if (PlayerSize == 0) {
    Player_BoundBoxCtrl = 0;
    if (CrouchingFlag != 0) {
      Player_BoundBoxCtrl = 2;
    }
  }
  if ((Player_X_Speed != 0)) {
    Player_MovingDir = (Player_X_Speed < 0x80) ? 1 : 2;
  }
  ScrollHandler();
  GetPlayerOffscreenBits();
  const u8 bVar3 = RelativePlayerPosition();
  BoundingBoxCore(0, bVar3);
  PlayerBGCollision();
  if (Player_Y_Position >= 0x40) {
    expect(is_gameroutine_valid(GameEngineSubroutine));

    switch (GameEngineSubroutine) {
    case GR_FLAGPOLESLIDE:
    case GR_PLAYERLOSELIFE:
    case GR_PLAYERCTRLROUTINE:
    case GR_PLAYERCHANGESIZE:
    case GR_PLAYERINJURYBLINK:
    case GR_PLAYERDEATH:
    case GR_PLAYERFIREFLOWER:
      Player_SprAttrib &= ~SPRATTR_DRAWBEHIND;
      break;
    }
  }
  if ((u8)(Player_Y_HighPos - 2) < 0x80) {
    ScrollLock = 1;
    cVar1 = 4;
    cVar2 = 0;
    if (((GameTimerExpiredFlag != 0) || (CloudTypeOverride == 0))) {
      cVar2 = 1;
      if (GameEngineSubroutine != GR_PLAYERDEATH) {
        if (DeathMusicLoaded == 0) {
          EventMusicQueue = MUSIC_EVENT_DEATH;
          DeathMusicLoaded = 1;
        }
        cVar1 = 6;
      }
    }
    if ((u8)(Player_Y_HighPos - cVar1) < 0x80) {
      if (0x7f < (u8)(cVar2 - 1U)) {
        JoypadOverride = 0;
        SetEntr();
        AltEntranceControl += 1;
        return;
      }
      if (EventMusicBuffer == 0) {
        GameEngineSubroutine = GR_PLAYERLOSELIFE;
      }
    }
  }
}


// SMB:b1c7
// SM2MAIN:7d1f
// Signature: [] -> []
void Vine_AutoClimb(void) {
  if ((Player_Y_HighPos == 0) && (Player_Y_Position < 0xe4)) {
    SetEntr();
  } else {
    JoypadOverride = 8;
    Player_State = PLAYERSTATE_CLIMBING;
    AutoControlPlayer(8);
  }
}


// SMB:b1dd
// SM2MAIN:7d35
// Signature: [] -> []
void SetEntr(void) {
  AltEntranceControl = 2;
  ChgAreaMode();
}


// SMB:b1e5
// SM2MAIN:7d3d
// Signature: [] -> []
void VerticalPipeEntry(void) {
  MovePlayerYAxis(1);
  ScrollHandler();
  ChangeAreaTimer -= 1;
  if (ChangeAreaTimer == 0) {
    if (WarpZoneControl != 0) {
      AltEntranceControl = 0;
    } else if (AreaType != AREA_CASTLE) {
      AltEntranceControl = 1;
    } else {
      AltEntranceControl = 2;
    }
    ChgAreaMode();
  }
}


// SMB:b200
// SM2MAIN:7d58
// Signature: [A] -> []
void MovePlayerYAxis(const u8 param_1) {
  Player_Y_Position = param_1 + Player_Y_Position;
}


// SMB:b206
// SM2MAIN:7d5e
// Signature: [] -> []
void SideExitPipeEntry(void) {
  EnterSidePipe();
  ChangeAreaTimer -= 1;
  if (ChangeAreaTimer == 0) {
    AltEntranceControl = 2;
    ChgAreaMode();
  }
}


// SMB:b213
// SM2MAIN:7d6b
// Signature: [] -> [A]
u8 ChgAreaMode(void) {
  DisableScreenFlag += 1;
  expect(OperMode == OM_GAME);
  OperMode_Task = OMT_GAME_START;
#ifdef SMB1_MODE
  Sprite0HitDetectFlag = 0;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag = 0;
#endif
  return 0;
}


// SMB:b21f
// SM2MAIN:7d77
// Signature: [] -> []
void EnterSidePipe(void) {
  Player_X_Speed = 8;
  const bool bVar1 = (Player_X_Position & 0xf) == 0;
  if (bVar1) {
    Player_X_Speed = 0;
  }
  AutoControlPlayer(!bVar1);
}


// SMB:b233
// SM2MAIN:7d8b
// Signature: [] -> []
void PlayerChangeSize(void) {
  if (TimerControl == 0xf8) {
    InitChangeSize();
  } else if (TimerControl == 0xc4) {
    DonePlayerTask();
  }
}


// SMB:b245
// SM2MAIN:7d9d
// Signature: [] -> []
void PlayerInjuryBlink(void) {
  if (TimerControl >= 0xf0) {
    if (TimerControl == 0xf0) {
      InitChangeSize();
    }
  } else if (TimerControl == 200) {
    DonePlayerTask();
  } else {
    PlayerCtrlRoutine();
  }
}


// SMB:b255
// SM2MAIN:7dad
// Signature: [] -> []
void InitChangeSize(void) {
  if (PlayerChangeSizeFlag == 0) {
    PlayerAnimCtrl = PlayerChangeSizeFlag;
    PlayerChangeSizeFlag = 1;
    PlayerSize ^= 1;
  }
}


// SMB:b269
// SM2MAIN:7dc1
// Signature: [] -> []
void PlayerDeath(void) {
  if (TimerControl < 0xf0) {
    PlayerCtrlRoutine();
  }
}


// SMB:b273
// SM2MAIN:7dcb
// Signature: [] -> []
void DonePlayerTask(void) {
  TimerControl = 0;
  GameEngineSubroutine = GR_PLAYERCTRLROUTINE;
}


// SMB:b27d
// SM2MAIN:7dd5
// Signature: [] -> []
void PlayerFireFlower(void) {
  if (TimerControl != 0xc0) {
    CyclePlayerPalette(FrameCounter >> 2);
  } else {
    DonePlayerTask();
    ResetPalStar();
  }
}


// SMB:b288
// SM2MAIN:7de0
// Signature: [A] -> []
void CyclePlayerPalette(const u8 param_1) {
  Player_SprAttrib = (Player_SprAttrib & 0xfc) | (param_1 & 3);
}


// SMB:b29a
// SM2MAIN:7df2
// Signature: [] -> []
void ResetPalStar(void) {
  Player_SprAttrib &= 0xfc;
}


// SMB:b2a4
// SM2MAIN:7dfb
// Signature: [] -> []
void FlagpoleSlide(void) {
  u8 bVar1;

  if (Enemy_ID[5] == A_FLAGPOLE) {
    Square1SoundQueue = FlagpoleSoundQueue;
    bVar1 = 0;
    FlagpoleSoundQueue = SOUND_SQ1_NONE;
    if (Player_Y_Position < 0x9e) {
      bVar1 = 4;
    }
    AutoControlPlayer(bVar1);
  } else {
    expect(GameEngineSubroutine == GR_FLAGPOLESLIDE);
    GameEngineSubroutine = GR_PLAYERENDLEVEL;
  }
}


// SMB:b2ca
// SM2MAIN:7e19
// Signature: [] -> []
void PlayerEndLevel(void) {
  AutoControlPlayer(1);
#ifdef SMB1_MODE
  if ((Player_Y_Position >= 0xae) && (ScrollLock != 0)) {
    EventMusicQueue = MUSIC_EVENT_LEVELEND;
    ScrollLock = 0;
  }
#endif
#ifdef SMB2J_MODE
  if ((Player_Y_Position >= 0xae)) {
    ScrollLock = 0;
    if (FlagpoleMusicFlag == 0) {
      EventMusicQueue = MUSIC_EVENT_LEVELEND;
      FlagpoleMusicFlag = 1;
    }
  }
#endif
  if ((Player_CollisionBits & 1) == 0) {
    if (StarFlagTaskControl == STARFLAGTASK_IDLE) {
      StarFlagTaskControl = STARFLAGTASK_GAMETIMERFIREWORKS;
    }
    Player_SprAttrib = 0x20;
  }
  if (StarFlagTaskControl != STARFLAGTASK_DONE) {
    return;
  }
  LevelNumber += 1;
#ifdef SMB1_MODE
  if (LevelNumber == 3 && CoinTallyFor1Ups >= Hidden1UpCoinAmts[WorldNumber]) {
    Hidden1UpFlag += 1;
  }
#endif
#ifdef SMB2J_MODE
  if (LevelNumber == 3 && CoinTallyFor1Ups >= 10) {
    Hidden1UpFlag += 1;
  }
#endif
  NextArea();
}


// SMB:b315
// SM2MAIN:7e66
// Signature: [] -> []
void NextArea(void) {
  AreaNumber += 1;
  if (SMB2J_ONLY && (WorldNumber == 8) && (LevelNumber == 4)) {
    LevelNumber = 0;
    AreaNumber = 0;
  }
  LoadAreaPointer();
  FetchNewGameTimerFlag += 1;
  HalfwayPage = ChgAreaMode();
  EventMusicQueue = MUSIC_EVENT_STOP;
}


// SMB:b329
// SM2MAIN:7e90
// Signature: [] -> []
void PlayerMovementSubs(void) {
  u8 bVar1 = 0;
  if (PlayerSize == 0) {
    bVar1 = CrouchingFlag;
    if (Player_State == PLAYERSTATE_ONGROUND) {
      bVar1 = Up_Down_Buttons & BUTTON_D;
    }
  }
  CrouchingFlag = bVar1;
  PlayerPhysicsSub();
  if (PlayerChangeSizeFlag != 0) {
    return;
  }
  if (Player_State != PLAYERSTATE_CLIMBING) {
    ClimbSideTimer = 0x18;
  }

  switch (Player_State) {
  case PLAYERSTATE_ONGROUND:
    OnGroundStateSub();
    return;

  case PLAYERSTATE_JUMPSWIM:
    JumpSwimSub();
    return;

  case PLAYERSTATE_FALLING:
    FallingSub();
    return;

  case PLAYERSTATE_CLIMBING:
    ClimbingSub();
    return;

  default:
    jmpengine_overflow(Player_State);
  }
}


// SMB:b35a
// SM2MAIN:7ec1
// Signature: [] -> []
void OnGroundStateSub(void) {
  GetPlayerAnimSpeed();
  if (Left_Right_Buttons != 0) {
    PlayerFacingDir = Left_Right_Buttons;
  }
  ImposeFriction(Left_Right_Buttons);
  Player_X_Scroll = MovePlayerHorizontally();
#ifdef SMB2J_MODE
  if (SMB2J_ONLY && FileListNumber != 0) {
    BlowPlayerAround();
  }
#endif
}


// SMB:b36d
// SM2MAIN:7edc
// Signature: [] -> []
void FallingSub(void) {
  VerticalForce = VerticalForceDown;
  LRAir();
}


// SMB:b376
// SM2MAIN:7ee5
// Signature: [] -> []
void JumpSwimSub(void) {
  if ((Player_Y_Speed < 0x80)
      || (((A_B_Buttons & BUTTON_A & PreviousA_B_Buttons) == 0
           && (DiffToHaltJump <= (u8)(JumpOrigin_Y_Position - Player_Y_Position))))) {
    VerticalForce = VerticalForceDown;
  }
  if (SwimmingFlag != 0) {
    GetPlayerAnimSpeed();
    if (Player_Y_Position < 0x14) {
      VerticalForce = 0x18;
    }
    if (Left_Right_Buttons != 0) {
      PlayerFacingDir = Left_Right_Buttons;
    }
  }
  LRAir();
}


// SMB:b3ac
// SM2MAIN:7f1b
// Signature: [] -> []
void LRAir(void) {
  if (Left_Right_Buttons != 0) {
    ImposeFriction(Left_Right_Buttons);
  }
  Player_X_Scroll = MovePlayerHorizontally();
#ifdef SMB2J_MODE
  if (SMB2J_ONLY && FileListNumber != 0) {
    BlowPlayerAround();
  }
#endif
  if (GameEngineSubroutine == GR_PLAYERDEATH) {
    VerticalForce = 0x28;
  }
  MovePlayerVertically();
}


// SMB:b3cf
// SM2MAIN:7f3b
// Signature: [] -> []
void ClimbingSub(void) {
  ADD_SIGNED_24_16(Player_Y_HighPos, Player_Y_Position, Player_YMF_Dummy,
                   Player_Y_Speed, Player_Y_MoveForce);

  const u8 bVar3 = Left_Right_Buttons & Player_CollisionBits;
  if (bVar3 != 0) {
    if (ClimbSideTimer == 0) {
      ClimbSideTimer = 0x18;
      u8 bVar4 = (bVar3 & 1) == 0 ? 2 : 0;
      if (PlayerFacingDir != 1) {
        bVar4 += 1;
      }
      static const i8 climb_adder[4] = { 14, 4, -4, -14 };
      ADD_SIGNED_16_8(Player_PageLoc, Player_X_Position,
                      climb_adder[bVar4]);
      PlayerFacingDir = Left_Right_Buttons ^ 3;
    }
  } else {
    ClimbSideTimer = 0;
  }
}


// SMB:b450
// SM2MAIN:7fbc
// Signature: [] -> []
void PlayerPhysicsSub(void) {
  if (Player_State == PLAYERSTATE_CLIMBING) {
    if (((Up_Down_Buttons & Player_CollisionBits) == 0)) {
      Player_Y_MoveForce = 0;
      Player_Y_Speed = 0;
      PlayerAnimTimerSet = 4;
    } else if ((Up_Down_Buttons & Player_CollisionBits & BUTTON_U) == 0) {
      Player_Y_MoveForce = -1;
      Player_Y_Speed = 1;
      PlayerAnimTimerSet = 4;
    } else {
      Player_Y_MoveForce = 32;
      Player_Y_Speed = -1;
      PlayerAnimTimerSet = 8;
    }

    return;
  }

  const bool button_a_newly_pressed = ((A_B_Buttons & BUTTON_A) != 0) && ((A_B_Buttons & BUTTON_A & PreviousA_B_Buttons) == 0);
  if ((JumpspringAnimCtrl == 0) && button_a_newly_pressed) {
    if (Player_State == PLAYERSTATE_ONGROUND || (SwimmingFlag != 0 && (JumpSwimTimer != 0 || (Player_Y_Speed < 0x80)))) {
      JumpSwimTimer = 0x20;
      Player_YMF_Dummy = 0;
      JumpOrigin_Y_HighPos = Player_Y_HighPos;
      JumpOrigin_Y_Position = Player_Y_Position;
      Player_State = PLAYERSTATE_JUMPSWIM;

      u8 bVar1;
      if (SwimmingFlag == 0) {
        const u8 xs = Player_XSpeedAbsolute;
        if (xs <= 8) {
          bVar1 = 0;
        } else if (xs < 16) {
          bVar1 = 1;
        } else if (xs <= 24) {
          bVar1 = 2;
        } else if (xs < 28) {
          bVar1 = 3;
        } else {
          bVar1 = 4;
        }
      } else {
        bVar1 = (Whirlpool_Flag == 0) ? 5 : 6;
      }

      DiffToHaltJump = 1;

      static const u8 init_mforce_lookup[7] = { 0,0,0,0,0,128,0 };
      static const i8 player_yspd_lookup[7] = { -4,-4,-4,-5,-5,-2,-1 };

      if (MarioPhysics) {
        // Mario

        static const u8 jump_mforce_lookup[7] = { 0x20, 0x20, 0x1e, 0x28, 0x28, 0x0d, 0x04 };
        static const u8 fall_mforce_lookup[7] = { 0x70, 0x70, 0x60, 0x90, 0x90, 0x0a, 0x09 };

        VerticalForce = jump_mforce_lookup[bVar1];
        VerticalForceDown = fall_mforce_lookup[bVar1];
      } else {
        // Luigi (SMB2J only)

        static const u8 jump_mforce_lookup[7] = { 0x18, 0x18, 0x18, 0x22, 0x22, 0x0d, 0x04 };
        static const u8 fall_mforce_lookup[7] = { 0x42, 0x42, 0x3e, 0x5d, 0x5d, 0x0a, 0x09 };

        VerticalForce = jump_mforce_lookup[bVar1];
        VerticalForceDown = fall_mforce_lookup[bVar1];
      }

      Player_Y_MoveForce = init_mforce_lookup[bVar1];
      Player_Y_Speed = player_yspd_lookup[bVar1];

      if (SwimmingFlag == 0) {
        Square1SoundQueue = (PlayerSize != 0) ? SOUND_SQ1_JUMP_SMALL : SOUND_SQ1_JUMP_BIG;
      } else {
        Square1SoundQueue = SOUND_SQ1_SWIM_OR_SQUISH;
        if (Player_Y_Position < 0x14) {
          Player_Y_Speed = 0;
        }
      }
    }
  }

  u8 bVar2 = 0;
  u8 bVar1 = 1;

  const bool same_direction = Left_Right_Buttons == Player_MovingDir;
  const bool holding_b = (A_B_Buttons & BUTTON_B) != 0;
  const bool running = same_direction && holding_b;

  if (Player_State == PLAYERSTATE_ONGROUND) {
    // ProcPRun
    if ((AreaType != AREA_WATER)) {
      if (running) {
        RunningTimer = 10;
      }
      if (same_direction) {
        if (RunningTimer != 0) {
          bVar1 = 0;
        }
      }
    }
  } else if (Player_XSpeedAbsolute > 0x18) {
    bVar1 = 0;
  }

  bVar2 = (Player_State == PLAYERSTATE_ONGROUND && AreaType == AREA_WATER) ? 1 : 0;

  if (bVar1) {
    bVar2 += 1;
    if ((RunningSpeed != 0) || (Player_XSpeedAbsolute > 0x20)) {
      bVar1 = 2;
    }
  }

  static const u8 max_left_xspd_lookup[3] = { 0xd8, 0xe8, 0xf0 };
  static const u8 max_right_xspd_lookup[3] = { 0x28, 0x18, 0x10 };

  // getxphy
  MaximumLeftSpeed  = max_left_xspd_lookup[bVar2];
  MaximumRightSpeed = max_right_xspd_lookup[bVar2];
  if (GameEngineSubroutine == GR_PLAYERENTRANCE) {
    MaximumRightSpeed = 12;
  }

  // NES note: In SMB2J, the code here is modified by LoadMarioPhysics/LoadLuigiPhysics.
  // LoadMarioPhysics patches with the ASL (0x0e) instruction
  // LoadLuigiPhysics patches with the RTS (0x60) instruction
  //
  // This effectively makes Luigi's physics skip increasing the friction while turning

  if (MarioPhysics) {
    // Mario

    static const u16 friction_adder_lookup[3] = { 0xe4, 0x98, 0xd0 };

    if (PlayerFacingDir == Player_MovingDir) {
      STORE_16(FrictionAdderHigh, FrictionAdderLow, friction_adder_lookup[bVar1]);
    } else {
      STORE_16(FrictionAdderHigh, FrictionAdderLow, friction_adder_lookup[bVar1]*2);
    }
  } else {
    // Luigi (SMB2J only)

    static const u16 friction_adder_lookup[3] = { 0xb4, 0x68, 0xa0 };

    STORE_16(FrictionAdderHigh, FrictionAdderLow, friction_adder_lookup[bVar1]);
  }
}


// SMB:b58f
// SM2MAIN:80fb
// Signature: [] -> []
void GetPlayerAnimSpeed(void) {
  if (Player_XSpeedAbsolute < 28) {
    PlayerAnimTimerSet = Player_XSpeedAbsolute < 14 ? 7 : 4;

    if ((SavedJoypadBits[0] & ~(BUTTON_A)) != 0) {
      if ((SavedJoypadBits[0] & (BUTTON_L | BUTTON_R)) == Player_MovingDir) {
        RunningSpeed = 0;
      } else if (Player_XSpeedAbsolute < 0xb) {
        Player_MovingDir = PlayerFacingDir;
        Player_X_Speed = 0;
        Player_X_MoveForce = 0;
      }
    }
  } else {
    PlayerAnimTimerSet = 2;
    RunningSpeed = Player_XSpeedAbsolute;
  }
}


// SMB:b5cc
// SM2MAIN:8138
// Signature: [A] -> []
void ImposeFriction(const u8 param_1) {
  const u8 tmp1 = param_1 & Player_CollisionBits;

  bool go_left = true;

  if (tmp1 == 0) {
    if (Player_X_Speed == 0) {
      Player_XSpeedAbsolute = 0;
      return;
    }

    go_left = Player_X_Speed >= 0x80;
  } else {
    go_left = (tmp1 & 1) != 0;
  }

  if (go_left) {
    // LeftFrict
    ADD_16_16(Player_X_Speed, Player_X_MoveForce,
              FrictionAdderHigh, FrictionAdderLow);

    if ((u8)(Player_X_Speed - MaximumRightSpeed) < 0x80) {
      Player_X_Speed = MaximumRightSpeed;
      Player_XSpeedAbsolute = MaximumRightSpeed;
      return;
    }
  } else {
    // RghtFrict
    SUB_16_16(Player_X_Speed, Player_X_MoveForce,
              FrictionAdderHigh, FrictionAdderLow);

    if ((u8)(Player_X_Speed - MaximumLeftSpeed) >= 0x80) {
      Player_X_Speed = MaximumLeftSpeed;
    }
  }

  if (Player_X_Speed >= 0x80) {
    Player_XSpeedAbsolute = -Player_X_Speed;
  } else {
    Player_XSpeedAbsolute = Player_X_Speed;
  }
}


// SMB:b624
// SM2MAIN:8190
// Signature: [] -> []
void ProcFireball_Bubble(void) {
  expect(is_playerstatus_valid(PlayerStatus));

  if (PlayerStatus == PLAYERSTATUS_FIREFLOWER) {
    bool cond = true;
    cond &= (A_B_Buttons & BUTTON_B) != 0;
    cond &= (A_B_Buttons & BUTTON_B & PreviousA_B_Buttons) == 0;
    cond &= Fireball_State[FireballCounter & 1] == 0;
    cond &= Player_Y_HighPos == 1;
    cond &= CrouchingFlag == 0;
    cond &= Player_State != PLAYERSTATE_CLIMBING;

    if (cond) {
      Square1SoundQueue = SOUND_SQ1_FIREBALL;
      Fireball_State[FireballCounter & 1] = 2;
      FireballThrowingTimer = PlayerAnimTimerSet;
      PlayerAnimTimer = PlayerAnimTimerSet - 1;
      FireballCounter += 1;
    }

    FireballObjCore(0);
    FireballObjCore(1);
  }

  if (AreaType == AREA_WATER) {
    for (int i = 2; i >= 0; i--) {
      BubbleCheck(i);
      RelativeBubblePosition(i);
      GetBubbleOffscreenBits(i);
      DrawBubble(i);
    }
  }
}


// SMB:b689
// SM2MAIN:81f5
// Signature: [X] -> []
void FireballObjCore(const u8 objoff) {
  // objoff is always 0 or 1

  if ((Fireball_State[objoff] & 0x80) != 0) {
    RelativeFireballPosition(objoff);
    DrawExplosion_Fireball(objoff);
    return;
  }

  if (Fireball_State[objoff] != 0) {
    if (Fireball_State[objoff] != 1) {
      ADD_UNSIGNED_16_16_8(Fireball_PageLoc[objoff], Fireball_X_Position[objoff],
                           Player_PageLoc, Player_X_Position,
                           4);

      Fireball_Y_Position[objoff] = Player_Y_Position;
      Fireball_Y_HighPos[objoff] = 1;

      // NES note: xspd_lookup[0] and [3] are bugs.
      // PlayerFacingDir may = 0 or 3 sometimes, so this goes out of bounds in the original.
      // The original lookup is FireballXSpdData[(u8)(PlayerFacingDir - 1)].
      const i8 xspd_lookup[4] = { -87, 64, -64, -122 };
      expect(PlayerFacingDir < 4);

      Fireball_X_Speed[objoff] = xspd_lookup[PlayerFacingDir];
      Fireball_Y_Speed[objoff] = 4;

      Fireball_BoundBoxCtrl[objoff] = 7;
      Fireball_State[objoff] = Fireball_State[objoff] - 1;
    }

    const u8 bVar4 = objoff + 7;

    const u8 in_r01 = 0;
    ImposeGravity(0, bVar4, 0x50, in_r01, 3);

    MoveObjectHorizontally(bVar4);

    RelativeFireballPosition(objoff);
    GetFireballOffscreenBits(objoff);
    GetFireballBoundBox(objoff);
    FireballBGCollision(objoff);
    if ((FBall_OffscreenBits & 0xcc) == 0) {
      FireballEnemyCollision(objoff);
      DrawFireball(objoff);
      return;
    }
    Fireball_State[objoff] = 0;
  }
}

static inline void check_and_setup_bubble(const u8 param_1, const bool random, const bool docheck, const bool bug) {
  bool setup_bubble = true;

  if (docheck) {
    if (Bubble_Y_Position[param_1] != SPRITE_Y_OFFSCREEN) {
      setup_bubble = false;
    } else if (AirBubbleTimer != 0) {
      return;
    }
  }

  const u8 air_bubble_timer_lookup[] = {0x40, 0x20};
  const u8 bubble_mforce_data_lookup[] = {0xff, 0x50};

  const int idx = random ? 1 : 0;

  const u8 air_bubble_timer   = !bug ? air_bubble_timer_lookup[idx] : 4;
  const u8 bubble_mforce_data = !bug ? bubble_mforce_data_lookup[idx] : ssw(0xf9, 0x8d);

  if (setup_bubble) {
    const bool c = (PlayerFacingDir & 1) != 0;
    // NES note: The carry flag causes the constant to be incremented by 1
    const u8 a = c ? (8 + 1) : 0;

    SET_16_16(Bubble_PageLoc[param_1], Bubble_X_Position[param_1],
              Player_PageLoc, Player_X_Position);

    ADD_UNSIGNED_16_8(Bubble_PageLoc[param_1], Bubble_X_Position[param_1],
                      a);

    Bubble_Y_Position[param_1] = Player_Y_Position + 8;
    Bubble_Y_HighPos[param_1] = 1;

    AirBubbleTimer = air_bubble_timer;
  }

  // MoveBubl

  SUB_UNSIGNED_16_8(Bubble_Y_Position[param_1], Bubble_YMF_Dummy[param_1],
                    bubble_mforce_data);

  if (Bubble_Y_Position[param_1] < 0x20) {
    Bubble_Y_Position[param_1] = SPRITE_Y_OFFSCREEN;
  }
}

// SMB:b6f9
// SM2MAIN:8265
// Signature: [X] -> []
void BubbleCheck(const u8 objoff) {
  const bool docheck = true;
  const bool bug = false;
  check_and_setup_bubble(objoff, PseudoRandomBitReg[objoff + 1] & 1, docheck, bug);
}


// SMB:b70b
// SM2MAIN:8277
// Signature: [X, r07] -> []
void SetupBubble_buggy(const u8 buggy_argument_1, const u8 buggy_argument_2) {
  // This procedure is only ever called from Entrance_GameTimerSetup.
  // BubbleCheck falls through to SetupBubble, but we take care of that case in check_and_setup_bubble.

  // unused
  (void)buggy_argument_2;

  const bool random_unused = false;
  const bool docheck = false;
  const bool bug = true;
  check_and_setup_bubble(buggy_argument_1, random_unused, docheck, bug);
}


// SMB:b74f
// SM2MAIN:82bb
// Signature: [] -> []
void RunGameTimer(void) {
  if (OperMode == OM_TITLESCREEN) {
    return;
  }

  if (GameTimerCtrlTimer != 0) {
    return;
  }


#ifdef SMB1_MODE
  if (Player_Y_HighPos >= 2) {
    return;
  }
#endif
#ifdef SMB2J_MODE
  if (Player_Y_HighPos >= 2 && Player_Y_HighPos < 0x82) {
    return;
  }
#endif

  expect(is_gameroutine_valid(GameEngineSubroutine));

  // GameEngineSubroutine >= 8 and GameEngineSubroutine != 11
  switch (GameEngineSubroutine) {
  case GR_PLAYERCTRLROUTINE:
  case GR_PLAYERCHANGESIZE:
  case GR_PLAYERINJURYBLINK:
  case GR_PLAYERFIREFLOWER:
    const bool is_time_up = GameTimerDisplay[0] == 0 && GameTimerDisplay[1] == 0 && GameTimerDisplay[2] == 0;
    if (is_time_up) {
      PlayerStatus = PLAYERSTATUS_SMALL;
      ForceInjury();
      GameTimerExpiredFlag += 1;
    } else {
      if (GameTimerDisplay[0] == 1 && GameTimerDisplay[1] == 0 && GameTimerDisplay[2] == 0) {
        EventMusicQueue = MUSIC_EVENT_TIMERUNNINGOUT;
      }
      GameTimerCtrlTimer = 0x18;
      DigitModifier[5] = 0xff;
      DigitsMathRoutine(ssw(0x23, 0x17));
      PrintStatusBarNumbers(ssw(0xa4, 0xa2));
    }
    break;
  }
}


// SMB:b7a4
// SM2MAIN:8310
// Signature: [X] -> []
void WarpZoneObject(const u8 objoff) {
  if ((ScrollLock != 0) && ((Player_Y_Position & Player_Y_HighPos) == 0)) {
    if (SMB1_ONLY) {
      WarpZoneControl += 1;
    }
    ScrollLock = Player_Y_Position & Player_Y_HighPos;
    EraseEnemyObject(objoff);
  }
}


// SMB:b7b8
// SM2MAIN:8321
// Signature: [] -> []
void ProcessWhirlpools(void) {
  if (AreaType != AREA_WATER) {
    return;
  }

  Whirlpool_Flag = 0;

  if (TimerControl != 0) {
    return;
  }

  for (int i = 4; i >= 0; i--) {
    const u8 whirlpool_x_hi = Whirlpool_PageLoc[i];
    const u8 whirlpool_x_lo = Whirlpool_X_Position[i];

    const u8 player_x_hi = Player_PageLoc;
    const u8 player_x_lo = Player_X_Position;

    const u8 length = Whirlpool_Length[i];

    const u16 player_x = (player_x_hi << 8) | player_x_lo;
    const u16 whirlpool_x = (whirlpool_x_hi << 8) | whirlpool_x_lo;

    if (whirlpool_x < 256) {
      continue;
    }

    if (player_x < whirlpool_x) {
      continue;
    }

    const i16 diff = player_x - whirlpool_x;

    if (diff <= length) {
      if ((FrameCounter & 1) != 0) {
        if (diff > (length / 2)) {
          // On the right side of the whirlpool
          // Pull the player to the left
          SUB_UNSIGNED_16_8(Player_PageLoc, Player_X_Position,
                            1);
        } else if ((Player_CollisionBits & 1) != 0) {
          // On the left side of the whirlpool, with collision bit
          // Pull the player to the right
          ADD_UNSIGNED_16_8(Player_PageLoc, Player_X_Position,
                            1);
        }
      }

      Whirlpool_Flag = 1;

      const u8 in_r01 = 0;
      ImposeGravity(0, 0, 0x10, in_r01, 1);

      return;
    }
  }
}


// SMB:b855
// SM2MAIN:83be
// Signature: [] -> []
void FlagpoleRoutine(void) {
  if (Enemy_ID[5] != A_FLAGPOLE) {
    return;
  }

  static const u8 score_digits[5] = { 3, 3, 4, 4, 4 };
  static const u8 score_mods[5]   = { 5, 2, 8, 4, 1 };

  if ((GameEngineSubroutine == GR_FLAGPOLESLIDE) && (Player_State == PLAYERSTATE_CLIMBING)) {
    if ((Enemy_Y_Position[5] >= 0xaa) || (Player_Y_Position >= 0xa2)) {
      if (SMB2J_ONLY && FlagpoleScore == 5) {
        NumberofLives += 1;
        Square2SoundQueue = SOUND_SQ2_1UP;
      } else {
        expect(FlagpoleScore < 5);
        DigitModifier[score_digits[FlagpoleScore]] = score_mods[FlagpoleScore];
        AddToScore();
      }
      GameEngineSubroutine = GR_PLAYERENDLEVEL;
    } else {
      const bool bVar3 = Player_Y_Position >= 0xa2;
      const u8 bVar1 = (Enemy_YMF_Dummy[5] - 1) + bVar3;
      Enemy_Y_Position[5] = Enemy_Y_Position[5] + 1 + ((Enemy_YMF_Dummy[5] != 0) || (bVar3 && bVar1 == 0));
      FlagpoleFNum_Y_Pos = (FlagpoleFNum_Y_Pos - 1) - (FlagpoleFNum_YMFDummy != 0xff);
      FlagpoleFNum_YMFDummy += 1;
      Enemy_YMF_Dummy[5] = bVar1;
    }
  }
  GetEnemyOffscreenBits(5);
  RelativeEnemyPosition(5);
  FlagpoleGfxHandler(5);
}


// SMB:b8ba
// SM2MAIN:8431
// Signature: [X] -> []
void JumpspringHandler(const u8 objoff) {
  GetEnemyOffscreenBits(objoff);

  const u8 animctrl = JumpspringAnimCtrl;

  if ((TimerControl == 0) && (animctrl != 0)) {
    expect(animctrl < 5);

    if (animctrl <= 2) {
      Player_Y_Position += 2;
    } else {
      Player_Y_Position -= 2;
    }

    static const u8 ypos_lookup[4] = { 8, 16, 8, 0 };

    Enemy_Y_Position[objoff] = Jumpspring_FixedYPos[objoff] + ypos_lookup[animctrl - 1];

    if ((((animctrl != 1) && ((A_B_Buttons & BUTTON_A) != 0)) && ((A_B_Buttons & BUTTON_A & PreviousA_B_Buttons) == 0))) {
      JumpspringForce = 0xf4;
      if (SMB2J_ONLY && (WorldNumber == 1 || WorldNumber == 2 || WorldNumber == 6)) {
        JumpspringForce = 0xe0;
      }
    }

    if (animctrl == 4) {
      Player_Y_Speed = JumpspringForce;
      JumpspringAnimCtrl = 0;
    }
  }

  RelativeEnemyPosition(objoff);
  EnemyGfxHandler(objoff);
  OffscreenBoundsCheck(objoff);
  if ((JumpspringAnimCtrl != 0) && (JumpspringTimer == 0)) {
    JumpspringTimer = 4;
    JumpspringAnimCtrl += 1;
  }
}


// SMB:b91e
// SM2MAIN:84aa
// Signature: [X, Y] -> []
void Setup_Vine(const u8 param_1, const u8 param_2) {
  // NES note: Y=0x60 is passed by CheckpointEnemyID. This is a bug.
  const bool bug = param_2 == 0x60;

  expect(param_2 == 0 || param_2 == 1 || param_2 == 0x60);

  Enemy_ID[param_1] = A_VINE;
  Enemy_Flag[param_1] = 1;

  if (!bug) {
    // Normal behavaior
    Enemy_PageLoc[param_1] = Block_PageLoc[param_2];
    Enemy_X_Position[param_1] = Block_X_Position[param_2];
    Enemy_Y_Position[param_1] = Block_Y_Position[param_2];
  } else {
    // The workaround is to resolve as the variables that would be accessed in the original game.
    // If Y == 0x60, then Block_X_Position[param_2] accesses address $EF,
    // which we've designated as a temporary register used the Gfx subroutines.
    Enemy_PageLoc[param_1] = SprObject_Y_Position[8];
    Enemy_X_Position[param_1] = rEF;
    Enemy_Y_Position[param_1] = DigitModifier[3];
  }

  if (VineFlagOffset == 0) {
    VineStart_Y_Position = Enemy_Y_Position[param_1];
  }

  VineObjOffset[VineFlagOffset] = param_1;
  VineFlagOffset += 1;
  Square2SoundQueue = SOUND_SQ2_VINE;
}


// SMB:b94b
// SM2MAIN:84d7
// Signature: [X] -> []
void VineObjectHandler(const u8 objoff) {
  if (objoff != 5) {
    return;
  }

  // It's easier to assume these are the only two values.
  // It simplifies loops and lookups.
  expect(VineFlagOffset == 1 || VineFlagOffset == 2);

  const u8 checkheight = VineFlagOffset == 1 ? 0x30 : 0x60;

  if (VineHeight != checkheight) {
    if ((FrameCounter & 2) != 0) {
      Enemy_Y_Position[5] -= 1;
      VineHeight += 1;
    }
  }

  if (VineHeight >= 8) {
    RelativeEnemyPosition(5);
    GetEnemyOffscreenBits(objoff);

    DrawVine(0);
    if (VineFlagOffset == 2) {
      DrawVine(1);
    }

    if ((Enemy_OffscreenBits & 0xc) != 0) {
      if (VineFlagOffset == 2) {
        EraseEnemyObject(VineObjOffset[1]);
      }
      EraseEnemyObject(VineObjOffset[0]);

      // NES note: these are set to 0 because EraseEnemyObject always set the A register to 0
      VineHeight = 0;
      VineFlagOffset = 0;
    }

    if (VineHeight >= 0x20) {
      const struct blockbuffer_colli_result sVar6 = BlockBufferCollision_coords(1, 6, 27);
      const u16 mt_x = sVar6.mt_x;
      const u16 mt_y = sVar6.mt_y;

      if (mt_y < 13) {
        if (get_metatile(mt_x, mt_y) == MT_0) {
          set_metatile(mt_x, mt_y, MT_SPECIAL_VINE);
        }
      }
    }
  }

#ifdef SMB2J_MODE

  const u16 xpos = LOAD_16(Enemy_PageLoc[5], Enemy_X_Position[5]);

  const u8 cmpA = (u8)((Enemy_PageLoc[5] - ScreenLeft_PageLoc) - (Enemy_X_Position[5] < ScreenLeft_X_Pos));
  const u8 cmpB = (u8)(Enemy_X_Position[5] - ScreenLeft_X_Pos);
  if ((cmpA >= 0x80) || (cmpB < 9)) {
    Enemy_Flag[5] = 0;

    const u16 mt_x = xpos >> 4;

    for (int i = 0; i < 13; i++) {
      if (get_metatile(mt_x, i) == MT_SPECIAL_VINE) {
        set_metatile(mt_x, i, MT_0);
      }
    }
  }
#endif
}


// SMB:b9bc
// SM2MAIN:8587
// Signature: [] -> []
void ProcessCannons(void) {
  if (AreaType == AREA_WATER) {
    return;
  }

  for (int i = 2; i >= 0; i--) {
    bool chk_bb = true;

    if (Enemy_Flag[i] == 0) {
      const u8 rng = PseudoRandomBitReg[i + 1] & (SecondaryHardMode == 0 ? 15 : 7);

      if (rng < 6) {
        if (Cannon_PageLoc[rng] != 0) {
          if (Cannon_Timer[rng] != 0) {
            Cannon_Timer[rng] -= 1;
          } else if (TimerControl == 0) {
            // Fire cannon

            // Note: cannon timer is decremented after this
            Cannon_Timer[rng] = 14;
            Enemy_PageLoc[i] = Cannon_PageLoc[rng];
            Enemy_X_Position[i] = Cannon_X_Position[rng];
            Enemy_Y_Position[i] = Cannon_Y_Position[rng] - 8;
            Enemy_Y_HighPos[i] = 1;
            Enemy_Flag[i] = 1;
            Enemy_State[i] = 0;
            Enemy_BoundBoxCtrl[i] = 9;
            Enemy_ID[i] = A_BULLET_BILL_CANNON;

            chk_bb = false;
          }
        }
      }
    }

    if (chk_bb) {
      if (Enemy_ID[i] == A_BULLET_BILL_CANNON) {
        OffscreenBoundsCheck(i);
        if (Enemy_Flag[i] != 0) {
          GetEnemyOffscreenBits(i);

          BulletBillHandler(i);
        }
      }
    }
  }
}


// SMB:ba33
// SM2MAIN:85fe
// Signature: [X] -> []
void BulletBillHandler(const u8 objoff) {
  if (TimerControl == 0) {
    if (Enemy_State[objoff] == 0) {
      if ((Enemy_OffscreenBits & 0xc) == 0xc) {
        EraseEnemyObject(objoff);
        return;
      }

      const struct_ncr00 sVar2 = PlayerEnemyDiff(objoff);

      if (sVar2.n) {
        Enemy_MovingDir[objoff] = 1;
        Enemy_X_Speed[objoff] = 0x18;
      } else {
        Enemy_MovingDir[objoff] = 2;
        Enemy_X_Speed[objoff] = -0x18;
      }

      if ((u8)(sVar2.r00 + 0x28 + sVar2.c) < 0x50) {
        EraseEnemyObject(objoff);
        return;
      }
      Enemy_State[objoff] = 1;
      EnemyFrameTimer[objoff] = 10;
      Square2SoundQueue = SOUND_SQ2_KABOOM;
    }
    if ((Enemy_State[objoff] & 0x20) != 0) {
      MoveD_EnemyVertically(objoff);
      MoveEnemyHorizontally(objoff);
    } else {
      MoveEnemyHorizontally(objoff);
    }
  }
  GetEnemyOffscreenBits(objoff);
  RelativeEnemyPosition(objoff);
  GetEnemyBoundBox(objoff);
  PlayerEnemyCollision(objoff);
  EnemyGfxHandler(objoff);
}


// SMB:ba94
// SM2MAIN:865f
// Signature: [r08] -> [C]
bool SpawnHammerObj(const u8 objoff) {
  u8 bVar2 = PseudoRandomBitReg[1] & 7;
  if (bVar2 == 0) {
    bVar2 = PseudoRandomBitReg[1] & 8;
  }

  // ofs = 4, 5, 6
  const u8 ofs = 4 + bVar2 / 3;

  if ((Misc_State[bVar2] == 0) && (Enemy_Flag[ofs] == 0)) {
    HammerEnemyOffset[bVar2] = objoff;
    Misc_State[bVar2] = 0x90;
    Misc_BoundBoxCtrl[bVar2] = 7;
    return true;
  }
  return false;
}


// SMB:bb38
// SM2MAIN:8703
// Signature: [X] -> []
void CoinBlock(const u8 param_1) {
  // NES Note: The carry flag is technically an input to this function. However, it's a bug.
  // This function is always called from a jumptable, which sets the carry flag (C) to false for jumptable indices < 0x80 (which CoinBlock always is)

  // Inlines FindEmptyMiscSlot

  JumpCoinMiscOffset = 8;

  for (int i = 8; i >= 6; i--) {
    if (Misc_State[i] == 0) {
      JumpCoinMiscOffset = i;
      break;
    }
  }

  Misc_PageLoc[JumpCoinMiscOffset] = Block_PageLoc[param_1];
  Misc_X_Position[JumpCoinMiscOffset] = Block_X_Position[param_1] | 5;
  Misc_Y_Position[JumpCoinMiscOffset] = Block_Y_Position[param_1] - 0x10;

  // NES Note: There's a bug where the carry flag is unmodified by FindEmptyMiscSlot.
  // It's usually set by this point, but in the below case, it's not.
  if (Misc_State[8] == 0) {
    Misc_Y_Position[JumpCoinMiscOffset] -= 1;
  }

  JCoinC(param_1, JumpCoinMiscOffset);
}


// SMB:bb6c
// SM2MAIN:8737
// Signature: [X, Y] -> []
void JCoinC(const u8 param_1, const u8 param_2) {
  Misc_Y_Speed[param_2] = 0xfb;
  Misc_Y_HighPos[param_2] = 1;
  Misc_State[param_2] = 1;
  Square2SoundQueue = SOUND_SQ2_COIN;
  GiveOneCoin();
  CoinTallyFor1Ups += 1;
}


// SMB:bac3
// SM2MAIN:868e
// Signature: [X] -> []
static inline void ProcHammerObj(const u8 objoff) {
  if (TimerControl == 0) {
    if ((Misc_State[objoff] & 0x7f) < 2) {
      const u8 bVar2 = objoff + 0xd;

      const u8 in_r01 = 0xf;
      ImposeGravity(0, bVar2, 0x10, in_r01, 4);

      MoveObjectHorizontally(bVar2);
      PlayerHammerCollision(objoff);
    } else {
      const u8 bVar2 = HammerEnemyOffset[objoff];
      if ((Misc_State[objoff] & 0x7f) == 2) {
        // SetHSpd
        Misc_Y_Speed[objoff] = 0xfe;
        Enemy_State[bVar2] = Enemy_State[bVar2] & 0xf7;

        expect(Enemy_MovingDir[bVar2] == 1 || Enemy_MovingDir[bVar2] == 2);

        Misc_X_Speed[objoff] = Enemy_MovingDir[bVar2] == 1 ? 16 : -16;
      }

      // SetHPos
      Misc_State[objoff] -= 1;

      ADD_UNSIGNED_16_16_8(Misc_PageLoc[objoff], Misc_X_Position[objoff],
                           Enemy_PageLoc[bVar2], Enemy_X_Position[bVar2],
                           2);

      Misc_Y_Position[objoff] = Enemy_Y_Position[bVar2] - 10;
      Misc_Y_HighPos[objoff] = 1;
    }
  }

  GetMiscOffscreenBits(objoff);
  RelativeMiscPosition(objoff);
  GetMiscBoundBox(objoff);
  DrawHammer(objoff);
}

// SMB:bba7
// SM2MAIN:8772
// Signature: [X] -> []
static inline void ProcJumpCoin(const u8 objoff) {
  if (Misc_State[objoff] == 1) {
    // JCoinRun
    const u8 in_r01 = 3;
    ImposeGravity(0, objoff + 0xd, 0x50, in_r01, 6);

    if (Misc_Y_Speed[objoff] == 5) {
      Misc_State[objoff] += 1;
    }
  } else {
    Misc_State[objoff] += 1;

    ADD_UNSIGNED_16_8(Misc_PageLoc[objoff], Misc_X_Position[objoff],
                      ScrollAmount);

    if (Misc_State[objoff] == 0x30) {
      Misc_State[objoff] = 0;
      return;
    }
  }

  RelativeMiscPosition(objoff);
  GetMiscOffscreenBits(objoff);
  GetMiscBoundBox(objoff);
  JCoinGfxHandler(objoff);
}

// SMB:bb96
// SM2MAIN:8761
// Signature: [] -> []
void MiscObjectsCore(void) {
  for (int i = 8; i >= 0; i--) {
    if (Misc_State[i] == 0) {
      continue;
    }

    if ((i8)Misc_State[i] < 0) {
      ProcHammerObj(i);
    } else {
      ProcJumpCoin(i);
    }
  }
}


// SMB:bbfe
// SM2MAIN:87c3
// Signature: [] -> []
void GiveOneCoin(void) {
  DigitModifier[5] = 1;

#ifdef SMB1_MODE
  DigitsMathRoutine(CurrentPlayer == 0 ? 0x17 : 0x1d);
#endif
#ifdef SMB2J_MODE
  DigitsMathRoutine(0x11);
#endif

  CoinTally += 1;
  if (CoinTally == 100) {
    CoinTally = 0;
    NumberofLives += 1;
    Square2SoundQueue = SOUND_SQ2_1UP;
  }
  DigitModifier[4] = 2;
  AddToScore();
}


// SMB:bc27
// SM2MAIN:87e8
// Signature: [] -> []
void AddToScore(void) {
#ifdef SMB1_MODE
  DigitsMathRoutine(CurrentPlayer == 0 ? 11 : 17);
#endif

#ifdef SMB2J_MODE
  DigitsMathRoutine(0xb);
#endif

  WriteScoreAndCoinTally();
}


// SMB:bc30
// SM2MAIN:87ed
// Signature: [] -> []
void WriteScoreAndCoinTally(void) {
  // Also called "GetSBNybbles" in the SMB1 disassembly

  #ifdef SMB1_MODE
    WriteDigits(CurrentPlayer == 0 ? 0x02 : 0x13);
  #endif

  #ifdef SMB2J_MODE
    WriteDigits(0x01);
  #endif
}


// SMB:bc36
// SM2MAIN:87ef
// Signature: [A] -> []
void WriteDigits(const u8 param_1) {
  PrintStatusBarNumbers(param_1);
  if (VRAM_Buffer1[VRAM_Buffer1_Offset - 6] == 0) {
    VRAM_Buffer1[VRAM_Buffer1_Offset - 6] = 0x24;
  }
}


// SMB:bc49
// SM2MAIN:8802
// Signature: [X] -> []
void SetupPowerUp(const u8 param_1) {
  Enemy_ID[5] = A_POWERUP;
  Enemy_PageLoc[5] = Block_PageLoc[param_1];
  Enemy_X_Position[5] = Block_X_Position[param_1];
  Enemy_Y_HighPos[5] = 1;
  Enemy_Y_Position[5] = Block_Y_Position[param_1] - 8;
  PwrUpJmp();
}


// SMB:bc60
// SM2MAIN:8819
// Signature: [] -> []
void PwrUpJmp(void) {
  Enemy_State[5] = 1;
  Enemy_Flag[5] = 1;
  Enemy_BoundBoxCtrl[5] = 3;
  if (PowerUpType == POWERUP_MUSHROOM || PowerUpType == POWERUP_FIREFLOWER) {
    expect(is_playerstatus_valid(PlayerStatus));

    switch (PlayerStatus) {
    case PLAYERSTATUS_SMALL:      PowerUpType = POWERUP_MUSHROOM; break;
    case PLAYERSTATUS_BIG:        PowerUpType = POWERUP_FIREFLOWER; break;
    case PLAYERSTATUS_FIREFLOWER: PowerUpType = POWERUP_FIREFLOWER; break;
    }
  }
  Enemy_SprAttrib[5] = 0x20;
  Square2SoundQueue = SOUND_SQ2_POWERUP_BLOCK;
}


// SMB:bc85
// SM2MAIN:883e
void PowerUpObjHandler(const u8 objoff) {
  // Original signature: [] -> []
  // Note: This port accepts an objoff argument. The original hard-coded "5".

  if (Enemy_State[objoff] != 0) {
    if ((char)Enemy_State[objoff] < 0) {
      if (TimerControl == 0) {

        // NES note: The original SMB2J checks for PowerUpType == 5,
        // but it doesn't exist.
        // This port ignores it.

        expect(is_powerup_valid(PowerUpType));

        switch (PowerUpType) {
        case POWERUP_MUSHROOM:
        case POWERUP_1UP:
#ifdef SMB2J_MODE
        case POWERUP_POISONSHROOM:
#endif
          MoveNormalEnemy(objoff);
          EnemyToBGCollisionDet(objoff);
          break;

        case POWERUP_STAR:
          MoveJumpingEnemy(objoff);
          EnemyJump(objoff);
          break;
        }
      }
    } else {
      if ((FrameCounter & 3) == 0) {
        Enemy_Y_Position[objoff] -= 1;
        const bool bVar2 = Enemy_State[objoff] > 0x10;
        Enemy_State[objoff] = Enemy_State[objoff] + 1;
        if (bVar2) {
          Enemy_X_Speed[objoff] = 0x10;
          Enemy_State[objoff] = 0x80;
          Enemy_SprAttrib[objoff] = 0;
          Enemy_MovingDir[objoff] = 1;
        }
      }
      if (Enemy_State[objoff] < 6) {
        return;
      }
    }
    RelativeEnemyPosition(objoff);
    GetEnemyOffscreenBits(objoff);
    GetEnemyBoundBox(objoff);
    DrawPowerUp(objoff);
    PlayerEnemyCollision(objoff);
    OffscreenBoundsCheck(objoff);
  }
}


// SMB:bced
// SM2MAIN:88ae
void PlayerHeadCollision(const u8 param_1, const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [A, r02, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  Block_State[BlockOffsetToggle] = (PlayerSize == 0) ? 0x12 : 0x11;
  DestroyBlockMetatile(mt_x, mt_y);

  const u8 sprdataoff = BlockOffsetToggle;

  // These are only read from BlockObjMT_Updater.
  Block_Orig_YPos[sprdataoff] = mt_y * 16;
  Block_BBuf_Low[sprdataoff] = MTX_TO_R06(mt_x);

  const u8 mt = get_metatile(mt_x, mt_y);

  // Inlined: BlockBumpedChk

  if (metatile_is_itemblock(mt)) {
    Block_State[sprdataoff] = 0x11;
    if ((mt == MT_BRICK_2_COINS) || (mt == MT_BRICK_COINS)) {
      if (BrickCoinTimerFlag == 0) {
        BrickCoinTimer = 0xb;
        BrickCoinTimerFlag = 1;
      }
      Block_Metatile[sprdataoff] = (BrickCoinTimer == 0) ? MT_BLOCK_EMPTY : mt;
    } else {
      Block_Metatile[sprdataoff] = MT_BLOCK_EMPTY;
    }
  } else {
    Block_Metatile[sprdataoff] = (PlayerSize == 0) ? MT_0 : mt;
  }

  InitBlock_XY_Pos(sprdataoff);

  set_metatile(mt_x, mt_y, MT_SPECIAL_BLOCKHIT);

  BlockBounceTimer = 0x10;
  const u8 yadderdata = ((CrouchingFlag == 0) && (PlayerSize == 0)) ? 0x4 : 0x12;
  Block_Y_Position[sprdataoff] = (Player_Y_Position + yadderdata) & 0xf0;

  if (Block_State[sprdataoff] == 0x11) {
    BumpBlock(mt_x, mt_y, param_1);
  } else {
    BrickShatter(mt_x, mt_y);
  }
  BlockOffsetToggle ^= 1;
}


// SMB:bd84
// SM2MAIN:8945
// Signature: [X] -> []
void InitBlock_XY_Pos(const u8 param_1) {
  ADD_UNSIGNED_16_16_8(Block_PageLoc[param_1], Block_X_Position[param_1],
                       Player_PageLoc, Player_X_Position,
                       8);

  Block_X_Position[param_1] &= 0xf0;
  Block_PageLoc2[param_1] = Block_PageLoc[param_1];

  Block_Y_HighPos[param_1] = Player_Y_HighPos;
}


// SMB:bd9b
// SM2MAIN:895c
void BumpBlock(const u16 mt_x, const u16 mt_y, const u8 mt) {
  // Note: Old signature was [r02, r05, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  bool bug = false;

  // NES note: We're reimplementing a bug here.
  // The call to `CheckTopOfBlock` might set $05 to a value between 0x20 and 0x28 inclusive.
  // The value in $05 is later used as an argument to `BlockBumpedChk`:
  //   LDA $05
  //   JSR BlockBumpedChk
  //
  // Unmodded ROMs for SMB1 and SMB2J will never match anything in `BlockBumpedChk` in this case,
  // because all values in the table it uses are >= 0x52.
#if 1
  // Start bug reimplementation here

  // -> CheckTopOfBlock
  if (mt_y > 0) {
    const u16 mt_y_above = mt_y - 1;
    if (get_metatile(mt_x, mt_y_above) == MT_COIN) {
      // -> RemoveCoin_Axe
      //   -> PutBlockMetatile

      bug = true;
    }
  }

  // End bug reimplementation here
#endif

  const u8 bVar2 = CheckTopOfBlock(mt_x, mt_y);
  Square1SoundQueue = SOUND_SQ1_BUMP;
  Block_X_Speed[bVar2] = 0;
  Block_Y_MoveForce[bVar2] = 0;
  Player_Y_Speed = 0;
  Block_Y_Speed[bVar2] = 0xfe;

  if (bug) {
    return;
  }

  // NES note: the original remapped the metatiles to indices in the jumptable list.
  // Instead, we'll just switch on the metatile itself.
  // The original lookup comes from the index in BlockBumpedChk() -> BrickQBlockMetatiles, which is optimized away in this port.

  switch (mt) {
  case MT_QUESTIONBLOCK_POWERUP:
  case MT_BRICK_2_POWERUP:
  case MT_BRICK_POWERUP:
    MushFlowerBlock(bVar2);
    break;

  case MT_QUESTIONBLOCK_COIN:
  case MT_HIDDEN_1COIN:
  case MT_BRICK_2_COINS:
  case MT_BRICK_COINS:
    CoinBlock(bVar2);
    break;

  case MT_HIDDEN_1UP:
  case MT_BRICK_2_1UP:
  case MT_BRICK_1UP:
    ExtraLifeMushBlock(bVar2);
    break;

  case MT_BRICK_2_VINE:
  case MT_BRICK_VINE:
    VineBlock();
    break;

  case MT_BRICK_2_STAR:
  case MT_BRICK_STAR:
    StarBlock(bVar2);
    break;

#ifdef SMB2J_MODE
  case MT_HIDDEN_POWERUP:
    MushFlowerBlock(bVar2);
    break;

  case MT_QUESTIONBLOCK_POISONSHROOM:
  case MT_HIDDEN_POISONSHROOM:
  case MT_BRICK_2_POISONSHROOM:
  case MT_BRICK_POISONSHROOM:
    PoisonMushBlock(bVar2);
    break;
#endif
  }
}


// SMB:bdd2
// SM2MAIN:899b
// Signature: [X] -> []
void MushFlowerBlock(const u8 param_1) {
  PowerUpType = POWERUP_MUSHROOM;
  SetupPowerUp(param_1);
}


// SMB:bdd5
// SM2MAIN:899e
// Signature: [X] -> []
void StarBlock(const u8 param_1) {
  PowerUpType = POWERUP_STAR;
  SetupPowerUp(param_1);
}


// SMB:bdd8
// SM2MAIN:89a4
// Signature: [X] -> []
void ExtraLifeMushBlock(const u8 param_1) {
  PowerUpType = POWERUP_1UP;
  SetupPowerUp(param_1);
}


// SMB:bddf
// SM2MAIN:89ab
// Signature: [] -> []
void VineBlock(void) {
  Setup_Vine(5, BlockOffsetToggle);
}


// SMB:be02
// SM2MAIN:89d3
void BrickShatter(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  const u8 sVar1 = CheckTopOfBlock(mt_x, mt_y);
  Block_RepFlag[sVar1] = 1;
  NoiseSoundQueue = SOUND_NOISE_BRICKSHATTER;
  SpawnBrickChunks(sVar1);
  Player_Y_Speed = 0xfe;
  DigitModifier[5] = 5;
  AddToScore();
}


// SMB:be1f
// SM2MAIN:89f0
u8 CheckTopOfBlock(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06, r07] -> [X]
  // Reworked to use metatile coordinates instead of pointer

  if (mt_y == 0) {
    return BlockOffsetToggle;
  }

  const u16 mt_y_above = mt_y - 1;

  if (get_metatile(mt_x, mt_y_above) != MT_COIN) {
    return BlockOffsetToggle;
  }

  set_metatile(mt_x, mt_y_above, MT_0);

  RemoveCoin_Axe(mt_x, mt_y_above);

  const u8 sprdataoffset_ctrl = BlockOffsetToggle;

  // Inlines SetupJumpCoin
  // Inlines FindEmptyMiscSlot

  JumpCoinMiscOffset = 8;

  for (int i = 8; i >= 6; i--) {
    if (Misc_State[i] == 0) {
      JumpCoinMiscOffset = i;
      break;
    }
  }

  Misc_PageLoc[JumpCoinMiscOffset] = Block_PageLoc2[sprdataoffset_ctrl];
  Misc_X_Position[JumpCoinMiscOffset] = mt_x * 16 + 5;
  Misc_Y_Position[JumpCoinMiscOffset] = mt_y_above * 16 + 32 + (mt_x & 0x10 ? 1 : 0);
  JCoinC(sprdataoffset_ctrl, JumpCoinMiscOffset);
  return sprdataoffset_ctrl;
}


// SMB:be41
// SM2MAIN:8a12
// Signature: [X] -> []
void SpawnBrickChunks(const u8 param_1) {
  Block_Orig_XPos[param_1] = Block_X_Position[param_1];
  Block_X_Speed[param_1] = 0xf0;
  Block_X_Speed[param_1 + 2] = 0xf0;
  Block_Y_Speed[param_1] = 0xfa;
  Block_Y_Speed[param_1 + 2] = 0xfc;
  Block_Y_MoveForce[param_1] = 0;
  Block_Y_MoveForce[param_1 + 2] = 0;
  Block_PageLoc[param_1 + 2] = Block_PageLoc[param_1];
  Block_X_Position[param_1 + 2] = Block_X_Position[param_1];
  Block_Y_Position[param_1 + 2] = Block_Y_Position[param_1] + 8;
  Block_Y_Speed[param_1] = 0xfa;
}


// SMB:be70
// SM2MAIN:8a41
// Signature: [X] -> []
void BlockObjectsCore(const u8 objoff) {
  u8 bStack0000 = Block_State[objoff];
  if (bStack0000 == 0) {
    Block_State[objoff] = 0;
    return;
  }
  bStack0000 &= 0xf;
  if (bStack0000 == 1) {
    ImposeGravityBlock(objoff + 9);
    RelativeBlockPosition(objoff);
    GetBlockOffscreenBits(objoff);
    DrawBlock(objoff);
    if (4 < (Block_Y_Position[objoff] & 0xf)) {
      Block_State[objoff] = 1;
      return;
    }
    Block_RepFlag[objoff] = 1;
    Block_State[objoff] = 0;
    return;
  } else {
    ImposeGravityBlock(objoff + 9);
    MoveObjectHorizontally(objoff + 9);
    ImposeGravityBlock(objoff + 9 + 2);
    MoveObjectHorizontally(objoff + 9 + 2);
    RelativeBlockPosition(objoff);
    GetBlockOffscreenBits(objoff);
    DrawBrickChunks(objoff);
    if (Block_Y_HighPos[objoff] == 0) {
      Block_State[objoff] = bStack0000;
      return;
    }
    if (Block_Y_Position[objoff + 2] > 0xf0) {
      Block_Y_Position[objoff + 2] = 0xf0;
    }
    if (Block_Y_Position[objoff] < 0xf0) {
      Block_State[objoff] = bStack0000;
      return;
    }
    Block_State[objoff] = 0;
  }
}


// SMB:bed4
// SM2MAIN:8aa5
// Signature: [] -> []
void BlockObjMT_Updater(void) {
  for (int i = 1; i >= 0; i--) {
    if (VRAM_Buffer1[0] != 0) {
      continue;
    }

    if (Block_RepFlag[i] == 0) {
      continue;
    }

    // These are only written from PlayerHeadCollision.
    const u8 bbuf_lo = Block_BBuf_Low[i];
    const u8 ypos = Block_Orig_YPos[i];
    const u8 metatile = Block_Metatile[i];

    const u16 mt_x = R06_TO_MTX_lossy(bbuf_lo);
    const u16 mt_y = ypos / 16;

    set_metatile(mt_x, mt_y, metatile);

    ReplaceBlockMetatile(metatile, i, mt_x, mt_y);

    Block_RepFlag[i] = 0;
  }
}


// SMB:bf02
// SM2MAIN:8ad3
// Signature: [X] -> [A]
u8 MoveEnemyHorizontally(const u8 param_1) {
  return MoveObjectHorizontally(param_1 + 1);
}


// SMB:bf09
// SM2MAIN:8ada
// Signature: [] -> [A]
u8 MovePlayerHorizontally(void) {
  if (JumpspringAnimCtrl == 0) {
    return MoveObjectHorizontally(0);
  }
  return JumpspringAnimCtrl;
}


// SMB:bf0f
// SM2MAIN:8ae0
// Signature: [X] -> [A]
u8 MoveObjectHorizontally(const u8 param_1) {
  // NES note: the original sign-extends the high nibble (ORA #$F0), but we just cast it to signed here.
  const i16 b = ((i16)(i8)SprObject_X_Speed[param_1]) * 16;

  const u8 old_x = SprObject_X_Position[param_1];

  ADD_SIGNED_24_16(SprObject_PageLoc[param_1], SprObject_X_Position[param_1], SprObject_X_MoveForce[param_1],
                   b>>8, b&0xff);

  // The NES version is a bit tricker with the way it carries the bytes around,
  // but the return value ends up being the difference in the x position.

  // The return value of this function is eventually used by PositionPlayerOnHPlat.
  return SprObject_X_Position[param_1] - old_x;
}


// SMB:bf4d
// SM2MAIN:8b1e
// Signature: [] -> []
void MovePlayerVertically(void) {
  if ((TimerControl != 0) || (JumpspringAnimCtrl == 0)) {
    ImposeGravitySprObj(4, 0, VerticalForce);
  }
}


// SMB:bf63
// SM2MAIN:8b34
// Signature: [X] -> []
void MoveD_EnemyVertically(const u8 objoff) {
  if (Enemy_State[objoff] == 5) {
    MoveFallingPlatform(objoff);
  } else {
    SetXMoveAmt(3, objoff, 0x3d);
  }
}


// SMB:bf6b
// SM2MAIN:8b3c
// Signature: [X] -> []
void MoveFallingPlatform(const u8 param_1) {
  SetXMoveAmt(3, param_1, 0x20);
}


// SMB:bf70
// SM2MAIN:8b41
// Signature: [X] -> []
void MoveRedPTroopaDown(const u8 objoff) {
  ImposeGravity(0, objoff + 1, 3, 6, 2);
}


// SMB:bf75
// SM2MAIN:8b46
// Signature: [X] -> []
void MoveRedPTroopaUp(const u8 objoff) {
  ImposeGravity(1, objoff + 1, 3, 6, 2);
}


// SMB:bf88
// SM2MAIN:8b59
// Signature: [X] -> []
void MoveDropPlatform(const u8 objoff) {
  SetXMoveAmt(2, objoff, 0x7f);
}


// SMB:bf8c
// SM2MAIN:8b5d
// Signature: [X] -> []
void MoveEnemySlowVert(const u8 objoff) {
  SetXMoveAmt(2, objoff, 0xf);
}


// SMB:bf92
// SM2MAIN:8b63
// Signature: [X] -> []
void MoveJ_EnemyVertically(const u8 objoff) {
  SetXMoveAmt(3, objoff, 0x1c);
}


// SMB:bf96
// SM2MAIN:8b67
// Signature: [A, X, Y] -> []
void SetXMoveAmt(const u8 param_1, const u8 param_2, const u8 param_3) {
  ImposeGravitySprObj(param_1, param_2 + 1, param_3);
}


// SMB:bfa4
// SM2MAIN:8b75
// Signature: [X] -> []
void ImposeGravityBlock(const u8 param_1) {
  const u8 in_r01 = 0;

  ImposeGravity(0, param_1, 0x50, in_r01, 8);
}


// SMB:bfad
// SM2MAIN:8b7e
// Signature: [A, X, r00] -> []
void ImposeGravitySprObj(const u8 param_1, const u8 param_2, const u8 param_3) {
  const u8 in_r01 = 0;

  ImposeGravity(0, param_2, param_3, in_r01, param_1);
}


// SMB:bfb4
// SM2MAIN:8b85
// Signature: [X] -> []
void MovePlatformDown(const u8 objoff) {
  const u8 bVar1 = (Enemy_ID[objoff] == A_LARGEPLATFORM_DROP) ? 9 : 5;
  ImposeGravity(0, objoff + 1, bVar1, 10, 3);
}


// SMB:bfb7
// SM2MAIN:8b88
// Signature: [X] -> []
void MovePlatformUp(const u8 objoff) {
  const u8 bVar1 = (Enemy_ID[objoff] == A_LARGEPLATFORM_DROP) ? 9 : 5;
  ImposeGravity(1, objoff + 1, bVar1, 10, 3);
}


// SMB:bfd7
// SM2MAIN:8ba8
// Signature: [A, X, r00, r01, r02] -> []
void ImposeGravity(const u8 param_1, const u8 param_2, const u8 param_3, const u8 param_4, const u8 param_5) {
  ADD_SIGNED_24_16(SprObject_Y_HighPos[param_2], SprObject_Y_Position[param_2], SprObject_YMF_Dummy[param_2],
                   SprObject_Y_Speed[param_2], SprObject_Y_MoveForce[param_2]);

  ADD_UNSIGNED_16_8(SprObject_Y_Speed[param_2], SprObject_Y_MoveForce[param_2],
                    param_3);

  const u8 q = param_5;
  const u8 h = SprObject_Y_Speed[param_2];
  const u8 r = SprObject_Y_MoveForce[param_2];

  // The intention is probably to compare `hr - q0 >= 0x80`,
  // but there may be edge cases

  if ((i8)(h - q) >= 0) {
    if (r >= 0x80) {
      // Clamp the speed to a maximum value
      SprObject_Y_Speed[param_2] = q;
      SprObject_Y_MoveForce[param_2] = 0;
    }
  }

  if (param_1 != 0) {
    SUB_UNSIGNED_16_8(SprObject_Y_Speed[param_2], SprObject_Y_MoveForce[param_2],
                      param_4);

    const u8 s = SprObject_Y_Speed[param_2];
    const u8 t = SprObject_Y_MoveForce[param_2];

    if ((i8)(s + q) < 0) {
      if (t < 0x80) {
        // Clamp the speed to a minimum value
        SprObject_Y_Speed[param_2] = -q;
        SprObject_Y_MoveForce[param_2] = 0xff;
      }
    }
  }
}


// SMB:c047
// SM2MAIN:8c23
// Signature: [X] -> []
void EnemiesAndLoopsCore(const u8 objoff) {
  if (Enemy_Flag[objoff] & 0x80) {
    if (Enemy_Flag[Enemy_Flag[objoff] & 0xf] == 0) {
      Enemy_Flag[objoff] = 0;
    }
  } else {
    if (Enemy_Flag[objoff] != 0) {
      RunEnemyObjectsCore(objoff);
      return;
    }
    if ((AreaParserTaskNum & 7) != 7) {
      ProcLoopCommand(objoff);
    }
  }
}


// SMB:c08c
// SM2MAIN:8c77
// Signature: [Y] -> []
void ExecGameLoopback(const u8 param_1) {
  Player_PageLoc -= 4;
  CurrentPageLoc -= 4;
  ScreenLeft_PageLoc -= 4;
  ScreenRight_PageLoc -= 4;
  AreaObjectPageLoc -= 4;
  EnemyObjectPageSel = 0;
  AreaObjectPageSel = 0;
  EnemyDataOffset = 0;
  EnemyObjectPageLoc = 0;
  AreaDataOffset = AreaDataOfsLoopback[param_1];
}


// SMB:c0cc
// SM2MAIN:8cb7
// Signature: [X] -> []
void ProcLoopCommand(const u8 objoff) {
  u8 bVar3;
  bool bVar6;

  do {
    if (LoopCommand != 0 && CurrentColumnPos == 0) {
      for (int idx = ssw(0xb,0xc)-1; idx >= 0; idx--) {
        if (WorldNumber != LoopCmdWorldNumber[idx] || CurrentPageLoc != LoopCmdPageNumber[idx]) {
          continue;
        }

        if (Player_Y_Position == LoopCmdYPosition[idx] && Player_State == PLAYERSTATE_ONGROUND) {
          MultiLoopCorrectCntr += 1;
        }

        if (SMB1_ONLY && WorldNumber != 6) {
          if (Player_Y_Position != LoopCmdYPosition[idx] || Player_State != PLAYERSTATE_ONGROUND) {
            ExecGameLoopback(idx);
            KillAllEnemies();
          }
          MultiLoopPassCntr = 0;
          MultiLoopCorrectCntr = 0;
          LoopCommand = 0;
          break;
        }

        MultiLoopPassCntr += 1;
    #ifdef SMB1_MODE
        const u8 cmp_val = 3;
    #endif
    #ifdef SMB2J_MODE
        const u8 cmp_val = MultiLoopCount[idx];
    #endif
        if (MultiLoopPassCntr == cmp_val) {
          if (MultiLoopCorrectCntr != cmp_val) {
            ExecGameLoopback(idx);
            KillAllEnemies();
          }
          MultiLoopPassCntr = 0;
          MultiLoopCorrectCntr = 0;
        }
        LoopCommand = 0;
        break;
      }
    }

    u8 bVar4 = EnemyDataOffset;
    if (EnemyFrenzyQueue != 0) {
      Enemy_ID[objoff] = EnemyFrenzyQueue;
      Enemy_Flag[objoff] = 1;
      Enemy_State[objoff] = 0;
      EnemyFrenzyQueue = 0;
      InitEnemyObject(objoff);
      return;
    }

    if (EnemyData[EnemyDataOffset] == 0xff) {
      // CheckFrenzyBuffer
      bVar4 = EnemyFrenzyBuffer;
      if (EnemyFrenzyBuffer == 0) {
        if (VineFlagOffset != 1) {
          return;
        }
        bVar4 = A_VINE;
      }
      Enemy_ID[objoff] = bVar4;
      InitEnemyObject(objoff);
      return;
    }

    if ((((EnemyData[EnemyDataOffset] & 0xf) != 0xe) && (objoff >= 5))
        && ((EnemyData[(u8)(EnemyDataOffset + 1)] & 0x3f) != 0x2e)) {
      return;
    }

    u8 bVar1 = ScreenRight_X_Pos + 0x30;
    const u8 bVar2 = ScreenRight_PageLoc + (ScreenRight_X_Pos >= 0xd0);
    const u8 bVar5 = EnemyDataOffset + 1;
    if (((char)EnemyData[bVar5] < 0) && (EnemyObjectPageSel == 0)) {
      EnemyObjectPageSel = 1;
      EnemyObjectPageLoc += 1;
    }

    if (((EnemyData[EnemyDataOffset] & 0xf) != 0xf) || (EnemyObjectPageSel != 0)) {
      Enemy_PageLoc[objoff] = EnemyObjectPageLoc;
      bVar3 = EnemyData[bVar4] & 0xf0;
      Enemy_X_Position[objoff] = bVar3;
      if ((ScreenRight_X_Pos <= bVar3 && ScreenRight_PageLoc <= Enemy_PageLoc[objoff])
          || (ScreenRight_X_Pos > bVar3 && ScreenRight_PageLoc < Enemy_PageLoc[objoff])) {
        bVar6 = (bVar1 & 0xf0) < Enemy_X_Position[objoff];
        if ((bVar6 || bVar2 < Enemy_PageLoc[objoff]) && (!bVar6 || bVar2 <= Enemy_PageLoc[objoff])) {
          // CheckFrenzyBuffer
          bVar4 = EnemyFrenzyBuffer;
          if (EnemyFrenzyBuffer == 0) {
            if (VineFlagOffset != 1) {
              return;
            }
            bVar4 = A_VINE;
          }
          Enemy_ID[objoff] = bVar4;
          InitEnemyObject(objoff);
          return;
        }
        Enemy_Y_HighPos[objoff] = 1;
        bVar1 = EnemyData[bVar4];
        Enemy_Y_Position[objoff] = bVar1 * 0x10;
        if ((u8)(bVar1 * 0x10) != 0xe0) {
          if (((EnemyData[bVar5] & 0x40) != 0) && (SecondaryHardMode == 0)) {
            EnemyDataOffset += 2;
            EnemyObjectPageSel = 0;
            return;
          }
          bVar4 = EnemyData[bVar5] & 0x3f;
          if (is_actor_groupenemy(bVar4)) {
            HandleGroupEnemies(bVar4);
            return;
          }
          if ((bVar4 == A_GOOMBA) && (PrimaryHardMode != 0)) {
            bVar4 = A_BUZZY_BEETLE;
          }
          Enemy_ID[objoff] = bVar4;
          Enemy_Flag[objoff] = 1;
          InitEnemyObject(objoff);
          if (Enemy_Flag[objoff] == 0) {
            return;
          }
          EnemyDataOffset += 2;
          EnemyObjectPageSel = 0;
          return;
        }
      } else if ((EnemyData[bVar4] & 0xf) != 0xe) {
        CheckThreeBytes();
        return;
      }
      if ((SMB2J_ONLY && WorldNumber == 8) || (EnemyData[(u8)(bVar4 + 2)] >> 5 == WorldNumber)) {
        AreaPointer = EnemyData[(u8)(bVar4 + 1)];
        EntrancePage = EnemyData[(u8)(bVar4 + 2)] & 0x1f;
      }
      EnemyDataOffset += 1;
      EnemyDataOffset += 2;
      EnemyObjectPageSel = 0;
      return;
    }

    EnemyObjectPageLoc = EnemyData[bVar5] & 0x3f;
    EnemyDataOffset += 2;
    EnemyObjectPageSel = 1;
  } while (true);
}


// SMB:c226
// SM2MAIN:8e03
// Signature: [X] -> []
void InitEnemyObject(const u8 objoff) {
  Enemy_State[objoff] = 0;
  CheckpointEnemyID(objoff);
}


// SMB:c250
// SM2MAIN:8e34
// Signature: [] -> []
void CheckThreeBytes(void) {
  if ((EnemyData[EnemyDataOffset] & 0xf) == 0xe) {
    EnemyDataOffset += 1;
  }
  EnemyDataOffset += 2;
  EnemyObjectPageSel = 0;
}


// SMB:c26c
// SM2MAIN:8e50
// Signature: [X] -> []
void CheckpointEnemyID(const u8 param_1) {
  const u8 enemy_id = Enemy_ID[param_1];

  expect(is_actor_valid(enemy_id));
  expect(!is_actor_groupenemy(enemy_id));

  if (is_actor_enemy(enemy_id)) {
    Enemy_Y_Position[param_1] += 8;
    EnemyOffscrBitsMasked[param_1] = 1;
  }

  // For most of these, param_1 = objoff ($08)
  // exceptions may be:
  // Enemy_ID = 0,2,6 (HandleGroupEnemies)
  const u8 objoff = param_1;

  switch (enemy_id) {
  case A_GREEN_KOOPA:
  case A_RED_KOOPA_GREENLIKE:
  case A_BUZZY_BEETLE:
    InitNormalEnemy(param_1);
    return;

  case A_RED_KOOPA:
    InitRedKoopa(objoff);
    return;

  case A_PIRANHA_PLANT_SMB2J:
    if (SMB2J_ONLY) {
      InitPiranhaPlant(objoff);
    }
    return;

  case A_HAMMER_BRO:
    InitHammerBro(objoff);
    return;

  case A_GOOMBA:
    InitGoomba(param_1);
    return;

  case A_BLOOBER:
    InitBloober(objoff);
    return;

  case A_BULLET_BILL:
    InitBulletBill(objoff);
    return;

  case A_CHEEPCHEEP_GRAY:
  case A_CHEEPCHEEP_RED:
    InitCheepCheep(objoff);
    return;

  case A_PODOBOO:
    InitPodoboo(objoff);
    return;

  case A_PIRANHA_PLANT:
    InitPiranhaPlant(objoff);
    return;

  case A_GREEN_PARATROOPA:
    InitJumpGPTroopa(objoff);
    return;

  case A_RED_PARATROOPA:
    InitRedPTroopa(objoff);
    return;

  case A_GREEN_PARATROOPA_HORIZONTAL:
    InitHorizFlySwimEnemy(objoff);
    return;

  case A_LAKITU:
    InitLakitu(objoff);
    return;

  case A_SPINY:
  case A_FLYING_CHEEPCHEEP:
  case A_BOWSER_FLAME:
  case A_FIREWORKS:
  case A_BULLET_BILL_OR_CHEEPCHEEP_FRENZY:
    InitEnemyFrenzy(objoff);
    return;

  case A_STOP_FRENZY:
    EndFrenzy(objoff);
    return;

  case A_FIREBAR_1:
  case A_FIREBAR_2:
  case A_FIREBAR_3:
  case A_FIREBAR_4:
    InitShortFirebar(objoff);
    return;

  case A_FIREBAR_5:
    InitLongFirebar(objoff);
    return;

  case A_LARGEPLATFORM_BALANCE:
    InitBalPlatform(objoff);
    return;

  case A_LARGEPLATFORM_Y_MOVING:
    InitVertPlatform(objoff);
    return;

  case A_LARGEPLATFORM_LIFT1:
    LargeLiftUp(objoff);
    return;

  case A_LARGEPLATFORM_LIFT2:
    LargeLiftDown(objoff);
    return;

  case A_LARGEPLATFORM_X_MOVING:
  case A_LARGEPLATFORM_RIGHT:
    InitHoriPlatform(objoff);
    return;

  case A_LARGEPLATFORM_DROP:
    InitDropPlatform(objoff);
    return;

  case A_SMALLPLATFORM_1:
    PlatLiftUp(objoff);
    return;

  case A_SMALLPLATFORM_2:
    PlatLiftDown(objoff);
    return;

  case A_BOWSER:
    InitBowser(objoff);
    return;

  case A_POWERUP:
    PwrUpJmp();
    return;

  case A_VINE:
    // NES note: Y is set to 0x60 by the jump engine and used by Setup_Vine. This is a bug.
    // The bug is worked around in Setup_Vine.
    Setup_Vine(objoff, 0x60);
    return;

  case A_RETAINER:
    InitRetainerObj(objoff);
    return;
  }
}


// SMB:c2f1
// SM2MAIN:8ed5
// Signature: [X] -> []
void InitGoomba(const u8 param_1) {
  InitNormalEnemy(param_1);
  SmallBBox(param_1);
}


// SMB:c2f7
// SM2MAIN:8edb
// Signature: [X] -> []
void InitPodoboo(const u8 objoff) {
  Enemy_Y_HighPos[objoff] = 2;
  Enemy_Y_Position[objoff] = 2;
  EnemyIntervalTimer[objoff] = 1;
  Enemy_State[objoff] = 0;
  SmallBBox(objoff);
}


// SMB:c307
// SM2MAIN:8eeb
// Signature: [X] -> []
void InitRetainerObj(const u8 param_1) {
  Enemy_Y_Position[param_1] = 0xb8;
}


// SMB:c30e
// SM2MAIN:8ef2
// Signature: [X] -> []
void InitNormalEnemy(const u8 param_1) {
  Enemy_X_Speed[param_1] = PrimaryHardMode != 0 ? -12 : -8;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
}


// SMB:c31e
// SM2MAIN:8f02
// Signature: [X] -> []
void InitRedKoopa(const u8 objoff) {
  InitNormalEnemy(objoff);
  Enemy_State[objoff] = 1;
}


// SMB:c328
// SM2MAIN:8f0c
// Signature: [X] -> []
void InitHammerBro(const u8 objoff) {
  expect(SecondaryHardMode <= 1);

  HammerThrowingTimer[objoff] = 0;
  Enemy_X_Speed[objoff] = 0;

  bool set_timer = true;

#ifdef SMB2J_MODE
  if (WorldNumber >= 6) { set_timer = false; }
#endif

  if (set_timer) {
    EnemyIntervalTimer[objoff] = SecondaryHardMode == 0 ? 0x80 : 0x50;
  }

  Enemy_BoundBoxCtrl[objoff] = 0xb;
  Enemy_MovingDir[objoff] = 2;
  InitVStf(objoff);
}


// SMB:c33d
// SM2MAIN:8f28
// Signature: [X] -> []
void InitHorizFlySwimEnemy(const u8 param_1) {
  Enemy_X_Speed[param_1] = 0;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
}


// SMB:c342
// SM2MAIN:8f2d
// Signature: [X] -> []
void InitBloober(const u8 objoff) {
  BlooperMoveSpeed[objoff] = 0;
  SmallBBox(objoff);
}


// SMB:c346
// SM2MAIN:8f31
// Signature: [X] -> [A]
u8 SmallBBox(const u8 param_1) {
  Enemy_BoundBoxCtrl[param_1] = 9;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
  return 0;
}


// SMB:c34a
// SM2MAIN:8f35
// Signature: [X] -> []
void InitRedPTroopa(const u8 objoff) {
  char cVar1 = 0x30;
  RedPTroopaOrigXPos[objoff] = Enemy_Y_Position[objoff];
  if (Enemy_Y_Position[objoff] >= 0x80) {
    cVar1 = -0x20;
  }

  // NES note: Carry flag is set to 0 by the caller. ADC without carry is here.
  RedPTroopaCenterYPos[objoff] = cVar1 + Enemy_Y_Position[objoff];

  Enemy_BoundBoxCtrl[objoff] = 3;
  Enemy_MovingDir[objoff] = 2;
  InitVStf(objoff);
}


// SMB:c363
// SM2MAIN:8f4e
// Signature: [X] -> []
void InitVStf(const u8 param_1) {
  Enemy_Y_Speed[param_1] = 0;
  Enemy_Y_MoveForce[param_1] = 0;
}


// SMB:c36b
// SM2MAIN:8f56
// Signature: [X] -> []
void InitBulletBill(const u8 objoff) {
  Enemy_MovingDir[objoff] = 2;
  Enemy_BoundBoxCtrl[objoff] = 9;
}


// SMB:c375
// SM2MAIN:8f60
// Signature: [X] -> []
void InitCheepCheep(const u8 objoff) {
  SmallBBox(objoff);
  CheepCheepMoveMFlag[objoff] = PseudoRandomBitReg[objoff] & 0x10;
  CheepCheepOrigYPos[objoff] = Enemy_Y_Position[objoff];
}


// SMB:c385
// SM2MAIN:8f70
// Signature: [X] -> []
void InitLakitu(const u8 objoff) {
  if (EnemyFrenzyBuffer == 0) {
    SetupLakitu(objoff);
  } else {
    EraseEnemyObject(objoff);
  }
}


// SMB:c38a
// SM2MAIN:8f75
// Signature: [X] -> []
void SetupLakitu(const u8 param_1) {
  // param_1 is not necessarily objoff

  LakituReappearTimer = 0;
  InitHorizFlySwimEnemy(param_1);
  Enemy_BoundBoxCtrl[param_1] = 3;
}


// SMB:c3a4
// SM2MAIN:8f8f
// Signature: [X] -> []
void LakituAndSpinyHandler(const u8 objoff) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }

  if (objoff >= 5) {
    return;
  }

  static const u8 diff_adjust[3][4] = {
    { 0x26, 0x2c, 0x32, 0x38 },
    { 0x20, 0x22, 0x24, 0x26 },
    { 0x13, 0x14, 0x15, 0x16 },
  };

  FrenzyEnemyTimer = 0x80;

  for (int i = 4; i >= 0; i--) {
    if (Enemy_ID[i] == A_LAKITU) {
      if (Player_Y_Position < 0x2c) {
        return;
      }
      if (Enemy_State[i] != 0) {
        return;
      }
      Enemy_PageLoc[objoff] = Enemy_PageLoc[i];
      Enemy_X_Position[objoff] = Enemy_X_Position[i];
      Enemy_Y_HighPos[objoff] = 1;
      Enemy_Y_Position[objoff] = Enemy_Y_Position[i] - 8;

      const u8 rng = PseudoRandomBitReg[objoff] & 3;

      PlayerLakituDiff(objoff,
                       diff_adjust[0][rng],
                       diff_adjust[1][rng],
                       diff_adjust[2][rng]);

      const u8 bVar1 = SmallBBox(objoff);
      Enemy_X_Speed[objoff] = bVar1;
      Enemy_MovingDir[objoff] = (bVar1 < 0x80) ? 1 : 2;
      Enemy_Y_Speed[objoff] = 0xfd;
      Enemy_Flag[objoff] = 1;
      Enemy_State[objoff] = 5;
      return;
    }
  }

  LakituReappearTimer += 1;
  if (LakituReappearTimer > ssw(6, 2)) {
    for (int i = 4; i >= 0; i--) {
      if (Enemy_Flag[i] == 0) {
        Enemy_State[i] = 0;
        Enemy_ID[i] = A_LAKITU;
        SetupLakitu(i);
        u8 bVar1 = 0x20;
        if (SMB2J_ONLY && (HardWorldFlag != 0 || WorldNumber >= 6)) {
          bVar1 = 0x60;
        }
        PutAtRightExtent(bVar1, i);
        return;
      }
    }
  }
}


// SMB:c459
// SM2MAIN:9052
// Signature: [X] -> []
void InitLongFirebar(const u8 objoff) {
  DuplicateEnemyObj(objoff);
  InitShortFirebar(objoff);
}


// SMB:c45c
// SM2MAIN:9055
// Signature: [X] -> []
void InitShortFirebar(const u8 objoff) {
  const u8 enemy_id = Enemy_ID[objoff];

  u8 speed;
  u8 dir;

  switch (enemy_id) {
  case A_FIREBAR_1: speed = 0x28; dir = 0; break;
  case A_FIREBAR_2: speed = 0x38; dir = 0; break;
  case A_FIREBAR_3: speed = 0x28; dir = 16; break;
  case A_FIREBAR_4: speed = 0x38; dir = 16; break;
  case A_FIREBAR_5: speed = 0x28; dir = 0; break;
  default: unreachable(); break;
  }

  FirebarSpinState_Low[objoff] = 0;
  FirebarSpinSpeed[objoff] = speed;
  FirebarSpinDirection[objoff] = dir;
  Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] + 4;

  ADD_UNSIGNED_16_8(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
                    4);

  Enemy_BoundBoxCtrl[objoff] = 3;
}


// SMB:c4a8
// SM2MAIN:90a1
// Signature: [X] -> []
void InitFlyingCheepCheep(const u8 objoff) {
  static const u8 position_lookup[4][4] = {
    { 0x80, 0x30, 0x40, 0x80, },
    { 0x30, 0x50, 0x50, 0x70, },
    { 0x20, 0x40, 0x80, 0xa0, },
    { 0x70, 0x40, 0x90, 0x68, },
  };

  static const u8 speed_lookup[3][4] = {
    { 0x0e, 0x05, 0x06, 0x0e, },
    { 0x1c, 0x20, 0x10, 0x0c, },
    { 0x1e, 0x22, 0x18, 0x14, },
  };

  static const u8 timer_lookup[4] = {
    0x10, 0x60, 0x20, 0x48,
  };

  if (FrenzyEnemyTimer != 0) {
    return;
  }

  expect(objoff <= 5);

  const u8 rng0 = PseudoRandomBitReg[objoff];
  const u8 rng1 = PseudoRandomBitReg[objoff + 1];

  SmallBBox(objoff);

  FrenzyEnemyTimer = timer_lookup[rng1 & 3];

  if (objoff >= ((SecondaryHardMode != 0) ? 4 : 3)) {
    return;
  }

  // This access would be out of bounds if defined earlier
  const u8 rng2 = PseudoRandomBitReg[objoff + 2];

  Enemy_Y_Speed[objoff] = 0xfb;

  u8 currng = rng0 & 3;
  u8 idx = 0;

  if (Player_X_Speed == 0) {
    idx = 0;
  } else if (Player_X_Speed <= 0x18) {
    idx = 1;
  } else {
    idx = 2;
  }

  Enemy_X_Speed[objoff] = speed_lookup[idx][currng];
  Enemy_MovingDir[objoff] = 1;

  if (Player_X_Speed == 0) {
    if ((rng1 & 3) != 0) {
      currng = rng2 & 3;
      idx = (rng2 >> 2) & 3;
    }

    if (currng >= 2) {
      Enemy_X_Speed[objoff] *= 1;
      Enemy_MovingDir[objoff] += 1;
    }
  }

  SET_16_16(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
            Player_PageLoc, Player_X_Position);

  if (currng < 2) {
    SUB_UNSIGNED_16_8(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
                      position_lookup[idx][currng]);
  } else {
    ADD_UNSIGNED_16_8(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
                      position_lookup[idx][currng]);
  }

  Enemy_Flag[objoff] = 1;
  Enemy_Y_HighPos[objoff] = 1;
  Enemy_Y_Position[objoff] = SPRITE_Y_OFFSCREEN;
}


// SMB:c549
// SM2MAIN:9142
// Signature: [X] -> []
void InitBowser(const u8 objoff) {
  if (SMB2J_ONLY) {
    for (int i = 0; i < 5; i++) {
      if (i == objoff) {
        continue;
      }
      if (Enemy_ID[i] == A_BOWSER) {
        Enemy_ID[i] = A_GREEN_KOOPA;
        Enemy_Flag[i] = 0;
      }
    }
  }

  DuplicateEnemyObj(objoff);
  BowserBodyControls = 0;
  BridgeCollapseOffset = 0;
  BowserOrigXPos = Enemy_X_Position[objoff];
  BowserFireBreathTimer = 0xdf;
  BowserFront_Offset = objoff;
  Enemy_MovingDir[objoff] = 0xdf;
  BowserFeetCounter = 0x20;
  EnemyFrameTimer[objoff] = 0x20;
  BowserHitPoints = 5;
  BowserMovementSpeed = 2;
}


// SMB:c575
// SM2MAIN:9186
// Signature: [X] -> []
void DuplicateEnemyObj(const u8 objoff) {
  int i;
  for (i = 0; Enemy_Flag[i] != 0; i++) {
  }

  // i = first offset with flag=0

  DuplicateObj_Offset = i;
  Enemy_Flag[i] = objoff | 0x80;
  Enemy_PageLoc[i] = Enemy_PageLoc[objoff];
  Enemy_X_Position[i] = Enemy_X_Position[objoff];
  Enemy_Flag[objoff] = 1;
  Enemy_Y_HighPos[i] = 1;
  Enemy_Y_Position[i] = Enemy_Y_Position[objoff];
}


// SMB:c5a3
// SM2MAIN:91b4
// Signature: [X] -> []
void InitBowserFlame(const u8 objoff) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }
  Enemy_Y_MoveForce[objoff] = 0;
  u8 bVar1 = BowserFront_Offset;
  NoiseSoundQueue |= SOUND_NOISE_BOWSERFLAME;
  if (Enemy_ID[BowserFront_Offset] != A_BOWSER) {
    bVar1 = SetFlameTimer();
    FrenzyEnemyTimer = bVar1 + 0x20;
    if (SecondaryHardMode != 0) {
      FrenzyEnemyTimer = bVar1 + 0x10;
    }

    const u8 rng = PseudoRandomBitReg[objoff] & 3;
    BowserFlamePRandomOfs[objoff] = rng;
    PutAtRightExtent(FlameYPosData[rng], objoff);
    return;
  }
  const u8 rng = PseudoRandomBitReg[objoff] & 3;
  Enemy_X_Position[objoff] = Enemy_X_Position[BowserFront_Offset] - 0xe;
  Enemy_PageLoc[objoff] = Enemy_PageLoc[bVar1];
  Enemy_Y_Position[objoff] = Enemy_Y_Position[bVar1] + 8;
  BowserFlamePRandomOfs[objoff] = rng;
  Enemy_Y_MoveForce[objoff] = Enemy_Y_Position[objoff] <= FlameYPosData[rng] ? 1 : 0xff;
  EnemyFrenzyBuffer = 0;
  Enemy_BoundBoxCtrl[objoff] = 8;
  Enemy_Y_HighPos[objoff] = 1;
  Enemy_Flag[objoff] = 1;
  Enemy_X_MoveForce[objoff] = 0;
  Enemy_State[objoff] = 0;
}


// SMB:c5d8
// SM2MAIN:91e9
// Signature: [A, X] -> []
void PutAtRightExtent(const u8 param_1, const u8 param_2) {
  Enemy_Y_Position[param_2] = param_1;
  const bool bVar1 = ScreenRight_X_Pos >= 0xe0;
  Enemy_X_Position[param_2] = ScreenRight_X_Pos + 0x20;
  Enemy_PageLoc[param_2] = ScreenRight_PageLoc + bVar1;
  Enemy_BoundBoxCtrl[param_2] = 8;
  Enemy_Y_HighPos[param_2] = 1;
  Enemy_Flag[param_2] = 1;
  Enemy_X_MoveForce[param_2] = 0;
  Enemy_State[param_2] = 0;

  // NES note: The "A" register is set to 0 here. Used by BulletBillCheepCheep
}


// SMB:c63d
// SM2MAIN:924e
// Signature: [X] -> []
void InitFireworks(const u8 objoff) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }

  FrenzyEnemyTimer = 0x20;
  FireworksCounter -= 1;

  int i;

  // Find the star flag object
  for (i = 5; i >= 0; i--) {
    if (Enemy_ID[i] == A_STARFLAG) {
      break;
    }
  }

  assert_smb_crashbug(i >= 0, "A star flag object should exist. If not, the original game would loop infinitely or do something weird here");

  const u8 bVar3 = FireworksCounter + Enemy_State[i];

  u16 x = LOAD_16(Enemy_PageLoc[i], Enemy_X_Position[i]);

  static const u8 xpos_lookup[6] = { 0x00, 0x30, 0x60, 0x60, 0x00, 0x20 };
  static const u8 ypos_lookup[6] = { 0x60, 0x40, 0x70, 0x40, 0x60, 0x30 };

  expect(bVar3 < 6);

  x -= 0x30;
  x += xpos_lookup[bVar3];

  STORE_16(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
           x);

  Enemy_Y_Position[objoff] = ypos_lookup[bVar3];
  Enemy_Y_HighPos[objoff] = 1;

  Enemy_Flag[objoff] = 1;

  ExplosionGfxCounter[objoff] = 0;
  ExplosionTimerCounter[objoff] = 8;
}


// Implements a bag of numbers between 0 and 7 inclusive.
static inline u8 random_from_bag(const u8 seed, u8 * const set) {
  // If all numbers are taken, refill the bag

  if (*set == 0xff) {
    *set = 0;
  }

  u8 i = seed;

  // Find the next available number in the bag
  while (true) {
    i &= 7;
    const u8 mask = 1 << i;
    if ((mask & *set) == 0) {
      // Set as taken
      *set |= mask;

      return i;
    }
    i += 1;
  }
}


// SMB:c69c
// SM2MAIN:92ad
// Signature: [X] -> []
void BulletBillCheepCheep(const u8 objoff) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }

  if (AreaType == AREA_WATER) {
    // Auto-appearing cheep cheeps (in SMB1 2-2 and 7-2)

    if (objoff >= 3) {
      return;
    }

    // Spawn a random cheep-cheep

    bool red_cheepcheep = PseudoRandomBitReg[objoff] >= 0xaa;

    if (WorldNumber != 1) {
      red_cheepcheep = !red_cheepcheep;
    }

    Enemy_ID[objoff] = red_cheepcheep ? A_CHEEPCHEEP_RED : A_CHEEPCHEEP_GRAY;
  } else {
    // Auto-appearing bullet bills (in SMB1 5-3 and 6-3)

    // Prevent too many bullet bills from being spawned
    for (int i = 0; i < 5; i++) {
      if ((Enemy_Flag[i] != 0) && (Enemy_ID[i] == A_BULLET_BILL)) {
        return;
      }
    }

    // Bullet sound
    Square2SoundQueue |= SOUND_SQ2_KABOOM;

    // Spawn a bullet bill
    Enemy_ID[objoff] = A_BULLET_BILL;
  }

  const u8 rng_bag = random_from_bag(PseudoRandomBitReg[objoff], &BitMFilter);

  // Inlining Enemy17YPosData, because it's only used in this subroutine
  static const u8 ypos_lookup[8] = {
    0x40, 0x30, 0x90, 0x50, 0x20, 0x60, 0xa0, 0x70
  };

  PutAtRightExtent(ypos_lookup[rng_bag], objoff);
  Enemy_YMF_Dummy[objoff] = 0;

  FrenzyEnemyTimer = 0x20;
  CheckpointEnemyID(objoff);
}


// SMB:c71b
// SM2MAIN:932c
// Signature: [A] -> []
void HandleGroupEnemies(const u8 param_1) {
  const u8 groupenemy_data = actor_groupenemy(param_1);
  u8 id;

  if ((groupenemy_data & 4) != 0) {
    id = A_GREEN_KOOPA;
  } else {
    if (PrimaryHardMode != 0) {
      id = A_BUZZY_BEETLE;
    } else {
      id = A_GOOMBA;
    }
  }

  const u8 ypos = (groupenemy_data & 2) ? 0x70 : 0xb0;

  NumberofGroupEnemies = (groupenemy_data & 1) ? 3 : 2;

  u8 xpos = ScreenRight_X_Pos;
  u8 pageloc = ScreenRight_PageLoc;

  do {
    int k;
    for (k = 0; ; k++) {
      if (k == 5) {
        // exit
        EnemyDataOffset += 2;
        EnemyObjectPageSel = 0;
        return;
      }
      if (Enemy_Flag[k] == 0) {
        break;
      }
    }
    // k = 0..=4; object index with zero'd enemy flag

    Enemy_ID[k] = id;
    Enemy_PageLoc[k] = pageloc;
    Enemy_X_Position[k] = xpos;
    Enemy_Y_Position[k] = ypos;
    Enemy_Y_HighPos[k] = 1;
    Enemy_Flag[k] = 1;
    CheckpointEnemyID(k);
    if (xpos >= 0xe8) {
      pageloc += 1;
    }
    xpos += 0x18;
  } while (NumberofGroupEnemies -= 1, NumberofGroupEnemies != 0);

  EnemyDataOffset += 2;
  EnemyObjectPageSel = 0;
}


// SMB:c787
// SM2MAIN:9398
// Signature: [X] -> []
void InitPiranhaPlant(const u8 objoff) {
  // NES note: SMB2J sets EnemyAttributeData[13] to give the plants a different color on hard worlds,
  // but this port moves the logic into EnemyGfxHandler

  #ifdef SMB2J_MODE
    PiranhaPlantCompareOperand = 0x13;
    if ((HardWorldFlag == 0) && (WorldNumber < 3)) {
      PiranhaPlantCompareOperand = 0x21;
    }
  #endif
  Enemy_X_Speed[objoff] = 1;
  Enemy_State[objoff] = 0;
  PiranhaPlant_MoveFlag[objoff] = 0;
  PiranhaPlantDownYPos[objoff] = Enemy_Y_Position[objoff];
  PiranhaPlantUpYPos[objoff] = Enemy_Y_Position[objoff] - 0x18;
  Enemy_BoundBoxCtrl[objoff] = 9;
}


// SMB:c7a0
// SM2MAIN:93d5
// Signature: [X] -> []
void InitEnemyFrenzy(const u8 objoff) {
  const u8 enemy_id = Enemy_ID[objoff];
  EnemyFrenzyBuffer = enemy_id;

  switch (enemy_id) {
  case A_SPINY:
    LakituAndSpinyHandler(objoff);
    return;

  case A_FLYING_CHEEPCHEEP:
    InitFlyingCheepCheep(objoff);
    return;

  case A_BOWSER_FLAME:
    InitBowserFlame(objoff);
    return;

  case A_FIREWORKS:
    InitFireworks(objoff);
    return;

  case A_BULLET_BILL_OR_CHEEPCHEEP_FRENZY:
    BulletBillCheepCheep(objoff);
    return;

  case A_UNK_0x13:
    return;

  default:
    jmpengine_overflow(enemy_id - A_SPINY);
    return;
  }
}


// SMB:c7b8
// SM2MAIN:93ed
// Signature: [X] -> []
void EndFrenzy(const u8 objoff) {
  for (int i = 0; i < 6; i++) {
    if (Enemy_ID[i] == A_LAKITU) {
      Enemy_State[i] = 1;
    }
  }

  EnemyFrenzyBuffer = 0;
  Enemy_Flag[objoff] = 0;
}


// SMB:c7d1
// SM2MAIN:9406
// Signature: [X] -> []
void InitJumpGPTroopa(const u8 objoff) {
  Enemy_MovingDir[objoff] = 2;
  Enemy_X_Speed[objoff] = ssw(0xf8, 0xf4);
  Enemy_BoundBoxCtrl[objoff] = 3;
}


// SMB:c7df
// SM2MAIN:9414
// Signature: [X] -> []
void InitBalPlatform(const u8 objoff) {
  Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] - 1;
  Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] - 1;
  if (SecondaryHardMode == 0) {
    PosPlatform(objoff, 2);
  }
  const bool bVar1 = BalPlatformAlignment >= 0x80;
  Enemy_State[objoff] = BalPlatformAlignment;
  BalPlatformAlignment = 0xff;
  if (bVar1) {
    BalPlatformAlignment = objoff;
  }
  Enemy_MovingDir[objoff] = 0;
  PosPlatform(objoff, 0);
  InitDropPlatform(objoff);
}


// SMB:c803
// SM2MAIN:9438
// Signature: [X] -> []
void InitDropPlatform(const u8 objoff) {
  PlatformCollisionFlag[objoff] = 0xff;
  InitVStf(objoff);
  SPBBox(objoff);
}


// SMB:c80b
// SM2MAIN:9440
// Signature: [X] -> []
void InitHoriPlatform(const u8 objoff) {
  XMoveSecondaryCounter[objoff] = 0;
  InitVStf(objoff);
  SPBBox(objoff);
}


// SMB:c812
// SM2MAIN:9447
// Signature: [X] -> []
void InitVertPlatform(const u8 objoff) {
  i8 bVar1 = Enemy_Y_Position[objoff];
  if (bVar1 >= 0) {
    YPlatformTopYPos[objoff] = bVar1;
    YPlatformCenterYPos[objoff] = Enemy_Y_Position[objoff] + 0x40;
  } else {
    YPlatformTopYPos[objoff] = -bVar1;
    YPlatformCenterYPos[objoff] = Enemy_Y_Position[objoff] - 0x40;
  }
  InitVStf(objoff);
  SPBBox(objoff);
}


// SMB:c82b
// SM2MAIN:9460
// Signature: [X] -> []
void SPBBox(const u8 objoff) {
  Enemy_BoundBoxCtrl[objoff] = ((AreaType != AREA_CASTLE) && (SecondaryHardMode == 0)) ? 6 : 5;
}


// SMB:c83f
// SM2MAIN:9474
// Signature: [X] -> []
void LargeLiftUp(const u8 objoff) {
  PlatLiftUp(objoff);
  SPBBox(objoff);
}


// SMB:c845
// SM2MAIN:947a
// Signature: [X] -> []
void LargeLiftDown(const u8 objoff) {
  PlatLiftDown(objoff);
  SPBBox(objoff);
}


// SMB:c84b
// SM2MAIN:9480
// Signature: [X] -> []
void PlatLiftUp(const u8 objoff) {
  Enemy_Y_MoveForce[objoff] = 0x10;
  Enemy_Y_Speed[objoff] = 0xff;
  PosPlatform(objoff, 1);
  Enemy_BoundBoxCtrl[objoff] = 4;
}


// SMB:c857
// SM2MAIN:948c
// Signature: [X] -> []
void PlatLiftDown(const u8 objoff) {
  Enemy_Y_MoveForce[objoff] = 0xf0;
  Enemy_Y_Speed[objoff] = 0;
  PosPlatform(objoff, 1);
  Enemy_BoundBoxCtrl[objoff] = 4;
}


// SMB:c871
// SM2MAIN:94a6
// Signature: [X, Y] -> []
void PosPlatform(const u8 objoff, const u8 param_2) {
  static const i16 pos_lookup[3] = {8, 12, -8 };

  const i16 pos = pos_lookup[param_2];

  ADD_16_16(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
            pos >> 8, pos & 0xff);
}


// SMB:c882
// SM2MAIN:94b7
// Signature: [r08] -> []
void RunEnemyObjectsCore(const u8 objoff) {
  const u8 enemy_id = Enemy_ID[objoff];

  if (is_actor_enemy(enemy_id)) {
    RunNormalEnemies(objoff);
    return;
  }

  if (is_actor_platform_large(enemy_id)) {
    RunLargePlatform(objoff);
    return;
  }

  if (is_actor_firebar(enemy_id)) {
    RunFirebarObj(objoff);
    return;
  }

  if (enemy_id == A_UNK_0x36 || is_actor_groupenemy(enemy_id) || !is_actor_valid(enemy_id)) {
    jmpengine_overflow(enemy_id - 0x14);
    return;
  }

  switch (enemy_id) {
  case A_BOWSER_FLAME:
    RunBowserFlame(objoff);
    return;

  case A_FIREWORKS:
    RunFireworks(objoff);
    return;

  case A_SMALLPLATFORM_1:
  case A_SMALLPLATFORM_2:
    RunSmallPlatform(objoff);
    return;

  case A_BOWSER:
    RunBowser(objoff);
    return;

  case A_POWERUP:
    // NES note: Power ups are always set to index 5.
    // The original makes this assumption in PowerUpObjHandler
    expect(objoff == 5);
    PowerUpObjHandler(objoff);
    return;

  case A_VINE:
    VineObjectHandler(objoff);
    return;

  case A_STARFLAG:
    RunStarFlagObj(objoff);
    return;

  case A_JUMPSPRING:
    JumpspringHandler(objoff);
    return;

  case A_WARPZONE:
    WarpZoneObject(objoff);
    return;

  case A_RETAINER:
    RunRetainerObj(objoff);
    return;
  }
}


// SMB:c8d7
// SM2MAIN:950c
// Signature: [X] -> []
void RunRetainerObj(const u8 objoff) {
  GetEnemyOffscreenBits(objoff);
  RelativeEnemyPosition(objoff);
  EnemyGfxHandler(objoff);
}


// SMB:c8e0
// SM2MAIN:9515
// Signature: [X] -> []
void RunNormalEnemies(const u8 objoff) {
  Enemy_SprAttrib[objoff] = 0;
  GetEnemyOffscreenBits(objoff);
  RelativeEnemyPosition(objoff);
  EnemyGfxHandler(objoff);
  GetEnemyBoundBox(objoff);

  EnemyToBGCollisionDet(objoff);
  EnemiesCollision(objoff);
  PlayerEnemyCollision(objoff);
  if (TimerControl == 0) {
    EnemyMovementSubs(objoff);
  }
  OffscreenBoundsCheck(objoff);
}


// SMB:c905
// SM2MAIN:953a
// Signature: [X] -> []
void EnemyMovementSubs(const u8 objoff) {
  const u8 enemy_id = Enemy_ID[objoff];

  if (!is_actor_enemy(enemy_id)) {
    jmpengine_overflow(enemy_id);
    return;
  }

  switch (enemy_id) {
  case A_GREEN_KOOPA:
  case A_RED_KOOPA_GREENLIKE:
  case A_BUZZY_BEETLE:
  case A_RED_KOOPA:
  case A_GOOMBA:
  case A_SPINY:
    MoveNormalEnemy(objoff);
    return;

  case A_PIRANHA_PLANT_SMB2J:
#ifdef SMB2J_MODE
    MoveUpsideDownPiranhaP(objoff);
#else
    MoveNormalEnemy(objoff);
#endif
    return;

  case A_HAMMER_BRO:
    ProcHammerBro(objoff);
    return;

  case A_BLOOBER:
    MoveBloober(objoff, false);
    return;

  case A_BULLET_BILL:
    MoveBulletBill(objoff);
    return;

  case A_CHEEPCHEEP_GRAY:
  case A_CHEEPCHEEP_RED:
    MoveSwimmingCheepCheep(objoff);
    return;

  case A_PODOBOO:
    MovePodoboo(objoff);
    return;

  case A_PIRANHA_PLANT:
    MovePiranhaPlant(objoff);
    return;

  case A_GREEN_PARATROOPA:
    MoveJumpingEnemy(objoff);
    return;

  case A_RED_PARATROOPA:
    ProcMoveRedPTroopa(objoff);
    return;

  case A_GREEN_PARATROOPA_HORIZONTAL:
    MoveFlyGreenPTroopa(objoff);
    return;

  case A_LAKITU:
    MoveLakitu(objoff);
    return;

  case A_FLYING_CHEEPCHEEP:
    MoveFlyingCheepCheep(objoff);
    return;
  }
}


// SMB:c935
// SM2MAIN:956a
// Signature: [X] -> []
void RunBowserFlame(const u8 objoff) {
  ProcBowserFlame(objoff);
  GetEnemyOffscreenBits(objoff);
  RelativeEnemyPosition(objoff);
  GetEnemyBoundBox(objoff);
  PlayerEnemyCollision(objoff);
  OffscreenBoundsCheck(objoff);
}


// SMB:c947
// SM2MAIN:957c
// Signature: [X] -> []
void RunFirebarObj(const u8 objoff) {
  ProcFirebar(objoff);
  OffscreenBoundsCheck(objoff);
}


// SMB:c94d
// SM2MAIN:9582
// Signature: [X] -> []
void RunSmallPlatform(const u8 objoff) {
  GetEnemyOffscreenBits(objoff);
  RelativeEnemyPosition(objoff);
  SmallPlatformBoundBox(objoff);
  SmallPlatformCollision(objoff);
  RelativeEnemyPosition(objoff);
  DrawSmallPlatform(objoff);
  MoveSmallPlatform(objoff);
  OffscreenBoundsCheck(objoff);
}


// SMB:c965
// SM2MAIN:959a
// Signature: [X] -> []
void RunLargePlatform(const u8 objoff) {
  GetEnemyOffscreenBits(objoff);
  RelativeEnemyPosition(objoff);
  LargePlatformBoundBox(objoff);
  LargePlatformCollision(objoff);
  if (TimerControl == 0) {
    LargePlatformSubroutines(objoff);
  }
  RelativeEnemyPosition(objoff);
  DrawLargePlatform(objoff);
  OffscreenBoundsCheck(objoff);
}


// SMB:c982
// SM2MAIN:95b7
// Signature: [X] -> []
void LargePlatformSubroutines(const u8 objoff) {
  const u8 enemy_id = Enemy_ID[objoff];

  if (!is_actor_platform_large(enemy_id)) {
    jmpengine_overflow(enemy_id - A_LARGEPLATFORM_BALANCE);
    return;
  }

  switch (enemy_id) {
  case A_LARGEPLATFORM_BALANCE:
    BalancePlatform(objoff);
    return;

  case A_LARGEPLATFORM_Y_MOVING:
    YMovingPlatform(objoff);
    return;

  case A_LARGEPLATFORM_LIFT1:
  case A_LARGEPLATFORM_LIFT2:
    MoveLargeLiftPlat(objoff);
    return;

  case A_LARGEPLATFORM_X_MOVING:
    XMovingPlatform(objoff);
    return;

  case A_LARGEPLATFORM_DROP:
    DropPlatform(objoff);
    return;

  case A_LARGEPLATFORM_RIGHT:
    RightPlatform(objoff);
    return;
  }
}


// SMB:c998
// SM2MAIN:95cd
// Signature: [X] -> []
void EraseEnemyObject(const u8 param_1) {
  Enemy_Flag[param_1] = 0;
  Enemy_ID[param_1] = A_GREEN_KOOPA;
  Enemy_State[param_1] = 0;
  FloateyNum_Control[param_1] = 0;
  EnemyIntervalTimer[param_1] = 0;
  ShellChainCounter[param_1] = 0;
  Enemy_SprAttrib[param_1] = 0;
  EnemyFrameTimer[param_1] = 0;

  // NES note: the A register is set to 0 here.
  // VineObjectHandler uses it
}


// SMB:c9b0
// SM2MAIN:95e5
// Signature: [X] -> []
void MovePodoboo(const u8 objoff) {
  u8 bVar1;

  if (EnemyIntervalTimer[objoff] == 0) {
    InitPodoboo(objoff);
    bVar1 = PseudoRandomBitReg[objoff + 1];
    Enemy_Y_MoveForce[objoff] = bVar1 | 0x80;
    EnemyIntervalTimer[objoff] = (bVar1 & 0xf) | 6;
    Enemy_Y_Speed[objoff] = 0xf9;
  }
  MoveJ_EnemyVertically(objoff);
}


// SMB:c9d8
// SM2MAIN:960d
// Signature: [X] -> []
void ProcHammerBro(const u8 objoff) {
  if ((Enemy_State[objoff] & 0x20) != 0) {
    MoveDefeatedEnemy(objoff);
    return;
  }
  if (HammerBroJumpTimer[objoff] != 0) {
    HammerBroJumpTimer[objoff] = HammerBroJumpTimer[objoff] - 1;
    if ((Enemy_OffscreenBits & 0xc) != 0) {
      MoveHammerBroXDir(objoff);
      return;
    }
    if (HammerThrowingTimer[objoff] == 0) {
      expect(SecondaryHardMode <= 1);
      HammerThrowingTimer[objoff] = SecondaryHardMode == 0 ? 0x30 : 0x1c;
      const bool sVar2 = SpawnHammerObj(objoff);
      if (sVar2) {
        Enemy_State[objoff] = Enemy_State[objoff] | 8;
        MoveHammerBroXDir(objoff);
        return;
      }
      HammerThrowingTimer[objoff] = HammerThrowingTimer[objoff] - 1;
      MoveHammerBroXDir(objoff);
      return;
    }
    HammerThrowingTimer[objoff] = HammerThrowingTimer[objoff] - 1;
    MoveHammerBroXDir(objoff);
    return;
  }
  if ((Enemy_State[objoff] & 7) == 1) {
    MoveHammerBroXDir(objoff);
    return;
  }
  if (Enemy_Y_Position[objoff] >= 0x80) {
    SetHJ(objoff, 0xfa, 0);
    return;
  }
  if (Enemy_Y_Position[objoff] < 0x70) {
    SetHJ(objoff, 0xfd, 1);
    return;
  }
  if ((PseudoRandomBitReg[objoff + 1] & 1) != 0) {
    SetHJ(objoff, 0xfd, 0);
    return;
  }
  SetHJ(objoff, 0xfa, 0);
}


// SMB:ca37
// SM2MAIN:966c
// Signature: [X, Y, r00] -> []
void SetHJ(const u8 objoff, const u8 param_2, const u8 param_3) {
  // param_3 is always 0 or 1

  Enemy_Y_Speed[objoff] = param_2;
  Enemy_State[objoff] = Enemy_State[objoff] | 1;

  EnemyFrameTimer[objoff] = 0x20;

  if (param_3 && SecondaryHardMode != 0) {
    if (PseudoRandomBitReg[objoff + 2] & 1) {
      EnemyFrameTimer[objoff] = 0x37;
    }
  }

  HammerBroJumpTimer[objoff] = PseudoRandomBitReg[objoff + 1] | 0xc0;
  MoveHammerBroXDir(objoff);
}


// SMB:ca58
// SM2MAIN:968d
// Signature: [X] -> []
void MoveHammerBroXDir(const u8 objoff) {
  Enemy_X_Speed[objoff] = ((FrameCounter & 0x40) == 0) ? 4 : 0xfc;;
  const struct_ncr00 sVar2 = PlayerEnemyDiff(objoff);
  if (!sVar2.n) {
    if (EnemyIntervalTimer[objoff] == 0) {
      Enemy_X_Speed[objoff] = 0xf8;
    }
  }
  Enemy_MovingDir[objoff] = (sVar2.n) ? 1 : 2;
  MoveNormalEnemy(objoff);
}


// SMB:ca77
// SM2MAIN:96ac
// Signature: [X] -> []
void MoveNormalEnemy(const u8 objoff) {
  bool fall_e = true;

  if ((Enemy_State[objoff] & 0x40) == 0) {
    const u8 bVar1 = Enemy_State[objoff] & 7;

    if (Enemy_State[objoff] & 0x80) {
      fall_e = false;
    } else if ((Enemy_State[objoff] & 0x20) != 0) {
      MoveDefeatedEnemy(objoff);
      return;
    } else if (bVar1 == 0) {
      fall_e = false;
    } else if (bVar1 == 3 || bVar1 == 4 || bVar1 == 6 || bVar1 == 7) {
      if (EnemyIntervalTimer[objoff] == 0) {
        Enemy_State[objoff] = 0;
        u8 bVar2 = FrameCounter & 1;
        Enemy_MovingDir[objoff] = bVar2 + 1;

        if (PrimaryHardMode == 0) {
          Enemy_X_Speed[objoff] = bVar2 == 0 ? 8 : -8;
        } else {
          Enemy_X_Speed[objoff] = bVar2 == 0 ? 12 : -12;
        }

        return;
      }
      if ((EnemyIntervalTimer[objoff] == 0xe) && (Enemy_ID[objoff] == A_GOOMBA)) {
        EraseEnemyObject(objoff);
      }
      return;
    }
  }

  u8 bVar2 = 0;

  // FallE
  if (fall_e) {
    MoveD_EnemyVertically(objoff);
    const u8 tmp1 = objoff;
    expect(tmp1 == objoff);

    if (Enemy_State[objoff] == 2) {
      // MEHor
      MoveEnemyHorizontally(objoff);
      return;
    }

    if (((Enemy_State[objoff] & 0x40) != 0) && (Enemy_ID[objoff] != A_POWERUP)) {
      bVar2 = 1;
    }
  }

  const u8 old_enemy_speed = Enemy_X_Speed[objoff];

  if (old_enemy_speed < 0x80) {
    Enemy_X_Speed[objoff] -= bVar2 == 0 ? 0 : 24;
  } else {
    Enemy_X_Speed[objoff] += bVar2 == 0 ? 0 : 24;
  }

  MoveEnemyHorizontally(objoff);

  Enemy_X_Speed[objoff] = old_enemy_speed;
}


// SMB:cae5
// SM2MAIN:971a
// Signature: [X] -> []
void MoveDefeatedEnemy(const u8 objoff) {
  MoveD_EnemyVertically(objoff);
  MoveEnemyHorizontally(objoff);
}


// SMB:caf9
// SM2MAIN:972e
// Signature: [X] -> []
void MoveJumpingEnemy(const u8 objoff) {
  MoveJ_EnemyVertically(objoff);
  MoveEnemyHorizontally(objoff);
}


// SMB:caff
// SM2MAIN:9734
// Signature: [X] -> []
void ProcMoveRedPTroopa(const u8 objoff) {
  if (((Enemy_Y_Speed[objoff] | Enemy_Y_MoveForce[objoff]) == 0)) {
    Enemy_YMF_Dummy[objoff] = 0;
    if (Enemy_Y_Position[objoff] < RedPTroopaOrigXPos[objoff]) {
      if ((FrameCounter & 7) == 0) {
        Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] + 1;
      }
      return;
    }
  }

  if (RedPTroopaCenterYPos[objoff] <= Enemy_Y_Position[objoff]) {
    MoveRedPTroopaUp(objoff);
  } else {
    MoveRedPTroopaDown(objoff);
  }
}


// SMB:cb25
// SM2MAIN:975a
// Signature: [X] -> []
void MoveFlyGreenPTroopa(const u8 objoff) {
  XMoveCntr_GreenPTroopa(objoff);
  MoveWithXMCntrs(objoff);
  char cVar2 = 1;
  if ((FrameCounter & 3) == 0) {
    if ((FrameCounter & 0x40) == 0) {
      cVar2 = -1;
    }
    Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] + cVar2;
  }
}


// SMB:cb45
// SM2MAIN:977a
// Signature: [X] -> []
void XMoveCntr_GreenPTroopa(const u8 objoff) {
  XMoveCntr_Platform(0x13, objoff);
}


// SMB:cb47
// SM2MAIN:977c
// Signature: [A, X] -> []
void XMoveCntr_Platform(const u8 param_1, const u8 objoff) {
  if ((FrameCounter & 3) != 0) {
    return;
  }
  if ((XMovePrimaryCounter[objoff] & 1) != 0) {
    if (XMoveSecondaryCounter[objoff] != 0) {
      XMoveSecondaryCounter[objoff] = XMoveSecondaryCounter[objoff] - 1;
      return;
    }
  } else if (XMoveSecondaryCounter[objoff] != param_1) {
    XMoveSecondaryCounter[objoff] = XMoveSecondaryCounter[objoff] + 1;
    return;
  }
  XMovePrimaryCounter[objoff] = XMovePrimaryCounter[objoff] + 1;
}


// SMB:cb66
// SM2MAIN:979b
// Signature: [X] -> [r00]
u8 MoveWithXMCntrs(const u8 objoff) {
  const u8 bStack0000 = XMoveSecondaryCounter[objoff];

  if ((Enemy_Y_Speed[objoff] & 2) != 0) {
    Enemy_MovingDir[objoff] = 1;
  } else {
    XMoveSecondaryCounter[objoff] *= -1;
    Enemy_MovingDir[objoff] = 2;
  }

  const u8 sVar2 = MoveEnemyHorizontally(objoff);
  XMoveSecondaryCounter[objoff] = bStack0000;
  return sVar2;
}


// SMB:cb89
// SM2MAIN:97be
// Signature: [X, C] -> []
void MoveBloober(const u8 objoff, const bool param_2) {
  if ((Enemy_State[objoff] & 0x20) != 0) {
    MoveEnemySlowVert(objoff);
    return;
  }

  const u8 rng = PseudoRandomBitReg[objoff + 1] & (SecondaryHardMode == 0 ? 63 : 3);

  if (rng == 0) {
    u8 bVar2;
    bool tmp2;

    if ((objoff & 1) != 0) {
      bVar2 = Player_MovingDir;
      tmp2 = true;
    } else {
      const struct_ncr00 sVar3 = PlayerEnemyDiff(objoff);
      bVar2 = sVar3.n ? 1 : 2;
      tmp2 = sVar3.c;
    }
    Enemy_MovingDir[objoff] = bVar2;
    ProcSwimmingB(objoff, tmp2);
  } else {
    ProcSwimmingB(objoff, param_2);
  }

  const u8 ydiff = Enemy_Y_Position[objoff] - Enemy_Y_MoveForce[objoff];

  if (ydiff >= 0x20) {
    Enemy_Y_Position[objoff] = ydiff;
  }

  if (Enemy_MovingDir[objoff] == 1) {
    ADD_UNSIGNED_16_8(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
                      BlooperMoveSpeed[objoff]);
  } else {
    SUB_UNSIGNED_16_8(Enemy_PageLoc[objoff], Enemy_X_Position[objoff],
                      BlooperMoveSpeed[objoff]);
  }
}


// SMB:cbdf
// SM2MAIN:9814
// Signature: [X, C] -> []
void ProcSwimmingB(const u8 param_1, const bool param_2) {
  if ((BlooperMoveCounter[param_1] & 2) == 0) {
    if ((BlooperMoveCounter[param_1] & 1) == 0) {
      if ((FrameCounter & 7) == 0) {
        const u8 bVar1 = Enemy_Y_MoveForce[param_1] + 1;
        Enemy_Y_MoveForce[param_1] = bVar1;
        BlooperMoveSpeed[param_1] = bVar1;
        if (bVar1 == 2) {
          BlooperMoveCounter[param_1] = BlooperMoveCounter[param_1] + 1;
        }
      }
    } else if ((FrameCounter & 7) == 0) {
      const u8 bVar1 = Enemy_Y_MoveForce[param_1] - 1;
      Enemy_Y_MoveForce[param_1] = bVar1;
      BlooperMoveSpeed[param_1] = bVar1;
      if (bVar1 == 0) {
        BlooperMoveCounter[param_1] = BlooperMoveCounter[param_1] + 1;
        EnemyIntervalTimer[param_1] = 2;
      }
    }
  } else if ((EnemyIntervalTimer[param_1] == 0)
      && (Player_Y_Position <= (u8)(Enemy_Y_Position[param_1] + 0x10 + param_2))) {
    BlooperMoveCounter[param_1] = 0;
  } else if ((FrameCounter & 1) == 0) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
  }
}


// SMB:cc36
// SM2MAIN:986b
// Signature: [X] -> []
void MoveBulletBill(const u8 objoff) {
  if ((Enemy_State[objoff] & 0x20) != 0) {
    MoveJ_EnemyVertically(objoff);
  } else {
    Enemy_X_Speed[objoff] = 0xe8;
    MoveEnemyHorizontally(objoff);
  }
}


// SMB:cc4a
// SM2MAIN:987f
// Signature: [X] -> []
void MoveSwimmingCheepCheep(const u8 objoff) {
  if ((Enemy_State[objoff] & 0x20) != 0) {
    MoveEnemySlowVert(objoff);
    return;
  }

  const u8 cheepcheep_speed = Enemy_ID[objoff] == A_CHEEPCHEEP_GRAY ? 0x40 : 0x80;

  SUB_24_24(Enemy_PageLoc[objoff], Enemy_X_Position[objoff], Enemy_X_MoveForce[objoff],
            0, 0, cheepcheep_speed);

  if (objoff > 1) {
    if (CheepCheepMoveMFlag[objoff] < 0x10) {
      SUB_24_24(Enemy_Y_HighPos[objoff], Enemy_Y_Position[objoff], Enemy_YMF_Dummy[objoff],
                0, 0, ssw(0x20, 0x40));
    } else {
      ADD_24_24(Enemy_Y_HighPos[objoff], Enemy_Y_Position[objoff], Enemy_YMF_Dummy[objoff],
                0, 0, ssw(0x20, 0x40));
    }

    const i8 bVar3 = Enemy_Y_Position[objoff] - CheepCheepOrigYPos[objoff];

    if (bVar3 > 0xe) {
      CheepCheepMoveMFlag[objoff] = 0;
    } else if (bVar3 < -0xe) {
      CheepCheepMoveMFlag[objoff] = 0x10;
    }
  }
}


// SMB:cd3c
// SM2MAIN:9971
// Signature: [X] -> []
void ProcFirebar(const u8 objoff) {
  GetEnemyOffscreenBits(objoff);

  if ((Enemy_OffscreenBits & 8) != 0) {
    return;
  }

  if (TimerControl == 0) {
    // Inlined: FirebarSpin
    // NES note: it's only called once, and inlining reveals a full 16-bit addition and subtraction

    u16 val = LOAD_16(FirebarSpinState_High[objoff], FirebarSpinState_Low[objoff]);

    if (FirebarSpinDirection[objoff] == 0) {
      val += FirebarSpinSpeed[objoff];
    } else {
      val -= FirebarSpinSpeed[objoff];
    }

    val &= 0x1fff;

    STORE_16(FirebarSpinState_High[objoff], FirebarSpinState_Low[objoff],
             val);
  }


  u8 tmp1 = FirebarSpinState_High[objoff];

  expect(is_actor_firebar(Enemy_ID[objoff]));

  if (is_actor_firebar_long(Enemy_ID[objoff])) {
    if (tmp1 == 8 || tmp1 == 0x18) {
      tmp1 += 1;
      FirebarSpinState_High[objoff] = tmp1;
    }
  }

  RelativeEnemyPosition(objoff);
  // NES note: There's normally a call to GetFirebarPosition right after RelativeEnemyPosition,
  // but it does nothing. The results are unused.
  // This port omits it.

  const u8 bVar4 = Enemy_Rel_YPos;
  const u8 sproff = Enemy_SprDataOffset[objoff];
  SPRITE_Y(sproff, 0) = Enemy_Rel_YPos;
  SPRITE_X(sproff, 0) = Enemy_Rel_XPos;

  u8 bVar2 = FirebarCollision(sproff, Enemy_Rel_XPos, bVar4);

  expect(is_actor_firebar(Enemy_ID[objoff]));

  const u8 tmpred = is_actor_firebar_long(Enemy_ID[objoff]) ? 11 : 5;

  for (int i = 0; i < tmpred; i++) {
    struct_r01r02r03 sVar6;
    sVar6 = GetFirebarPosition(tmp1, i);
    bVar2 = DrawFirebar_Collision(sVar6.r01, sVar6.r02, sVar6.r03, bVar2);

    if (i == 4) {
      bVar2 = Enemy_SprDataOffset[DuplicateObj_Offset];
    }
  }

  // Workaround for CheckpointEnemyID() -> Setup_Vine() bug
  rEF = tmp1;
}


// SMB:cdbb
// SM2MAIN:99f0
// Signature: [r01, r02, r03, r06] -> [r06]
u8 DrawFirebar_Collision(const u8 param_2, const u8 param_3, const u8 param_4, const u8 param_5) {
  const u8 bVar1 = Enemy_Rel_XPos + ((param_4 & 1) != 0 ? param_2 : -param_2);

  SPRITE_X(param_5, 0) = bVar1;

  u8 bVar3;
  if (ABS_DIFF(bVar1, Enemy_Rel_XPos) <= 0x58) {
    bVar3 = Enemy_Rel_YPos;
    if (Enemy_Rel_YPos != SPRITE_Y_OFFSCREEN) {
      bVar3 = Enemy_Rel_YPos + ((param_4 & 2) != 0 ? param_3 : -param_3);
    }
  } else {
    bVar3 = SPRITE_Y_OFFSCREEN;
  }
  SPRITE_Y(param_5, 0) = bVar3;

  return FirebarCollision(param_5, bVar1, bVar3);
}


// SMB:ce08
// SM2MAIN:9a3d
// Signature: [Y, r06, r07] -> [r06]
u8 FirebarCollision(const u8 param_1, const u8 param_3, const u8 param_4) {
  DrawFirebar(param_1);

  if ((StarInvincibleTimer != 0 && TimerControl != 0) || (Player_Y_HighPos != 1)) {
    return param_1 + 4;
  }

  static const u8 firebar_y_pos[3] = {0, 12, 24};

  for (int i = 0; i < 3; i++) {
    if (i < 2) {
      if ((PlayerSize != 0) || (CrouchingFlag != 0)) {
        continue;
      }
    }

    if (param_3 >= 0xf0) {
      continue;
    }

    const u8 x = SPRITE_X(0, 1) + 4;
    const u8 y = Player_Y_Position + firebar_y_pos[i];

    const u8 diff_x = ABS_DIFF_SIGNED(x, param_3);
    const u8 diff_y = ABS_DIFF_SIGNED(y, param_4);

    if (diff_x < 8 && diff_y < 8) {
      Enemy_MovingDir[0] = x >= param_3 ? 1 : 2;
      InjurePlayer();
      break;
    }
  }

  return param_1 + 4;
}


// SMB:ce8e
// SM2MAIN:9ac3
// Signature: [A, r00] -> [r01, r02, r03]
struct_r01r02r03 GetFirebarPosition(const u8 param_1, const u8 param_2) {
  struct_r01r02r03 sVar3;

  // bVar1 = 0123456787654321 ...
  // bVar2 = 8765432101234567 ...
  u8 bVar1 = param_1 % 16;
  if (bVar1 > 8) {
    bVar1 = 16 - bVar1;
  }
  u8 bVar2 = (param_1 + 8) % 16;
  if (bVar2 > 8) {
    bVar2 = 16 - bVar2;
  }

  expect(param_1 <= 0x1f);
  expect(param_2 < 11);

  static const u8 mirror_lookup[4] = { 1, 3, 2, 0 };

  static const u8 pos_lookup[11][9] = {
    { 0x00, 0x01, 0x03, 0x04, 0x05, 0x06, 0x07, 0x07, 0x08, },
    { 0x00, 0x03, 0x06, 0x09, 0x0b, 0x0d, 0x0e, 0x0f, 0x10, },
    { 0x00, 0x04, 0x09, 0x0d, 0x10, 0x13, 0x16, 0x17, 0x18, },
    { 0x00, 0x06, 0x0c, 0x12, 0x16, 0x1a, 0x1d, 0x1f, 0x20, },
    { 0x00, 0x07, 0x0f, 0x16, 0x1c, 0x21, 0x25, 0x27, 0x28, },
    { 0x00, 0x09, 0x12, 0x1b, 0x21, 0x27, 0x2c, 0x2f, 0x30, },
    { 0x00, 0x0b, 0x15, 0x1f, 0x27, 0x2e, 0x33, 0x37, 0x38, },
    { 0x00, 0x0c, 0x18, 0x24, 0x2d, 0x35, 0x3b, 0x3e, 0x40, },
    { 0x00, 0x0e, 0x1b, 0x28, 0x32, 0x3b, 0x42, 0x46, 0x48, },
    { 0x00, 0x0f, 0x1f, 0x2d, 0x38, 0x42, 0x4a, 0x4e, 0x50, },
    { 0x00, 0x11, 0x22, 0x31, 0x3e, 0x49, 0x51, 0x56, 0x58, },
  };

  // NES note: The FirebarTblOffsets table (optimized away)
  // is just the index multiplied by 9

  sVar3.r02 = pos_lookup[param_2][bVar2];
  sVar3.r01 = pos_lookup[param_2][bVar1];
  sVar3.r03 = mirror_lookup[param_1 >> 3];
  return sVar3;
}


// SMB:cedf
// SM2MAIN:9b14
// Signature: [X] -> []
void MoveFlyingCheepCheep(const u8 objoff) {
  if ((Enemy_State[objoff] & 0x20) != 0) {
    Enemy_SprAttrib[objoff] = 0;
    MoveJ_EnemyVertically(objoff);
    return;
  }

  static const i8 ypos_sub_lookup[16] = {
    -8, -96, 112, -67, 0, 32, 32, 32, 0, 0, -75, 30, 41, 32, -16, 8
  };

  MoveEnemyHorizontally(objoff);
  SetXMoveAmt(5, objoff, 0xd);
  u8 bVar3 = Enemy_Y_MoveForce[objoff] >> 4;

  u8 bVar1 = Enemy_Y_Position[objoff] - ypos_sub_lookup[bVar3];

  if (bVar1 >= 0x80) {
    bVar1 *= -1;
  }
  if (bVar1 < 8) {
    bVar1 = Enemy_Y_MoveForce[objoff];
    Enemy_Y_MoveForce[objoff] = bVar1 + 0x10;
    bVar3 = (u8)(bVar1 + 0x10) >> 4;
  }

  // NES note: There's an assignment to Enemy_SprAttrib in the original here.
  // It looked up FlyCCBPriority.
  // It's ultimately unused by the time it reaches Enemy_SprAttrib, however.
  // The FlyCCBPriority lookup also accesses code.

  Enemy_SprAttrib[objoff] = 0;
}


// SMB:cf28
// SM2MAIN:9b5d
// Signature: [X] -> []
void MoveLakitu(const u8 objoff) {
  if ((Enemy_State[objoff] & 0x20) == 0) {
    if (Enemy_State[objoff] == 0) {
      EnemyFrenzyBuffer = A_SPINY;
      LakituMoveSpeed[objoff] = PlayerLakituDiff(objoff, 21, 48, 64);
    } else {
      LakituMoveDirection[objoff] = 0;
      EnemyFrenzyBuffer = 0;
      LakituMoveSpeed[objoff] = 0x10;
    }

    if ((LakituMoveDirection[objoff] & 1) != 0) {
      Enemy_MovingDir[objoff] = 1;
    } else {
      LakituMoveSpeed[objoff] *= -1;
      Enemy_MovingDir[objoff] = 2;
    }

    MoveEnemyHorizontally(objoff);
  } else {
    MoveD_EnemyVertically(objoff);
  }
}


// SMB:cf6c
// SM2MAIN:9ba1
// Signature: [X, r01, r02, r03] -> [A]
u8 PlayerLakituDiff(const u8 objoff, const u8 param_2, const u8 param_3, const u8 param_4) {
  u8 bVar2 = 0;
  const struct_ncr00 sVar4 = PlayerEnemyDiff(objoff);
  u8 bVar1 = sVar4.r00;
  if (sVar4.n) {
    bVar2 = 1;
    bVar1 *= -1;
  }

  if (bVar1 >= 0x3c) {
    bVar1 = 0x3c;
    if (Enemy_ID[objoff] == A_LAKITU) {
      if (bVar2 != LakituMoveDirection[objoff]) {
        if (LakituMoveDirection[objoff] != 0) {
          LakituMoveSpeed[objoff] = LakituMoveSpeed[objoff] - 1;
          if (LakituMoveSpeed[objoff] != 0) {
            return LakituMoveSpeed[objoff];
          }
        }
        LakituMoveDirection[objoff] = bVar2;
      }
    }
  }

  // NES note: the bit math and subtraction is simplified here.
  // The original treated the temporary registers as an array, which has to be flattened.
  // The original also performed a do-while loop where each iteration decremented A by 1 (lmao):
  //
  //    ; y = 0, 1, 2
  //    LDA $0001, y
  //    LDY $00
  // -  SEC
  //    SBC #1
  //    DEY
  //    BPL -

  bVar1 >>= 2;
  bVar1 &= 0xf;
  bVar1 += 1;

  if ((Player_X_Speed == 0) || (ScrollAmount == 0)) {
    return param_2 - bVar1;
  } else if ((Enemy_ID[objoff] != A_SPINY) && (LakituMoveDirection[objoff] == 0)) {
    return param_2 - bVar1;
  } else if ((Player_X_Speed <= 0x18) || (ScrollAmount <= 1)) {
    return param_3 - bVar1;
  } else {
    return param_4 - bVar1;
  }
}


// SMB:cfec
// SM2MAIN:9c21
// Signature: [] -> []
void BridgeCollapse(void) {
  if (Enemy_ID[BowserFront_Offset] == A_BOWSER) {
    const u8 objoff = BowserFront_Offset;
    if (Enemy_State[BowserFront_Offset] == 0) {
      BowserFeetCounter -= 1;
      if (BowserFeetCounter == 0) {
        BowserFeetCounter = 4;
        BowserBodyControls ^= 1;

        // NES note: x_lookup and y_lookup are extracted from BridgeCollapseData

        //                                axe chain  [                      bridge                    ]
        static const u8 x_lookup[15] = { 26,   24, 24, 22, 20, 18, 16, 14, 12, 10,  8,  6,  4,  2,  0};
        static const u8 y_lookup[15] = {  0,    2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4};

        expect(BridgeCollapseOffset < 15);

        const u8 x = x_lookup[BridgeCollapseOffset];
        const u8 y = y_lookup[BridgeCollapseOffset];

        // x and y should be multiples of 2
        expect((x % 2) == 0);
        expect((y % 2) == 0);

        const u8 vramoff = VRAM_Buffer1_Offset + 1;

        // Inlined: RemBridge
        draw_block_metatile(vramoff, 3, x/2, (y/2)+8, 0);

        // Inlined: MoveVOffset
        VRAM_Buffer1_Offset += 10;

        Square2SoundQueue = SOUND_SQ2_KABOOM;
        NoiseSoundQueue = SOUND_NOISE_BRICKSHATTER;
        BridgeCollapseOffset += 1;
        if (BridgeCollapseOffset == 0xf) {
          InitVStf(objoff);
          Enemy_State[objoff] = 0x40;
          Square2SoundQueue = SOUND_SQ2_BOWSERFALL;
        }
      }
      BowserGfxHandler(objoff);
      return;
    }
    if (((Enemy_State[objoff] & 0x40) != 0) && (Enemy_Y_Position[objoff] < 0xe0)) {
      MoveD_Bowser(objoff);
      return;
    }
  }
  EventMusicQueue = MUSIC_EVENT_STOP;
  expect(OperMode == OM_VICTORY);
  expect(OperMode_Task == OMT_VICTORY_BRIDGECOLLAPSE);
  OperMode_Task = OMT_VICTORY_SETUPVICTORYMODE;
  KillAllEnemies();
}


// SMB:d00f
// SM2MAIN:9c44
// Signature: [X] -> []
void MoveD_Bowser(const u8 objoff) {
  MoveEnemySlowVert(objoff);
  BowserGfxHandler(objoff);
}


// SMB:d065
// SM2MAIN:9c9a
// Signature: [X] -> []
void RunBowser(const u8 objoff) {
  u8 bVar1;
  u8 bVar2;
  struct_ncr00 sVar4;

  static const u8 random_lookup[4] = { 0x21, 0x41, 0x11, 0x31 };

  if ((Enemy_State[objoff] & 0x20) != 0) {
    if (Enemy_Y_Position[objoff] >= 0xe0) {
      KillAllEnemies();
      return;
    }
    MoveD_Bowser(objoff);
    return;
  }
  EnemyFrenzyBuffer = 0;
  if (TimerControl != 0) {
    goto ChkFireB;
  }
  if (BowserBodyControls < 0x80) {
    BowserFeetCounter -= 1;
    if (BowserFeetCounter == 0) {
      BowserFeetCounter = 0x20;
      BowserBodyControls ^= 1;
    }
    if ((FrameCounter & 0xf) == 0) {
      Enemy_MovingDir[objoff] = 2;
    }
    if ((EnemyFrameTimer[objoff] != 0)) {
      sVar4 = PlayerEnemyDiff(objoff);
      if (sVar4.n) {
        Enemy_MovingDir[objoff] = 1;
        BowserMovementSpeed = 2;
        EnemyFrameTimer[objoff] = 0x20;
        BowserFireBreathTimer = 0x20;
        if (199 < Enemy_X_Position[objoff]) {
          goto HammerChk;
        }
      }
    }
    if ((FrameCounter & 3) == 0) {
      if (Enemy_X_Position[objoff] == BowserOrigXPos) {
        MaxRangeFromOrigin = random_lookup[PseudoRandomBitReg[objoff] & 3];
      }
      bVar1 = Enemy_X_Position[objoff] + BowserMovementSpeed;
      Enemy_X_Position[objoff] = bVar1;
      if (Enemy_MovingDir[objoff] != 1) {
        bVar2 = 0xff;
        bVar1 -= BowserOrigXPos;
        if (bVar1 >= 0x80) {
          bVar1 *= -1;
          bVar2 = 1;
        }
        if (MaxRangeFromOrigin <= bVar1) {
          BowserMovementSpeed = bVar2;
        }
      }
    }
  }
HammerChk:
  if (EnemyFrameTimer[objoff] == 0) {
    MoveEnemySlowVert(objoff);
    if ((WorldNumber >= 5) && ((FrameCounter & 3) == 0)) {
      SpawnHammerObj(objoff);
    }
    if (Enemy_Y_Position[objoff] >= 0x80) {
      EnemyFrameTimer[objoff] = random_lookup[PseudoRandomBitReg[objoff] & 3];
    }
  } else if (EnemyFrameTimer[objoff] == 1) {
    Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] - 1;
    InitVStf(objoff);
    Enemy_Y_Speed[objoff] = 0xfe;
  }
ChkFireB:

  if ((WorldNumber != 7) && (WorldNumber >= 5)) {
    BowserGfxHandler(objoff);
    return;
  }
  if (BowserFireBreathTimer != 0) {
    BowserGfxHandler(objoff);
    return;
  }
  BowserFireBreathTimer = 0x20;
  BowserBodyControls ^= 0x80;

  if ((BowserBodyControls & 0x80) == 0) {
    BowserGfxHandler(objoff);
    return;
  }

  BowserFireBreathTimer = SetFlameTimer();

  if (SecondaryHardMode != 0) {
    BowserFireBreathTimer -= 0x10;
  }
  EnemyFrenzyBuffer = A_BOWSER_FLAME;
  BowserGfxHandler(objoff);
}


// SMB:d071
// SM2MAIN:9ca6
// Signature: [] -> []
void KillAllEnemies(void) {
  for (int i = 0; i < 5; i++) {
    EraseEnemyObject(i);
  }

  EnemyFrenzyBuffer = 0;
}


static void EnemyGfxHandler_bowser(const u8 objoff, const u8 bowser_gfx_flag);


// SMB:d17b
// SM2MAIN:9db0
// Signature: [X] -> []
void BowserGfxHandler(const u8 objoff) {
  expect(BowserGfxFlag == 0);

  // NES note: BowserGfxFlag ($036a) is only used here and the EnemyGfxHandler tree.
  // It's been optimized away.
  // Between the increment and its uses, there are no accidental array reads/writes in the original that could access it.

  // Inlined: ProcessBowserHalf
  // Inlined: RunRetainerObj

  // Inlined: RunRetainerObj
  GetEnemyOffscreenBits(objoff);
  RelativeEnemyPosition(objoff);
  EnemyGfxHandler_bowser(objoff, 1);

  if (Enemy_State[objoff] == 0) {
    Enemy_BoundBoxCtrl[objoff] = 10;
    GetEnemyBoundBox(objoff);
    PlayerEnemyCollision(objoff);
  }

  const u8 dup_objoff = DuplicateObj_Offset;

  const char cVar3 = ((Enemy_MovingDir[objoff] & 1) != 0) ? -0x10 : 0x10;
  Enemy_X_Position[dup_objoff] = cVar3 + Enemy_X_Position[objoff];
  Enemy_Y_Position[dup_objoff] = Enemy_Y_Position[objoff] + 8;
  Enemy_State[dup_objoff] = Enemy_State[objoff];
  Enemy_MovingDir[dup_objoff] = Enemy_MovingDir[objoff];

  Enemy_ID[dup_objoff] = A_BOWSER;

  GetEnemyOffscreenBits(dup_objoff);
  RelativeEnemyPosition(dup_objoff);
  EnemyGfxHandler_bowser(dup_objoff, 2);

  if (Enemy_State[dup_objoff] == 0) {
    Enemy_BoundBoxCtrl[dup_objoff] = 10;
    GetEnemyBoundBox(dup_objoff);
    PlayerEnemyCollision(dup_objoff);
  }

  expect(BowserGfxFlag == 0);
}


// SMB:d1d9
// SM2MAIN:9e0e
// Signature: [] -> [A]
u8 SetFlameTimer(void) {
  static const u8 timer_lookup[8] = { 0xbf, 0x40, 0xbf, 0xbf, 0xbf, 0x40, 0x40, 0xbf };

  expect(BowserFlameTimerCtrl < 8);

  const u8 bVar1 = BowserFlameTimerCtrl;
  BowserFlameTimerCtrl = (BowserFlameTimerCtrl + 1) & 7;

  return timer_lookup[bVar1];
}


// SMB:d1eb
// SM2MAIN:9e20
// Signature: [X] -> []
void ProcBowserFlame(const u8 objoff) {
  if (TimerControl == 0) {
    const u8 bVar33 = (SecondaryHardMode != 0) ? 0x60 : 0x40;
    const bool bVar1 = Enemy_X_MoveForce[objoff] < bVar33;
    Enemy_X_MoveForce[objoff] = Enemy_X_MoveForce[objoff] - bVar33;

    const u8 bVar3 = Enemy_X_Position[objoff];
    Enemy_X_Position[objoff] = (bVar3 - 1) - bVar1;
    Enemy_PageLoc[objoff] = Enemy_PageLoc[objoff] - ((bVar1 || bVar3 == 0) && (!bVar1 || bVar3 < 2));
    if (Enemy_Y_Position[objoff]
        != FlameYPosData[BowserFlamePRandomOfs[objoff]]) {
      Enemy_Y_Position[objoff]
          = Enemy_Y_Position[objoff] + Enemy_Y_MoveForce[objoff];
    }
  }

  RelativeEnemyPosition(objoff);

  if (Enemy_State[objoff] != 0) {
    return;
  }

  const u8 bVar55 = ((FrameCounter & 2) != 0) ? 0x82 : 2;
  const u8 offset = Enemy_SprDataOffset[objoff];
  for (int i = 0; i < 3; i++) {
    SPRITE_Y_strict(offset, i) = Enemy_Rel_YPos;
    SPRITE_TILE_semistrict(offset, i) = 0x51 + i;
    SPRITE_ATTR_semistrict(offset, i) = bVar55;
    SPRITE_X_semistrict(offset, i) = Enemy_Rel_XPos;
    Enemy_Rel_XPos += 8;
  }

  GetEnemyOffscreenBits(objoff);
  const u8 bVar3 = Enemy_SprDataOffset[objoff];

  const u8 bits = Enemy_OffscreenBits;

  if ((bits & 1) != 0) {
    SPRITE_Y(bVar3, 3) = SPRITE_Y_OFFSCREEN;
  }
  if ((bits & 2) != 0) {
    SPRITE_Y(bVar3, 2) = SPRITE_Y_OFFSCREEN;
  }
  if ((bits & 4) != 0) {
    SPRITE_Y(bVar3, 1) = SPRITE_Y_OFFSCREEN;
  }
  if ((bits & 8) != 0) {
    SPRITE_Y(bVar3, 0) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:d295
// SM2MAIN:9eca
// Signature: [X] -> []
void RunFireworks(const u8 objoff) {
  const u8 bVar1 = ExplosionTimerCounter[objoff] - 1;
  ExplosionTimerCounter[objoff] = bVar1;
  if (bVar1 == 0) {
    ExplosionTimerCounter[objoff] = 8;
    ExplosionGfxCounter[objoff] = ExplosionGfxCounter[objoff] + 1;
    if (ExplosionGfxCounter[objoff] > 2) {
      Enemy_Flag[objoff] = 0;
      Square2SoundQueue = SOUND_SQ2_KABOOM;
      DigitModifier[4] = 5;
      EndAreaPoints();
      return;
    }
  }
  RelativeEnemyPosition(objoff);
  Fireball_Rel_YPos = Enemy_Rel_YPos;
  Fireball_Rel_XPos = Enemy_Rel_XPos;
  DrawExplosion_Fireworks(ExplosionGfxCounter[objoff], Enemy_SprDataOffset[objoff]);
}


// SMB:d2d9
// SM2MAIN:9f0e
// Signature: [X] -> []
void RunStarFlagObj(const u8 objoff) {
  EnemyFrenzyBuffer = 0;

  switch (StarFlagTaskControl) {
  case STARFLAGTASK_GAMETIMERFIREWORKS:
    GameTimerFireworks(objoff);
    StarFlagTaskControl = STARFLAGTASK_AWARDGAMETIMERPOINTS;
    return;

  case STARFLAGTASK_AWARDGAMETIMERPOINTS:
    if ((GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2]) != 0) {
      AwardTimerCastle();
    } else {
      StarFlagTaskControl = STARFLAGTASK_RAISEFLAGSETOFFFWORKS;
    }
    return;

  case STARFLAGTASK_RAISEFLAGSETOFFFWORKS:
    if (Enemy_Y_Position[objoff] >= 0x72) {
      Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] - 1;
      DrawStarFlag(objoff);
    } else if ((FireworksCounter != 0) && (FireworksCounter < 0x80)) {
      EnemyFrenzyBuffer = A_FIREWORKS;
      DrawStarFlag(objoff);
    } else {
      DrawStarFlag(objoff);
      EnemyIntervalTimer[objoff] = 6;
      StarFlagTaskControl = STARFLAGTASK_DELAYTOAREAEND;
    }
    return;

  case STARFLAGTASK_DELAYTOAREAEND:
    DrawStarFlag(objoff);
    if ((EnemyIntervalTimer[objoff] == 0) && (EventMusicBuffer == 0)) {
      StarFlagTaskControl = STARFLAGTASK_DONE;
    }
    return;
  }
}


// SMB:d2f2
// SM2MAIN:9f27
// Signature: [X] -> []
void GameTimerFireworks(const u8 objoff) {
  const u8 last_digit = GameTimerDisplay[2];

  Enemy_State[objoff] = 0;
  FireworksCounter = 0xff;

#ifdef SMB1_MODE
  if (last_digit == 1) {
    Enemy_State[objoff] = 5;
    FireworksCounter = 1;
  } else if (last_digit == 3) {
    Enemy_State[objoff] = 3;
    FireworksCounter = 3;
  } else if (last_digit == 6) {
    Enemy_State[objoff] = 0;
    FireworksCounter = 6;
  }
#endif
#ifdef SMB2J_MODE
  if (last_digit == CoinDisplay[1]) {
    // only show fireworks if the last digit of the timer
    // is the last digit of the coins

    if ((last_digit & 1) == 0) {
      // timer is even
      Enemy_State[objoff] = 0;
      FireworksCounter = 6;
    } else {
      // timer is odd
      Enemy_State[objoff] = 3;
      FireworksCounter = 3;
    }
  }
#endif

  // Note: StarFlagTaskControl increment moved to caller
}


// SMB:d31d
// SM2MAIN:9f57
// Signature: [] -> []
void AwardTimerCastle(void) {
  if ((FrameCounter & 4) != 0) {
    Square2SoundQueue = SOUND_SQ2_TIMER_TICK;
  }
  DigitModifier[5] = 0xff;
  DigitsMathRoutine(ssw(0x23, 0x17));
  DigitModifier[5] = 5;
  EndAreaPoints();
}


// SMB:d336
// SM2MAIN:9f70
// Signature: [] -> []
void EndAreaPoints(void) {
#ifdef SMB1_MODE
  DigitsMathRoutine(CurrentPlayer == 0 ? 0xb : 0x11);
  WriteDigits((CurrentPlayer * 16) + 4);
#endif

#ifdef SMB2J_MODE
  DigitsMathRoutine(0xb);
  WriteDigits(2);
#endif
}


// SMB:d365
// SM2MAIN:9f91
// Signature: [X] -> []
void DrawStarFlag(const u8 objoff) {
  static const u8 xpos_lookup[4] = { 0, 8, 0, 8 };
  static const u8 ypos_lookup[4] = { 0, 0, 8, 8 };
  static const u8 tile_lookup[4] = { 0x54, 0x55, 0x56, 0x57 };

  RelativeEnemyPosition(objoff);
  const u8 bVar2 = Enemy_SprDataOffset[objoff];

  for (int i = 0; i < 4; i++) {
    SPRITE_X_semistrict(bVar2, 3-i)    = Enemy_Rel_XPos + xpos_lookup[i];
    SPRITE_Y_strict(bVar2, 3-i)        = Enemy_Rel_YPos + ypos_lookup[i];
    SPRITE_TILE_semistrict(bVar2, 3-i) = tile_lookup[i];
    SPRITE_ATTR_semistrict(bVar2, 3-i) = SPRATTR_DRAWBEHIND | 2;
  }
}


// SMB:d3b0
// SM2MAIN:9fdc
// Signature: [X] -> []
void MovePiranhaPlant(const u8 objoff) {
  if ((Enemy_State[objoff] == 0) && (EnemyFrameTimer[objoff] == 0)) {
    if (PiranhaPlant_MoveFlag[objoff] == 0) {
      if (PiranhaPlant_Y_Speed[objoff] < 0x80) {
        const struct_ncr00 sVar4 = PlayerEnemyDiff(objoff);
        const u8 bVar3 = sVar4.n ? -sVar4.r00 : sVar4.r00;

        if (bVar3 < PiranhaPlantCompareOperand) {
          // PutinPipe
          Enemy_SprAttrib[objoff] = 0x20;
          return;
        }
      }

      PiranhaPlant_Y_Speed[objoff] *= -1;
      PiranhaPlant_MoveFlag[objoff] += 1;
    }

    const u8 bVar3 = PiranhaPlant_Y_Speed[objoff] >= 0x80
      ? PiranhaPlantUpYPos[objoff]
      : PiranhaPlantDownYPos[objoff];

    if (TimerControl == 0) {
      bool cond1 = (FrameCounter & 1) != 0;

      // NES note: The original SMB2J compared EnemyAttributeData[13],
      // but it's a value in code that's changed by InitPiranhaPlant.
      // It's indirectly checking for World 4 or hard worlds.
#ifdef SMB2J_MODE
      cond1 |= PiranhaPlantHardMode;
#endif

      if (cond1) {
        Enemy_Y_Position[objoff] += PiranhaPlant_Y_Speed[objoff];

        if (Enemy_Y_Position[objoff] == bVar3) {
          PiranhaPlant_MoveFlag[objoff] = 0;
          EnemyFrameTimer[objoff] = 0x40;
        }
      }
    }
  }

  // PutinPipe
  Enemy_SprAttrib[objoff] = 0x20;
}


// SMB:d541
// SM2MAIN:a17b
static inline u16 SetupPlatformRope(const bool cond1, const u8 objoff) {
  // Note: Reworked just to return a PPU address
  // Original Signature: [A, Y] -> [X, r00, r01]

  const u8 ypos = Enemy_Y_Position[objoff] + (cond1 ? 0 : 8);

  u16 xpos = LOAD_16(Enemy_PageLoc[objoff], Enemy_X_Position[objoff]);

  if (SecondaryHardMode == 0) {
    // NES note: There's a carry bug here.
    // The original game adds 8, then 16 if not in secondary hard mode.
    // The carry result from adding the 16 is used, instead of the total 24.

    if ((xpos & 0xff) >= 256-8) {
      xpos -= 256;
    }

    xpos += 24;
  } else {
    xpos += 8;
  }

  const u16 nametable = ((xpos & 0x100) == 0) ? 0x2000 : 0x2400;

  const u8 y_tile_pos = ypos >> 3;
  const u8 x_tile_pos = (xpos & 0xff) >> 3;

  u16 addr = nametable | (y_tile_pos << 5) | (x_tile_pos & 0xfe);

  //                             v bits 7-4 of x
  // PPU address: 0010 0Nyy yyyx xxx0
  //                     ^ bits 7-3 of y
  //                    ^ nametable if x is on odd page

  if (Enemy_Y_Position[objoff] >= 0xe8) {
    // Turn off bit 6
    // Probably to prevent the address from going into the attribute table
    addr &= ~0x0040;
  }

  return addr;
}


// SMB:d432
// SM2MAIN:a065
// Signature: [X] -> []
void BalancePlatform(const u8 objoff) {
  if (Enemy_Y_HighPos[objoff] == 3) {
    EraseEnemyObject(objoff);
    return;
  }

  const u8 enemy_state = Enemy_State[objoff];

#ifdef SMB2J_MODE
  if (Enemy_ID[enemy_state] != A_LARGEPLATFORM_BALANCE) {
    return;
  }
#endif

  if (enemy_state >= 0x80) {
    return;
  }

  if (Enemy_MovingDir[objoff] != 0) {
    PlatformFall(objoff, enemy_state);
    return;
  }

  if (Enemy_Y_Position[objoff] < 0x2e) {
    if (enemy_state != PlatformCollisionFlag[objoff]) {
      Enemy_Y_Position[objoff] = 0x2f;
      StopPlatforms(objoff, enemy_state);
      return;
    }
    InitPlatformFall(enemy_state, objoff);
    return;
  }

  if (Enemy_Y_Position[enemy_state] < 0x2e) {
    if (objoff != PlatformCollisionFlag[objoff]) {
      Enemy_Y_Position[enemy_state] = 0x2f;
      StopPlatforms(objoff, enemy_state);
      return;
    }
    InitPlatformFall(enemy_state, objoff);
    return;
  }

  // 0 = stop
  // 1 = up
  // 2 = down
  int platform_mode = 1;

  const u8 bVar2 = PlatformCollisionFlag[objoff];

  if ((bVar2 & 0x80) == 0) {
    if (bVar2 == objoff) {
      platform_mode = 2;
    }
  } else {
    u16 yvel = LOAD_16(Enemy_Y_Speed[objoff], Enemy_Y_MoveForce[objoff]);
    yvel += 5;

    if ((i16)yvel < 0) {
      platform_mode = 2;
    }
    if (yvel <= 10) {
      platform_mode = 0;
    }
  }

  const u8 bStack0000 = Enemy_Y_Position[objoff];

  switch (platform_mode) {
  case 0:
    StopPlatforms(objoff, enemy_state);
    break;

  case 1:
    MovePlatformUp(objoff);
    break;

  case 2:
    MovePlatformDown(objoff);
    break;
  }

  Enemy_Y_Position[Enemy_State[objoff]] = (bStack0000 - Enemy_Y_Position[objoff]) + Enemy_Y_Position[Enemy_State[objoff]];

  if ((PlatformCollisionFlag[objoff] & 0x80) == 0) {
    PositionPlayerOnVPlat(PlatformCollisionFlag[objoff]);
  }

  const i16 yvel = LOAD_16(Enemy_Y_Speed[objoff], Enemy_Y_MoveForce[objoff]);
  const i8 yspd = Enemy_Y_Speed[objoff];

  if ((yvel != 0) && (VRAM_Buffer1_Offset < 32)) {
    // Draw or erase both ends of the platform ropes

    // Note: This whole block is reworked to be easier to understand.
    // The logic for writing to the vram is different, but the output is exactly the same.

    const bool cond = yspd >= 0;


    // Right hand side

    const u16 ppuaddr_1 = SetupPlatformRope(cond, objoff);

    VRAM1_DRAW(ppuaddr_1,
               cond ? 0xa2 : 0x24,
               cond ? 0xa3 : 0x24);

    // Left hand side

    const u16 ppuaddr_2 = SetupPlatformRope(!cond, Enemy_State[objoff]);

    VRAM1_DRAW(ppuaddr_2,
               !cond ? 0xa2 : 0x24,
               !cond ? 0xa3 : 0x24);
  }
}


// SMB:d598
// SM2MAIN:a1d2
// Signature: [Y, r08] -> []
void InitPlatformFall(const u8 param_1, const u8 objoff) {
  GetEnemyOffscreenBits(param_1);

  SetupFloateyNumber(6, objoff);
  FloateyNum_X_Pos[objoff] = Player_Rel_XPos;
  FloateyNum_Y_Pos[objoff] = Player_Y_Position;
  Enemy_MovingDir[objoff] = 1;

  // NES note: GetEnemyOffscreenBits sets Y=1. This is later used by StopPlatforms.
  // This is either a bug, or just a way to reuse the value. Either way, it's best extracted out to the caller (here).
  StopPlatforms(objoff, 1);
}


// SMB:d5b1
// SM2MAIN:a1eb
// Signature: [X, Y] -> []
void StopPlatforms(const u8 param_1, const u8 param_2) {
  InitVStf(param_1);
  Enemy_Y_Speed[param_2] = 0;
  Enemy_Y_MoveForce[param_2] = 0;
}


// SMB:d5bb
// SM2MAIN:a1f5
// Signature: [X, Y] -> []
void PlatformFall(const u8 objoff, const u8 param_2) {
  const u8 bStack0000 = param_2;
  MoveFallingPlatform(objoff);
  MoveFallingPlatform(bStack0000);
  if (PlatformCollisionFlag[objoff] < 0x80) {
    PositionPlayerOnVPlat(PlatformCollisionFlag[objoff]);
  }
}


// SMB:d5d3
// SM2MAIN:a20d
// Signature: [X] -> []
void YMovingPlatform(const u8 objoff) {
  if (((Enemy_Y_Speed[objoff] | Enemy_Y_MoveForce[objoff]) == 0)) {
    Enemy_YMF_Dummy[objoff] = 0;
    if (Enemy_Y_Position[objoff] < YPlatformTopYPos[objoff]) {
      if ((FrameCounter & 7) == 0) {
        Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] + 1;
      }
      ChkYPCollision(objoff);
      return;
    }
  }
  if (YPlatformCenterYPos[objoff] <= Enemy_Y_Position[objoff]) {
    MovePlatformUp(objoff);
    ChkYPCollision(objoff);
    return;
  }
  MovePlatformDown(objoff);
  ChkYPCollision(objoff);
}


// SMB:d5fe
// SM2MAIN:a238
// Signature: [X] -> []
void ChkYPCollision(const u8 param_1) {
  if (PlatformCollisionFlag[param_1] < 0x80) {
    PositionPlayerOnVPlat(param_1);
  }
}


// SMB:d607
// SM2MAIN:a241
// Signature: [X] -> []
void XMovingPlatform(const u8 objoff) {
  XMoveCntr_Platform(0xe, objoff);
  const u8 sVar2 = MoveWithXMCntrs(objoff);
  if (PlatformCollisionFlag[objoff] < 0x80) {
    PositionPlayerOnHPlat(objoff, sVar2);
  }
}


// SMB:d614
// SM2MAIN:a24e
// Signature: [X, r00] -> []
void PositionPlayerOnHPlat(const u8 param_1, const u8 param_2) {
  ADD_SIGNED_16_8(Player_PageLoc, Player_X_Position, param_2);

  Platform_X_Scroll = param_2;
  PositionPlayerOnVPlat(param_1);
}


// SMB:d631
// SM2MAIN:a26b
// Signature: [X] -> []
void DropPlatform(const u8 objoff) {
  if (PlatformCollisionFlag[objoff] >= 0x80) {
    return;
  }

  MoveDropPlatform(objoff);
  PositionPlayerOnVPlat(objoff);
}


// SMB:d63d
// SM2MAIN:a277
// Signature: [X] -> []
void RightPlatform(const u8 objoff) {
  const u8 sVar2 = MoveEnemyHorizontally(objoff);
  if (PlatformCollisionFlag[objoff] < 0x80) {
    Enemy_X_Speed[objoff] = 0x10;
    PositionPlayerOnHPlat(objoff, sVar2);
  }
}


// SMB:d64f
// SM2MAIN:a289
// Signature: [X] -> []
void MoveLargeLiftPlat(const u8 param_1) {
  MoveLiftPlatforms(param_1);
  ChkYPCollision(param_1);
}


// SMB:d655
// SM2MAIN:a28f
// Signature: [X] -> []
void MoveSmallPlatform(const u8 param_1) {
  MoveLiftPlatforms(param_1);
  ChkSmallPlatCollision(param_1);
}


// SMB:d65b
// SM2MAIN:a295
// Signature: [X] -> []
void MoveLiftPlatforms(const u8 param_1) {
  if (TimerControl != 0) {
    return;
  }

  ADD_16_16(Enemy_Y_Position[param_1], Enemy_YMF_Dummy[param_1],
            Enemy_Y_Speed[param_1], Enemy_Y_MoveForce[param_1]);
}


// SMB:d671
// SM2MAIN:a2ab
// Signature: [X] -> []
void ChkSmallPlatCollision(const u8 param_1) {
  if (PlatformCollisionFlag[param_1] != 0) {
    PositionPlayerOnS_Plat(PlatformCollisionFlag[param_1], param_1);
  }
}


// SMB:d67a
// SM2MAIN:a2b4
// Signature: [X] -> []
void OffscreenBoundsCheck(const u8 param_1) {
  if (Enemy_ID[param_1] == A_FLYING_CHEEPCHEEP) {
    return;
  }
  const u8 enemy_id = Enemy_ID[param_1];

  bool bVar3;
  u8 abVar5;

  switch (enemy_id) {
  case A_HAMMER_BRO:
  case A_PIRANHA_PLANT:
#ifdef SMB2J_MODE
  case A_PIRANHA_PLANT_SMB2J:
#endif
    abVar5 = ScreenLeft_X_Pos + 0x38 + 1;
    bVar3 = ScreenLeft_X_Pos < 200 && abVar5 != 0;
    break;

  case A_GREEN_KOOPA:
  case A_RED_KOOPA_GREENLIKE:
  case A_BUZZY_BEETLE:
  case A_RED_KOOPA:
  case A_GOOMBA:
  case A_BLOOBER:
  case A_BULLET_BILL:
  case A_GREEN_PARATROOPA_INPLACE:
  case A_CHEEPCHEEP_GRAY:
  case A_CHEEPCHEEP_RED:
  case A_PODOBOO:
#ifdef SMB1_MODE
  // Note: This matches the behavior of SMB1, even though this id isn't supposed to be used.
  case A_PIRANHA_PLANT_SMB2J:
#endif
    abVar5 = ScreenLeft_X_Pos;
    bVar3 = true;
    break;

  default:
    abVar5 = ScreenLeft_X_Pos;
    bVar3 = false;
    break;
  }

  const bool bVar2 = abVar5 >= 0x48;
  const bool bVar4 = abVar5 > 0x48;
  const bool nk = (!bVar3 && bVar2) || (bVar3 && bVar4);
  const bool k = !nk;
  const bool bVar8 = nk || (!nk && ScreenLeft_PageLoc != 0);
  const u8 bVar6 = ScreenRight_X_Pos + 0x48 + bVar8;

  const u8 e_ploc = Enemy_PageLoc[param_1];
  const u8 e_xp = Enemy_X_Position[param_1];
  const bool p = (ScreenRight_X_Pos >= 0xb8) || (bVar8 && bVar6 == 0);
  const u8 q = (u8)(abVar5 + 0xb8 - bVar3);
  const u8 sl_ploc = ScreenLeft_PageLoc;
  const u8 sr_ploc = ScreenRight_PageLoc;

  const bool A = (u8)(e_ploc - sl_ploc + k - (e_xp < q)) >= 0x80;
  const bool B = (u8)(e_ploc - sr_ploc - p - (e_xp < bVar6)) >= 0x80;

  if (A) {
    // object is to the left of the screen
    EraseEnemyObject(param_1);
    return;
  }

  if (B) {
    // object is on the screen, do not erase
    return;
  }

  // object is to the right of the screen
  // erase, with some exceptions

  if (Enemy_State[param_1] == 5) { return; }
  if (enemy_id == A_PIRANHA_PLANT) { return; }
  if (enemy_id == A_FLAGPOLE) { return; }
  if (enemy_id == A_STARFLAG) { return; }
  if (enemy_id == A_JUMPSPRING) { return; }
  if (SMB2J_ONLY && enemy_id == A_PIRANHA_PLANT_SMB2J) { return; }

  EraseEnemyObject(param_1);
}


// SMB:d6d9
// SM2MAIN:a319
// Signature: [X] -> []
void FireballEnemyCollision(const u8 objoff) {
  if (Fireball_State[objoff] == 0) { return; }
  if ((Fireball_State[objoff] & 0x80) != 0) { return; }
  if ((FrameCounter & 1) != 0) { return; }

  for (int i = 4; i >= 0; i--) {
    const u8 enemy_id = Enemy_ID[i];

    if ((Enemy_State[i] & 0x20) != 0) { continue; }
    if (Enemy_Flag[i] == 0) { continue; }
    if (is_actor_platform_large(enemy_id)) { continue; }
    if (enemy_id == A_GOOMBA && Enemy_State[i] >= 2) { continue; }
    if (EnemyOffscrBitsMasked[i] != 0) { continue; }

    const bool bVar3 = SprObjectCollisionCore(i * 4 + 4, objoff * 4 + 0x1c);
    if (bVar3) {
      Fireball_State[objoff] = 0x80;
      HandleEnemyFBallCol(i);
    }
  }
}


// SMB:d73e
// SM2MAIN:a37f
// Signature: [X+r01] -> []
void HandleEnemyFBallCol(const u8 param_1) {
  u8 bVar2;
  RelativeEnemyPosition(param_1);
  if ((Enemy_Flag[param_1] < 0x80) || (Enemy_ID[Enemy_Flag[param_1] & 0xf] != A_BOWSER)) {
    const u8 enemy_id = Enemy_ID[param_1];
    if (enemy_id == A_BUZZY_BEETLE) {
      return;
    }
    bVar2 = param_1;
    if (enemy_id != A_BOWSER) {
      if (enemy_id == A_BULLET_BILL) {
        return;
      }
      if (enemy_id == A_PODOBOO) {
        return;
      }
      if (!is_actor_enemy(enemy_id)) {
        return;
      }
      ShellOrBlockDefeat(param_1);
      return;
    }
  } else {
    bVar2 = Enemy_Flag[param_1] & 0xf;
  }
  BowserHitPoints -= 1;
  if (BowserHitPoints != 0) {
    return;
  }
  InitVStf(bVar2);
  EnemyFrenzyBuffer = 0;
  Enemy_X_Speed[bVar2] = 0;
  Enemy_Y_Speed[bVar2] = 0xfe;
  Enemy_ID[bVar2] = BowserIdentities[WorldNumber];
  Enemy_State[bVar2] = (WorldNumber < 3) ? 0x23 : 0x20;
  Square2SoundQueue = SOUND_SQ2_BOWSERFALL;
  EnemySmackScore(9, param_1);
}


// SMB:d795
// SM2MAIN:a3d6
// Signature: [X] -> []
void ShellOrBlockDefeat(const u8 param_1) {
  u8 enemy_id = Enemy_ID[param_1];

#ifdef SMB2J_MODE
  if (enemy_id == A_PIRANHA_PLANT_SMB2J) {
    // +1 is possible oversight in original game, didn't clc before adc
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 0x18 + 1 - 0x31;
  }
#endif

  if (enemy_id == A_PIRANHA_PLANT) {
    // +1 is possible oversight in original game, didn't clc before adc
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 0x18 + 1;
  }

#ifdef SMB1_MODE
  if (enemy_id == A_PIRANHA_PLANT) {
    // this reimplements a bug in SMB1
    // NES note: The "A" register is overwritten by the Piranha plant case
    enemy_id = Enemy_Y_Position[param_1];
  }

  ChkToStunEnemies(enemy_id, param_1);
#endif

#ifdef SMB2J_MODE
  ChkToStunEnemies(param_1);
#endif

  Enemy_State[param_1] = (Enemy_State[param_1] & 0x1f) | 0x20;
  if (Enemy_ID[param_1] == A_GOOMBA) {
    EnemySmackScore(1, param_1);
  } else if (Enemy_ID[param_1] == A_HAMMER_BRO) {
    EnemySmackScore(6, param_1);
  } else {
    EnemySmackScore(2, param_1);
  }
}


// SMB:d7bc
// SM2MAIN:a408
// Signature: [A, X] -> []
void EnemySmackScore(const u8 param_1, const u8 param_2) {
  SetupFloateyNumber(param_1, param_2);
  Square1SoundQueue = SOUND_SQ1_KICK;
}


// SMB:d7c4
// SM2MAIN:a410
// Signature: [X] -> []
void PlayerHammerCollision(const u8 objoff) {
  const u8 smb2j_sprobj = SMB2J_ONLY ? SprObject_OffscrBits[0] : 0;

  if (((FrameCounter & 1) != 0) && ((smb2j_sprobj | TimerControl | Misc_OffscreenBits) == 0)) {
    const bool bVar2 = PlayerCollisionCore(objoff * 4 + 0x24);
    if (bVar2) {
      if (Misc_Collision_Flag[objoff] == 0) {
        Misc_Collision_Flag[objoff] = 1;
        Misc_X_Speed[objoff] *= -1;
        if (StarInvincibleTimer == 0) {
          InjurePlayer();
          return;
        }
      }
    } else {
      Misc_Collision_Flag[objoff] = 0;
    }
  }
}


// SMB:d800
// SM2MAIN:a44f
// Signature: [X] -> []
void HandlePowerUpCollision(const u8 objoff) {
  // note: the caller always set X to r08

  EraseEnemyObject(objoff);

  expect(is_powerup_valid(PowerUpType));

#ifdef SMB2J_MODE
  if (PowerUpType == POWERUP_POISONSHROOM) {
    InjurePlayer();
    return;
  }
#endif

  SetupFloateyNumber(6, objoff);

  Square2SoundQueue = SOUND_SQ2_POWERUP_GRAB;

  if (PowerUpType == POWERUP_1UP) {
    FloateyNum_Control[objoff] = 0xb;
  } else if (PowerUpType == POWERUP_STAR) {
    StarInvincibleTimer = 0x23;
    AreaMusicQueue = MUSIC_AREA_STAR;
  } else if (PlayerStatus == PLAYERSTATUS_SMALL) {
    PlayerStatus = PLAYERSTATUS_BIG;
    GameEngineSubroutine = GR_PLAYERCHANGESIZE;
    Player_State = PLAYERSTATE_ONGROUND;
    TimerControl = 0xff;
    ScrollAmount = 0;
  } else if (PlayerStatus == PLAYERSTATUS_BIG) {
    PlayerStatus = PLAYERSTATUS_FIREFLOWER;
    GetPlayerColors();
    GameEngineSubroutine = GR_PLAYERFIREFLOWER;
    Player_State = PLAYERSTATE_ONGROUND;
    TimerControl = 0xff;
    ScrollAmount = 0;
  }
}


// SMB:d853
// SM2MAIN:a4ab
// Signature: [X] -> []
void PlayerEnemyCollision(const u8 objoff) {
  // Note: X is always equal to r08 at the caller

  if (FrameCounter & 1) {
    return;
  }
  if (CheckPlayerVertical()) {
    return;
  }
  if (EnemyOffscrBitsMasked[objoff] != 0) {
    return;
  }
  if (GameEngineSubroutine != GR_PLAYERCTRLROUTINE) {
    return;
  }
  if ((Enemy_State[objoff] & 0x20) != 0) {
    return;
  }

  // Inlined: GetEnemyBoundBoxOfs
  const bool bVar3 = PlayerCollisionCore(objoff * 4 + 4);
  if (!bVar3) {
    Enemy_CollisionBits[objoff] = Enemy_CollisionBits[objoff] & 0xfe;
    return;
  }

  const u8 enemy_id = Enemy_ID[objoff];

  if (enemy_id == A_POWERUP) {
    HandlePowerUpCollision(objoff);
    return;
  }

  if (StarInvincibleTimer != 0) {
    ShellOrBlockDefeat(objoff);
    return;
  }

  if (((Enemy_CollisionBits[objoff] & 1) | EnemyOffscrBitsMasked[objoff]) != 0) {
    return;
  }

  Enemy_CollisionBits[objoff] = Enemy_CollisionBits[objoff] | 1;

  if (enemy_id == A_PODOBOO || enemy_id == A_PIRANHA_PLANT) {
    InjurePlayer();
    return;
  }

#ifdef SMB2J_MODE
  if (enemy_id == A_PIRANHA_PLANT_SMB2J) {
    InjurePlayer();
    return;
  }
#endif

  if ((enemy_id != A_SPINY) && (enemy_id != A_BULLET_BILL_CANNON)) {
    if (!is_actor_enemy(enemy_id)) {
      InjurePlayer();
      return;
    }

    if (AreaType == AREA_WATER) {
      InjurePlayer();
      return;
    }

    if (((Enemy_State[objoff] & 0x80) == 0) && ((Enemy_State[objoff] & 6) != 0)) {
      if (enemy_id == A_GOOMBA) {
        return;
      }
      Square1SoundQueue = SOUND_SQ1_KICK;
      Enemy_State[objoff] |= 0x80;
      Enemy_X_Speed[objoff] = EnemyFacePlayer(objoff) ? -0x30 : 0x30;

      const u8 interval_timer = EnemyIntervalTimer[objoff];

      u8 points;

      switch (interval_timer) {
      case 0:  points = 10; break;
      case 1:  points = 6; break;
      case 2:  points = 4; break;
      default: points = StompChainCounter + 3; break;
      }

      SetupFloateyNumber(points, objoff);
      return;
    }
  }

  expect(is_actor_enemy(enemy_id) || enemy_id == A_BULLET_BILL_CANNON);

  if (StompTimer == 0) {
    bool cond1 = false;

    switch (enemy_id) {
    case A_GREEN_KOOPA:
    case A_RED_KOOPA_GREENLIKE:
    case A_BUZZY_BEETLE:
    case A_RED_KOOPA:
    case A_PIRANHA_PLANT_SMB2J:
    case A_HAMMER_BRO:
    case A_GOOMBA:
      cond1 = true;
      break;

    default:
      cond1 = Enemy_Y_Position[objoff] <= (u8)(Player_Y_Position + 0xC);
      break;
    }

#ifdef SMB1_MODE
      const bool cond2 = (Player_Y_Speed == 0) || (Player_Y_Speed >= 0x80);
#endif
#ifdef SMB2J_MODE
      const bool cond2 = (Player_Y_Speed == 0) || (Player_Y_Speed > 0x80);
#endif

    if (cond1 && cond2) {
      if (InjuryTimer != 0) {
        return;
      }

      if (Player_Rel_XPos >= Enemy_Rel_XPos) {
        ChkEnemyFaceRight(objoff);
      } else if (Enemy_MovingDir[objoff] != 1) {
        InjurePlayer();
      } else {
        LInj(objoff);
      }

      return;
    }
  }

  if (enemy_id == A_SPINY) {
    InjurePlayer();
    return;
  }
  Square1SoundQueue = SOUND_SQ1_SWIM_OR_SQUISH;

  bool cond3 = true;

  u8 points;

  switch (enemy_id) {
    case A_HAMMER_BRO:
      points = 6;
      cond3 = false;
      break;

    case A_BLOOBER:
      points = 6;
      cond3 = false;
      break;

    case A_BULLET_BILL:
    case A_FLYING_CHEEPCHEEP:
    case A_BULLET_BILL_CANNON:
      points = 2;
      cond3 = false;
      break;

    case A_LAKITU:
      points = 5;
      cond3 = false;
      break;
  }

  if (cond3) {
    bool cond4 = false;

    switch (enemy_id) {
    case A_GREEN_KOOPA:
    case A_RED_KOOPA_GREENLIKE:
    case A_BUZZY_BEETLE:
    case A_RED_KOOPA:
    case A_PIRANHA_PLANT_SMB2J:
    case A_GOOMBA:
      cond4 = true;
      break;

    default:
      cond4 = false;
      break;
    }

    if (cond4) {
      Enemy_State[objoff] = 4;
      StompChainCounter += 1;
      SetupFloateyNumber(StompChainCounter + StompTimer, objoff);
      StompTimer += 1;

      expect(PrimaryHardMode <= 1);

      EnemyIntervalTimer[objoff] = PrimaryHardMode == 0 ? 16 : 11;

#ifdef SMB1_MODE
      Player_Y_Speed = 0xfc;
#endif
#ifdef SMB2J_MODE
      SetBounce(objoff);
#endif
    } else {
#ifdef SMB2J_MODE
      // NES note: SetBounce could overwrite the enemy id if it misbehaves
      // I'm not sure if this is achievable
      expect(objoff != 0x9f - 0x16);

      SetBounce(objoff);
#endif

      Enemy_ID[objoff] = is_actor_even(Enemy_ID[objoff]) ? A_GREEN_KOOPA : A_RED_KOOPA_GREENLIKE;
      Enemy_State[objoff] = 0;
      SetupFloateyNumber(3, objoff);
      InitVStf(objoff);
      Enemy_X_Speed[objoff] = EnemyFacePlayer(objoff) ? -8 : 8;
#ifdef SMB1_MODE
      Player_Y_Speed = 0xfc;
#endif
    }
  } else {
    SetupFloateyNumber(points, objoff);
    const u8 old_movingdir = Enemy_MovingDir[objoff];

    // Inlined: SetStun (SMB1), NoDemote (SMB2J)
    // Note: removing an Enemy_State assignment here because it's not read until it's written to again

    SetStun2(objoff);
    Enemy_MovingDir[objoff] = old_movingdir;
    Enemy_State[objoff] = 0x20;
    InitVStf(objoff);
    Enemy_X_Speed[objoff] = 0;

#ifdef SMB1_MODE
    Player_Y_Speed = 0xfd;
#endif
#ifdef SMB2J_MODE
    SetBounce(objoff);
#endif
  }
  return;
}


// SMB:d92c
// SM2MAIN:a587
// Signature: [] -> []
void InjurePlayer(void) {
  if (InjuryTimer == 0) {
    if (SMB1_ONLY || (SMB2J_ONLY && StarInvincibleTimer == 0)) {
      ForceInjury();
    }
  }
}


// SMB:d931
// SM2MAIN:a58f
// Signature: [] -> []
void ForceInjury(void) {
  // NES note: The caller always sets register "A" to 0, so we're omitting a parameter.

  if (PlayerStatus == PLAYERSTATUS_SMALL) {
    EventMusicQueue = MUSIC_EVENT_DEATH;
    Player_Y_Speed = 0xfc;
    Player_X_Speed = 0;
    GameEngineSubroutine = GR_PLAYERDEATH;
  } else {
    InjuryTimer = 8;
    Square1SoundQueue = SOUND_SQ1_PIPE_OR_INJURY;
    PlayerStatus = PLAYERSTATUS_SMALL;
    GetPlayerColors();
    GameEngineSubroutine = GR_PLAYERINJURYBLINK;
  }
  Player_State = PLAYERSTATE_JUMPSWIM;
  TimerControl = 0xff;
  ScrollAmount = 0;
}


// SMB:d9f6
// SM2MAIN:a65f
// Signature: [X] -> []
void ChkEnemyFaceRight(const u8 objoff) {
  if (Enemy_MovingDir[objoff] != 1) {
    LInj(objoff);
  } else {
    InjurePlayer();
  }
}


// SMB:d9ff
// SM2MAIN:a668
// Signature: [X] -> []
void LInj(const u8 objoff) {
  EnemyTurnAround(objoff);
  InjurePlayer();
}


// SMB:da05
// SM2MAIN:a66e
// Signature: [X] -> [Y]
bool EnemyFacePlayer(const u8 objoff) {
  const struct_ncr00 sVar2 = PlayerEnemyDiff(objoff);
  Enemy_MovingDir[objoff] = sVar2.n ? 2 : 1;
  return sVar2.n;
}


// SMB:da11
// SM2MAIN:a67a
// Signature: [A, X] -> []
void SetupFloateyNumber(const u8 param_1, const u8 param_2) {
  FloateyNum_Control[param_2] = param_1;
  FloateyNum_Timer[param_2] = 0x30;
  FloateyNum_Y_Pos[param_2] = Enemy_Y_Position[param_2];
  FloateyNum_X_Pos[param_2] = Enemy_Rel_XPos;
}


static inline bool EnemiesCollision_condition(const u8 enemyoff) {
  const u8 enemy_id = Enemy_ID[enemyoff];

  if (!is_actor_enemy(enemy_id)) { return true; }
  if (enemy_id == A_LAKITU) { return true; }
  if (enemy_id == A_PIRANHA_PLANT) { return true; }

#ifdef SMB2J_MODE
  if (enemy_id == A_PIRANHA_PLANT_SMB2J) { return true; }
#endif

  if (EnemyOffscrBitsMasked[enemyoff] != 0) { return true; }

  return false;
}

// SMB:da33
// SM2MAIN:a69c
// Signature: [X] -> []
void EnemiesCollision(const u8 objoff) {
  if ((FrameCounter & 1) == 0) {
    return;
  }

  if (AreaType == AREA_WATER) {
    return;
  }

  expect(objoff < 0x80);

  if (EnemiesCollision_condition(objoff)) {
    return;
  }

  // Inlined: GetEnemyBoundBoxOfs
  const u8 bStack0000 = objoff * 4 + 4;

  for (int i = objoff - 1; i >= 0; i--) {
    if (Enemy_Flag[i] == 0) {
      continue;
    }

    if (EnemiesCollision_condition(i)) {
      continue;
    }

    const bool bVar2 = SprObjectCollisionCore(i * 4 + 4, bStack0000);

    // objectoffset must be between 0 and 6 inclusive

    expect(objoff >= 0 && objoff <= 6);

    const u8 bitsmask = 1 << (7 - objoff);

    if (!bVar2) {
      Enemy_CollisionBits[i] &= ~bitsmask;
    } else if ((Enemy_State[objoff] & 0x80) != 0 || (Enemy_State[i] & 0x80) != 0) {
      ProcEnemyCollisions(objoff, i);
    } else if ((Enemy_CollisionBits[i] & bitsmask) == 0) {
      Enemy_CollisionBits[i] |= bitsmask;
      ProcEnemyCollisions(objoff, i);
    }
  }
}


// SMB:dab4
// SM2MAIN:a725
// Signature: [X, Y+r01] -> []
void ProcEnemyCollisions(const u8 objoff, const u8 param_2) {
  if (((Enemy_State[param_2] | Enemy_State[objoff]) & 0x20) == 0) {
    if (Enemy_State[objoff] < 6) {
      if (Enemy_State[param_2] < 6) {
        EnemyTurnAround(param_2);
        EnemyTurnAround(objoff);
        return;
      }
      if (Enemy_ID[param_2] != A_HAMMER_BRO) {
        ShellOrBlockDefeat(objoff);
        SetupFloateyNumber(ShellChainCounter[param_2] + 4, objoff);
        ShellChainCounter[param_2] = ShellChainCounter[param_2] + 1;
        return;
      }
    } else if (Enemy_ID[objoff] != A_HAMMER_BRO) {
      if ((char)Enemy_State[param_2] < 0) {
        SetupFloateyNumber(6, objoff);
        ShellOrBlockDefeat(objoff);
      }
      ShellOrBlockDefeat(param_2);
      SetupFloateyNumber(ShellChainCounter[objoff] + 4, param_2);
      ShellChainCounter[objoff] = ShellChainCounter[objoff] + 1;
    }
  }
}


// SMB:db1c
// SM2MAIN:a78d
// Signature: [X] -> []
void EnemyTurnAround(const u8 param_1) {
  const u8 enemy_id = Enemy_ID[param_1];

  switch (enemy_id) {
  case A_GREEN_KOOPA:
  case A_RED_KOOPA_GREENLIKE:
  case A_BUZZY_BEETLE:
  case A_RED_KOOPA:
  case A_GOOMBA:
  case A_GREEN_PARATROOPA:
  case A_SPINY:
#ifdef SMB1_MODE
  // Note: This matches the behavior of SMB1, even though this id isn't supposed to be used.
  case A_PIRANHA_PLANT_SMB2J:
#endif
    // Inlined: RXSpd
    Enemy_X_Speed[param_1] *= -1;
    Enemy_MovingDir[param_1] ^= 3;
    break;
  }
}


static inline void ChkForPlayerC_LargeP(const u8 param_1, const u8 objoff);

// SMB:db45
// SM2MAIN:a7ba
// Signature: [X] -> []
void LargePlatformCollision(const u8 objoff) {
  PlatformCollisionFlag[objoff] = 0xff;
  if ((TimerControl == 0) && (Enemy_State[objoff] < 0x80)) {
    if (Enemy_ID[objoff] == A_LARGEPLATFORM_BALANCE) {
      ChkForPlayerC_LargeP(Enemy_State[objoff], objoff);
    }
    ChkForPlayerC_LargeP(objoff, objoff);
  }
}


// SMB:db5f
// SM2MAIN:a7d4
// Signature: [X, r08] -> []
static inline void ChkForPlayerC_LargeP(const u8 param_1, const u8 objoff) {
  if (CheckPlayerVertical()) {
    return;
  }

  // Inlined: GetEnemyBoundBoxOfs
  const u8 bVar2 = (param_1 + 1) * 4;

  const u8 bVar1 = Enemy_Y_Position[param_1];
  const bool bVar3 = PlayerCollisionCore(bVar2);
  if (bVar3) {
    ProcLPlatCollisions(param_1, bVar2, bVar1, objoff);
  }
}


// SMB:db7b
// SM2MAIN:a7f0
// Signature: [X] -> []
void SmallPlatformCollision(const u8 objoff) {
  if (TimerControl != 0) {
    return;
  }

  PlatformCollisionFlag[objoff] = 0;

  if (CheckPlayerVertical()) {
    return;
  }

  for (int i = 2; i > 0; i--) {
    // Inlined: GetEnemyBoundBoxOfs
    // NES note: (Enemy_OffscreenBits & 0x2) came from GetEnemyBoundBoxOfs. We're inlining it here.
    if ((Enemy_OffscreenBits & 0x2) != 0) {
      return;
    }
    const u8 bVar1 = objoff + 1;
    if ((BBOX_TOPLEFT_Y(bVar1) >= 0x20)) {
      const bool bVar3 = PlayerCollisionCore(bVar1 * 4);
      if (bVar3) {
        ProcLPlatCollisions(objoff, bVar1 * 4, i, objoff);
        return;
      }
    }
    BBOX_TOPLEFT_Y(bVar1) += 0x80;
    BBOX_BOTRIGHT_Y(bVar1) += 0x80;
  }
}


// SMB:dbbc
// SM2MAIN:a831
// Signature: [X, Y, r00, r08] -> []
void ProcLPlatCollisions(const u8 param_1, const u8 param_2, const u8 param_3, const u8 objoff) {
  // This is always the case in the original
  // TODO: check if any other values would make sense and if param_2 should be eliminated
  expect(param_2 == (param_1+1)*4);
  const u8 param_2_div4 = param_2 / 4;

  if (((u8)(BBOX_BOTRIGHT_Y(param_2_div4) - BBOX_TOPLEFT_Y(0)) < 4) && (Player_Y_Speed >= 0x80)) {
    Player_Y_Speed = 1;
  }
  if (((u8)(BBOX_BOTRIGHT_Y(0) - BBOX_TOPLEFT_Y(param_2_div4)) < 6) && (Player_Y_Speed < 0x80)) {
    u8 tmp3 = param_3;
    if ((Enemy_ID[param_1] != A_SMALLPLATFORM_1) && (Enemy_ID[param_1] != A_SMALLPLATFORM_2)) {
      tmp3 = param_1;
    }
    PlatformCollisionFlag[objoff] = tmp3;
    Player_State = PLAYERSTATE_ONGROUND;
    return;
  }

  if ((u8)(BBOX_BOTRIGHT_X(0) - BBOX_TOPLEFT_X(param_2_div4)) <= 7) {
    ImpedePlayerMove(1);
  } else {
    if ((u8)(BBOX_BOTRIGHT_X(param_2_div4) - BBOX_TOPLEFT_X(0) - 1) <= 8) {
      ImpedePlayerMove(2);
    }
  }
}


// SMB:dc19
// SM2MAIN:a88e
// Signature: [A, X] -> []
void PositionPlayerOnS_Plat(const u8 param_1, const u8 param_2) {
  expect(param_1 == 1 || param_1 == 2);

  if ((GameEngineSubroutine != GR_PLAYERDEATH) && (Enemy_Y_HighPos[param_2] == 1)) {
    u16 ypos = LOAD_16(Enemy_Y_HighPos[param_2],
                       Enemy_Y_Position[param_2] + (param_1 == 1 ? 0x80 : 0));
    ypos -= 32;

    STORE_16(Player_Y_HighPos, Player_Y_Position, ypos);

    Player_Y_Speed = 0;
    Player_Y_MoveForce = 0;
  }
}


// SMB:dc21
// SM2MAIN:a896
// Signature: [X] -> []
void PositionPlayerOnVPlat(const u8 param_1) {
  if ((GameEngineSubroutine != GR_PLAYERDEATH) && (Enemy_Y_HighPos[param_1] == 1)) {
    Player_Y_Position = Enemy_Y_Position[param_1] - 0x20;
    Player_Y_HighPos = 1 - (Enemy_Y_Position[param_1] < 0x20);
    Player_Y_Speed = 0;
    Player_Y_MoveForce = 0;
  }
}


// SMB:dc41
// SM2MAIN:a8b6
// Signature: [] -> [C]
bool CheckPlayerVertical(void) {
#ifdef SMB1_MODE
  return SprObject_OffscrBits[0] >= 0xf0 || (Player_Y_HighPos == 1 && Player_Y_Position >= 0xd0);
#endif
#ifdef SMB2J_MODE
  return (SprObject_OffscrBits[0] & 0xf0) != 0;
#endif
}


// SMB:de05
// SM2MAIN:aa73
static void HandleCoinMetatile(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  set_metatile(mt_x, mt_y, MT_0);

  RemoveCoin_Axe(mt_x, mt_y);

  CoinTallyFor1Ups += 1;
  GiveOneCoin();
}


// SMB:de0e
// SM2MAIN:aa7c
static void HandleAxeMetatile(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  OperMode = OM_VICTORY;
  OperMode_Task = OMT_VICTORY_BRIDGECOLLAPSE;
#ifdef SMB2J_MODE
  LoadMarioPhysics();
#endif
  Player_X_Speed = 0x18;

  set_metatile(mt_x, mt_y, MT_0);

  RemoveCoin_Axe(mt_x, mt_y);
}

static void CheckSideMTiles(const u8 i, const u8 bVar5, const u8 bVar2, const u16 mt_x, const u16 mt_y);

// SMB:dc64
// SM2MAIN:a8d2
// Signature: [] -> []
void PlayerBGCollision(void) {
  u8 bVar2;
  u8 bVar5;
  u8 bVar7;
  bool bVar8;
  struct blockbuffer_colli_result sVar11;

  if (DisableCollisionDet != 0) {
    return;
  }

  // GameEngineSubroutine < 4 or GameEngineSubroutine == 11
  switch (GameEngineSubroutine) {
  case GR_ENTRANCE_GAMETIMERSETUP:
  case GR_VINE_AUTOCLIMB:
  case GR_SIDEEXITPIPEENTRY:
  case GR_VERTICALPIPEENTRY:
  case GR_PLAYERDEATH:
    return;
  }

  if (SwimmingFlag == 0) {
    if ((Player_State == PLAYERSTATE_ONGROUND) || (Player_State == PLAYERSTATE_CLIMBING)) {
      Player_State = PLAYERSTATE_FALLING;
    }
  } else {
    Player_State = PLAYERSTATE_JUMPSWIM;
  }

  if (Player_Y_HighPos != 1) {
    return;
  }

  Player_CollisionBits = 0xff;

  if (Player_Y_Position > 0xce) {
    return;
  }

  u8 tmp1;

  if ((CrouchingFlag == 0) && (PlayerSize == 0)) {
    if (SwimmingFlag == 0) {
      tmp1 = 0;
    } else {
      tmp1 = 7;
    }
  } else {
    tmp1 = 14;
  }

  // Note: assuming these both cannot be non-zero. it simplifies a lookup.
  expect(PlayerSize == 0 || CrouchingFlag == 0);
  expect(PlayerSize <= 1);

  const u8 upperextent = (PlayerSize != 0 || CrouchingFlag != 0) ? 0x10 : 0x20;

  if (upperextent <= Player_Y_Position) {
    // Inlined: BlockBufferColli_Head
    // head collision
    const struct blockbuffer_colli_result sVar9 = BlockBufferCollision(0, 0, tmp1);
    const u8 bVar1 = sVar9.r04;
    if (sVar9.a != 0) {
      if (CheckForCoinMTiles(sVar9.a)) {
        HandleCoinMetatile(sVar9.mt_x, sVar9.mt_y);
        return;
      }
      bVar7 = sVar9.a;
      if ((Player_Y_Speed >= 0x80) && (bVar1 >= 4)) {
        bVar8 = CheckForSolidMTiles(bVar7);

        bool myspd = true;

        if (bVar8) {
          if (bVar7 != MT_SPECIAL_VINE) {
            Square1SoundQueue = SOUND_SQ1_BUMP;
          }
        } else if ((AreaType != AREA_WATER) && (BlockBounceTimer == 0)) {
          const u16 mt_x = sVar9.mt_x;
          const u16 mt_y = sVar9.mt_y;
          PlayerHeadCollision(bVar7, mt_x, mt_y);
          myspd = false;
        }

        if (myspd) {
          // MYSpd
          Player_Y_Speed = 1;
        }
      }
    }
  }

  // DoFootCheck

  if (Player_Y_Position < 0xcf) {
    // Inlined: BlockBufferColli_Feet
    // foot check 1
    sVar11 = BlockBufferCollision(0, 0, tmp1 + 1);
    if (CheckForCoinMTiles(sVar11.a)) {
      HandleCoinMetatile(sVar11.mt_x, sVar11.mt_y);
      return;
    }
    const u8 bVar1 = sVar11.a;
    // Inlined: BlockBufferColli_Feet
    // foot check 2
    sVar11 = BlockBufferCollision(0, 0, tmp1 + 2);
    bVar5 = sVar11.r04;
    bVar2 = sVar11.a;
    bVar7 = bVar1;
    if ((bVar1 != 0) || (bVar2 != 0)) {
      if (bVar1 == 0) {
        if (CheckForCoinMTiles(bVar2)) {
          HandleCoinMetatile(sVar11.mt_x, sVar11.mt_y);
          return;
        }
        bVar7 = bVar2;
      }
      bVar8 = CheckForClimbMTiles(bVar7);
      if ((!bVar8) && (Player_Y_Speed < 0x80)) {
        if (bVar7 == MT_AXE) {
          HandleAxeMetatile(sVar11.mt_x, sVar11.mt_y);
          return;
        }
        bVar8 = ChkInvisibleMTiles(bVar7);
        if (!bVar8) {
          if (JumpspringAnimCtrl == 0) {
            if (bVar5 >= 5) {
              ImpedePlayerMove(Player_MovingDir);
              return;
            }
            ChkForLandJumpSpring(bVar7);
            Player_Y_Position &= 0xf0;
            HandlePipeEntry(bVar2, bVar1);
            Player_Y_Speed = 0;
            Player_Y_MoveForce = 0;
            StompChainCounter = 0;
          }
          Player_State = PLAYERSTATE_ONGROUND;
        }
      }
    }
  }

  // DoPlayerSideCheck

  if (Player_Y_Position >= 8 && Player_Y_Position < 0xe4) {
    if (Player_Y_Position >= 0x20) {
      // Inlined: BlockBufferColli_Side
      // side check 1
      const struct blockbuffer_colli_result sVar9 = BlockBufferCollision(1, 0, tmp1 + 3);
      bVar5 = sVar9.a;
      const bool cond = (bVar5 == MT_0) || (bVar5 == MT_PIPE_SIDEWAYS_TL) || (bVar5 == MT_WATERPIPE_T) || CheckForClimbMTiles(bVar5);
      if (!cond) {
        CheckSideMTiles(2, bVar5, sVar9.r04, sVar9.mt_x, sVar9.mt_y);
        return;
      }
    }

    if (Player_Y_Position < 0xd0) {
      // Inlined: BlockBufferColli_Side
      // side check 2
      const struct blockbuffer_colli_result sVar9 = BlockBufferCollision(1, 0, tmp1 + 4);
      bVar5 = sVar9.a;
      const bool cond = sVar9.a == MT_0;
      if (!cond) {
        CheckSideMTiles(2, bVar5, sVar9.r04, sVar9.mt_x, sVar9.mt_y);
        return;
      }
    }

    if (Player_Y_Position >= 0x20 && Player_Y_Position < 0xd0) {
      // Inlined: BlockBufferColli_Side
      // side check 1
      const struct blockbuffer_colli_result sVar9 = BlockBufferCollision(1, 0, tmp1 + 5);
      bVar5 = sVar9.a;
      const bool cond = (bVar5 == MT_0) || (bVar5 == MT_PIPE_SIDEWAYS_TL) || (bVar5 == MT_WATERPIPE_T) || CheckForClimbMTiles(bVar5);
      if (!cond) {
        CheckSideMTiles(1, bVar5, sVar9.r04, sVar9.mt_x, sVar9.mt_y);
        return;
      }
    }

    if (Player_Y_Position < 0xd0) {
      // Inlined: BlockBufferColli_Side
      // side check 2
      const struct blockbuffer_colli_result sVar9 = BlockBufferCollision(1, 0, tmp1 + 6);
      bVar5 = sVar9.a;
      const bool cond = sVar9.a == MT_0;
      if (!cond) {
        CheckSideMTiles(1, bVar5, sVar9.r04, sVar9.mt_x, sVar9.mt_y);
        return;
      }
    }
  }
}


// SMB:dd9c
// SM2MAIN:aa0a
static void CheckSideMTiles(const u8 dir, const u8 bVar5, const u8 bVar2, const u16 mt_x, const u16 mt_y) {
  if (ChkInvisibleMTiles(bVar5)) {
    return;
  }

  if (CheckForClimbMTiles(bVar5)) {
    HandleClimbing(bVar5, bVar2, mt_x);
    return;
  }

  if (CheckForCoinMTiles(bVar5)) {
    HandleCoinMetatile(mt_x, mt_y);
    return;
  }

  if (ChkJumpspringMetatiles(bVar5)) {
    if (JumpspringAnimCtrl != 0) {
      return;
    }
  } else if ((Player_State == PLAYERSTATE_ONGROUND) && (PlayerFacingDir == 1) && ((bVar5 == MT_WATERPIPE_B || (bVar5 == MT_PIPE_SIDEWAYS_BL)))) {
    if (Player_SprAttrib == 0) {
      Square1SoundQueue = SOUND_SQ1_PIPE_OR_INJURY;
    }
    Player_SprAttrib |= 0x20;
    if ((Player_X_Position & 0xf) != 0) {
      ChangeAreaTimer = ScreenLeft_PageLoc != 0 ? 0x34 : 0xa0;
    }

    // 7 != 8, so this seems redundant. But it's in the assembly.
    // We'll keep it in in case it's semantically meaningful in later refactor efforts.
    if (GameEngineSubroutine == GR_PLAYERENTRANCE) {
      return;
    }
    if (GameEngineSubroutine != GR_PLAYERCTRLROUTINE) {
      return;
    }
    GameEngineSubroutine = GR_SIDEEXITPIPEENTRY;
    return;
  }

  ImpedePlayerMove(dir);
}

// SMB:de2e
// SM2MAIN:aa9f
void HandleClimbing(const u8 param_1, const u8 param_2, const u16 mt_x) {
  // Note: Old signature was [A, r04, r06] -> []
  // Reworked to use metatile coordinates instead of pointer

  if ((param_2 < 6) || (param_2 >= 10)) {
    return;
  }

  if ((param_1 == MT_FLAGPOLE_T) || (param_1 == MT_FLAGPOLE_M)) {
    if (GameEngineSubroutine != GR_PLAYERENDLEVEL) {
      PlayerFacingDir = 1;
      ScrollLock += 1;
      if (GameEngineSubroutine != GR_FLAGPOLESLIDE) {
        KillEnemies(0x33);
        EventMusicQueue = MUSIC_EVENT_STOP;
        FlagpoleSoundQueue = SOUND_SQ1_FLAGPOLE;
        FlagpoleCollisionYPos = Player_Y_Position;

        FlagpoleScore = 0;

        static const u8 flagpole_score_y_pos[] = {24, 34, 80, 104, 144};

        // Award the player points depending on how far up the flag pole they are
        for (int i = 4; i > 0; i--) {
          if (flagpole_score_y_pos[i] <= Player_Y_Position) {
            FlagpoleScore = i;
            break;
          }
        }

        // In SMB2J, if the coins are a multiple of 11 and have the same digit as the last digit of the timer,
        // then award a 1-up.
        if (SMB2J_ONLY && (CoinDisplay[0] == CoinDisplay[1]) && (CoinDisplay[0] == GameTimerDisplay[2])) {
          FlagpoleScore = 5;
        }
      }
      GameEngineSubroutine = GR_FLAGPOLESLIDE;
    }
  } else if ((param_1 == MT_SPECIAL_VINE) && (Player_Y_Position < 0x20)) {
    GameEngineSubroutine = GR_VINE_AUTOCLIMB;
  }
  Player_State = PLAYERSTATE_CLIMBING;
  Player_X_Speed = 0;
  Player_X_MoveForce = 0;
  if ((u8)(Player_X_Position - ScreenLeft_X_Pos) < 0x10) {
    PlayerFacingDir = 2;
  }

  // NES note: The game assumes PlayerFacingDir is >= 1, but that's not always the case.
  // It can = 0, and when it is, it references a 6502 instruction operand ($8A in SMB1, $69 in SMB2J).
  // It occurs in level 2-1 in this SMB1 TAS: https://tasvideos.org/6913S
  //
  // It sometimes = 3 as well.
  // It occurs in level 8-2 in this SMB2J TAS: https://tasvideos.org/5394S

#ifdef SMB1_MODE
  static const i8 xpos_adder_lookup[4] = { (i8)0x8a, -7, 7, -1 };
  static const i8 ploc_adder_lookup[4] = { 7, -1, 0, 24 };
#endif
#ifdef SMB2J_MODE
  static const i8 xpos_adder_lookup[4] = { (i8)0x69, -7, 7, -1 };
  static const i8 ploc_adder_lookup[4] = { 7, -1, 0, 24 };
#endif

  Player_X_Position = (u8)(mt_x * 16) + xpos_adder_lookup[PlayerFacingDir];

  if ((mt_x % 32) == 0) {
    // mt_x is the first column of an even page

    Player_PageLoc = ScreenRight_PageLoc + ploc_adder_lookup[PlayerFacingDir];
  }
}


// SMB:debd
// SM2MAIN:ab40
// Signature: [A] -> [Z]
bool ChkInvisibleMTiles(const u8 mtile) {
#ifdef SMB1_MODE
  return mtile == 0x5f || mtile == 0x60;
#endif
#ifdef SMB2J_MODE
  return mtile == 0x5e || mtile == 0x5f || mtile == 0x60 || mtile == 0x61;
#endif
}


// SMB:dec4
// SM2MAIN:ab4f
// Signature: [A] -> []
void ChkForLandJumpSpring(const u8 param_1) {
  const bool bVar1 = ChkJumpspringMetatiles(param_1);
  if (bVar1) {
    VerticalForce = 0x70;
    if (SMB2J_ONLY) {
      VerticalForceDown = 0x70;
    }
    JumpspringForce = 0xf9;
    JumpspringTimer = 3;
    JumpspringAnimCtrl = 1;
  }
}


// SMB:dedd
// SM2MAIN:ab6b
// Signature: [A] -> [C]
bool ChkJumpspringMetatiles(const u8 param_1) {
  if (param_1 == MT_JUMPSPRING_T) {
    return true;
  }

  if (param_1 == MT_JUMPSPRING_B) {
    return true;
  }

  return false;
}


// SMB:dee8
// SM2MAIN:ab76
// Signature: [r00, r01] -> []
void HandlePipeEntry(const u8 param_1, const u8 param_2) {
  u8 bVar1;

  if ((((Up_Down_Buttons & BUTTON_D) != 0) && (param_1 == 0x11)) && (param_2 == 0x10)) {
    ChangeAreaTimer = 0x30;
    GameEngineSubroutine = GR_VERTICALPIPEENTRY;
    Square1SoundQueue = SOUND_SQ1_PIPE_OR_INJURY;
    Player_SprAttrib = 0x20;
    if (WarpZoneControl != 0) {
      if (SMB1_ONLY) {
        if (Player_X_Position < 0x60) {
          bVar1 = WarpZoneNumbers[(WarpZoneControl & 3) * 4];
        } else if (Player_X_Position < 0xa0) {
          bVar1 = WarpZoneNumbers[(WarpZoneControl & 3) * 4 + 1];
        } else {
          bVar1 = WarpZoneNumbers[(WarpZoneControl & 3) * 4 + 2];
        }
        WorldNumber = bVar1 - 1;
      }
      if (SMB2J_ONLY) {
        if (HardWorldFlag != 0) {
          bVar1 = WarpZoneNumbers[WarpZoneControl & 0xf] - 9;
        } else {
          bVar1 = WarpZoneNumbers[WarpZoneControl & 0xf];
        }
        WorldNumber = bVar1 - 1;
      }
      AreaPointer = AreaAddrOffsets[WorldAddrOffsets[WorldNumber]];
      EventMusicQueue = MUSIC_EVENT_STOP;
      EntrancePage = 0;
      AreaNumber = 0;
      LevelNumber = 0;
      AltEntranceControl = 0;
      Hidden1UpFlag += 1;
      FetchNewGameTimerFlag += 1;
    }
  }
}


// SMB:df4b
// SM2MAIN:abd4
// Signature: [r00] -> []
void ImpedePlayerMove(const u8 param_1) {
  u8 bVar1;
  u8 bVar2;
  bool nxspd;

  if (param_1 == 1) {
    nxspd = Player_X_Speed < 0x80;
    bVar2 = 1;
    bVar1 = -1;
  } else {
    nxspd = (u8)(Player_X_Speed - 1) >= 0x80;
    bVar2 = 2;
    bVar1 = 1;
  }

  if (nxspd) {
    // NXSpd

    SideCollisionTimer = 0x10;
    Player_X_Speed = 0;

    ADD_SIGNED_16_8(Player_PageLoc, Player_X_Position,
                    bVar1);
  }

  // ExIPM
  Player_CollisionBits = (bVar2 ^ 0xff) & Player_CollisionBits;
}


// SMB:df8f
// SM2MAIN:ac18
// Signature: [A] -> [C]
bool CheckForSolidMTiles(const u8 mt) {
  // Note: expanded to explicit comparisons.
  // TODO: identify the classses of metatiles below

  if (mt >= MT_PIPE_VERT_WARP_TL && mt < 0x40) { return true; }

  if (mt >= MT_STAIR_BLOCK && mt < 0x80) { return true; }

  if (mt >= MT_CLOUD_BLOCK && mt < 0xc0) { return true; }

  if (mt >= MT_BLOCK_EMPTY) { return true; }

  return false;
}


// SMB:df9a
// SM2MAIN:ac23
// Signature: [A] -> [C]
bool CheckForClimbMTiles(const u8 mt) {
  // Note: expanded to explicit comparisons.
  // TODO: identify the classses of metatiles below

  if (mt >= MT_FLAGPOLE_T && mt < 0x40) { return true; }

  if (mt >= MT_FLAGBALL && mt < 0x80) { return true; }

  if (mt >= MT_unk21 && mt < 0xc0) { return true; }

  if (mt >= MT_unk20) { return true; }

  return false;
}


// SMB:dfa1
// SM2MAIN:ac2a
// Signature: [A] -> [C]
bool CheckForCoinMTiles(const u8 param_1) {
  if (param_1 == MT_COIN || param_1 == MT_COIN_UNDERWATER) {
    Square2SoundQueue = SOUND_SQ2_COIN;
    return true;
  }

  return false;
}


// SMB:dfc1
// SM2MAIN:ac4a
// Signature: [X] -> []
void EnemyToBGCollisionDet(const u8 objoff) {
  struct_ncr00 sVar5;

  if ((Enemy_State[objoff] & 0x20) != 0) {
    return;
  }

  const bool bVarDD = SubtEnemyYPos(objoff);
  if (!bVarDD) {
    return;
  }

  const u8 enemy_id = Enemy_ID[objoff];

  switch (enemy_id) {
  case A_GREEN_PARATROOPA:
    EnemyJump(objoff);
    return;

  case A_HAMMER_BRO:
    HammerBroBGColl(objoff);
    return;

  case A_SPINY:
    if (Enemy_Y_Position[objoff] < 0x25) {
      return;
    }
    break;

  case A_POWERUP:
  case A_GREEN_KOOPA:
  case A_RED_KOOPA_GREENLIKE:
  case A_BUZZY_BEETLE:
  case A_RED_KOOPA:
  case A_GOOMBA:
#ifdef SMB1_MODE
  // Note: This matches the behavior of SMB1, even though this id isn't supposed to be used.
  case A_PIRANHA_PLANT_SMB2J:
#endif
    break;

  default:
    return;
  }

  // Inlined: ChkUnderEnemy
  const struct blockbuffer_colli_result sVar6 = BlockBufferCollision(0, objoff + 1, 21);

  if (sVar6.a == 0 || ChkForNonSolids(sVar6.a)) {
    ChkForRedKoopa(objoff);
    return;
  }

  if (sVar6.a == MT_SPECIAL_BLOCKHIT) {
#ifdef SMB1_MODE
    set_metatile(sVar6.mt_x, sVar6.mt_y, MT_0);
#endif

    if (is_actor_enemy(enemy_id)) {
      if (enemy_id == A_GOOMBA) {
        KillEnemyAboveBlock(objoff);
      }
      SetupFloateyNumber(1, objoff);
    }

#ifdef SMB1_MODE
    if (is_actor_enemy(enemy_id)) {
      // this reimplements a bug in SMB1
      // NES note: The "A" register is overwritten by the call to SetupFloateyNumber.
      // The value happens to be Enemy_Rel_XPos
      ChkToStunEnemies(Enemy_Rel_XPos, objoff);
    } else {
      ChkToStunEnemies(enemy_id, objoff);
    }
#endif

#ifdef SMB2J_MODE
    ChkToStunEnemies(objoff);
#endif

    return;
  }

  if ((u8)(sVar6.r04 - 8) > 4) {
    ChkForRedKoopa(objoff);
    return;
  }
  if ((Enemy_State[objoff] & 0x40) == 0) {
    const u8 tmp1 = Enemy_State[objoff];
    if ((i8)tmp1 < 0) {
      DoEnemySideCheck(objoff);
      return;
    }
    else {
      if (tmp1 == 0) {
        DoEnemySideCheck(objoff);
        return;
      }
    }
    if (tmp1 != 5) {
      if (tmp1 > 2) {
        return;
      }
      if (Enemy_State[objoff] == 2) {
        EnemyIntervalTimer[objoff] = (Enemy_ID[objoff] == A_SPINY) ? 0 : 0x10;
        Enemy_State[objoff] = 3;
        EnemyLanding(objoff);
        return;
      }
    }
    if (enemy_id != A_GOOMBA) {
      if (enemy_id == A_SPINY) {
        Enemy_MovingDir[objoff] = 1;
        Enemy_X_Speed[objoff] = 8;
        if ((FrameCounter & 7) == 0) {
          goto LandEnemyInitState;
        }
      }
      sVar5 = PlayerEnemyDiff(objoff);
      const u8 tmp2 = sVar5.n ? 2 : 1;
      if (tmp2 == Enemy_MovingDir[objoff]) {
        ChkForBump_HammerBroJ(objoff);
      }
    }
  }
LandEnemyInitState:
  EnemyLanding(objoff);
  if ((Enemy_State[objoff] & 0x80) != 0) {
    Enemy_State[objoff] = Enemy_State[objoff] & 0xbf;
    return;
  }
  Enemy_State[objoff] = 0;
}


// SMB:e037
// SM2MAIN:accd
// Signature: [X] -> []
void SetStun2(const u8 param_1) {
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;

  if ((Enemy_ID[param_1] == A_BLOOBER) || (AreaType == AREA_WATER)) {
    Enemy_Y_Speed[param_1] = 0xff;
  } else {
    Enemy_Y_Speed[param_1] = 0xfd;
  }

  const struct_ncr00 sVar2 = PlayerEnemyDiff(param_1);

  if ((Enemy_ID[param_1] != A_BULLET_BILL_CANNON) && (Enemy_ID[param_1] != A_BULLET_BILL)) {
    Enemy_MovingDir[param_1] = sVar2.n ? 2 : 1;
  }
  Enemy_X_Speed[param_1] = sVar2.n ? -16 : 16;
}


// SMB:e0e2
// SM2MAIN:ad78
// Signature: [X] -> []
void ChkForRedKoopa(const u8 objoff) {
  if ((Enemy_ID[objoff] == A_RED_KOOPA) && (Enemy_State[objoff] == 0)) {
    ChkForBump_HammerBroJ(objoff);
    return;
  }

  if ((Enemy_State[objoff] & 0x80) != 0) {
    Enemy_State[objoff] |= 0x40;
  } else {
    expect(Enemy_State[objoff] < 6);

    static const u8 new_state_lookup[] = { 1, 1, 2, 2, 2, 5 };

    Enemy_State[objoff] = new_state_lookup[Enemy_State[objoff]];
  }

  DoEnemySideCheck(objoff);
}


// SMB:e0fe
// SM2MAIN:ad94
// Signature: [X] -> []
void DoEnemySideCheck(const u8 objoff) {
  if (Enemy_Y_Position[objoff] < 0x20) {
    return;
  }

  const u8 dir = Enemy_MovingDir[objoff];

  if (dir != 1 && dir != 2) {
    return;
  }

  // Inlined: BlockBufferChk_Enemy
  const struct blockbuffer_colli_result sVar2 = BlockBufferCollision(1, objoff + 1, dir == 1 ? 23 : 22);

  if (sVar2.a != 0) {
    if (!ChkForNonSolids(sVar2.a)) {
      ChkForBump_HammerBroJ(objoff);
      return;
    }
  }
}


// SMB:e124
// SM2MAIN:adba
// Signature: [X] -> []
void ChkForBump_HammerBroJ(const u8 objoff) {
  if ((objoff != 5) && ((char)Enemy_State[objoff] < 0)) {
    Square1SoundQueue = SOUND_SQ1_BUMP;
  }
  if (Enemy_ID[objoff] == A_HAMMER_BRO) {
    SetHJ(objoff, 0xfa, 0);
  } else {
    // Turn the enemy around

    // Inlined: RXSpd
    Enemy_X_Speed[objoff] *= -1;
    Enemy_MovingDir[objoff] ^= 3;
  }
}


// SMB:e143
// SM2MAIN:add9
// Signature: [X] -> [N, C, r00]
struct_ncr00 PlayerEnemyDiff(const u8 param_1) {
  const u16 player_pos = (Player_PageLoc << 8) | (Player_X_Position);
  const u16 enemy_pos = (Enemy_PageLoc[param_1] << 8) | (Enemy_X_Position[param_1]);

  const i16 diff = enemy_pos - player_pos;

  struct_ncr00 sVar3;
  sVar3.n = diff < 0;
  sVar3.c = player_pos <= enemy_pos;
  sVar3.r00 = diff & 0xff;
  return sVar3;
}


// SMB:e14f
// SM2MAIN:ade5
// Signature: [X] -> []
void EnemyLanding(const u8 objoff) {
  InitVStf(objoff);
  Enemy_Y_Position[objoff] = (Enemy_Y_Position[objoff] & 0xf0) | 8;
}


// SMB:e15b
// SM2MAIN:adf1
// Signature: [X] -> [C]
bool SubtEnemyYPos(const u8 objoff) {
  return (u8)(Enemy_Y_Position[objoff] + 0x3e) > 0x43;
}


// SMB:e163
// SM2MAIN:adf9
// Signature: [X] -> []
void EnemyJump(const u8 objoff) {
  bool bVar2 = SubtEnemyYPos(objoff);
  if ((bVar2) && (2 < (u8)(Enemy_Y_Speed[objoff] + 2))) {
    // Inlined: ChkUnderEnemy
    const struct blockbuffer_colli_result sVar3 = BlockBufferCollision(0, objoff + 1, 21);

    if (sVar3.a != 0) {
      bVar2 = ChkForNonSolids(sVar3.a);
      if (!bVar2) {
        EnemyLanding(objoff);
        Enemy_Y_Speed[objoff] = 0xfd;
      }
    }
  }
  DoEnemySideCheck(objoff);
}


// SMB:e185
// SM2MAIN:ae1b
// Signature: [X] -> []
void HammerBroBGColl(const u8 objoff) {
  // Inlined: ChkUnderEnemy
  const struct blockbuffer_colli_result sVar2 = BlockBufferCollision(0, objoff + 1, 21);

  if (sVar2.a != 0) {
    if (sVar2.a == MT_SPECIAL_BLOCKHIT) {
      KillEnemyAboveBlock(objoff);
      return;
    }
    if (EnemyFrameTimer[objoff] == 0) {
      Enemy_State[objoff] = Enemy_State[objoff] & 0x88;
      EnemyLanding(objoff);
      DoEnemySideCheck(objoff);
      return;
    }
  }
  Enemy_State[objoff] = Enemy_State[objoff] | 1;
}


// SMB:e18e
// SM2MAIN:ae24
// Signature: [X] -> []
void KillEnemyAboveBlock(const u8 objoff) {
  ShellOrBlockDefeat(objoff);
  Enemy_Y_Speed[objoff] = 0xfc;
}


// SMB:e1b5
// SM2MAIN:ae4b
// Signature: [A] -> [Z]
bool ChkForNonSolids(const u8 v) {
  if (SMB1_ONLY) {
    return v == 0x26 || v == 0x5f || v == 0x60 || v == 0xc2 || v == 0xc3;
  } else if (SMB2J_ONLY) {
    return v == 0x23 || v == 0x5e || v == 0x5f || v == 0x60 || v == 0x61 || v == 0xc3 || v == 0xc4;
  }
  return false;
}


// SMB:e1c8
// SM2MAIN:ae66
// Signature: [X] -> []
void FireballBGCollision(const u8 objoff) {
  // objoff is always 0 or 1

  if (Fireball_Y_Position[objoff] >= 24) {
    // Inlined: BlockBufferChk_FBall
    const struct blockbuffer_colli_result sVar2 = BlockBufferCollision(0, objoff + 7, 26);

    // If the fireball's Y position is 232 or greater, it overflows the Block_Buffers array.

    if (sVar2.a != 0) {
      const bool bVar1 = ChkForNonSolids(sVar2.a);
      if (!bVar1) {
        if ((Fireball_Y_Speed[objoff] < 0x80) && (FireballBouncingFlag[objoff] == 0)) {
          Fireball_Y_Speed[objoff] = 0xfd;
          FireballBouncingFlag[objoff] = 1;
          Fireball_Y_Position[objoff] = Fireball_Y_Position[objoff] & 0xf8;
          return;
        }
        Fireball_State[objoff] = 0x80;
        Square1SoundQueue = SOUND_SQ1_BUMP;
        return;
      }
    }
    FireballBouncingFlag[objoff] = 0;
  } else {
    FireballBouncingFlag[objoff] = 0;
  }
}


// SMB:e22d
// SM2MAIN:aecb
// Signature: [X] -> []
void GetFireballBoundBox(const u8 objoff) {
  const u8 bVar1 = objoff + 7;
  BoundingBoxCore(bVar1, 2);
  CheckRightScreenBBox(bVar1);
}


// SMB:e236
// SM2MAIN:aed4
// Signature: [X] -> []
void GetMiscBoundBox(const u8 objoff) {
  const u8 bVar1 = objoff + 9;
  BoundingBoxCore(bVar1, 6);
  CheckRightScreenBBox(bVar1);
}


// SMB:e243
// SM2MAIN:aee1
// Signature: [X] -> []
void GetEnemyBoundBox(const u8 objoff) {
  GetMaskedOffScrBits(objoff, 0x44, 0x48);
}


// SMB:e24c
// SM2MAIN:aeea
// Signature: [X] -> []
void SmallPlatformBoundBox(const u8 objoff) {
  GetMaskedOffScrBits(objoff, 4, 8);
}


// SMB:e252
// SM2MAIN:aef0
// Signature: [X, Y, r00] -> []
void GetMaskedOffScrBits(const u8 objoff, const u8 param_2, const u8 param_3) {
  u8 bVar1 = (Enemy_PageLoc[objoff] - ScreenLeft_PageLoc) - (Enemy_X_Position[objoff] < ScreenLeft_X_Pos);
  if ((bVar1 < 0x80) && ((u8)(bVar1 | (Enemy_X_Position[objoff] - ScreenLeft_X_Pos)) != 0)) {
    bVar1 = param_3 & Enemy_OffscreenBits;
  } else {
    bVar1 = param_2 & Enemy_OffscreenBits;
  }
  EnemyOffscrBitsMasked[objoff] = bVar1;

  if (bVar1 != 0) {
    MoveBoundBoxOffscreen(objoff);
  } else {
    SetupEOffsetFBBox(objoff);
  }
}


// SMB:e273
// SM2MAIN:af11
// Signature: [X] -> []
void LargePlatformBoundBox(const u8 objoff) {
  const u8 bVar1 = GetXOffscreenBits(objoff + 1);
  if (bVar1 >= 0xfe) {
    MoveBoundBoxOffscreen(objoff);
  } else {
    SetupEOffsetFBBox(objoff);
  }
}


// SMB:e27c
// SM2MAIN:af1a
// Signature: [X] -> []
void SetupEOffsetFBBox(const u8 objoff) {
  const u8 bVar1 = objoff + 1;
  BoundingBoxCore(bVar1, 1);
  CheckRightScreenBBox(bVar1);
}


// SMB:e289
// SM2MAIN:af27
// Signature: [X] -> []
void MoveBoundBoxOffscreen(const u8 objoff) {
  // This condition being false would create wraparound behavior with the bounding box arrays,
  // so assume it never happens
  expect(objoff % 64 != 63);

  BBOX_TOPLEFT_X(objoff + 1)  = 0xff;
  BBOX_TOPLEFT_Y(objoff + 1)  = 0xff;
  BBOX_BOTRIGHT_X(objoff + 1) = 0xff;
  BBOX_BOTRIGHT_Y(objoff + 1) = 0xff;
}


// SMB:e29c
// SM2MAIN:af3a
// Signature: [X, Y] -> []
void BoundingBoxCore(const u8 param_1, const u8 param_2) {
  static const u8 lookup[12][4] = {
    { 2, 8, 14, 32 },
    { 3, 20, 13, 32 },
    { 2, 20, 14, 32 },
    { 2, 9, 14, 21 },
    { 0, 0, 24, 6 },
    { 0, 0, 32, 13 },
    { 0, 0, 48, 13 },
    { 0, 0, 8, 8 },
    { 6, 4, 10, 8 },
#ifdef SMB1_MODE
    { 3, 14, 13, 20 },
#endif
#ifdef SMB2J_MODE
    { 3, 14, 13, 22 },
#endif
    { 0, 2, 16, 21 },
    { 4, 4, 12, 28 },
  };

  const u8 ctrl = SprObj_BoundBoxCtrl[param_1];
  const u8 ypos = SprObject_Rel_YPos[param_2];
  const u8 xpos = SprObject_Rel_XPos[param_2];

  expect(ctrl < 12);

  BBOX_TOPLEFT_X(param_1)  = xpos + lookup[ctrl][0];
  BBOX_TOPLEFT_Y(param_1)  = ypos + lookup[ctrl][1];
  BBOX_BOTRIGHT_X(param_1) = xpos + lookup[ctrl][2];
  BBOX_BOTRIGHT_Y(param_1) = ypos + lookup[ctrl][3];

  // NES note: The "Y" register is param_1*4, and may eventually be used in CheckRightScreenBBox.
  // The ports omits it for clarity.
}


// SMB:e2de
// SM2MAIN:af7c
// Signature: [X] -> []
void CheckRightScreenBBox(const u8 param_1) {
  // NES note: The "Y" register is technically an input, but's always X*4 (param_1*4) in practice.
  // This value comes from BoundingBoxCore.

  const u16 screen_left_pos = (ScreenLeft_PageLoc << 8) | ScreenLeft_X_Pos;
  const u16 object_x_pos = (SprObject_PageLoc[param_1] << 8) | SprObject_X_Position[param_1];

  const u8 a = BBOX_BOTRIGHT_X(param_1);
  const u8 b = BBOX_TOPLEFT_X(param_1);

  if (object_x_pos >= (screen_left_pos + 0x80)) {
    if (a < 0x80) {
      if (b < 0x80) {
        BBOX_TOPLEFT_X(param_1) = 0xff;
      }
      BBOX_BOTRIGHT_X(param_1) = 0xff;
    }
  } else {
    // CheckLeftScreenBBox
    if (b >= 0xa0) {
      if (a >= 0x80) {
        BBOX_BOTRIGHT_X(param_1) = 0;
      }
      BBOX_TOPLEFT_X(param_1) = 0;
    }
  }
}


// SMB:e325
// SM2MAIN:afc3
// Signature: [Y] -> [C]
bool PlayerCollisionCore(const u8 param_1) {
  return SprObjectCollisionCore(0, param_1);
}


// SMB:e327
// SM2MAIN:afc5
// Signature: [X, Y] -> [C]
bool SprObjectCollisionCore(const u8 param_1, const u8 param_2) {
  expect(param_1 % 4 == 0);
  expect(param_2 % 4 == 0);

  // Iterate on both the X and Y axes
  for (int i = 0; i < 2; i++) {
    const u8 tl1 = BoundingBoxCoords[param_1+i];
    const u8 tl2 = BoundingBoxCoords[param_2+i];
    const u8 br1 = BoundingBoxCoords[param_1+i + 2];
    const u8 br2 = BoundingBoxCoords[param_2+i + 2];

    // This is _almost_ symmetrical, but not quite!

    if (tl2 < tl1 && br2 < tl1 && (tl1 <= br1 || (tl2 > br1 && tl2 <= br2))) {
      return false;
    }

    if (tl2 > tl1 && br1 < tl2 && (tl2 <= br2 || (tl1 > br2))) {
      return false;
    }
  }

  return true;
}

struct blockbuffer_colli_result BlockBufferCollision_coords(const u8 use_x, const u8 param_2, const u8 param_3) {
  // head feet1 feet2 side
  static const u8 xadder_lookup[28] = {
    0x08, 0x03, 0x0c, 0x02, 0x02, 0x0d, 0x0d,
    0x08, 0x03, 0x0c, 0x02, 0x02, 0x0d, 0x0d,
    0x08, 0x03, 0x0c, 0x02, 0x02, 0x0d, 0x0d,
    0x08, 0x00, 0x10, 0x04, 0x14, 0x04, 0x04,
  };

  static const u8 yadder_lookup[28] = {
    0x04, 0x20, 0x20, 0x08, 0x18, 0x08, 0x18,
    0x02, 0x20, 0x20, 0x08, 0x18, 0x08, 0x18,
    0x12, 0x20, 0x20, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x14, 0x14, 0x06, 0x06, 0x08, 0x10,
  };

  const u16 xpos = LOAD_16(SprObject_PageLoc[param_2], SprObject_X_Position[param_2]);
  const u8 xadder = xadder_lookup[param_3];

  const u8 ypos = SprObject_Y_Position[param_2];
  const u8 yadder = yadder_lookup[param_3];

  const u16 mt_x = (xpos + xadder) / 16;
  const u16 mt_y = (ypos + yadder) / 16 - MT_Y_TOP_MARGIN;

  struct blockbuffer_colli_result res;

  // "A" is unused here
  res.a = 0;
  res.r04 = (use_x ? xpos : ypos) & 0xf;
  res.mt_x = mt_x;
  res.mt_y = mt_y;

  return res;
}

// SMB:e3f0
// SM2MAIN:b08e
struct blockbuffer_colli_result BlockBufferCollision(const u8 use_x, const u8 param_2, const u8 param_3) {
  // Note: Old signature was [A, X, Y] -> [A, Z, r02, r04, r06, r07]
  // Reworked to use metatile coordinates instead of pointer
  // Original would set the Z flag to check if the metatile is zero.
  // This check, if needed, is moved to the caller.

  struct blockbuffer_colli_result res = BlockBufferCollision_coords(use_x, param_2, param_3);

  res.a = get_metatile(res.mt_x, res.mt_y);
  return res;
}


// Draws a row of two sprites. Implements what happens in DrawSpriteObject.
//
// The original games would call DrawSpriteObject/DrawOneSpriteRow/DrawEnemyObjRow,
// which also took the responsibility of controlling the caller's loops by feeding incremented
// paramers to the caller.
// This port eliminates the feeback in favor of providing a `row` argument, because it's easier to understand at a glance.
static void draw_sprite_row(const u8 row,
                            const u8 sproff,
                            const u8 left_tileidx,
                            const u8 right_tileidx,
                            const u8 xpos,
                            const u8 ypos,
                            const u8 attrs,
                            const bool flip_horz)
{
  const u8 effective_attrs = attrs | (flip_horz ? 0x40 : 0);

  const u8 off = SPRITE_calculate_wrap(sproff, 2*row);

  if (flip_horz) {
    SPRITE_TILE(off, 0) = right_tileidx;
    SPRITE_TILE(off, 1) = left_tileidx;
  } else {
    SPRITE_TILE(off, 0) = left_tileidx;
    SPRITE_TILE(off, 1) = right_tileidx;
  }

  SPRITE_ATTR(off, 0) = effective_attrs;
  SPRITE_ATTR(off, 1) = effective_attrs;

  SPRITE_Y(off, 0) = ypos + row*8;
  SPRITE_Y(off, 1) = ypos + row*8;

  SPRITE_X(off, 0) = xpos;
  SPRITE_X(off, 1) = xpos + 8;
}


// SMB:e435
// SM2MAIN:b0d9
// Signature: [Y] -> []
void DrawVine(const u8 vineoff) {
  // vineoff is either 0 or 1

  const u8 sproff = Enemy_SprDataOffset[VineObjOffset[vineoff]];

  const u8 xpos = Enemy_Rel_XPos;
  const u8 ypos = Enemy_Rel_YPos + (vineoff == 0 ? 0 : 0x30);

  for (int i = 0; i < 6; i++) {
    const bool even = i % 2 == 0;

    // Inlined: SixSpriteStacker (for the sprite's Y component)
    SPRITE_Y_strict(sproff, i)        = ypos + i*8;
    SPRITE_X(sproff, i)               = xpos + (even ? 0 : 6);
    SPRITE_ATTR(sproff, i)            = 0x21 | (even ? 0 : 0x40);
    SPRITE_TILE_semistrict(sproff, i) = 0xe1;
  }

  if (vineoff == 0) {
    SPRITE_TILE(sproff, 0) = 0xe0;
  }

  for (int i = 0; i < 6; i++) {
    const u8 diff = VineStart_Y_Position - SPRITE_Y(sproff, i);
    if (diff >= 100) {
      SPRITE_Y_strict(sproff, i) = SPRITE_Y_OFFSCREEN;
    }
  }
}


// SMB:e4dc
// SM2MAIN:b180
// Signature: [X] -> []
void DrawHammer(const u8 objoff) {
  static const u8 xpos1_lookup[4] = { 4, 0, 4, 0 };
  static const u8 ypos1_lookup[4] = { 0, 4, 0, 4 };
  static const u8 tilenum1_lookup[4] = { 0x80, 0x82, 0x81, 0x83 };

  static const u8 xpos2_lookup[4] = { 0, 8, 0, 8 };
  static const u8 ypos2_lookup[4] = { 8, 0, 8, 0 };
  static const u8 tilenum2_lookup[4] = { 0x81, 0x83, 0x80, 0x82 };

  static const u8 attr_lookup[4] = {
    3,
    3,
    SPRATTR_FLIPVERT | SPRATTR_FLIPHORZ | 3,
    SPRATTR_FLIPVERT | SPRATTR_FLIPHORZ | 3,
  };

  const u8 sproff = Misc_SprDataOffset[objoff];

  u8 i;
  if ((TimerControl == 0) && ((Misc_State[objoff] & 0x7f) == 1)) {
    i = (FrameCounter >> 2) & 3;
  } else {
    i = 0;
  }

  SPRITE_Y(sproff, 0) = Misc_Rel_YPos + ypos1_lookup[i];
  SPRITE_Y(sproff, 1) = Misc_Rel_YPos + ypos1_lookup[i] + ypos2_lookup[i];

  SPRITE_X(sproff, 0) = Misc_Rel_XPos + xpos1_lookup[i];
  SPRITE_X(sproff, 1) = Misc_Rel_XPos + xpos1_lookup[i] + xpos2_lookup[i];

  SPRITE_TILE(sproff, 0) = tilenum1_lookup[i];
  SPRITE_TILE(sproff, 1) = tilenum2_lookup[i];

  SPRITE_ATTR(sproff, 0) = attr_lookup[i];
  SPRITE_ATTR(sproff, 1) = attr_lookup[i];

  if ((Misc_OffscreenBits & 0xfc) != 0) {
    Misc_State[objoff] = 0;

    // Inlined: DumpTwoSpr
    SPRITE_Y(sproff, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(sproff, 1) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:e54b
// SM2MAIN:b1f1
// Signature: [X] -> []
void FlagpoleGfxHandler(const u8 objoff) {
  const u8 off = Enemy_SprDataOffset[objoff];

  const u8 xpos = Enemy_Rel_XPos;
  const u8 ypos = Enemy_Y_Position[objoff];
  // NES note: There's a carry bug after adding 8 and 12 to Enemy_Rel_XPos
  const bool carry_bug = xpos >= 236 && xpos < 248;

  SPRITE_X(off, 0) = xpos;
  SPRITE_X(off, 1) = xpos + 8;
  SPRITE_X(off, 2) = xpos + 8;

  // Inlined: DumpTwoSpr
  SPRITE_Y(off, 0) = ypos;
  SPRITE_Y(off, 1) = ypos;
  SPRITE_Y(off, 2) = ypos + 8 + carry_bug;

  SPRITE_ATTR(off, 0) = 1;
  SPRITE_ATTR(off, 1) = 1;
  SPRITE_ATTR(off, 2) = 1;

  SPRITE_TILE(off, 0) = 0x7e;
  SPRITE_TILE(off, 1) = 0x7f;
  SPRITE_TILE(off, 2) = 0x7e;

  static const u8 score_tiles[][2] = {
    { 0xf9, 0x50 },
    { 0xf7, 0x50 },
    { 0xfa, 0xfb },
    { 0xf8, 0xfb },
    { 0xf6, 0xfb },
    { 0xfd, 0xfe },    // 1-UP (SMB2J only)
  };

  if (FlagpoleCollisionYPos != 0) {
    // Inlined: DrawOneSpriteRow

#ifdef SMB1_MODE
    expect(FlagpoleScore < 5);
#endif
#ifdef SMB2J_MODE
    expect(FlagpoleScore < 6);
#endif

    const u8 left_tileidx  = score_tiles[FlagpoleScore][0];
    const u8 right_tileidx = score_tiles[FlagpoleScore][1];
    const u8 xposN = xpos + 20;
    const u8 yposN = FlagpoleFNum_Y_Pos;
    const u8 attrs = 1;
    const bool flip_horz = false;
    draw_sprite_row(0, off + 3*4, left_tileidx, right_tileidx, xposN, yposN, attrs, flip_horz);
  }

  if ((Enemy_OffscreenBits & 0xe) != 0) {
    // Inlined: MoveSixSpritesOffscreen
    const u8 sprite_offset = Enemy_SprDataOffset[objoff];
    for (int i = 0; i < 6; i++) {
      SPRITE_Y(sprite_offset, i) = SPRITE_Y_OFFSCREEN;
    }
  }
}


// SMB:e5c8
// SM2MAIN:b26e
// Signature: [X] -> []
void DrawLargePlatform(const u8 objoff) {
  const u8 sproff1 = Enemy_SprDataOffset[objoff];

  // Inlined: SixSpriteStacker
  for (int i = 0; i < 6; i++) {
    SPRITE_X_strict(sproff1, i) = Enemy_Rel_XPos + i*8;
  }

  const u8 ypos = Enemy_Y_Position[objoff];

  // Inlined: DumpFourSpr
  SPRITE_Y(sproff1, 0) = ypos;
  SPRITE_Y(sproff1, 1) = ypos;
  SPRITE_Y(sproff1, 2) = ypos;
  SPRITE_Y(sproff1, 3) = ypos;

  u8 bVar11 = ypos;
  if ((AreaType == AREA_CASTLE) || (SecondaryHardMode != 0)) {
    bVar11 = SPRITE_Y_OFFSCREEN;
  }

  const u8 bVar3 = Enemy_SprDataOffset[objoff];

  // NES note: If the offset is 254 or 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpSixSpr.
  // This port assumes it can't happen.
  expect(bVar3 <= 253);

  SPRITE_Y(bVar3, 4) = bVar11;
  SPRITE_Y(bVar3, 5) = bVar11;

  const u8 tile = (CloudTypeOverride != 0) ? 0x75 : 0x5b;

  // Inlined: DumpSixSpr
  for (int i = 0; i < 6; i++) {
    SPRITE_TILE(bVar3, i) = tile;
    SPRITE_ATTR(bVar3, i) = 2;
  }

  const u8 xoffscrbits = GetXOffscreenBits(objoff+1);
  const u8 bVar1 = Enemy_SprDataOffset[objoff];

  // NES version is unrolled. We rolled up the loop in this port
  for (int i = 0; i < 6; i++) {
    // 0x80, 0x40, 0x20, 0x10, 0x08, 0x04
    const u8 mask = 1 << (7-i);
    if (xoffscrbits & mask) {
      SPRITE_Y(bVar1, i) = SPRITE_Y_OFFSCREEN;
    }
  }

  if (Enemy_OffscreenBits & 0x80) {
    // Inlined: MoveSixSpritesOffscreen
    for (int i = 0; i < 6; i++) {
      SPRITE_Y(bVar1, i) = SPRITE_Y_OFFSCREEN;
    }
  }
}


// SMB:e686
// SM2MAIN:b32c
// Signature: [X] -> []
void JCoinGfxHandler(const u8 objoff) {
  static const u8 jumping_coin_tiles[4] = { 0x60, 0x61, 0x62, 0x63 };

  u8 bVar2 = Misc_SprDataOffset[objoff];
  if (Misc_State[objoff] < 2) {
    u8 bVar1 = Misc_Y_Position[objoff];
    SPRITE_Y(bVar2, 0) = bVar1;
    SPRITE_Y(bVar2, 1) = bVar1 + 8;
    bVar1 = Misc_Rel_XPos;
    SPRITE_X(bVar2, 0) = Misc_Rel_XPos;
    SPRITE_X(bVar2, 1) = bVar1;

    // Inlined: DumpTwoSpr
    // NES note: If the offset is 255, this wraparounds the sprite page
    // because it's incremented before passing to DumpTwoSpr.
    // This port assumes it can't happen.
    expect(bVar2 != 255);
    const u8 tile = jumping_coin_tiles[(FrameCounter >> 1) & 3];
    SPRITE_TILE(bVar2, 0) = tile;
    SPRITE_TILE(bVar2, 1) = tile;

    SPRITE_ATTR(bVar2, 0) = 2;
    SPRITE_ATTR(bVar2, 1) = 0x82;
  } else {
    if ((FrameCounter & 1) == 0) {
      Misc_Y_Position[objoff] = Misc_Y_Position[objoff] - 1;
    }

    // Inlined: DumpTwoSpr
    SPRITE_Y(bVar2, 0) = Misc_Y_Position[objoff];
    SPRITE_Y(bVar2, 1) = Misc_Y_Position[objoff];

    const u8 bVar1 = Misc_Rel_XPos;
    SPRITE_X(bVar2, 0) = Misc_Rel_XPos;
    SPRITE_X(bVar2, 1) = bVar1 + 8;
    SPRITE_ATTR(bVar2, 0) = 2;
    SPRITE_ATTR(bVar2, 1) = 2;
    SPRITE_TILE(bVar2, 0) = 0xf7;
    SPRITE_TILE(bVar2, 1) = 0xfb;
  }
}


// SMB:e6d2
// SM2MAIN:b37d
void DrawPowerUp(const u8 objoff) {
  // Original signature: [] -> []
  // Note: This port accepts an objoff argument. The original hard-coded "5".

  static const u8 tiles[_POWERUP_NUM][4] = {
#ifdef SMB1_MODE
    { 0x76, 0x77, 0x78, 0x79 }, // regular mushroom
    { 0xd6, 0xd6, 0xd9, 0xd9 }, // fire flower
    { 0x8d, 0x8d, 0xe4, 0xe4 }, // star
    { 0x76, 0x77, 0x78, 0x79 }, // 1-up mushroom
#endif

#ifdef SMB2J_MODE
    { 0xd8, 0xda, 0xdb, 0xff }, // regular mushroom
    { 0xd6, 0xd6, 0xd9, 0xd9 }, // fire flower
    { 0x8d, 0x8d, 0xe4, 0xe4 }, // star
    { 0xd8, 0xda, 0xdb, 0xff }, // 1-up mushroom
    { 0xd8, 0xda, 0xdb, 0xff }, // poison mushroom
#endif
  };

  static const u8 palettes[] = { 2, 1, 2, 1, 3 };

  const u8 sproff = Enemy_SprDataOffset[objoff];

  {
    // Inlined: DrawOneSpriteRow

    const u8 left_tileidx_1  = tiles[PowerUpType][0];
    const u8 right_tileidx_1 = tiles[PowerUpType][1];
    const u8 left_tileidx_2  = tiles[PowerUpType][2];
    const u8 right_tileidx_2 = tiles[PowerUpType][3];

    const u8 xpos = Enemy_Rel_XPos;
    const u8 ypos = Enemy_Rel_YPos + 8;
    const u8 attrs = palettes[PowerUpType] | Enemy_SprAttrib[objoff];

    const bool flip_horz = false;

    draw_sprite_row(0, sproff, left_tileidx_1, right_tileidx_1, xpos, ypos, attrs, flip_horz);
    draw_sprite_row(1, sproff, left_tileidx_2, right_tileidx_2, xpos, ypos, attrs, flip_horz);
  }

  expect(is_powerup_valid(PowerUpType));

  if (PowerUpType == POWERUP_FIREFLOWER) {
    // Flicker the powerup by cycling its palette

    const u8 attrs = ((FrameCounter >> 1) & 3) | Enemy_SprAttrib[objoff];

    // Only flicker the top half of the fire flower
    SPRITE_ATTR(sproff, 0) = attrs;
    SPRITE_ATTR(sproff, 1) = attrs;

    // Flip the right half horizontally
    SPRITE_ATTR(sproff, 1) |= SPRATTR_FLIPHORZ;
    SPRITE_ATTR(sproff, 3) |= SPRATTR_FLIPHORZ;
  }

  if (PowerUpType == POWERUP_STAR) {
    // Flicker the powerup by cycling its palette

    const u8 attrs = ((FrameCounter >> 1) & 3) | Enemy_SprAttrib[objoff];

    SPRITE_ATTR(sproff, 0) = attrs;
    SPRITE_ATTR(sproff, 1) = attrs;
    SPRITE_ATTR(sproff, 2) = attrs;
    SPRITE_ATTR(sproff, 3) = attrs;

    // Flip the right half horizontally
    SPRITE_ATTR(sproff, 1) |= SPRATTR_FLIPHORZ;
    SPRITE_ATTR(sproff, 3) |= SPRATTR_FLIPHORZ;
  }

  SprObjectOffscrChk(objoff);
}


static inline void draw_enemy_object_2x3(const u8 tableoff, const u8 sproff,
                                         const u8 xpos, const u8 ypos,
                                         const u8 palette,
                                         const bool draw_behind,
                                         bool flip_horz,
                                         const bool flip_vert,
                                         const bool tall,
                                         const bool mirror_horz)
{
  // Inlined: DrawEnemyObjRow

  const u8 attrs = (draw_behind ? SPRATTR_DRAWBEHIND : 0) | palette;

  u8 tableoff_tmp = tableoff;

  const u8 left_tileidx_1  = EnemyGraphicsTable[tableoff_tmp];
  const u8 right_tileidx_1 = EnemyGraphicsTable[tableoff_tmp + 1];
  tableoff_tmp += 2;
  const u8 left_tileidx_2  = EnemyGraphicsTable[tableoff_tmp];
  const u8 right_tileidx_2 = EnemyGraphicsTable[tableoff_tmp + 1];
  tableoff_tmp += 2;
  const u8 left_tileidx_3  = EnemyGraphicsTable[tableoff_tmp];
  const u8 right_tileidx_3 = EnemyGraphicsTable[tableoff_tmp + 1];

  draw_sprite_row(0, sproff, left_tileidx_1, right_tileidx_1, xpos, ypos, attrs, flip_horz);
  draw_sprite_row(1, sproff, left_tileidx_2, right_tileidx_2, xpos, ypos, attrs, flip_horz);
  draw_sprite_row(2, sproff, left_tileidx_3, right_tileidx_3, xpos, ypos, attrs, flip_horz);

  if (flip_vert) {
    // NES note: If the offset is 254 or 255, this wraparounds the sprite page
    // because it's incremented before passing to DumpSixSpr.
    // This port assumes it can't happen.
    expect(sproff <= 253);

    // Flip all tiles vertically
    // Inlined: DumpSixSpr
    const u8 tmpattr = SPRITE_ATTR(sproff, 0) | SPRATTR_FLIPVERT;
    for (int i =  0; i < 6; i++) {
      SPRITE_ATTR(sproff, i) = tmpattr;
    }

    if (tall) {
      SWAP(SPRITE_TILE(sproff, 0), SPRITE_TILE(sproff, 4));
      SWAP(SPRITE_TILE(sproff, 1), SPRITE_TILE(sproff, 5));
    } else {
      const u8 bVar2 = SPRITE_calculate_wrap(sproff, 2);
      SWAP(SPRITE_TILE(bVar2, 0), SPRITE_TILE(sproff, 4));
      SWAP(SPRITE_TILE(bVar2, 1), SPRITE_TILE(sproff, 5));
    }
  }

  if (mirror_horz) {
    // Do not flip the left column tiles horizontally
    const u8 attr = SPRITE_ATTR(sproff, 0) & ~SPRATTR_FLIPHORZ;

    SPRITE_ATTR(sproff, 0) = attr;
    SPRITE_ATTR(sproff, 2) = attr;
    SPRITE_ATTR(sproff, 4) = attr;

    SPRITE_ATTR(sproff, 1) = attr | SPRATTR_FLIPHORZ;
    SPRITE_ATTR(sproff, 3) = attr | SPRATTR_FLIPHORZ;
    SPRITE_ATTR(sproff, 5) = attr | SPRATTR_FLIPHORZ;
  }
}


// SMB:e87d
// SM2MAIN:b52c
// Signature: [X] -> []
void EnemyGfxHandler(const u8 objoff) {
  // Renders the actor to tiles.
  // This is heavily refactored and doesn't closely resemble the original machine code.
  //
  // The table offsets are inlined because they're highly coupled to the code.
  // Many assumptions about actor state are made to make the code more approachable.
  //
  // Everything is handled on a per-actor basis, instead of the hodge-podge of
  // spaghetti and tacked-on exceptions that the original did.
  //
  // The original would compare table indices, which are derived from Enemy_ID.
  // This implementation does a more straight-forward comparison to Enemy_ID, to keep it understandable.
  //   enemy_id -> table_idx
  //   53 (A_RETAINER)           -> 21
  //   51 (A_BULLET_BILL_CANNON) -> 8
  //   50 (A_JUMPSPRING)         -> 24, 25, 26
  //   *                         -> * (otherwise, keep the same)

  // Note that all Bowser paths have been extracted out to EnemyGfxHandler_bowser.
  expect(BowserGfxFlag == 0);

  // right before any array reads could access writes we optimized away
  expect(objoff < 0xeb - 0xcf);

  const u8 enemy_id = Enemy_ID[objoff];

  expect(is_actor_enemy(enemy_id) || enemy_id == A_JUMPSPRING || enemy_id == A_BULLET_BILL_CANNON || enemy_id == A_RETAINER);

  // Note: Enemy_SprAttrib[objoff] is always 0 for EnemyGfxHandler.
  // RunNormalEnemies sets this to 0 right before calling EnemyGfxHandler. The other non-enemy actor types never assign it to non-zero.
  // The intent of this variable is to draw sprites behind nametable tiles (with an attribute value of 0x20).
  // The use of this array is mostly residual, and is only meaningfully used in DrawPowerUp.
  expect_weak(Enemy_SprAttrib[objoff] == 0);

  if (enemy_id == A_PIRANHA_PLANT) {
    if ((PiranhaPlant_Y_Speed[objoff] < 0x80) && (EnemyFrameTimer[objoff] != 0)) {
      return;
    }
  }

  // Workaround for CheckpointEnemyID() -> Setup_Vine() bug
  rEF = enemy_id;

  const u8 xpos = Enemy_Rel_XPos;
  u8 ypos = Enemy_Y_Position[objoff];

  const u8 sproff = Enemy_SprDataOffset[objoff];
  const u8 interval_timer = EnemyIntervalTimer[objoff];
  const u8 enemy_state = Enemy_State[objoff];
  const u8 st = enemy_state & 0x1f;

  bool flip_horz = (Enemy_MovingDir[objoff] & 2) != 0;

  bool draw_behind = false;

  bool flip_vert = (enemy_state & 0x20) != 0;

  u8 tableoff;
  u8 next_tableoff;

  bool mirror_horz = false;
  u8 palette = 1;
  bool tall = false;

  const bool cond1 = (enemy_state & 0xa0) == 0 && TimerControl == 0;

  switch (enemy_id) {
  case A_LAKITU:
    palette = 1;
    tall = true;

    if (flip_vert || FrenzyEnemyTimer >= 16) {
      tableoff = TOFF_LAKITU_1;
    } else {
      tableoff = TOFF_LAKITU_2;
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

    if (!flip_vert) {
      SPRITE_ATTR(sproff, 4) &= ~(SPRATTR_FLIPHORZ);
      SPRITE_ATTR(sproff, 5) |= SPRATTR_FLIPHORZ;
      if (FrenzyEnemyTimer < 16) {
        const u8 bVar9 = SPRITE_ATTR(sproff, 5);
        SPRITE_ATTR(sproff, 2) = bVar9 & ~(SPRATTR_FLIPHORZ);
        SPRITE_ATTR(sproff, 3) = bVar9;
      }
    } else {
      SPRITE_ATTR(sproff, 0) &= ~(SPRATTR_FLIPHORZ);
      SPRITE_ATTR(sproff, 1) |= SPRATTR_FLIPHORZ;
    }
    break;

  case A_SPINY:
    palette = 2;

    tableoff = TOFF_SPINY_1;
    next_tableoff = TOFF_SPINY_2;

    if (st == 5) {
      tableoff = TOFF_SPINY_EGG_1;
      next_tableoff = TOFF_SPINY_EGG_2;
      flip_horz = true;
      mirror_horz = true;
    }

    expect_weak(interval_timer == 0);

    if (cond1) {
      if ((FrameCounter & 0x8) == 0) {
        tableoff = next_tableoff;
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

    if (st == 5) {
      // Flip right column vertically (effectively rotated 180 degrees)
      SPRITE_ATTR(sproff, 1) |= 0x80;
      SPRITE_ATTR(sproff, 3) |= 0x80;
      SPRITE_ATTR(sproff, 5) |= 0x80;
    }
    break;

  case A_GREEN_KOOPA:
  case A_RED_KOOPA_GREENLIKE:
  case A_RED_KOOPA:
    palette = 1;

    if (enemy_id == A_RED_KOOPA || enemy_id == A_RED_KOOPA_GREENLIKE) {
      palette = 2;
    }

    tableoff = TOFF_KOOPA_1;
    next_tableoff = TOFF_KOOPA_2;

    if (st > 1) {
      tableoff = TOFF_KOOPA_SHELL_UPSIDEDOWN_1;
      next_tableoff = TOFF_KOOPA_SHELL_UPSIDEDOWN_2;
    }

    if (st == 4) {
      tableoff = TOFF_KOOPA_SHELL_1;
      next_tableoff = TOFF_KOOPA_SHELL_2;
      ypos += 2;
    }

    flip_vert = false;

    if (st > 1) { mirror_horz = true; }

    if (interval_timer < 5) {
      if (cond1) {
        if ((FrameCounter & 0x8) == 0) {
          tableoff = next_tableoff;
        }
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

    if (st == 4) {
      // Flip bottom two rows vertically
      SPRITE_ATTR(sproff, 2) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 4) |= SPRATTR_FLIPVERT;

      SPRITE_ATTR(sproff, 3) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 5) |= SPRATTR_FLIPVERT;
    }

    break;

#ifdef SMB1_MODE
  case A_PIRANHA_PLANT_SMB2J:
    // A glitched version of a koopa

    tableoff = TOFF_KOOPA_1;
    next_tableoff = TOFF_KOOPA_2;
    palette = 1;

    if (st == 4) {
      tableoff = TOFF_KOOPA_SHELL_1;
      next_tableoff = TOFF_KOOPA_SHELL_2;
      ypos += 2;
    }

    if (!flip_vert && st > 1) { mirror_horz = true; }

    if (interval_timer < 5) {
      if (cond1) {
        if ((FrameCounter & 0x8) == 0) {
          tableoff = next_tableoff;
        }
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

    if (!flip_vert && st == 4) {
      // Flip bottom two rows vertically
      SPRITE_ATTR(sproff, 2) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 4) |= SPRATTR_FLIPVERT;

      SPRITE_ATTR(sproff, 3) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 5) |= SPRATTR_FLIPVERT;
    }

    break;
#endif

  case A_BUZZY_BEETLE:
    palette = 3;

    tableoff = TOFF_BUZZY_BEETLE_1;
    next_tableoff = TOFF_BUZZY_BEETLE_2;

    if (st > 1) {
      tableoff = TOFF_BUZZY_BEETLE_SHELL_1;
      next_tableoff = TOFF_BUZZY_BEETLE_SHELL_2;
      ypos += 1;
    }

    if (st == 4) {
      tableoff = TOFF_BUZZY_BEETLE_SHELL_UPSIDEDOWN_1;
      next_tableoff = TOFF_BUZZY_BEETLE_SHELL_UPSIDEDOWN_2;
      ypos += 1;
    }

    flip_vert = false;

    if (st > 1) { mirror_horz = true; }

    if (interval_timer < 5) {
      if (cond1) {
        if ((FrameCounter & 0x8) == 0) {
          tableoff = next_tableoff;
        }
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

    if (st == 4) {
      // Flip bottom two rows vertically
      SPRITE_ATTR(sproff, 2) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 4) |= SPRATTR_FLIPVERT;

      SPRITE_ATTR(sproff, 3) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 5) |= SPRATTR_FLIPVERT;
    }
    break;

  case A_GOOMBA:
    palette = 3;

    tableoff = TOFF_GOOMBA;

    if (flip_vert) {
      ypos += 2;
    } else {
      if (TimerControl == 0 && (FrameCounter & 8) == 0) {
        // Make the goomba waddle around
        flip_horz = !flip_horz;
      }

      if (enemy_state > 1) {
        tableoff = TOFF_STOMPED_GOOMBA;
        ypos += 1;
        mirror_horz = true;
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

    if (enemy_state > 1) {
      // Ensure bottom two rows are flipped vertically
      SPRITE_ATTR(sproff, 2) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 4) |= SPRATTR_FLIPVERT;

      SPRITE_ATTR(sproff, 3) |= SPRATTR_FLIPVERT;
      SPRITE_ATTR(sproff, 5) |= SPRATTR_FLIPVERT;
    }
    break;

  case A_HAMMER_BRO:
    palette = 1;
    tall = true;

    tableoff = TOFF_HAMMER_BRO_1;
    next_tableoff = TOFF_HAMMER_BRO_2;

    expect_weak(st != 4);

    if ((enemy_state & 8) != 0) {
        tableoff = TOFF_HAMMER_BRO_3;
        next_tableoff = TOFF_HAMMER_BRO_4;
    }

    if (enemy_state == 0 || (enemy_state & 8) != 0) {
      if (cond1) {
        if ((FrameCounter & 0x8) == 0) {
          tableoff = next_tableoff;
        }
      }
    }


    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_CHEEPCHEEP_GRAY:
  case A_CHEEPCHEEP_RED:
  case A_FLYING_CHEEPCHEEP:
    palette = 2;

    if (enemy_id == A_CHEEPCHEEP_GRAY) {
      palette = 1;
    }

    tableoff = TOFF_CHEEPCHEEP_1;
    next_tableoff = TOFF_CHEEPCHEEP_2;

    expect_weak(st <= 2);
    expect_weak(st != 2 || flip_vert);  // if st == 2 then flip_vert

    if (cond1) {
      if ((FrameCounter & 0x8) == 0) {
        tableoff = next_tableoff;
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_BLOOBER:
    palette = 3;

    tableoff = TOFF_BLOOBER_1;
    next_tableoff = TOFF_BLOOBER_2;

    expect_weak(st <= 2);

    if (interval_timer != 1 && interval_timer < 5) {
      ypos += 3;
      if (cond1) {
        tableoff = next_tableoff;
      }
    }

    mirror_horz = true;


    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_BULLET_BILL_CANNON:
    // Workaround for CheckpointEnemyID() -> Setup_Vine() bug
    rEF = 0x8;

    palette = 3;

    tableoff = TOFF_BULLET_BILL;

    ypos -= 1;
    draw_behind = EnemyFrameTimer[objoff] != 0;

    flip_vert = false;

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_BULLET_BILL:
    palette = 3;

    tableoff = TOFF_BULLET_BILL;

    draw_behind = false;
    expect_weak(st != 4);

    flip_vert = false;

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_PODOBOO:
    palette = 2;

    tableoff = TOFF_PODOBOO;

    expect_weak(st != 4);

    mirror_horz = true;

    if (Enemy_Y_Speed[objoff] < 0x80) {
      flip_vert = true;
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_JUMPSPRING:
    static const u8 jumpspring_offsets[5] = {
      TOFF_JUMPSPRING_1,
      TOFF_JUMPSPRING_2,
      TOFF_JUMPSPRING_3,
      TOFF_JUMPSPRING_2,
      TOFF_JUMPSPRING_1,
    };
    static const u8 jumpspring_indices[5] = {
      0x18, 0x19, 0x1a, 0x19, 0x18
    };

    expect(JumpspringAnimCtrl < 5);
    tableoff = jumpspring_offsets[JumpspringAnimCtrl];

    palette = 2;
    tall = true;

#ifdef SMB2J_MODE
    if (((WorldNumber == 1) || (WorldNumber == 2)) || (WorldNumber == 6)) {
      palette = 1;
    }
#endif

    // Workaround for CheckpointEnemyID() -> Setup_Vine() bug
    rEF = jumpspring_indices[JumpspringAnimCtrl];

    mirror_horz = true;

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

    SPRITE_ATTR(sproff, 2) |= SPRATTR_FLIPVERT;
    SPRITE_ATTR(sproff, 4) |= SPRATTR_FLIPVERT;
    SPRITE_ATTR(sproff, 3) |= SPRATTR_FLIPVERT | SPRATTR_FLIPHORZ;
    SPRITE_ATTR(sproff, 5) |= SPRATTR_FLIPVERT | SPRATTR_FLIPHORZ;
    break;

  case A_RETAINER:
    // Workaround for CheckpointEnemyID() -> Setup_Vine() bug
    rEF = 0x15;

    flip_horz = false;

    palette = 2;
    tall = true;

    expect_weak(interval_timer == 0);
    expect_weak(!flip_vert);

    if (WorldNumber < 7) {
      tableoff = TOFF_MUSHROOM_RETAINER;
      mirror_horz = true;
    } else {
      tableoff = TOFF_PRINCESS_OR_DOOR;

      // In SMB2J, it's a door, which has mirrored tiles
#ifdef SMB2J_MODE
      mirror_horz = true;
#endif
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

#ifdef SMB1_MODE
  if (WorldNumber == 7) {
    // Bottom right: flip horizontally
    SPRITE_ATTR(sproff, 5) ^= 0x40;
  }
#endif
    break;

#ifdef SMB2J_MODE
  case A_PIRANHA_PLANT_SMB2J:

    flip_vert = true;
    tall = true;
#endif
  case A_PIRANHA_PLANT:
    tableoff = TOFF_PIRANHA_PLANT_1;
    next_tableoff = TOFF_PIRANHA_PLANT_2;
    palette = 1;
    draw_behind = true;

#ifdef SMB2J_MODE
    if (PiranhaPlantHardMode) {
      palette = 2;
    }
#endif

    expect_weak(st != 4);

    mirror_horz = true;

    expect_weak(interval_timer == 0);

    if (cond1) {
      if ((FrameCounter & 0x8) == 0) {
        tableoff = next_tableoff;
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_GREEN_PARATROOPA:
  case A_RED_PARATROOPA:
  case A_GREEN_PARATROOPA_HORIZONTAL:
  case A_GREEN_PARATROOPA_INPLACE:
    tableoff = TOFF_PARATROOPA_1;
    next_tableoff = TOFF_PARATROOPA_2;
    palette = 1;

    if (enemy_id == A_RED_PARATROOPA) {
      palette = 2;
    }

    expect_weak(st != 4);

    if (st == 4) {
      tableoff = TOFF_KOOPA_SHELL_1;
      next_tableoff = TOFF_KOOPA_SHELL_2;
      ypos += 2;
    }

    if (st > 1) { mirror_horz = true; }

    expect_weak(!flip_vert);
    expect_weak(interval_timer == 0);

    if (cond1) {
      if ((FrameCounter & 0x8) == 0) {
        tableoff = next_tableoff;
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  case A_UNK_0x13:
    // This is a glitch. table offset and attributes are literally 0xff.

    tableoff = 0xff;
    next_tableoff = 0x05;

    draw_behind = true;
    palette = 0xff;

    if (st == 4) {
      tableoff = TOFF_KOOPA_SHELL_1;
      next_tableoff = TOFF_KOOPA_SHELL_2;
      ypos += 2;
    }

    if (!flip_vert && st > 1) { mirror_horz = true; }

    if (interval_timer < 5) {
      if (cond1) {
        if ((FrameCounter & 0x8) == 0) {
          tableoff = next_tableoff;
        }
      }
    }

    draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);
    break;

  default:
    // Any remaining actors should be unreachable
    expect(false);

    break;
  }

  SprObjectOffscrChk(objoff);
}

static void EnemyGfxHandler_bowser(const u8 objoff, const u8 bowser_gfx_flag) {
  // right before any array reads could access writes we optimized away
  expect(objoff < 0xeb - 0xcf);

  expect(Enemy_ID[objoff] == A_BOWSER);

  expect_weak(Enemy_SprAttrib[objoff] == 0);

  const u8 xpos = Enemy_Rel_XPos;
  const bool tall = true;
  const bool mirror_horz = false;
  const u8 palette = 1;
  const bool draw_behind = false;

  u8 ypos = Enemy_Y_Position[objoff];

  // sproff @ $eb
  const u8 sproff = Enemy_SprDataOffset[objoff];

  const u8 enemy_state = Enemy_State[objoff];

  // Bowser can turn upside down in World 8-4
  const bool flip_vert = (enemy_state & 0x20) != 0;

  const bool flip_horz = (Enemy_MovingDir[objoff] & 2) != 0;

  u8 tableoff;

  // Workaround for CheckpointEnemyID() -> Setup_Vine() bug
  rEF = (bowser_gfx_flag == 1) ? 0x16 : 0x17;

  if (bowser_gfx_flag == 1) {
    tableoff = TOFF_BOWSER_FRONT_1;
    if ((BowserBodyControls & 0x80) != 0) {
      // Close Bowser's mouth
      tableoff = TOFF_BOWSER_FRONT_2;
    }
  } else {
    tableoff = TOFF_BOWSER_REAR_1;
    if ((BowserBodyControls & 1) != 0) {
      // Make Bowser's feet stomp
      tableoff = TOFF_BOWSER_REAR_2;
    }

    if (flip_vert) {
      ypos -= 0x10;
    }
  }

  draw_enemy_object_2x3(tableoff, sproff, xpos, ypos, palette, draw_behind, flip_horz, flip_vert, tall, mirror_horz);

  SprObjectOffscrChk(objoff);
}


// SMB:eb64
// SM2MAIN:b83f
// Signature: [r08] -> []
void SprObjectOffscrChk(const u8 objoff) {
  const u8 original_bits = Enemy_OffscreenBits;

  if ((original_bits & 4) != 0) {
    // Inlined: MoveESprColOffscreen
    const u8 offset = SPRITE_calculate_wrap(Enemy_SprDataOffset[objoff], 1);
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 2) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 4) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 8) != 0) {
    // Inlined: MoveESprColOffscreen
    const u8 offset = Enemy_SprDataOffset[objoff];
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 2) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 4) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 0x20) != 0) {
    // Inlined: MoveESprRowOffscreen
    const u8 offset = SPRITE_calculate_wrap(Enemy_SprDataOffset[objoff], 4);
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 1) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 0x40) != 0) {
    // Inlined: MoveESprRowOffscreen
    const u8 offset = SPRITE_calculate_wrap(Enemy_SprDataOffset[objoff], 2);
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 1) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 0x80) != 0) {
    // Inlined: MoveESprRowOffscreen
    const u8 offset = Enemy_SprDataOffset[objoff];
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 1) = SPRITE_Y_OFFSCREEN;

    if ((Enemy_ID[objoff] != A_PODOBOO) && (Enemy_Y_HighPos[objoff] == 2)) {
      EraseEnemyObject(objoff);
    }
  }
}


// SMB:ebd1
// SM2MAIN:b8ac
// Signature: [X] -> []
void DrawBlock(const u8 objoff) {
  const u8 sproff = Block_SprDataOffset[objoff];

  {
    // Inlined: DrawOneSpriteRow

    const u8 left_tileidx_1  = 0x85;
    const u8 right_tileidx_1 = 0x85;
    const u8 left_tileidx_2  = 0x86;
    const u8 right_tileidx_2 = 0x86;

    const u8 xpos = Block_Rel_XPos;
    const u8 ypos = Block_Rel_YPos;
    const u8 attrs = 3;
    const bool flip_horz = false;

    draw_sprite_row(0, sproff, left_tileidx_1, right_tileidx_1, xpos, ypos, attrs, flip_horz);
    draw_sprite_row(1, sproff, left_tileidx_2, right_tileidx_2, xpos, ypos, attrs, flip_horz);
  }

  if (AreaType != AREA_GROUND) {
    SPRITE_TILE(sproff, 0) = 0x86;
    SPRITE_TILE(sproff, 1) = 0x86;
  }
  if (Block_Metatile[objoff] == MT_BLOCK_EMPTY) {
    // Inlined: DumpFourSpr
    // NES note: If the offset is 255, this wraparounds the sprite page
    // because it's incremented before passing to DumpFourSpr.
    // This port assumes it can't happen.
    expect(sproff != 255);
    SPRITE_TILE(sproff, 0) = 0x87;
    SPRITE_TILE(sproff, 1) = 0x87;
    SPRITE_TILE(sproff, 2) = 0x87;
    SPRITE_TILE(sproff, 3) = 0x87;


    const u8 bVar4 = (AreaType != AREA_GROUND) ? 1 : 3;
    SPRITE_ATTR(sproff, 0) = bVar4;
    SPRITE_ATTR(sproff, 1) = bVar4 | 0x40;
    SPRITE_ATTR(sproff, 2) = bVar4 | 0x80;
    SPRITE_ATTR(sproff, 3) = bVar4 | 0xc0;
  }

  if ((Block_OffscreenBits & 4) != 0) {
    SPRITE_Y(sproff, 1) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(sproff, 3) = SPRITE_Y_OFFSCREEN;
  }

  // Inlined: ChkLeftCo
  if ((Block_OffscreenBits & 8) != 0) {
    SPRITE_Y(sproff, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(sproff, 2) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:ec53
// SM2MAIN:b92e
// Signature: [X] -> []
void DrawBrickChunks(const u8 objoff) {
  const u8 tilepalette = GameEngineSubroutine != GR_PLAYERENDLEVEL ? 3 : 2;
  const u8 tileidx = GameEngineSubroutine != GR_PLAYERENDLEVEL ? 0x84 : 0x75;

  const u8 off = Block_SprDataOffset[objoff];

  // NES note: If the sprite offset is 254 or 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpFourSpr.
  // This port assumes it can't happen.
  expect(off <= 253);

  // Set tile indices for all 4 sprites
  // Inlined: DumpFourSpr
  SPRITE_TILE(off, 0) = tileidx;
  SPRITE_TILE(off, 1) = tileidx;
  SPRITE_TILE(off, 2) = tileidx;
  SPRITE_TILE(off, 3) = tileidx;

  // Set attributes for all 4 sprites
  // Cycle through flipping them vertically and horizontally based on the frame counter
  // None -> Horz -> Vert -> Vert+Horz -> None -> ...
  const u8 tileflipattr = (FrameCounter & 0xc) << 4;
  const u8 attr = tileflipattr | tilepalette;
  // Inlined: DumpFourSpr
  SPRITE_ATTR(off, 0) = attr;
  SPRITE_ATTR(off, 1) = attr;
  SPRITE_ATTR(off, 2) = attr;
  SPRITE_ATTR(off, 3) = attr;

  // Set Y for sprites +0, +1

  // Inlined: DumpTwoSpr
  SPRITE_Y(off, 0) = Block_Rel_YPos;
  SPRITE_Y(off, 1) = Block_Rel_YPos;

  const u8 x1 = Block_Rel_XPos;
  const u8 x2 = Block_Rel_XPos_2;

  const u8 b = Block_Orig_XPos[objoff] - ScreenLeft_X_Pos;

  // Set X for all 4 sprites
  SPRITE_X(off, 0) = x1;
  SPRITE_X(off, 1) = 6 + 2*b - x1;
  SPRITE_X(off, 2) = x2;
  SPRITE_X(off, 3) = 6 + 2*b - x2;

  // NES note: The carry additions here are probably an oversight in the original
  // It's separated out here in case a feature-enhacing port wants to remove it
  SPRITE_X(off, 1) += (b >= x1) + (2*b - x1 + (b >= x1) >= 0x100);
  SPRITE_X(off, 3) += (b >= x2) + (2*b - x2 + (b >= x2) >= 0x100);

  // Set Y for sprites +2, +3
  SPRITE_Y(off, 2) = Block_Rel_YPos_2;
  SPRITE_Y(off, 3) = Block_Rel_YPos_2;

  // Inlined: ChkLeftCo
  if ((Block_OffscreenBits & 8) != 0) {
    SPRITE_Y(off, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 2) = SPRITE_Y_OFFSCREEN;
  }

  if ((Block_OffscreenBits & 0x80) != 0) {
    // Inlined: DumpTwoSpr
    SPRITE_Y(off, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 1) = SPRITE_Y_OFFSCREEN;
  }

  if (((i8)b < 0) && (SPRITE_X(off, 1) <= SPRITE_X(off, 0))) {
    // Sprites +1 and +3 are offscreen
    SPRITE_Y(off, 1) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 3) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:ecde
// SM2MAIN:b9b9
// Signature: [X] -> []
void DrawFireball(const u8 objoff) {
  const u8 bVar1 = FBall_SprDataOffset[objoff];
  SPRITE_Y(bVar1, 0) = Fireball_Rel_YPos;
  SPRITE_X(bVar1, 0) = Fireball_Rel_XPos;
  DrawFirebar(bVar1);
}


// SMB:eced
// SM2MAIN:b9c8
// Signature: [Y] -> []
void DrawFirebar(const u8 param_1) {
  SPRITE_TILE(param_1, 0) = ((FrameCounter >> 2) & 1) ^ 100;
  SPRITE_ATTR(param_1, 0) = ((FrameCounter >> 3 & 1) != 0) ? 0xc2 : 2;
}


// SMB:ed09
// SM2MAIN:b9e4
// Signature: [X] -> []
void DrawExplosion_Fireball(const u8 objoff) {
  u8 bVar1 = Fireball_State[objoff];
  Fireball_State[objoff] = Fireball_State[objoff] + 1;
  bVar1 = (bVar1 >> 1) & 7;
  if (bVar1 < 3) {
    DrawExplosion_Fireworks(bVar1, Alt_SprDataOffset[objoff]);
  } else {
    Fireball_State[objoff] = 0;
  }
}


// SMB:ed17
// SM2MAIN:b9f2
// Signature: [A, Y] -> []
void DrawExplosion_Fireworks(const u8 param_1, const u8 param_2) {
  // NES note: If the offset is 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpFourSpr.
  // This port assumes it can't happen.
  expect(param_2 != 255);

  expect(param_1 < 3);

  static const u8 tiles[3] = { 0x68, 0x67, 0x66 };

  // Inlined: DumpFourSpr
  SPRITE_TILE(param_2, 0) = tiles[param_1];
  SPRITE_TILE(param_2, 1) = tiles[param_1];
  SPRITE_TILE(param_2, 2) = tiles[param_1];
  SPRITE_TILE(param_2, 3) = tiles[param_1];

  SPRITE_Y(param_2, 0) = Fireball_Rel_YPos - 4;
  SPRITE_Y(param_2, 2) = Fireball_Rel_YPos - 4;
  SPRITE_Y(param_2, 1) = Fireball_Rel_YPos + 4;
  SPRITE_Y(param_2, 3) = Fireball_Rel_YPos + 4;

  SPRITE_X(param_2, 0) = Fireball_Rel_XPos - 4;
  SPRITE_X(param_2, 1) = Fireball_Rel_XPos - 4;
  SPRITE_X(param_2, 2) = Fireball_Rel_XPos + 4;
  SPRITE_X(param_2, 3) = Fireball_Rel_XPos + 4;

  SPRITE_ATTR(param_2, 0) = 2;
  SPRITE_ATTR(param_2, 1) = 0x82;
  SPRITE_ATTR(param_2, 2) = 0x42;
  SPRITE_ATTR(param_2, 3) = 0xc2;
}


// SMB:ed66
// SM2MAIN:ba41
// Signature: [X] -> []
void DrawSmallPlatform(const u8 objoff) {
  const u8 bVar2 = Enemy_SprDataOffset[objoff];

  // NES note: If the offset is 254 or 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpSixSpr.
  // This port assumes it can't happen.
  expect(bVar2 <= 253);

  // Inlined: DumpSixSpr
  for (int i = 0; i < 6; i++) {
    SPRITE_TILE(bVar2, i) = 0x5b;
    SPRITE_ATTR(bVar2, i) = 2;
  }

  u8 bVar1 = Enemy_Rel_XPos;
  SPRITE_X(bVar2, 0) = Enemy_Rel_XPos;
  SPRITE_X(bVar2, 3) = bVar1;
  SPRITE_X(bVar2, 1) = bVar1 + 8;
  SPRITE_X(bVar2, 4) = bVar1 + 8;
  SPRITE_X(bVar2, 2) = bVar1 + 0x10;
  SPRITE_X(bVar2, 5) = bVar1 + 0x10;
  u8 bStack0000 = Enemy_Y_Position[objoff];
  bVar1 = bStack0000;
  if (bStack0000 < 0x20) {
    bVar1 = SPRITE_Y_OFFSCREEN;
  }

  // Inlined: DumpThreeSpr
  SPRITE_Y(bVar2, 0) = bVar1;
  SPRITE_Y(bVar2, 1) = bVar1;
  SPRITE_Y(bVar2, 2) = bVar1;

  bStack0000 += 0x80;
  if (bStack0000 < 0x20) {
    bStack0000 = SPRITE_Y_OFFSCREEN;
  }
  SPRITE_Y(bVar2, 3) = bStack0000;
  SPRITE_Y(bVar2, 4) = bStack0000;
  SPRITE_Y(bVar2, 5) = bStack0000;
  bVar1 = Enemy_OffscreenBits;
  if ((Enemy_OffscreenBits & 8) != 0) {
    SPRITE_Y(bVar2, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(bVar2, 3) = SPRITE_Y_OFFSCREEN;
  }
  if ((bVar1 & 4) != 0) {
    SPRITE_Y(bVar2, 1) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(bVar2, 4) = SPRITE_Y_OFFSCREEN;
  }
  if ((bVar1 & 2) != 0) {
    SPRITE_Y(bVar2, 2) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(bVar2, 5) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:ede1
// SM2MAIN:babc
// Signature: [X] -> []
void DrawBubble(const u8 objoff) {
  u8 bVar1;

  if ((Player_Y_HighPos == 1) && ((Bubble_OffscreenBits & 8) == 0)) {
    bVar1 = Bubble_SprDataOffset[objoff];
    SPRITE_X(bVar1, 0) = Bubble_Rel_XPos;
    SPRITE_Y(bVar1, 0) = Bubble_Rel_YPos;
    SPRITE_TILE(bVar1, 0) = 0x74;
    SPRITE_ATTR(bVar1, 0) = 2;
  }
}


// SMB:eee9
// SM2MAIN:bbc4
// Signature: [] -> []
void PlayerGfxHandler(void) {
  u8 bVar1;
  u8 abVar2;

  if ((InjuryTimer == 0) || ((FrameCounter & 1) == 0)) {
    if (GameEngineSubroutine == GR_PLAYERDEATH) {
      PlayerGfxProcessing(PlayerGfxTblOffsets[14]);
      return;
    }
    if (PlayerChangeSizeFlag != 0) {
      bVar1 = HandleChangeSize();
      PlayerGfxProcessing(bVar1);
      return;
    }
    if (SwimmingFlag == 0) {
      FindPlayerAction();
      return;
    }
    if (Player_State == PLAYERSTATE_ONGROUND) {
      FindPlayerAction();
      return;
    }
    FindPlayerAction();
    if ((FrameCounter & 4) == 0) {
      abVar2 = Player_SprDataOffset;
      if ((PlayerFacingDir & 1) == 0) {
        abVar2 = Player_SprDataOffset + 4;
      }
      bVar1 = 0;
      if (PlayerSize != 0) {
        if (SPRITE_TILE(abVar2, 6) == PlayerGraphicsTable[158]) {
          return;
        }
        bVar1 = 1;
      }
      SPRITE_TILE(abVar2, 6) = bVar1 == 0 ? 0x31 : 0x46;
    }
  }
}


// SMB:ef34
// SM2MAIN:bc0f
// Signature: [] -> []
void FindPlayerAction(void) {
  const u8 bVar1 = ProcessPlayerAction();
  PlayerGfxProcessing(bVar1);
}


// SMB:ef45
// SM2MAIN:bc20
// Signature: [A] -> []
void PlayerGfxProcessing(const u8 param_1) {
  PlayerGfxOffset = param_1;
  RenderPlayerSub(4);
  ChkForPlayerAttrib();
  if (FireballThrowingTimer != 0) {
    if (PlayerAnimTimer < FireballThrowingTimer) {
      FireballThrowingTimer = PlayerAnimTimer;
      PlayerGfxOffset = PlayerGfxTblOffsets[7];
      const u8 bVar3 = ((Player_X_Speed | Left_Right_Buttons) != 0) ? 3 : 4;
      RenderPlayerSub(bVar3);
    } else {
      FireballThrowingTimer = 0;
    }
  }

  const u8 sprite_offset = Player_SprDataOffset;

  if (SprObject_OffscrBits[0] & 0x10) {
    // Inlined: DumpTwoSpr
    const u8 off = SPRITE_calculate_wrap(sprite_offset, 6);
    SPRITE_Y(off, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 1) = SPRITE_Y_OFFSCREEN;
  }

  if (SprObject_OffscrBits[0] & 0x20) {
    // Inlined: DumpTwoSpr
    const u8 off = SPRITE_calculate_wrap(sprite_offset, 4);
    SPRITE_Y(off, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 1) = SPRITE_Y_OFFSCREEN;
  }

  if (SprObject_OffscrBits[0] & 0x40) {
    // Inlined: DumpTwoSpr
    const u8 off = SPRITE_calculate_wrap(sprite_offset, 2);
    SPRITE_Y(off, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 1) = SPRITE_Y_OFFSCREEN;
  }

  if (SprObject_OffscrBits[0] & 0x80) {
    // Inlined: DumpTwoSpr
    SPRITE_Y(sprite_offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(sprite_offset, 1) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:efa4
// SM2MAIN:bc7f
// Signature: [] -> []
void DrawPlayer_Intermediate(void) {
  const u8 ypos = 0x58;
  const u8 flags = 1;
  const u8 attrs = 0;
  const u8 xpos = 0x60;
  const u8 num_rows = 4;

  DrawPlayerLoop(0xb8, 4, ypos, flags, attrs, xpos, num_rows);
  SPRITE_ATTR(0, 8) = SPRITE_ATTR(0, 9) | 0x40;
}


// SMB:efbe
// SM2MAIN:bc99
// Signature: [A] -> []
void RenderPlayerSub(const u8 param_1) {
  Player_Pos_ForScroll = Player_Rel_XPos;
  DrawPlayerLoop(PlayerGfxOffset, Player_SprDataOffset, Player_Rel_YPos, PlayerFacingDir,
                 Player_SprAttrib, Player_Rel_XPos, param_1);
}


// SMB:efdc
// SM2MAIN:bcb7
// Signature: [X, Y, r02, r03, r04, r05, r07] -> []
void DrawPlayerLoop(const u8 param_1, const u8 sproff, const u8 ypos, const u8 flags, const u8 attrs, const u8 xpos, const u8 num_rows) {
  // NES note: The loop in the original checks at the end. If num_rows = 0, it loops 256 times.
  // This never occurs in unmodified ROMS, but it might in modified ones via DrawPlayer_Intermediate.
  // TODO: have a setting to disable this silly mostly-irrelevant workaround
  const int actual_num_rows = num_rows != 0 ? num_rows : 256;

  // Inlined: DrawOneSpriteRow

  const bool flip_horz = (flags & 2) != 0;

  u8 table_idx = param_1;

  for (int i = 0; i < actual_num_rows; i++) {
    const u8 left_tileidx  = PlayerGraphicsTable[table_idx];
    const u8 right_tileidx = PlayerGraphicsTable[table_idx + 1];

    draw_sprite_row(i, sproff, left_tileidx, right_tileidx, xpos, ypos, attrs, flip_horz);

    table_idx += 2;
  }
}


// SMB:efec
// SM2MAIN:bcc7
// Signature: [] -> [A]
u8 ProcessPlayerAction(void) {
  u8 bVar1;

  if (Player_State == PLAYERSTATE_CLIMBING) {
    bVar1 = 5;
    if (Player_Y_Speed != 0) {
      return ThreeFrameExtent(GetGfxOffsetAdder(5));
    }
  } else {
    if (Player_State == PLAYERSTATE_FALLING) {
      return GetCurrentAnimOffset(GetGfxOffsetAdder(4));
    }
    if (Player_State == PLAYERSTATE_JUMPSWIM) {
      if (SwimmingFlag != 0) {
        const u8 gfxoffsetadder = GetGfxOffsetAdder(1);
        if ((JumpSwimTimer | PlayerAnimCtrl) != 0) {
          return FourFrameExtent(gfxoffsetadder);
        }
        if (A_B_Buttons & BUTTON_A) {
          return FourFrameExtent(gfxoffsetadder);
        }
        return GetCurrentAnimOffset(gfxoffsetadder);
      }
      bVar1 = (CrouchingFlag == 0) ? 0 : 6;
    } else {
      bVar1 = 6;
      if (CrouchingFlag == 0) {
        bVar1 = 2;
        if ((Player_X_Speed | Left_Right_Buttons) != 0) {
          if ((Player_XSpeedAbsolute < 9) || ((Player_MovingDir & PlayerFacingDir) != 0)) {
            return FourFrameExtent(GetGfxOffsetAdder(4));
          }
#ifdef SMB2J_MODE
          expect(is_gameroutine_valid(GameEngineSubroutine));
          // GameEngineSubroutine < 9
          // TODO: is this the right way to express "< 9"?
          switch (GameEngineSubroutine) {
          case GR_PLAYERCHANGESIZE:
          case GR_PLAYERINJURYBLINK:
          case GR_PLAYERDEATH:
          case GR_PLAYERFIREFLOWER:
            break;

          default:
            NoiseSoundQueue = SOUND_NOISE_SKID;
            break;
          }
#endif
          bVar1 = 3;
        }
      }
    }
  }

  const u8 gfxoffsetadder = GetGfxOffsetAdder(bVar1);
  PlayerAnimCtrl = 0;
  return PlayerGfxTblOffsets[gfxoffsetadder];
}


// SMB:f062
// SM2MAIN:bd47
// Signature: [Y] -> [A]
u8 GetCurrentAnimOffset(const u8 param_1) {
  return GetOffsetFromAnimCtrl(PlayerAnimCtrl, param_1);
}


// SMB:f068
// SM2MAIN:bd4d
// Signature: [Y] -> [A]
u8 FourFrameExtent(const u8 param_1) {
  return AnimationControl(3, param_1);
}


// SMB:f06d
// SM2MAIN:bd52
// Signature: [Y] -> [A]
u8 ThreeFrameExtent(const u8 param_1) {
  return AnimationControl(2, param_1);
}


// SMB:f06f
// SM2MAIN:bd54
// Signature: [A, Y] -> [A]
u8 AnimationControl(const u8 param_1, const u8 param_2) {
  const u8 bVar1 = GetCurrentAnimOffset(param_2);
  if (PlayerAnimTimer == 0) {
    PlayerAnimTimer = PlayerAnimTimerSet;
    PlayerAnimCtrl += 1;
    if (param_1 <= PlayerAnimCtrl) {
      PlayerAnimCtrl = 0;
    }
  }
  return bVar1;
}


// SMB:f091
// SM2MAIN:bd76
// Signature: [Y] -> [Y]
u8 GetGfxOffsetAdder(const u8 param_1) {
  if (PlayerSize != 0) {
    return param_1 + 8;
  } else {
    return param_1;
  }
}


// SMB:f0b0
// SM2MAIN:bd95
// Signature: [] -> [A]
u8 HandleChangeSize(void) {
  if ((FrameCounter & 3) == 0) {
    PlayerAnimCtrl += 1;
    if (PlayerAnimCtrl >= 10) {
      PlayerAnimCtrl = 0;
      PlayerChangeSizeFlag = 0;
    }
  }

  static const u8 lookup[2][10] = {
    { 0, 1, 0, 1, 0, 1, 2, 0, 1, 2 },
    { 2, 0, 2, 0, 2, 0, 2, 0, 2, 0 }
  };

  expect(PlayerAnimCtrl < 10);

  if (PlayerSize != 0) {
    const u8 idx = (lookup[1][PlayerAnimCtrl] == 0) ? 1 : 9;
    return PlayerGfxTblOffsets[idx];
  }
  return GetOffsetFromAnimCtrl(lookup[0][PlayerAnimCtrl], 0xf);
}


// SMB:f0d0
// SM2MAIN:bdb5
// Signature: [A, Y] -> [A]
u8 GetOffsetFromAnimCtrl(const u8 param_1, const u8 param_2) {
  u8 o = param_1 * 8 + PlayerGfxTblOffsets[param_2];

  // param_1 is likely never >= 0x20, but the original game computes it this way
  // TODO: verify one way or the other
  o += ((param_1 & 0x20) != 0);

  return o;
}


// SMB:f0e9
// SM2MAIN:bdce
// Signature: [] -> []
void ChkForPlayerAttrib(void) {
  const u8 abVar1 = Player_SprDataOffset;
  if (GameEngineSubroutine != GR_PLAYERDEATH) {
    if (((PlayerGfxOffset == 0x50) || (PlayerGfxOffset == 0xb8)) || (PlayerGfxOffset == 0xc0)) {
      goto C_S_IGAtt;
    }
    if (PlayerGfxOffset != 200) {
      return;
    }
  }

  SPRITE_ATTR(Player_SprDataOffset, 4) &= 0x3f;

  SPRITE_ATTR(abVar1, 5) &= 0x3f;
  SPRITE_ATTR(abVar1, 5) |= 0x40;

C_S_IGAtt:

  SPRITE_ATTR(abVar1, 6) &= 0x3f;

  SPRITE_ATTR(abVar1, 7) &= 0x3f;
  SPRITE_ATTR(abVar1, 7) |= 0x40;
}


// SMB:f12a
// SM2MAIN:be0f
// Signature: [] -> [Y]
u8 RelativePlayerPosition(void) {
  GetObjRelativePosition(0, 0);
  return 0;
}


// SMB:f131
// SM2MAIN:be16
// Signature: [X] -> []
void RelativeBubblePosition(const u8 objoff) {
  // Inlined: GetProperObjOffset
  GetObjRelativePosition(objoff + 22, 3);
}


// SMB:f13b
// SM2MAIN:be20
// Signature: [X] -> []
void RelativeFireballPosition(const u8 objoff) {
  // Inlined: GetProperObjOffset
  GetObjRelativePosition(objoff + 7, 2);
}


// SMB:f148
// SM2MAIN:be2d
// Signature: [X] -> []
void RelativeMiscPosition(const u8 objoff) {
  // Inlined: GetProperObjOffset
  GetObjRelativePosition(objoff + 13, 6);
}


// SMB:f152
// SM2MAIN:be37
// Signature: [X] -> []
void RelativeEnemyPosition(const u8 param_1) {
  GetObjRelativePosition(1 + param_1, 1);
}


// SMB:f159
// SM2MAIN:be3e
// Signature: [X] -> []
void RelativeBlockPosition(const u8 objoff) {
  GetObjRelativePosition(9 + objoff, 4);
  GetObjRelativePosition(9 + objoff + 2, 5);
}


// SMB:f171
// SM2MAIN:be56
// Signature: [X, Y] -> []
void GetObjRelativePosition(const u8 param_1, const u8 param_2) {
  SprObject_Rel_YPos[param_2] = SprObject_Y_Position[param_1];
  SprObject_Rel_XPos[param_2] = SprObject_X_Position[param_1] - ScreenLeft_X_Pos;
}


// SMB:f180
// SM2MAIN:be65
// Signature: [] -> []
void GetPlayerOffscreenBits(void) {
  GetOffScreenBitsSet(0, 0);
}


// SMB:f187
// SM2MAIN:be6c
// Signature: [X] -> []
void GetFireballOffscreenBits(const u8 param_1) {
  // Inlined: GetProperObjOffset
  GetOffScreenBitsSet(param_1 + 7, 2);
}


// SMB:f191
// SM2MAIN:be76
// Signature: [X] -> []
void GetBubbleOffscreenBits(const u8 objoff) {
  // Inlined: GetProperObjOffset
  GetOffScreenBitsSet(objoff + 22, 3);
}


// SMB:f19b
// SM2MAIN:be80
// Signature: [X] -> []
void GetMiscOffscreenBits(const u8 param_1) {
  // Inlined: GetProperObjOffset
  GetOffScreenBitsSet(param_1 + 13, 6);
}


// SMB:f1af
// SM2MAIN:be94
// Signature: [X] -> []
void GetEnemyOffscreenBits(const u8 param_1) {
  // NES note: GetEnemyOffscreenBits sets Y=1. Used by InitPlatformFall.
  GetOffScreenBitsSet(param_1 + 1, 1);
}


// SMB:f1b6
// SM2MAIN:be9b
// Signature: [X] -> []
void GetBlockOffscreenBits(const u8 param_1) {
  GetOffScreenBitsSet(param_1 + 9, 4);
}


// SMB:f1c0
// SM2MAIN:bea5
// Signature: [X, Y] -> []
void GetOffScreenBitsSet(const u8 param_1, const u8 param_2) {
  // Inlined: RunOffscrBitsSubs (only used once in the original games)
  const u8 xbits = GetXOffscreenBits(param_1);
  const u8 ybits = GetYOffscreenBits(param_1);

  SprObject_OffscrBits[param_2] = (ybits << 4) | (xbits >> 4);
}


static u8 xoff_f(const u8 param_1, u8 is_right) {
  // a seriously inlined/simplified version of the original.
  // part of GetXOffscreenBits

  const u8 pageloc = is_right == 0 ? ScreenLeft_PageLoc : ScreenRight_PageLoc;
  const u8 xpos = is_right == 0 ? ScreenLeft_X_Pos : ScreenRight_X_Pos;

  const int j = pageloc - SprObject_PageLoc[param_1];
  const int ik = xpos - SprObject_X_Position[param_1];

  int z = ik + j*256;

  // wraparound as is_right signed 16-bit number to achieve the same glitchy behavior
  if (z >= 0x8000) { z -= 0x10000; }
  if (z < -0x8000) { z += 0x10000; }

  u8 v;
  if (z < 0) {
    v = 0x7;
  } else if (z < 56) {
    // 8 to e
    v = z/8 + 8;
  } else  {
    v = 0xf;
  }

  if (is_right) {
    v = (v+8)%16;
  }
  return v;
}

// SMB:f1f6
// SM2MAIN:bedb
// Signature: [X] -> [A]
u8 GetXOffscreenBits(const u8 param_1) {
  static const u8 lookup[16] = {
    0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00,
    0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff,
  };

  u8 i = xoff_f(param_1, 1);
  expect(i < 16);
  if (lookup[i] != 0) {
    return lookup[i];
  }
  i = xoff_f(param_1, 0);
  expect(i < 16);
  return lookup[i];
}

static u8 yoff_f(const u8 param_1, bool a) {
  // a seriously inlined/simplified version of the original.
  // part of GetYOffscreenBits

  bool is_smb2j = false;
  #ifdef SMB2J_MODE
  is_smb2j = true;
  #endif

  const int i = SprObject_Y_HighPos[param_1];
  const int j = SprObject_Y_Position[param_1];

  int z = 256 - i*256 - j;

  // SMB2J toggles when the offset is applied
  if (is_smb2j == a) {
    z += 255;
  }

  // wraparound as a signed 16-bit number to achieve the same glitchy behavior
  if (z >= 0x8000) { z -= 0x10000; }
  if (z < -0x8000) { z += 0x10000; }

  u8 v;
  if (z < 0) {
    v = 4;
  } else if (z < 32) {
    // 4 to 7
    v = z/8 + 4;
  } else {
    v = 0;
  }

  if (a) {
    v = (v+4)%8;
  }
  return v;
}

// SMB:f239
// SM2MAIN:bf1e
// Signature: [X] -> [A]
u8 GetYOffscreenBits(const u8 param_1) {
  static const u8 lookup[9] = {
#ifdef SMB1_MODE
    0x00, 0x08, 0x0c, 0x0e, 0x0f, 0x07, 0x03, 0x01, 0x00,
#endif
#ifdef SMB2J_MODE
    0x0f, 0x07, 0x03, 0x01, 0x00, 0x08, 0x0c, 0x0e, 0x00,
#endif
  };

  u8 i = yoff_f(param_1, 1);
  expect(i < 9);
  if (lookup[i] != 0) {
    return lookup[i];
  }
  i = yoff_f(param_1, 0);
  expect(i < 9);
  return lookup[i];
}
