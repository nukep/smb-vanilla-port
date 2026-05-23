#include "types.h"
#include "vars.h"

enum VictoryModeSubroutines_forW8_jumptable_item {
  VICTORYMODESUBROUTINES_FORW8_BRIDGECOLLAPSE,
  VICTORYMODESUBROUTINES_FORW8_SETUPVICTORYMODE,
  VICTORYMODESUBROUTINES_FORW8_PLAYERVICTORYWALK,
  VICTORYMODESUBROUTINES_FORW8_STARTVMDELAY,
  VICTORYMODESUBROUTINES_FORW8_CONTINUEVMDELAY,
  VICTORYMODESUBROUTINES_FORW8_VICTORYMODEDISKROUTINES,
  VICTORYMODESUBROUTINES_FORW8_SCREENSUBSFORFINALROOM,
  VICTORYMODESUBROUTINES_FORW8_PRINTVICTORYMSGSFORWORLD8,
  VICTORYMODESUBROUTINES_FORW8_ENDCASTLEAWARD,
  VICTORYMODESUBROUTINES_FORW8_AWARDEXTRALIVES,
  VICTORYMODESUBROUTINES_FORW8_FADETOBLUE,
  VICTORYMODESUBROUTINES_FORW8_ERASELIVESLINES,
  VICTORYMODESUBROUTINES_FORW8_RUNMUSHROOMRETAINERS,
  VICTORYMODESUBROUTINES_FORW8_ENDINGDISKROUTINES,
};


// SM2MAIN:n/a
// Signature: [A] -> []
void jumptable_VictoryModeSubroutines_forW8(const byte param_1) {
  switch (param_1) {
  case VICTORYMODESUBROUTINES_FORW8_BRIDGECOLLAPSE:
    BridgeCollapse();
    return;

  case VICTORYMODESUBROUTINES_FORW8_SETUPVICTORYMODE:
    SetupVictoryMode();
    return;

  case VICTORYMODESUBROUTINES_FORW8_PLAYERVICTORYWALK:
    PlayerVictoryWalk();
    return;

  case VICTORYMODESUBROUTINES_FORW8_STARTVMDELAY:
    StartVMDelay();
    return;

  case VICTORYMODESUBROUTINES_FORW8_CONTINUEVMDELAY:
    ContinueVMDelay();
    return;

  case VICTORYMODESUBROUTINES_FORW8_VICTORYMODEDISKROUTINES:
    VictoryModeDiskRoutines();
    return;

  case VICTORYMODESUBROUTINES_FORW8_SCREENSUBSFORFINALROOM:
    ScreenSubsForFinalRoom();
    return;

  case VICTORYMODESUBROUTINES_FORW8_PRINTVICTORYMSGSFORWORLD8:
    PrintVictoryMsgsForWorld8();
    return;

  case VICTORYMODESUBROUTINES_FORW8_ENDCASTLEAWARD:
    EndCastleAward();
    return;

  case VICTORYMODESUBROUTINES_FORW8_AWARDEXTRALIVES:
    AwardExtraLives();
    return;

  case VICTORYMODESUBROUTINES_FORW8_FADETOBLUE:
    FadeToBlue();
    return;

  case VICTORYMODESUBROUTINES_FORW8_ERASELIVESLINES:
    EraseLivesLines();
    return;

  case VICTORYMODESUBROUTINES_FORW8_RUNMUSHROOMRETAINERS:
    RunMushroomRetainers();
    return;

  case VICTORYMODESUBROUTINES_FORW8_ENDINGDISKROUTINES:
    EndingDiskRoutines();
    return;

  default:
    jmpengine_overflow(param_1);
  }
}


// SM2MAIN:632a
// Signature: [] -> []
void DrawTitleScreen(void) {
  if (OperMode == 0) {
    VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_TITLESCREENGFXDATA;
    ScreenRoutineTask = ScreenRoutineTask + 1;
  } else {
    OperMode_Task = OperMode_Task + 1;
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
  OperMode_Task += 1;
}


// SM2MAIN:63af
// Signature: [] -> []
void EndCastleAward(void) {
  if (WorldEndTimer < 6) {
    AwardTimerCastle();
    if ((byte)(GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2]) == 0) {
      SelectTimer = 0x30;
      WorldEndTimer = 6;
      OperMode_Task += 1;
    }
  }
}


// SM2MAIN:64f6
// Signature: [] -> []
void InitScreenPalette(void) {
  VRAM_Buffer_AddrCtrl = ADDRCTRL_UNDERGROUNDPALETTEDATA;
  ScreenRoutineTask = ScreenRoutineTask + 1;
}


// SM2MAIN:671b
// Signature: [A] -> []
void WriteGameText(const byte param_1) {
  byte offset = GameTextOffsets[param_1];

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


// SM2MAIN:675e
// Signature: [A] -> []
void WriteWarpZoneMessage(const byte warp_zone_control) {
  // "Welcome to warp zone!"

  VRAM_Buffer1_Offset = 0;

  int i;
  for (i = 0; i < 256; i++) {
    const u8 val = WarpZone[i];
    VRAM_Buffer1[i] = val;
    if (val == 0) {
      break;
    }
  }

  assert_smb_crashbug(i < 256, "An infinite loop would've occurred in the original game");

  // Note: The original game would set the offset to a hard-coded value after the loop (36).
  // Here we're just setting it to the actual length of the data.
  VRAM_Buffer1_Offset = i;

  // Bit 7 is always set, so toggle it.
  const u8 idx = warp_zone_control ^ 0x80;
  VRAM_Buffer1[27] = WarpZoneNumbers[idx];
}


static inline byte ScrollLockObject_Warp_impl(void) {
  if (HardWorldFlag != 0) {
    // 121 = 0x100 - 0x87
    if (LevelNumber != 121) {
      return 0x87 + LevelNumber;
    }

    // NES note: Getting to this point would be a glitch in the original game.
    // The BNE instruction is meant to be unconditional.

    // The disassembly shows:
    //   LDA #$87
    //   CLC
    //   ADC LevelNumber
    //   BNE DumpWarpCtrl
  }

  if (HardWorldFlag == 0 && WorldNumber == 0) {
    if (AreaType == 1) {
      return 0x81;
    }

    if (AreaAddrsLOffset == 0) {
      return 0x80;
    }

    return 0x82;
  }

  if (WorldNumber == 2) {
    return 0x83;
  }

  if (WorldNumber == 4) {
    if (AreaAddrsLOffset == 0xb) {
      return 0x84;
    }

    if (AreaType != 1) {
      return 0x85;
    }

    return 0x86;
  }

  return 0x87;
}

// SM2MAIN:7513
// Signature: [] -> []
void ScrollLockObject_Warp(void) {
  WarpZoneControl = ScrollLockObject_Warp_impl();
  WriteWarpZoneMessage(WarpZoneControl);
  KillEnemies(0xd);
  ScrollLockObject();
}


// SM2MAIN:75cf
// Signature: [X] -> []
void CloudLedge(const byte param_1) {
  const struct_ycr07 sVar2 = ChkLrgObjLength(param_1);
  const byte bVar1 = sVar2.r07;
  if (sVar2.c) {
    MushroomLedgeHalfLen[param_1] = AreaObjectLength[param_1] >> 1;
    NoUnder(0x8a, bVar1);
  } else if (AreaObjectLength[param_1] == 0) {
    NoUnder(0x8c, bVar1);
  } else {
    MetatileBuffer[bVar1] = 0x8b;
  }
}


// SM2MAIN:89a1
// Signature: [X] -> []
void PoisonMushBlock(const byte param_1) {
  PowerUpType = 4;
  SetupPowerUp(param_1);
}


// SM2MAIN:a64e
// Signature: [X] -> [A]
byte SetBounce(const byte param_1) {
  PlayerSpriteVarData2[0] = 0xfa;
  const byte bVar1 = Enemy_ID[param_1];
  if ((bVar1 == 0xf) || (bVar1 == 0x10)) {
    PlayerSpriteVarData2[0] = 0xf8;
  }
  return bVar1;
}


// SM2MAIN:aca3
// Signature: [X] -> []
void ChkToStunEnemies(const byte param_1) {
  // The port inlines NoDemote, because it more clearly reveals what's actually going on here.
  // The NES implementation did a bunch of compares to hoan in on the object types,
  // but it's more obvious to just do the comparisons directly.

  if (Enemy_ID[param_1] == 6 || Enemy_ID[param_1] == 0x2e) {
    SetStun2(param_1);
    return;
  }

  // Turn these enemies into koopas
  if (Enemy_ID[param_1] == 9)  { Enemy_ID[param_1] = 1; }
  if (Enemy_ID[param_1] == 14) { Enemy_ID[param_1] = 0; }
  if (Enemy_ID[param_1] == 15) { Enemy_ID[param_1] = 1; }
  if (Enemy_ID[param_1] == 16) { Enemy_ID[param_1] = 0; }

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
  byte bVar1;
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
  Hidden1UpFlag = Hidden1UpFlag + 1;
  FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
  OperMode = OperMode + 1;
  DiskIOTask = 0;
  OperMode_Task = 0;
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
  byte bVar1;
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
  ResetDiskIOTask();
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

  if (WorldNumber < 4) {
    ResetDiskIOTask();
    return;
  }
  if (FileListNumber != 0) {
    ResetDiskIOTask();
    return;
  }
  FileListNumber = 1;
  const struct_ayz sVar3 = LoadFiles();
  byte bVar1 = sVar3.a;
  if (sVar3.z) {
    bVar2 = CheckFileCount(sVar3.y);
    if (bVar2) {
      ResetDiskIOTask();
      return;
    }
    bVar1 = 0x40;
  }
  DiskIOTask += 1;
  DiskErrorHandler(bVar1);
}


// SM2MAIN:c078
// Signature: [] -> []
void ResetDiskIOTask(void) {
  DiskIOTask = 0;
  VMDelay();
}


// SM2MAIN:c07d
// Signature: [] -> []
void VMDelay(void) {
  OperMode_Task = OperMode_Task + 1;
}


// SM2MAIN:c081
// Signature: [] -> []
void StartVMDelay(void) {
  WorldEndTimer = 0x10;
  VMDelay();
}


// SM2MAIN:c088
// Signature: [] -> []
void ContinueVMDelay(void) {
  if (WorldEndTimer == 0) {
    VMDelay();
  }
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
    ResetDiskIOTask();
    WriteNameToVictoryMsg();
  } else {
    DiskIOTask += 1;
    DiskErrorHandler(sVar2.a);
  }
}


// SM2MAIN:c0ca
// Signature: [Y] -> [Z]
bool CheckFileCount(const byte param_1) { return param_1 == FileCount[FileListNumber]; }


// SM2MAIN:c113
// Signature: [] -> []
void DiskScreen(void) {
  Mirror_PPU_CTRL_REG2 = 0;
  ppumask(0);
  DisableScreenFlag = DisableScreenFlag + 1;
  VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_DISKSCREENPALETTE;
  DiskIOTask = DiskIOTask + 1;
}


// SM2MAIN:c126
// Signature: [] -> []
void WaitForEject(void) {
  NameTableSelect = 0;
  DisableScreenFlag = 0;
  const byte bVar1 = FDS_drive_status();
  if ((bVar1 & 1) != 0) {
    DiskIOTask += 1;
  }
}


// SM2MAIN:c138
// Signature: [] -> []
void WaitForReinsert(void) {
  const byte bVar1 = FDS_drive_status();
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
void DiskErrorHandler(const byte param_1) {
  DiskErrorMainMsg[19] = param_1 & 0xf;
  DiskErrorMainMsg[18] = param_1 >> 4;

  byte bVar1;
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

    SPRITE_TILE(0, 0) = GameOverCursorData[0];
    SPRITE_ATTR(0, 0) = GameOverCursorData[1];
    SPRITE_X(0, 0)    = GameOverCursorData[2];
    SPRITE_Y(0, 0)    = GameOverCursorY[ContinueMenuSelect];
    return;
  }
  if (ContinueMenuSelect != 0) {
    CompletedWorlds = 0;
    TerminateGame();
    return;
  }
  NumberofLives = 2;
  LevelNumber = ContinueMenuSelect;
  AreaNumber = ContinueMenuSelect;
  CoinTally = ContinueMenuSelect;
  for (int i = 0; i < 12; i++) {
    PlayerScoreDisplay_Or_ScoreAndCoinDisplay[i] = 0;
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

  for (int i = 0; i < 7; i++) {
    JumpMForceData[i] = JumpMForceData_Mario[i];
  }
  for (int i = 0; i < 7; i++) {
    FallMForceData[i] = FallMForceData_Mario[i];
  }
  for (int i = 0; i < 3; i++) {
    FrictionData[i] = FrictionData_Mario[i];
  }
}

static void LoadLuigiPhysics(void) {
  // The original game modifies an instruction to "RTS" (early-returns from that subroutine)
  PhysicsInstructionOpcode = 0x60;

  for (int i = 0; i < 7; i++) {
    JumpMForceData[i] = JumpMForceData_Luigi[i];
  }
  for (int i = 0; i < 7; i++) {
    FallMForceData[i] = FallMForceData_Luigi[i];
  }
  for (int i = 0; i < 3; i++) {
    FrictionData[i] = FrictionData_Luigi[i];
  }
}


// SM2MAIN:c5ff
// Signature: [] -> []
void PatchPlayerNamePal(void) {
  const byte off = PlayerNameOffsets[CurrentPlayer];
  for (int i = 0; i < 5; i++) {
    const byte j = (byte)(off-4 + i);
    TopStatusBarLine[i + 3] = PlayerNameData[j];
    ThankYouMessage[i + 13] = PlayerNameData[j];
  }

  for (int i = 0; i < 4; i++) {
    const byte j = (byte)(off-4-CurrentPlayer + i);
    PlayerColors[i] = PlayerPaletteData[j];
  }
}


// SM2DATA2+SM2DATA4:c470
// Signature: [X] -> []
void UpsideDownPipe_High(const byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar4;
  struct_xc sVar6;

  byte bStack0000 = 1;
  const struct_yr06r07 sVar7 = GetPipeHeight(param_1);
  const byte bVar3 = sVar7.r06;
  byte bVar5 = bStack0000;
  bStack0000 = sVar7.y;
  if (AreaObjectLength[param_1] != 0) {
    sVar6 = FindEmptyEnemySlot();
    bVar4 = sVar6.x;
    if (!sVar6.c) {
      SetupPiranhaPlant(4, bVar4, bVar5);
      cVar1 = bVar3 * 0x10 + Enemy_Y_Position[bVar4];
      bVar2 = cVar1 - 10;
      Enemy_Y_Position[bVar4] = bVar2;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar4] = bVar2;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[bVar4] = cVar1 + 0xe;
      SpriteVarData2[bVar4] = SpriteVarData2[bVar4] + 1;
    }
  }
  bVar5 = RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar5, bVar3 - 1);
  MetatileBuffer[bVar5] = VerticalPipeData[bStack0000];
}


// SM2DATA2+SM2DATA4:c475
// Signature: [X] -> []
void UpsideDownPipe_Low(const byte param_1) {
  char cVar1;
  byte bVar2;
  byte bVar4;
  struct_xc sVar7;

  byte bStack0000 = 4;
  const struct_yr06r07 sVar6 = GetPipeHeight(param_1);
  const byte bVar3 = sVar6.r06;
  byte bVar5 = bStack0000;
  bStack0000 = sVar6.y;
  if (AreaObjectLength[param_1] != 0) {
    sVar7 = FindEmptyEnemySlot();
    bVar4 = sVar7.x;
    if (!sVar7.c) {
      SetupPiranhaPlant(4, bVar4, bVar5);
      cVar1 = bVar3 * 0x10 + Enemy_Y_Position[bVar4];
      bVar2 = cVar1 - 10;
      Enemy_Y_Position[bVar4] = bVar2;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar4] = bVar2;
      BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[bVar4] = cVar1 + 0xe;
      SpriteVarData2[bVar4] = SpriteVarData2[bVar4] + 1;
    }
  }
  bVar5 = RenderUnderPart(VerticalPipeData[bStack0000 + 2], bVar5, bVar3 - 1);
  MetatileBuffer[bVar5] = VerticalPipeData[bStack0000];
}


// SM2DATA2+SM2DATA4:c4c0
// Signature: [X] -> []
void MoveUpsideDownPiranhaP(const byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  if ((Enemy_State[param_1] == 0) && (EnemyFrameTimer[param_1] == 0)) {
    if (SpriteVarData2[param_1] == 0) {
      SpriteVarData1[param_1] = NEGATE(SpriteVarData1[param_1]);
      SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
    }
    bVar3 = BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1];
    if (SpriteVarData1[param_1] >= 0x80) {
      bVar3 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    }
    if (TimerControl == 0) {
      bVar1 = Enemy_Y_Position[param_1];
      bVar2 = SpriteVarData1[param_1];
      Enemy_Y_Position[param_1] = bVar1 + bVar2;
      if ((byte)(bVar1 + bVar2) == bVar3) {
        SpriteVarData2[param_1] = 0;
        EnemyFrameTimer[param_1] = 0x20;
      }
    }
  }
}


// SM2DATA2+SM2DATA4:c4fe
// Signature: [] -> []
void BlowPlayerAround(void) {
  if ((WindFlag != 0) && (AreaType == 1)) {
    const byte mask = (FrameCounter & 0x80) ? 1 : 3;
    if ((FrameCounter & mask) == 0) {
      SprObject_PageLoc[0] += SprObject_X_Position[0] == 0xff;
      Player_X_Scroll += 1;
      SprObject_X_Position[0] = SprObject_X_Position[0] + 1;
    }
  }
}


// SM2DATA2+SM2DATA4:c550
// Signature: [] -> []
void SimulateWind(void) {
  byte bVar1;
  byte bVar2;

  if (WindFlag != 0) {
    NoiseSoundQueue = 4;
    ModifyLeavesPos();
    bVar1 = 0;
    bVar2 = Enemy_SprDataOffset[6];
    do {
      SPRITE_Y(bVar2, 0) = LeavesYPos[bVar1];
      SPRITE_TILE(bVar2, 0) = LeavesTile[bVar1];
      SPRITE_ATTR(bVar2, 0) = 0x41;
      SPRITE_X(bVar2, 0) = LeavesXPos[bVar1];
      bVar1 += 1;
      bVar2 = bVar2 + 4;
      if (bVar1 == 6) {
        bVar2 = AltOrBlock_SprDataOffset[0];
      }
    } while (bVar1 != 0xc);
  }
}


// SM2DATA2+SM2DATA4:c5a1
// Signature: [] -> []
void ModifyLeavesPos(void) {
  for (int i = 0; i < 12; i++) {
    // The carry seems like an oversight in the original game,
    // because the intent is to double the adder for the X axis
    // (The disassembly has two ADC instructions in a row)
    const byte adder = LeavesPosAdder[i];
    LeavesXPos[i] += adder + adder + CARRY1(LeavesXPos[i], adder);
    LeavesYPos[i] += adder;
  }
}


// SM2DATA2+SM2DATA4:c5be
// Signature: [] -> []
void WindOn(void) {
  WindFlag = 1;
}


// SM2DATA2+SM2DATA4:c5c2
// Signature: [] -> []
void WindOff(void) {
  WindFlag = 0;
}


enum ScreenSubsForFinalRoom_jumptable_item {
  SCREENSUBSFORFINALROOM_INITSCREENPALETTE,
  SCREENSUBSFORFINALROOM_WRITETOPSTATUSLINE,
  SCREENSUBSFORFINALROOM_WRITEBOTTOMSTATUSLINE,
  SCREENSUBSFORFINALROOM_DRAWFINALROOM,
  SCREENSUBSFORFINALROOM_GETAREAPALETTE,
  SCREENSUBSFORFINALROOM_GETBACKGROUNDCOLOR,
  SCREENSUBSFORFINALROOM_REVEALPRINCESS,
};


// SM2DATA3:c5fe
// Signature: [] -> []
void ScreenSubsForFinalRoom(void) {
  switch (ScreenRoutineTask) {
  case SCREENSUBSFORFINALROOM_INITSCREENPALETTE:
    InitScreenPalette();
    return;

  case SCREENSUBSFORFINALROOM_WRITETOPSTATUSLINE:
    WriteTopStatusLine();
    return;

  case SCREENSUBSFORFINALROOM_WRITEBOTTOMSTATUSLINE:
    WriteBottomStatusLine();
    return;

  case SCREENSUBSFORFINALROOM_DRAWFINALROOM:
    DrawFinalRoom();
    return;

  case SCREENSUBSFORFINALROOM_GETAREAPALETTE:
    GetAreaPalette();
    return;

  case SCREENSUBSFORFINALROOM_GETBACKGROUNDCOLOR:
    GetBackgroundColor();
    return;

  case SCREENSUBSFORFINALROOM_REVEALPRINCESS:
    RevealPrincess();
    return;

  default:
    jmpengine_overflow(ScreenRoutineTask);
  }
}


// SM2DATA3:c612
// Signature: [] -> []
void DrawFinalRoom(void) {
  VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_PRINCESSPEACHSROOM;
  IRQUpdateFlag = 0x1b;
  ScreenRoutineTask = ScreenRoutineTask + 1;
}


// SM2DATA3:c61e
// Signature: [] -> []
void RevealPrincess(void) {
  PrintStatusBarNumbers(0xa2);
  RAM(0x611d) = 0x5f;
  AreaMusicQueue = 1;
  Left_Right_Buttons = 0;
  NameTableSelect = 0;
  IRQUpdateFlag = 0;
  DisableScreenFlag = 0;
  OperMode_Task = OperMode_Task + 1;
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
      EventMusicQueue = 4;
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
      Square2SoundQueue = 0x40;
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

  for (int i = 0; i < 20; i++) {
    VRAM_Buffer1[i] = BlueTransPalette[i];
  }

  const u8 val = BlueTints[BlueColorOfs];

  VRAM_Buffer1[3 + 0] = val;
  VRAM_Buffer1[3 + 4] = val;
  VRAM_Buffer1[3 + 8] = val;
  VRAM_Buffer1[3 + 12] = val;

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
  if (Block_Buffers[BLOCK_BUFFER_2_OFFSET + 0x38] == 0) {
    if (HardWorldFlag != 0) {
      RAM(0x611d) = 0xa0;
      DiskIOTask = 0;
      OperMode_Task = 0;
      if ((HardWorldFlag == 0) && (CompletedWorlds == 0xff)) {
        CompletedWorlds = 0;
        NumberofLives = 0;
        FantasyW9MsgFlag = 0;
        AreaNumber = 0;
        LevelNumber = 0;
        OperMode_Task = 0;
        WorldNumber += 1;
        if (WorldNumber >= 8) {
          WorldNumber = 8;
        }
        LoadAreaPointer();
        FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
        OperMode = 1;
        return;
      }
      CompletedWorlds = 0;
      OperMode = 0;
      TitleScreenMode();
      return;
    }
    OperMode_Task += 1;
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
    MushroomRetDelay = MushroomRetDelay - 1;
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
    Square2SoundQueue = 1;
  }
  const byte bVar1 = BlueColorOfs;
  EndControlCntr += 1;
  const byte bStack0000 = WorldNumber;
  do {
    if ((BlueDelayFlag < 4)
        || (FlashMRSpriteDataOfs[(byte)((BlueDelayFlag - 4) - (BlueDelayFlag < 4))] != MRSpriteDataOfs[BlueColorOfs])) {
      Enemy_SprDataOffset[0] = MRSpriteDataOfs[BlueColorOfs];
      Enemy_ID[0] = 0x35;
      Enemy_Y_Position[0] = MRetainerYPos[BlueColorOfs];
      Enemy_Rel_XPos = MRetainerXPos[BlueColorOfs];
      WorldNumber = 0;
      ObjectOffset = 0;
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
  ScreenRoutineTask = 0;
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


// SM2DATA4:c2c3
// Signature: [] -> []
void AltHard_GetAreaDataAddrs(void) {
  // Inlined: GetAreaType
  const byte area_type = (AreaPointer & 0x60) >> 5;
  const byte loffset = AreaPointer & 0x1f;
  AreaType = area_type;
  AreaAddrsLOffset = loffset;

  {
    const byte off = AltHard_EnemyAddrHOffsets[area_type] + loffset;
    const byte lo = AltHard_EnemyDataAddrs[(byte)(off * 2)];
    const byte hi = AltHard_EnemyDataAddrs[(byte)(off * 2) + 1];
    const u16 addr = (hi << 8) | lo;
    STORE_16(EnemyData_addr_hi, EnemyData_addr_lo, addr);
    EnemyData = rom_ptr(addr);
  }

  {
    const byte off = (AltHard_AreaDataHOffsets[area_type] + loffset) * 2;
    const byte lo = AltHard_AreaDataAddrs[off];
    const byte hi = AltHard_AreaDataAddrs[off + 1];
    const u16 addr = (hi << 8) | lo;
    STORE_16(AreaData_addr_hi, AreaData_addr_lo, addr);
    AreaData = rom_ptr(addr);
  }

  const byte area_data_0 = AreaData[0];
  // gg ppp fff

  const byte area_data_1 = AreaData[1];
  // aa bb tttt

  const byte gg = area_data_0 >> 6;
  const byte ppp = (area_data_0 & 0x38) >> 3;
  const byte fff = area_data_0 & 7;

  if (fff >= 4) {
    ForegroundScenery = 0;
    BackgroundColorCtrl = fff;
  } else {
    ForegroundScenery = fff;
  }
  PlayerEntranceCtrl = ppp;
  GameTimerSetting = gg;

  const byte aa = area_data_1 >> 6;
  const byte bb = (area_data_1 & 0x30) >> 4;
  const byte tttt = area_data_1 & 0xf;

  TerrainControl = tttt;
  BackgroundScenery = bb;
  AreaStyle = aa;
  if (aa == 3) {
    AreaStyle = 0;
    CloudTypeOverride = 3;
  } else {
    AreaStyle = aa;
  }

  ADD_UNSIGNED_16_8(AreaData_addr_hi, AreaData_addr_lo,
                    2);
  AreaData += 2;
}


// SM2DATA4:c3d6
// Signature: [] -> []
void ChangeHalfwayPages(void) {
  for (int i = 0; i < 8; i++) {
    HalfwayPageNybbles[i] = AtoDHalfwayPages[i];
  }
}
