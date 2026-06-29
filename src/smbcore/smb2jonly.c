#include "ctx.h"


static bool RUN_IRQ = false;

// read $4032
static inline u8 FDS_drive_status(void) { return 0; }

static inline void trigger_scroll_irq_if_havent_yet(void) {
  if (RUN_IRQ) {
    IRQHandler();
    RUN_IRQ = false;
    if (IRQAckFlag != 0) {
      warning("IRQAckFlag is non-zero after the IRQ handler. This shouldn't happen!\n");
    }
  }
}

static inline void disable_interrupt(void) {}
static inline void enable_interrupt(void) {}

static inline u8 FDS_AcknowledgeIrq(void) {
  return 0x01;
}
static inline void FDSBIOS_Delay132(u8 val) {
  (void)val;
}
static inline void FDS_IrqTimer_Ctrl(u8 ctrl) {
  (void)ctrl;
}
static inline void FDS_Ctrl(u8 ctrl) {
  // $4025
  (void)ctrl;
}


// SM2MAIN:c0f4
// Signature: [] -> [A, Y, Z]
struct_ayz LoadFiles(void) {
  // The FDS version calls FDS BIOS subroutines to read the files from disk, but in the port, we're just gonna load from a buffer.
  // The BIOS call is responsible for a lot of lag frames on the original hardware! Fortunately we don't deal with those here.

  u8 files = 0;
  bool success = false;

  switch (FileListNumber) {
  case 0: // Worlds 1-4: SM2CHAR1, SM2MAIN, SM2SAVE
    if (!smb2j_load_file(SMB_STATE, "SM2CHAR1")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2MAIN ")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2SAVE ")) { goto end; }
    success = true;
    files = 3;
    break;
  case 1: // Worlds 5-8: SM2DATA2
    if (!smb2j_load_file(SMB_STATE, "SM2DATA2")) { goto end; }
    success = true;
    files = 1;
    break;
  case 2: // Ending, w9: SM2CHAR2, SM2DATA3, SM2SAVE
    if (!smb2j_load_file(SMB_STATE, "SM2CHAR2")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2DATA3")) { goto end; }
    if (!smb2j_load_file(SMB_STATE, "SM2SAVE ")) { goto end; }
    success = true;
    files = 3;

    // The FDS BIOS call overwrites some zero-page variables that are used during the ending.
    // This is a supremely gross hack.
    // Omitting this hack doesn't break the game, but it'd cause different conditionals to occur regarding Mario's sprites and fail RAM regression tests.

    // This isn't an issue for the other file loads, because when the worlds are loaded,
    // the memory is unused and is cleared on the next frame with InitializeMemory.

    // These are values when FileListNumber = 2, during a specific run of the game (idk if this changes):
    // TODO - set these to their corresponding variables when we're more sure what's going on
    RAM(0x08) = 0x0F;
    RAM(0x09) = 0x00;
    RAM(0x0A) = 0xA0;
    RAM(0x0B) = 0xD2;
    RAM(0x0C) = 0xFF;
    RAM(0x0D) = 0xFF;
    RAM(0x0E) = 0x03;
    RAM(0x0F) = 0x01;
    RAM(0xF9) = 0xF7;
    RAM(0xFA) = 0x27;
    break;
  case 3: // Worlds A-D: SM2DATA4
    smb2j_load_file(SMB_STATE, "SM2DATA4");
    success = true;
    files = 1;
    break;
  default:
    break;
  }

end:
  // this runs long enough for the scroll code of the irq to trigger
  trigger_scroll_irq_if_havent_yet();

  // A is the error code, should there be an error
  // Y is how many files were read
  // Z is set to 1 if the load is successful
  struct_ayz res;
  res.a = 0;
  res.y = files;
  res.z = success;
  return res;
}

// SM2MAIN:6000
// Signature: [] -> []
void Reset(void) {
  FDS_Ctrl(RAM(0xfa) & ~0x08);

  // On a hard reset, the World number is a value such as 0xFF
  // assuming a hard reset:
  WorldNumber = 0xFF;

  u8 const last_worldnumber = WorldNumber;

  u8 initialize_upto = WarmBootValidation == 0xa5 ? 0xd6 : 0xfe;

  for (int i = 0; i < 6; i++) {
    if (DisplayDigits[i] > 9) {
      initialize_upto = 0xfe;
      break;
    }
  }

  InitializeMemory(initialize_upto);
  OperMode = OM_TITLESCREEN;
  apu_dmc_raw(0);
  WorldNumber = last_worldnumber;
  WarmBootValidation = 0xa5;
  PseudoRandomBitReg[0] = 0xa5;
  apu_snd_chn(0xf);
  ppumask(6);
  DiskIOTask = 0;
  MoveAllSpritesOffscreen();
  InitializeNameTables();
  DisableScreenFlag += 1;

  FDSBIOS_IRQFlag = 0xc0;
  enable_interrupt();

  Mirror_PPU_CTRL_REG1 |= 0x80;
  ppuctrl(Mirror_PPU_CTRL_REG1);

  // There was an infinite do-nothing loop here for the FDS.
  // At this point, the NMI would interrupt the loop each frame.
  // But as for the port, we just call the NMI ourselves.
}

static const u8 * vram_buffer(u8 addr_ctrl, u16 *length) {
  // The VRAM buffers are tightly coupled with the code, so those are hard-coded in here.

  // Unlike SMB1, SMB2J's address table is 16-bit words, not segmented in hi and lo portions
  // Also unlike SMB1, index 5 (the title screen) is from the ROM.

  switch (addr_ctrl) {
  case ADDRCTRL_VRAM_BUFFER1:
    *length = 0x10000 - 0x301;
    return &VRAM_Buffer1[0];

  case ADDRCTRL_VRAM_BUFFER2:
  case ADDRCTRL_VRAM_BUFFER2_unused:
    *length = 0x10000 - 0x341;
    return &VRAM_Buffer2[0];

  default:
    {
      // Get the other ones from ROM
      const u8 hi = VRAM_AddrTable[addr_ctrl * 2 + 1];
      const u8 lo = VRAM_AddrTable[addr_ctrl * 2];
      const u16 addr = (hi << 8) | lo;

      // TODO - get actual length of the arrays
      *length = 0x10000 - addr;

      return rom_ptr(addr);
    }
  }
}

// SM2MAIN:60a0
// Signature: [] -> []
void NMI(void) {
  Mirror_PPU_CTRL_REG1 = Mirror_PPU_CTRL_REG1 & ~0x81;
  ppuctrl(Mirror_PPU_CTRL_REG1);

  disable_interrupt();

  RUN_IRQ = false;

  if (IRQUpdateFlag != 0) {
    // Set IRQ timer to 0x1658 (until the scanline reaches the bottom of the status bar)
    // $4020 = 0x58
    // $4021 = 0x16
    // Enable IRQ timer
    // $4022 = 0x02
    IRQAckFlag += 1;
    RUN_IRQ = true;
  }

  if (DisableScreenFlag == 0) {
    Mirror_PPU_CTRL_REG2 |= 0x1e;
  } else {
    Mirror_PPU_CTRL_REG2 &= 0xe6;
  }
  ppumask(Mirror_PPU_CTRL_REG2 & 0xe7);

  ppustatus();
  ppuscroll(0);
  ppuscroll(0);

  struct sprite sprites[64];

  // The NES wrote to OAM registers to initiate copying sprites
  // $2003 = 0
  // $4014 = 2
  transfer_sprite_data(&sprites[0], &Sprite_Data[0]);

  u16 vram_length = 0;
  const u8 *buf = vram_buffer(VRAM_Buffer_AddrCtrl, &vram_length);
  update_screen(buf, vram_length);

  if (VRAM_Buffer_AddrCtrl != ADDRCTRL_VRAM_BUFFER2) {
    VRAM_Buffer1_Offset = 0;
    VRAM_Buffer1[0] = 0;
  } else {
    VRAM_Buffer2_Offset = 0;
    VRAM_Buffer2[0] = 0;
  }

  VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER1;

  ppumask(Mirror_PPU_CTRL_REG2);
  enable_interrupt();

  // NES note: SMB2J patches the JSR instruction here when saving the princess
  if (AlternateSoundEngineEnabled) {
    AlternateSoundEngine();
  } else {
    SoundEngine();
  }

  apu_end_frame();
  ReadJoypads();
  PauseRoutine();
  UpdateTopScore();
  if ((GamePauseStatus & 1) == 0) {
    dectimers();
    FrameCounter += 1;
  }

  // Update PRNG (pseudo-random number generator)
  update_prng(&PseudoRandomBitReg[0]);

  if ((GamePauseStatus & 1) == 0) {
    if (IRQUpdateFlag != 0) {
      MoveSpritesOffscreen();
      SpriteShuffler();
    }
    if (WorldNumber > 8) {
      TerminateGame();
    }
    OperModeExecutionTree();
  }

  // The FDS version loops here until IRQAckFlag is 0.
  trigger_scroll_irq_if_havent_yet();

  draw_graphics(&sprites[0]);

  ppustatus();

  // Enable NMI (our port ignores this)
  Mirror_PPU_CTRL_REG1 |= 0x80;
  ppuctrl(Mirror_PPU_CTRL_REG1);
}

// SM2MAIN:61a2
// Signature: [] -> []
void IRQHandler(void) {
  disable_interrupt();
  u8 const status = FDS_AcknowledgeIrq();

  if ((status & 0x02) == 0) {
    if ((status & 0x01) != 0) {
      // Scrolling the screen right below the status bar
      // first 2 bits are 01: not transferring bytes, and an irq occurred

      Mirror_PPU_CTRL_REG1 = (Mirror_PPU_CTRL_REG1 & ~0x08) | NameTableSelect;
      ppuctrl(Mirror_PPU_CTRL_REG1);
      FDS_IrqTimer_Ctrl(0x00); // disable IRQ timer for the rest of the frame
      ppuscroll(HorizontalScroll);
      ppuscroll(VerticalScroll);
      IRQAckFlag = 0;
    }
  } else {
    // FDS is transferring bytes
    FDSBIOS_Delay132(status);
  }
  enable_interrupt();
}

// SM2MAIN:7b20
// Signature: [Y] -> []
void ScrollScreen(u8 scroll_amount) {
  // The FDS version loops here until IRQAckFlag is 0.
  trigger_scroll_irq_if_havent_yet();

  int const x_pos = ScreenLeft_X_Pos + scroll_amount;

  ScrollThirtyTwo += scroll_amount;
  HorizontalScroll = x_pos % 256;
  if (x_pos >= 256) {
    ScreenLeft_PageLoc += 1;
  }
  NameTableSelect = ScreenLeft_PageLoc % 2;
  ScreenLeft_X_Pos = HorizontalScroll;
  ScrollAmount = scroll_amount;
  GetScreenPosition();
  ScrollIntervalTimer = 8;
  ChkPOffscr();
}

// SM2DATA3::c759
// Signature: [] -> []
void UpdateGamesBeaten(void) {
  // The FDS version would use an FDS BIOS subroutine
  bool const success = smb2j_save_games_beaten(GamesBeatenCount);
  u8 const error_code = 0;

  if (!success) {
    DiskIOTask += 1;
    DiskErrorHandler(error_code);
    return;
  }

  BackToNormal();
}

// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_VictoryModeSubroutines_forW8(const u8 param_1) {
  switch (param_1) {
  case OMT_VICTORY_BRIDGECOLLAPSE:
    BridgeCollapse();
    return;

  case OMT_VICTORY_SETUPVICTORYMODE:
    SetupVictoryMode();
    return;

  case OMT_VICTORY_PLAYERVICTORYWALK:
    PlayerVictoryWalk();
    return;

  case OMT_VICTORY_W8SMB2J_STARTVMDELAY:
    WorldEndTimer = 0x10;
    expect(OperMode == OM_VICTORY);
    OperMode_Task = OMT_VICTORY_W8SMB2J_CONTINUEVMDELAY;
    return;

  case OMT_VICTORY_W8SMB2J_CONTINUEVMDELAY:
    if (WorldEndTimer == 0) {
      expect(OperMode == OM_VICTORY);
      OperMode_Task = OMT_VICTORY_W8SMB2J_VICTORYMODEDISKROUTINES;
    }
    return;

  case OMT_VICTORY_W8SMB2J_VICTORYMODEDISKROUTINES:
    VictoryModeDiskRoutines();
    return;

  case OMT_VICTORY_W8SMB2J_SCREENSUBSFORFINALROOM:
    ScreenSubsForFinalRoom();
    return;

  case OMT_VICTORY_W8SMB2J_PRINTVICTORYMSGSFORWORLD8:
    PrintVictoryMsgsForWorld8();
    return;

  case OMT_VICTORY_W8SMB2J_ENDCASTLEAWARD:
    EndCastleAward();
    return;

  case OMT_VICTORY_W8SMB2J_AWARDEXTRALIVES:
    AwardExtraLives();
    return;

  case OMT_VICTORY_W8SMB2J_FADETOBLUE:
    FadeToBlue();
    return;

  case OMT_VICTORY_W8SMB2J_ERASELIVESLINES:
    EraseLivesLines();
    return;

  case OMT_VICTORY_W8SMB2J_RUNMUSHROOMRETAINERS:
    RunMushroomRetainers();
    return;

  case OMT_VICTORY_W8SMB2J_ENDINGDISKROUTINES:
    EndingDiskRoutines();
    return;

  default:
    jmpengine_overflow(param_1);
  }
}


// SM2MAIN:636d
// Signature: [] -> []
void PrintVictoryMessages(void) {
  bool inc_msg_counter = true;

  if (SecondaryMsgCounter == 0) {
    if (PrimaryMsgCounter == 0) {
      VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_THANKYOUMESSAGE;
    } else if (PrimaryMsgCounter == 1) {
      VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_BUTOURPRINCESSISINANOTHERCASTLE;
    } else if (PrimaryMsgCounter < 8) {
      if (PrimaryMsgCounter >= 3) {
        inc_msg_counter = false;
      }
    }
  }

  if (inc_msg_counter) {
    ADD_UNSIGNED_16_8(PrimaryMsgCounter, SecondaryMsgCounter,
                      4);

    if (PrimaryMsgCounter <= 5) {
      return;
    }
  }

  WorldEndTimer = 8;
  expect(OperMode == OM_VICTORY);
  expect(OperMode_Task == OMT_VICTORY_PRINTVICTORYMESSAGES);
  OperMode_Task = OMT_VICTORY_ENDCASTLEAWARD;
}


// SM2MAIN:63af
// Signature: [] -> []
void EndCastleAward(void) {
  if (WorldEndTimer < 6) {
    AwardTimerCastle();
    if ((u8)(GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2]) == 0) {
      SelectTimer = 0x30;
      WorldEndTimer = 6;
      expect(OperMode == OM_VICTORY);
      if (WorldNumber == 7) {
        expect(OperMode_Task == OMT_VICTORY_W8SMB2J_ENDCASTLEAWARD);
        OperMode_Task = OMT_VICTORY_W8SMB2J_AWARDEXTRALIVES;
      } else {
        expect(OperMode_Task == OMT_VICTORY_ENDCASTLEAWARD);
        OperMode_Task = OMT_VICTORY_PLAYERENDWORLD;
      }
    }
  }
}


// SM2MAIN:671b
// Signature: [A] -> []
void WriteGameText(const u8 param_1) {
  u8 offset = GameTextOffsets[param_1];

  bool terminated = false;
  for (int i = 0; i < 256; i++) {
    if (GameText[offset] == 0xff) {
      VRAM_Buffer1[i] = 0;
      terminated = true;
      break;
    }
    VRAM_Buffer1[i] = GameText[offset];
    offset += 1;
  }

  if (!terminated) {
    VRAM_Buffer1[0] = 0;
  }

  if (param_1 == 1) {
    // Wrote the world and lives display screen

    const u8 lives_tile = NumberofLives + 1;

    if (lives_tile < 10) {
      // Draw the number of lives if under 10
      VRAM_Buffer1[8] = lives_tile;
    } else {
      // Draw crown tile, then the number of lives
      VRAM_Buffer1[7] = 0x9f;
      VRAM_Buffer1[8] = lives_tile - 10;
    }

    // Write the world and level numbers
    // Inlined: GetWorldNumForDisplay
    const u8 world_number_display = HardWorldFlag == 0 ? WorldNumber + 1 : (WorldNumber & 3) + 10;
    const u8 level_number_display = LevelNumber + 1;
    VRAM_Buffer1[19] = world_number_display;
    VRAM_Buffer1[21] = level_number_display;
  }
}


// SM2MAIN:89a1
// Signature: [X] -> []
void PoisonMushBlock(const u8 param_1) {
  PowerUpType = POWERUP_POISONSHROOM;
  SetupPowerUp(param_1);
}


// SM2MAIN:a64e
// Signature: [X] -> []
void SetBounce(const u8 param_1) {
  Player_Y_Speed = 0xfa;
  const u8 enemy_id = Enemy_ID[param_1];
  if ((enemy_id == A_RED_PARATROOPA) || (enemy_id == A_GREEN_PARATROOPA_HORIZONTAL)) {
    Player_Y_Speed = 0xf8;
  }
}


// SM2MAIN:aca3
// Signature: [X] -> []
void ChkToStunEnemies(const u8 param_1) {
  // The port inlines NoDemote, because it more clearly reveals what's actually going on here.
  // The NES implementation did a bunch of compares to hoan in on the object types,
  // but it's more obvious to just do the comparisons directly.

  const u8 enemy_id = Enemy_ID[param_1];

  if (enemy_id == A_GOOMBA || enemy_id == A_POWERUP) {
    SetStun2(param_1);
    return;
  }

  // Turn these enemies into koopas
  switch (enemy_id) {
  case A_GREEN_PARATROOPA_INPLACE:
  case A_RED_PARATROOPA:
    Enemy_ID[param_1] = A_RED_KOOPA_GREENLIKE;
    break;

  case A_GREEN_PARATROOPA:
  case A_GREEN_PARATROOPA_HORIZONTAL:
    Enemy_ID[param_1] = A_GREEN_KOOPA;
    break;
  }

  Enemy_State[param_1] = 2;
  SetStun2(param_1);
}


enum HardWorldsCheckpoint_jumptable_item {
  HARDWORLDSCHECKPOINT_DISKSCREEN,
  HARDWORLDSCHECKPOINT_LOADHARDWORLDS,
  HARDWORLDSCHECKPOINT_WAITFOREJECT,
  HARDWORLDSCHECKPOINT_WAITFORREINSERT,
  HARDWORLDSCHECKPOINT_RESETDISKVARS,
};


// SM2MAIN:bfc2
// Signature: [] -> []
void HardWorldsCheckpoint(void) {
  switch (DiskIOTask) {
  case HARDWORLDSCHECKPOINT_DISKSCREEN:
    DiskScreen();
    return;

  case HARDWORLDSCHECKPOINT_LOADHARDWORLDS:
    LoadHardWorlds();
    return;

  case HARDWORLDSCHECKPOINT_WAITFOREJECT:
    WaitForEject();
    return;

  case HARDWORLDSCHECKPOINT_WAITFORREINSERT:
    WaitForReinsert();
    return;

  case HARDWORLDSCHECKPOINT_RESETDISKVARS:
    ResetDiskVars();
    return;

  default:
    jmpengine_overflow(DiskIOTask);
  }
}


// SM2MAIN:bfd2
// Signature: [] -> []
void LoadHardWorlds(void) {
  u8 bVar1;
  bool bVar2;
  struct_ayz sVar3;

  if (HardWorldFlag != 0) {
    FileListNumber = 3;
    sVar3 = LoadFiles();
    bVar1 = sVar3.a;
    if (sVar3.z) {
      bVar2 = CheckFileCount(sVar3.y);
      if (bVar2) {
        goto NoLoadHW;
      }
      bVar1 = 0x40;
    }
    DiskIOTask += 1;
    DiskErrorHandler(bVar1);
    return;
  }
NoLoadHW:
  LoadAreaPointer();
  if (HardWorldFlag != 0) {
    ChangeHalfwayPages();
  }
  Hidden1UpFlag += 1;
  FetchNewGameTimerFlag += 1;
  expect(OperMode == OM_TITLESCREEN);
  OperMode = OM_GAME;
  // Inlined: ResetDiskIOTask
  DiskIOTask = 0;
  OperMode_Task = OMT_GAME_START;
  DemoTimer = 0;
}


enum AttractModeDiskRoutines_jumptable_item {
  ATTRACTMODEDISKROUTINES_DISKSCREEN,
  ATTRACTMODEDISKROUTINES_LOADWORLDS1THRU4,
  ATTRACTMODEDISKROUTINES_WAITFOREJECT,
  ATTRACTMODEDISKROUTINES_WAITFORREINSERT,
  ATTRACTMODEDISKROUTINES_RESETDISKVARS,
};


// SM2MAIN:c006
// Signature: [] -> []
void AttractModeDiskRoutines(void) {
  switch (DiskIOTask) {
  case ATTRACTMODEDISKROUTINES_DISKSCREEN:
    DiskScreen();
    return;

  case ATTRACTMODEDISKROUTINES_LOADWORLDS1THRU4:
    LoadWorlds1Thru4();
    return;

  case ATTRACTMODEDISKROUTINES_WAITFOREJECT:
    WaitForEject();
    return;

  case ATTRACTMODEDISKROUTINES_WAITFORREINSERT:
    WaitForReinsert();
    return;

  case ATTRACTMODEDISKROUTINES_RESETDISKVARS:
    ResetDiskVars();
    return;

  default:
    jmpengine_overflow(DiskIOTask);
  }
}


// SM2MAIN:c016
// Signature: [] -> []
void LoadWorlds1Thru4(void) {
  u8 bVar1;
  bool bVar2;
  struct_ayz sVar3;

  if ((NotColdFlag != 0) && ((HardWorldFlag != 0 || (WorldNumber >= 4)))) {
    FileListNumber = 0;
    sVar3 = LoadFiles();
    bVar1 = sVar3.a;
    if (sVar3.z) {
      bVar2 = CheckFileCount(sVar3.y);
      if (bVar2) {
        goto InitWorldPos;
      }
      bVar1 = 0x40;
    }
    DiskIOTask += 1;
    DiskErrorHandler(bVar1);
    return;
  }
InitWorldPos:
  NotColdFlag = 1;
  WorldNumber = 0;
  HardWorldFlag = 0;
  // Inlined: ResetDiskIOTask
  DiskIOTask = 0;
  expect(OperMode == OM_TITLESCREEN);
  expect(OperMode_Task == OMT_TITLESCREEN_START);
  OperMode_Task = OMT_TITLESCREEN_INITIALIZEGAME;
}


enum GameModeDiskRoutines_jumptable_item {
  GAMEMODEDISKROUTINES_DISKSCREEN,
  GAMEMODEDISKROUTINES_LOADWORLDS5THRU8,
  GAMEMODEDISKROUTINES_WAITFOREJECT,
  GAMEMODEDISKROUTINES_WAITFORREINSERT,
  GAMEMODEDISKROUTINES_RESETDISKVARS,
};


// SM2MAIN:c04d
// Signature: [] -> []
void GameModeDiskRoutines(void) {
  switch (DiskIOTask) {
  case GAMEMODEDISKROUTINES_DISKSCREEN:
    DiskScreen();
    return;

  case GAMEMODEDISKROUTINES_LOADWORLDS5THRU8:
    LoadWorlds5Thru8();
    return;

  case GAMEMODEDISKROUTINES_WAITFOREJECT:
    WaitForEject();
    return;

  case GAMEMODEDISKROUTINES_WAITFORREINSERT:
    WaitForReinsert();
    return;

  case GAMEMODEDISKROUTINES_RESETDISKVARS:
    ResetDiskVars();
    return;

  default:
    jmpengine_overflow(DiskIOTask);
  }
}


// SM2MAIN:c05d
// Signature: [] -> []
void LoadWorlds5Thru8(void) {
  bool bVar2;
  expect(OperMode == OM_GAME);
  expect(OperMode_Task == OMT_GAME_START);

  if (WorldNumber < 4) {
    // Inlined: ResetDiskIOTask
    DiskIOTask = 0;
    OperMode_Task = OMT_GAME_INITIALIZEAREA;
    return;
  }
  if (FileListNumber != 0) {
    // Inlined: ResetDiskIOTask
    DiskIOTask = 0;
    OperMode_Task = OMT_GAME_INITIALIZEAREA;
    return;
  }
  FileListNumber = 1;
  const struct_ayz sVar3 = LoadFiles();
  u8 bVar1 = sVar3.a;
  if (sVar3.z) {
    bVar2 = CheckFileCount(sVar3.y);
    if (bVar2) {
      // Inlined: ResetDiskIOTask
      DiskIOTask = 0;
      OperMode_Task = OMT_GAME_INITIALIZEAREA;
      return;
    }
    bVar1 = 0x40;
  }
  DiskIOTask += 1;
  DiskErrorHandler(bVar1);
}


enum VictoryModeDiskRoutines_jumptable_item {
  VICTORYMODEDISKROUTINES_DISKSCREEN,
  VICTORYMODEDISKROUTINES_LOADENDING,
  VICTORYMODEDISKROUTINES_WAITFOREJECT,
  VICTORYMODEDISKROUTINES_WAITFORREINSERT,
  VICTORYMODEDISKROUTINES_RESETDISKVARS,
};


// SM2MAIN:c08e
// Signature: [] -> []
void VictoryModeDiskRoutines(void) {
  switch (DiskIOTask) {
  case VICTORYMODEDISKROUTINES_DISKSCREEN:
    DiskScreen();
    return;

  case VICTORYMODEDISKROUTINES_LOADENDING:
    LoadEnding();
    return;

  case VICTORYMODEDISKROUTINES_WAITFOREJECT:
    WaitForEject();
    return;

  case VICTORYMODEDISKROUTINES_WAITFORREINSERT:
    WaitForReinsert();
    return;

  case VICTORYMODEDISKROUTINES_RESETDISKVARS:
    ResetDiskVars();
    return;

  default:
    jmpengine_overflow(DiskIOTask);
  }
}


// SM2MAIN:c09e
// Signature: [] -> []
void LoadEnding(void) {
  bool bVar1;

  FileListNumber = 2;
  const struct_ayz sVar2 = LoadFiles();
  if (sVar2.z) {
    bVar1 = CheckFileCount(sVar2.y);
    if (!bVar1) {
      GamesBeatenCount = 0;
    }
    GamesBeatenCount += 1;
    if (GamesBeatenCount > 0x18) {
      GamesBeatenCount = 0x18;
    }
    InitializeNameTables();
    // Inlined: ResetDiskIOTask
    DiskIOTask = 0;
    expect(OperMode == OM_VICTORY);
    expect(OperMode_Task == OMT_VICTORY_W8SMB2J_VICTORYMODEDISKROUTINES);
    OperMode_Task = OMT_VICTORY_W8SMB2J_SCREENSUBSFORFINALROOM;
    WriteNameToVictoryMsg();
  } else {
    DiskIOTask += 1;
    DiskErrorHandler(sVar2.a);
  }
}


// SM2MAIN:c0ca
// Signature: [Y] -> [Z]
bool CheckFileCount(const u8 param_1) { return param_1 == FileCount[FileListNumber]; }


// SM2MAIN:c113
// Signature: [] -> []
void DiskScreen(void) {
  Mirror_PPU_CTRL_REG2 = 0;
  ppumask(0);
  DisableScreenFlag += 1;
  VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_DISKSCREENPALETTE;
  DiskIOTask += 1;
}


// SM2MAIN:c126
// Signature: [] -> []
void WaitForEject(void) {
  NameTableSelect = 0;
  DisableScreenFlag = 0;
  const u8 bVar1 = FDS_drive_status();
  if ((bVar1 & 1) != 0) {
    DiskIOTask += 1;
  }
}


// SM2MAIN:c138
// Signature: [] -> []
void WaitForReinsert(void) {
  const u8 bVar1 = FDS_drive_status();
  if ((bVar1 & 1) == 0) {
    DiskIOTask += 1;
  }
}


// SM2MAIN:c140
// Signature: [] -> []
void ResetDiskVars(void) {
  DiskIOTask = 0;
  FileListNumber = 0;
}


// SM2MAIN:c182
// Signature: [A] -> []
void DiskErrorHandler(const u8 param_1) {
  DiskErrorMainMsg[19] = param_1 & 0xf;
  DiskErrorMainMsg[18] = param_1 >> 4;

  u8 bVar1;
  if (param_1 == 7) {
    bVar1 = DiskErrorMsgOffsets[3];
  } else if (param_1 == 2) {
    bVar1 = DiskErrorMsgOffsets[2];
  } else if (param_1 == 1) {
    bVar1 = DiskErrorMsgOffsets[1];
  } else {
    bVar1 = DiskErrorMsgOffsets[0];
  }

  for (int i = 0; i < 8; i++) {
    DiskErrorMainMsg[i+3] = DiskErrorMsgs[bVar1 + i - 7];
  }

  VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_DISKERRORMAIN;
  MoveAllSpritesOffscreen();
  InitializeNameTables();
}


// SM2MAIN:c1c2
// Signature: [] -> []
void GameOverMenu(void) {
  if ((SavedJoypadBits[0] & BUTTON_START) == 0) {
    if (((SavedJoypadBits[0] & BUTTON_SELECT) != 0) && (SelectTimer == 0)) {
      if ((SavedJoypadBits[0] & BUTTON_SELECT) != 0) {
        SelectTimer = 0x10;
      } else {
        SelectTimer = 0;
      }
      ContinueMenuSelect ^= 1;
    }

    expect(ContinueMenuSelect <= 1);

    SPRITE_TILE(0, 0) = 0x5b;
    SPRITE_ATTR(0, 0) = 2;
    SPRITE_X(0, 0)    = 72;
    SPRITE_Y(0, 0)    = ContinueMenuSelect == 0 ? 119 : 143;
    return;
  }
  if (ContinueMenuSelect != 0) {
    CompletedWorlds = 0;
    TerminateGame();
    return;
  }
  NumberofLives = 2;
  LevelNumber = 0;
  AreaNumber = 0;
  CoinTally = 0;
  for (int i = 0; i < 12; i++) {
    DisplayDigits[i + 6] = 0;
  }
  Hidden1UpFlag += 1;
  ContinueGame();
}

static void LoadLuigiPhysics(void);

// SM2MAIN:c241
// Signature: [] -> []
void LoadPhysicsData(void) {
  if (CurrentPlayer == 0) {
    LoadMarioPhysics();
  } else {
    LoadLuigiPhysics();
  }
}


// SM2MAIN:c24a
// Signature: [] -> []
void LoadMarioPhysics(void) {
  // The original game modifies an instruction to "ASL" (restores a bitshift intruction that's there by default)
  PhysicsInstructionOpcode = 0x0e;

  // NES note: This originally updated lookup tables used by PlayerPhysicsSub.
  // The logic is moved there.
}

static void LoadLuigiPhysics(void) {
  // The original game modifies an instruction to "RTS" (early-returns from that subroutine)
  PhysicsInstructionOpcode = 0x60;

  // NES note: This originally updated lookup tables used by PlayerPhysicsSub.
  // The logic is moved there.
}


// SM2MAIN:c5ff
// Signature: [] -> []
void PatchPlayerNamePal(void) {
  expect(CurrentPlayer <= 1);

  // Note: Inlined the offsets. The code assumes a length of 5 for both names, anyway.

  // Note: The original overwrites the player's palette, which is eventually
  // used by GetPlayerColors.
  // This is removed in favor of just checking in GetPlayerColors if Mario or Luigi is playing.
  // TODO: This subroutine name is now a misnomer. Change it.

  PatchCurrentPlayer = CurrentPlayer;

  if (CurrentPlayer == 0) {
    for (int i = 0; i < 5; i++) {
      TopStatusBarLine[i + 3] = PlayerNameMario[i];
      ThankYouMessage[i + 13] = PlayerNameMario[i];
    }
  } else {
    for (int i = 0; i < 5; i++) {
      TopStatusBarLine[i + 3] = PlayerNameLuigi[i];
      ThankYouMessage[i + 13] = PlayerNameLuigi[i];
    }
  }
}


// SM2DATA2+SM2DATA4:c4c0
// Signature: [X] -> []
void MoveUpsideDownPiranhaP(const u8 param_1) {
  u8 bVar1;
  u8 bVar2;
  u8 bVar3;

  if ((Enemy_State[param_1] == 0) && (EnemyFrameTimer[param_1] == 0)) {
    if (PiranhaPlant_MoveFlag[param_1] == 0) {
      PiranhaPlant_Y_Speed[param_1] *= -1;
      PiranhaPlant_MoveFlag[param_1] = PiranhaPlant_MoveFlag[param_1] + 1;
    }
    bVar3 = PiranhaPlantUpYPos[param_1];
    if (PiranhaPlant_Y_Speed[param_1] >= 0x80) {
      bVar3 = PiranhaPlantDownYPos[param_1];
    }
    if (TimerControl == 0) {
      bVar1 = Enemy_Y_Position[param_1];
      bVar2 = PiranhaPlant_Y_Speed[param_1];
      Enemy_Y_Position[param_1] = bVar1 + bVar2;
      if ((u8)(bVar1 + bVar2) == bVar3) {
        PiranhaPlant_MoveFlag[param_1] = 0;
        EnemyFrameTimer[param_1] = 0x20;
      }
    }
  }
}


// SM2DATA2+SM2DATA4:c4fe
// Signature: [] -> []
void BlowPlayerAround(void) {
  if ((WindFlag != 0) && (AreaType == AREA_GROUND)) {
    const u8 mask = (FrameCounter & 0x80) ? 1 : 3;
    if ((FrameCounter & mask) == 0) {
      Player_PageLoc += Player_X_Position == 0xff;
      Player_X_Scroll += 1;
      Player_X_Position += 1;
    }
  }
}


// SM2DATA2+SM2DATA4:c550
// Signature: [] -> []
void SimulateWind(void) {
  // TODO: bring in LeavesXPos/LeavesYPos,
  // figure out a way to accumulate it

  // static const u8 xpos[12] = {
  //   0x30, 0x30, 0x30, 0x60, 0x60, 0xa0,
  //   0xa0, 0xa0, 0xd0, 0xd0, 0xd0, 0x60,
  // };
  // static const u8 ypos[12] = {
  //   0x30, 0x70, 0xb8, 0x50, 0x98, 0x30,
  //   0x70, 0xb8, 0x50, 0x98, 0x30, 0x70,
  // };

  static const u8 tile[12] = {
    0x7b, 0x7b, 0x7b, 0x7b, 0x7a, 0x7a,
    0x7b, 0x7b, 0x7b, 0x7a, 0x7b, 0x7a,
  };

  static const u8 posadder[12] = {
    0x57, 0x57, 0x56, 0x56, 0x58, 0x58,
    0x56, 0x56, 0x57, 0x58, 0x57, 0x58,
  };

  if (WindFlag == 0) {
    return;
  }

  NoiseSoundQueue = SOUND_NOISE_WIND;

  // Inlined: ModifyLeavesPos
  for (int i = 0; i < 12; i++) {
    // The carry seems like an oversight in the original game,
    // because the intent is to double the adder for the X axis
    // (The disassembly has two ADC instructions in a row)
    const u8 adder = posadder[i];
    LeavesXPos[i] += adder + adder + (((u16)LeavesXPos[i] + (u16)adder) >= 256);
    LeavesYPos[i] += adder;
  }

  u8 sproff = Enemy_SprDataOffset[6];

  for (int i = 0; i < 12; i++) {
    SPRITE_Y(sproff, 0) = LeavesYPos[i];
    SPRITE_TILE(sproff, 0) = tile[i];
    SPRITE_ATTR(sproff, 0) = SPRATTR_FLIPHORZ | 1;
    SPRITE_X(sproff, 0) = LeavesXPos[i];
    sproff += 4;
    if (i+1 == 6) {
      sproff = Alt_SprDataOffset[0];
    }
  }
}


// SM2DATA3:c5fe
// Signature: [] -> []
void ScreenSubsForFinalRoom(void) {
  switch (ScreenRoutineTask) {
  case SRT_W8SMB2J_INITSCREENPALETTE:
    VRAM_Buffer_AddrCtrl = ADDRCTRL_UNDERGROUNDPALETTEDATA;
    ScreenRoutineTask = SRT_W8SMB2J_WRITETOPSTATUSLINE;
    return;

  case SRT_W8SMB2J_WRITETOPSTATUSLINE:
    WriteGameText(0);
    ScreenRoutineTask = SRT_W8SMB2J_WRITEBOTTOMSTATUSLINE;
    return;

  case SRT_W8SMB2J_WRITEBOTTOMSTATUSLINE:
    WriteBottomStatusLine();
    ScreenRoutineTask = SRT_W8SMB2J_DRAWFINALROOM;
    return;

  case SRT_W8SMB2J_DRAWFINALROOM:
    VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_PRINCESSPEACHSROOM;
    IRQUpdateFlag = 0x1b;
    ScreenRoutineTask = SRT_W8SMB2J_GETAREAPALETTE;
    return;

  case SRT_W8SMB2J_GETAREAPALETTE:
    GetAreaPalette();
    ScreenRoutineTask = SRT_W8SMB2J_GETBACKGROUNDCOLOR;
    return;

  case SRT_W8SMB2J_GETBACKGROUNDCOLOR:
    GetBackgroundColor();
    ScreenRoutineTask = SRT_W8SMB2J_REVEALPRINCESS;
    return;

  case SRT_W8SMB2J_REVEALPRINCESS:
    PrintStatusBarNumbers(0xa2);
    SoundEngineJsrOperandHi = 0xcc;
    SoundEngineJsrOperandLo = 0x5f;
    // TODO: replace with named constant once fds sound engine code is implemented
    AreaMusicQueue = 1;
    Left_Right_Buttons = 0;
    NameTableSelect = 0;
    IRQUpdateFlag = 0;
    DisableScreenFlag = 0;
    expect(OperMode == OM_VICTORY);
    expect(OperMode_Task == OMT_VICTORY_W8SMB2J_SCREENSUBSFORFINALROOM);
    OperMode_Task = OMT_VICTORY_W8SMB2J_PRINTVICTORYMSGSFORWORLD8;
    return;

  default:
    jmpengine_overflow(ScreenRoutineTask);
  }
}


// SM2DATA3:c642
// Signature: [] -> []
void PrintVictoryMsgsForWorld8(void) {
  if (SecondaryMsgCounter == 0) {
    if (PrimaryMsgCounter >= 10) {
      WorldEndTimer = 0xc;
      OperMode_Task += 1;
      EraseEndingCounters();
      return;
    }

    if (PrimaryMsgCounter == 2) {
      EventMusicQueue = MUSIC_EVENT_PRINCESS;
    }

    static const u8 addrctrl_lookup[10] = {
      ADDRCTRL_SMB2J_FINALROOMPALETTE,
      ADDRCTRL_SMB2J_THANKYOUMESSAGEFINAL,
      ADDRCTRL_SMB2J_PEACEISPAVED,
      ADDRCTRL_SMB2J_WITHKINGDOMSAVED,
      ADDRCTRL_SMB2J_HURRAH,
      ADDRCTRL_SMB2J_OURONLYHERO,
      ADDRCTRL_SMB2J_THISENDSYOURTRIP,
      ADDRCTRL_SMB2J_OFALONGFRIENDSHIP,
      ADDRCTRL_SMB2J_POINTSADDED,
      ADDRCTRL_SMB2J_FOREACHPLAYERLEFT,
    };

    VRAM_Buffer_AddrCtrl = addrctrl_lookup[PrimaryMsgCounter];
  }

  ADD_UNSIGNED_16_8(PrimaryMsgCounter, SecondaryMsgCounter,
                    4);
}


// SM2DATA3:c67a
// Signature: [] -> []
void EraseEndingCounters(void) {
  EndControlCntr = 0;
  BlueColorOfs = 0;
  BlueDelayFlag = 0;
}


// SM2DATA3:c686
// Signature: [] -> []
void AwardExtraLives(void) {
  if (WorldEndTimer == 0) {
    if (NumberofLives >= 0x80) {
      OperMode_Task += 1;
      EraseEndingCounters();
      return;
    }
    if (SelectTimer == 0) {
      SelectTimer = 0x30;
      Square2SoundQueue = SOUND_SQ2_1UP;
      NumberofLives -= 1;
      DigitModifier[1] = 1;
      EndAreaPoints();
      return;
    }
  }
}


// SM2DATA3:c6ca
// Signature: [] -> []
void FadeToBlue(void) {
  EndControlCntr += 1;

  if (BlueDelayFlag == 0) {
    if (EndControlCntr != 0) {
      return;
    }
    BlueDelayFlag = 1;
  } else if ((EndControlCntr & 0xf) != 0) {
    return;
  }

  const u8 blue_tints[4] = { 0x01, 0x02, 0x11, 0x21 };

  const u8 val = blue_tints[BlueColorOfs];

  const u8 oldoff = VRAM_Buffer1_Offset;

  VRAM_Buffer1_Offset = 0;

  VRAM1_DRAW(PPU_ADDR_PALETTE_BG(0,0),
             val, 0x30, 0x0f, 0x0f,
             val, 0x30, 0x10, 0x00,
             val, 0x21, 0x12, 0x21,
             val, 0x27, 0x17, 0x00);

  VRAM_Buffer1_Offset = oldoff;

  BlueColorOfs += 1;

  if (BlueColorOfs == 4) {
    OperMode_Task += 1;
  }
}


// SM2DATA3:c710
// Signature: [] -> []
void EraseLivesLines(void) {
  // Inlining TwoBlankRows, because it's tightly coupled to the code

  const u8 length = 21;
  const u8 tile = 0x24;

  // Saving and restoring the offset, in case it's not 0
  // TODO: is this ever not 0?
  const u8 saved_vramoff = VRAM_Buffer1_Offset;
  VRAM_Buffer1_Offset = 0;

  VRAM1_DRAW_RLE(PPU_ADDR_NT0_XY(6, 20), length, tile);
  VRAM1_DRAW_RLE(PPU_ADDR_NT0_XY(6, 21), length, tile);

  VRAM_Buffer1_Offset = saved_vramoff;

  OperMode_Task += 1;
  EraseEndingCounters();
  MushroomRetDelay = 0x60;
}


// SM2DATA3:c727
// Signature: [] -> []
void RunMushroomRetainers(void) {
  MushroomRetainersForW8();

  // The "absolute" x coordinate is not put in here, but it's on an odd page (+ 16).
  const u16 mt_x = 16 + 8;
  const u16 mt_y = 3;

  if (get_metatile(mt_x, mt_y) != MT_0) {
    return;
  }

  if (HardWorldFlag == 0) {
    expect(OperMode == OM_VICTORY);
    expect(OperMode_Task == OMT_VICTORY_W8SMB2J_RUNMUSHROOMRETAINERS);
    OperMode_Task = OMT_VICTORY_W8SMB2J_ENDINGDISKROUTINES;
    return;
  }

  BackToNormal();
}


// SM2DATA3:c76a
// Signature: [] -> []
void BackToNormal(void) {
  // Revert "JSR SoundEngine" in the NMI back to the original address
  SoundEngineJsrOperandHi = 0xd2;
  SoundEngineJsrOperandLo = 0xa0;

  DiskIOTask = 0;
  if ((HardWorldFlag == 0) && (CompletedWorlds == 0xff)) {
    CompletedWorlds = 0;
    NumberofLives = 0;
    FantasyW9MsgFlag = 0;
    AreaNumber = 0;
    LevelNumber = 0;
    WorldNumber += 1;
    if (WorldNumber >= 8) {
      WorldNumber = 8;
    }
    LoadAreaPointer();
    FetchNewGameTimerFlag += 1;
    OperMode = OM_GAME;
    OperMode_Task = OMT_GAME_START;
  } else {
    CompletedWorlds = 0;
    OperMode = OM_TITLESCREEN;
    OperMode_Task = OMT_TITLESCREEN_START;
    TitleScreenMode();
  }
}


enum EndingDiskRoutines_jumptable_item {
  ENDINGDISKROUTINES_DISKSCREEN,
  ENDINGDISKROUTINES_UPDATEGAMESBEATEN,
  ENDINGDISKROUTINES_WAITFOREJECT,
  ENDINGDISKROUTINES_WAITFORREINSERT,
  ENDINGDISKROUTINES_RESETDISKVARS,
};


// SM2DATA3:c738
// Signature: [] -> []
void EndingDiskRoutines(void) {
  switch (DiskIOTask) {
  case ENDINGDISKROUTINES_DISKSCREEN:
    DiskScreen();
    return;

  case ENDINGDISKROUTINES_UPDATEGAMESBEATEN:
    UpdateGamesBeaten();
    return;

  case ENDINGDISKROUTINES_WAITFOREJECT:
    WaitForEject();
    return;

  case ENDINGDISKROUTINES_WAITFORREINSERT:
    WaitForReinsert();
    return;

  case ENDINGDISKROUTINES_RESETDISKVARS:
    ResetDiskVars();
    return;

  default:
    jmpengine_overflow(DiskIOTask);
  }
}


// SM2DATA3:c7bd
// Signature: [] -> []
void MushroomRetainersForW8(void) {
  if (MushroomRetDelay != 0) {
    MushroomRetDelay -= 1;
    return;
  }
  MoveSpritesOffscreen();
  if (BlueColorOfs == 7) {
    if (((EndControlCntr & 0x1f) == 0)) {
      BlueDelayFlag += 1;
      if (BlueDelayFlag >= 0xb) {
        BlueDelayFlag = 4;
      }
    }
  } else if ((EndControlCntr & 0x1f) == 0) {
    BlueColorOfs += 1;
    Square2SoundQueue = SOUND_SQ2_COIN;
  }
  const u8 bVar1 = BlueColorOfs;
  EndControlCntr += 1;
  const u8 bStack0000 = WorldNumber;
  do {
    if ((BlueDelayFlag < 4)
        || (FlashMRSpriteDataOfs[(u8)((BlueDelayFlag - 4) - (BlueDelayFlag < 4))] != MRSpriteDataOfs[BlueColorOfs])) {
      Enemy_SprDataOffset[0] = MRSpriteDataOfs[BlueColorOfs];
      Enemy_ID[0] = A_RETAINER;
      Enemy_Y_Position[0] = MRetainerYPos[BlueColorOfs];
      Enemy_Rel_XPos = MRetainerXPos[BlueColorOfs];
      WorldNumber = 0;
      EnemyGfxHandler(0);
    }
  } while (BlueColorOfs -= 1, BlueColorOfs != 0);
  BlueColorOfs = bVar1;
  WorldNumber = bStack0000;
  Enemy_SprDataOffset[0] = 0x30;
  Enemy_Y_Position[0] = 0xb8;
}


// SM2DATA3:c858
// Signature: [] -> []
void WriteNameToVictoryMsg(void) {
  ScreenRoutineTask = SRT_INITSCREEN;
  if (CurrentPlayer == 0) {
    for (int i = 0; i < 5; i++) {
      ThankYouMessageFinal[i + 0xd] = EndPlayerName_Mario[i];
      HurrahMsg[i + 0xe] = EndPlayerName_Mario[i];
    }
  } else {
    for (int i = 0; i < 5; i++) {
      ThankYouMessageFinal[i + 0xd] = EndPlayerName_Luigi[i];
      HurrahMsg[i + 0xe] = EndPlayerName_Luigi[i];
    }
  }
}


// SM2DATA4:c3d6
// Signature: [] -> []
void ChangeHalfwayPages(void) {
  for (int i = 0; i < 8; i++) {
    HalfwayPageNybbles[i] = AtoDHalfwayPages[i];
  }
}
