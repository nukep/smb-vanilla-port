#include "types.h"
#include "vars.h"

static inline u16 MTX_MTY_TO_BLOCKOFF(const u16 mt_x, const u16 mt_y) {
  return get_block_buffer_offset(mt_x % 32) + mt_y * 16;
}

static inline u8 MTY_TO_R02(const u16 mt_y) {
  return mt_y * 16;
}

static inline u8 MTX_TO_R06(const u16 mt_x) {
  return get_block_buffer_offset(mt_x % 32) & 0xff;
}

static inline u8 R02_TO_MTY(const u8 r02) {
  return r02 / 16;
}

static inline u16 R06_TO_MTX_lossy(const u8 r06) {
  if (r06 < BLOCK_BUFFER_2_OFFSET) {
    return r06;
  } else {
    return 16 + r06 - BLOCK_BUFFER_2_OFFSET;
  }
}


// SMB:8325
// SM2MAIN:c51b
// Signature: [] -> []
void DrawMushroomIcon(void) {
  // This is called DrawMenuCursor in the SMB2J disassembly.

#ifdef SMB1_MODE
  for (int i = 0; i < 8; i++) {
    VRAM_Page[i] = MushroomIconData[i];
  }
  if (NumberOfPlayers != 0) {
    VRAM_Buffer1[3] = 0x24;
    VRAM_Buffer1[5] = 0xce;
  }
#endif
#ifdef SMB2J_MODE
  VRAM_Buffer_AddrCtrl = ADDRCTRL_SMB2J_MENUCURSORTEMPLATE;
  // Inlined: SetupMenuCursor
  MenuCursorTemplate[3] = MenuCursorTiles[CurrentPlayer];
  MenuCursorTemplate[5] = MenuCursorTiles[CurrentPlayer + 1];
#endif
}


static inline void GameMenuRoutine_ResetTitle() {
  OperMode = 0;
  OperMode_Task = 0;
#ifdef SMB1_MODE
  Sprite0HitDetectFlag = 0;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag = 0;
#endif
  DisableScreenFlag = DisableScreenFlag + 1;
}

#ifdef SMB1_MODE
// SMB:830e
// Signature: [A] -> [X]
static inline byte GoContinue(const byte param_1) {
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
  const byte buttons = SavedJoypadBits[0] | SavedJoypadBits[1];
#endif
#ifdef SMB2J_MODE
  const byte buttons = SavedJoypadBits[0];
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
    if (GameEngineSubroutine == 6) {
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
    OperMode += 1;
    PrimaryHardMode = WorldSelectEnableFlag;
    OperMode_Task = 0;
    DemoTimer = 0;
    for (int i = 0; i < 12*2; i++) {
      PlayerScoreDisplay_Or_ScoreAndCoinDisplay[i] = 0;
    }
#endif
#ifdef SMB2J_MODE
    CompletedWorlds = 0;
    DiskIOTask = 0;
    HardWorldFlag = ((GamesBeatenCount >= 8) && button_a_pushed) ? 1 : 0;

    OperMode_Task += 1;
    PatchPlayerNamePal();
    WorldNumber = 0;
    LevelNumber = 0;
    AreaNumber = 0;
    for (int i = 0; i < 12; i++) {
      PlayerScoreDisplay_Or_ScoreAndCoinDisplay[i] = 0;
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
      for (int i = 0; i < 6; i++) {
        VRAM_Page[i] = WSelectBufferTemplate[i];
      }
      VRAM_Page[4] = WorldNumber + 1;
    }
  }
#endif

  SavedJoypadBits[0] = 0;

  GameCoreRoutine();
  if (GameEngineSubroutine == 6) {
    GameMenuRoutine_ResetTitle();
  }
}


// SMB:8182
// SM2MAIN:61e9
// Signature: [] -> []
void PauseRoutine(void) {
  if ((OperMode == 2) || ((OperMode == 1 && (OperMode_Task == ssw(3, 4))))) {
    if (GamePauseTimer != 0) {
      GamePauseTimer = GamePauseTimer - 1;
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

    if (PlayerOrSprDataOffset[i] >= 0x28) {
      int amount = (int)PlayerOrSprDataOffset[i] + (int)SprShuffleAmt[SprShuffleAmtOffset];
      if (amount >= 256) {
        amount = (amount % 256) + 40;
      }
      PlayerOrSprDataOffset[i] = (byte)amount;
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


enum OperModeExecutionTree_jumptable_item {
  OPERMODEEXECUTIONTREE_TITLESCREENMODE,
  OPERMODEEXECUTIONTREE_GAMEMODE,
  OPERMODEEXECUTIONTREE_VICTORYMODE,
  OPERMODEEXECUTIONTREE_GAMEOVERMODE,
};


// SMB:8212
// SM2MAIN:6279
// Signature: [] -> []
void OperModeExecutionTree(void) {
  switch (OperMode) {
  case OPERMODEEXECUTIONTREE_TITLESCREENMODE:
    TitleScreenMode();
    return;

  case OPERMODEEXECUTIONTREE_GAMEMODE:
    GameMode();
    return;

  case OPERMODEEXECUTIONTREE_VICTORYMODE:
    VictoryMode();
    return;

  case OPERMODEEXECUTIONTREE_GAMEOVERMODE:
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


enum TitleScreenMode_jumptable_item {
#ifdef SMB2J_MODE
  TITLESCREENMODE_ATTRACTMODEDISKROUTINES,
#endif
  TITLESCREENMODE_INITIALIZEGAME,
  TITLESCREENMODE_SCREENROUTINES,
  TITLESCREENMODE_PRIMARYGAMESETUP,
  TITLESCREENMODE_GAMEMENUROUTINE,
#ifdef SMB2J_MODE
  TITLESCREENMODE_HARDWORLDSCHECKPOINT,
#endif
};


// SMB:8231
// SM2MAIN:bfb0
// Signature: [] -> []
void TitleScreenMode(void) {
  // Note: In the SMB2J disassembly, this is called "AttractModeSubs".
  // We consolidated it into SMB1's "TitleScreenMode" for clarity.

  switch (OperMode_Task) {
  case TITLESCREENMODE_INITIALIZEGAME:
    InitializeGame();
    return;

  case TITLESCREENMODE_SCREENROUTINES:
    ScreenRoutines();
    return;

  case TITLESCREENMODE_PRIMARYGAMESETUP:
    PrimaryGameSetup();
    return;

  case TITLESCREENMODE_GAMEMENUROUTINE:
    GameMenuRoutine();
    return;

#ifdef SMB2J_MODE
  case TITLESCREENMODE_ATTRACTMODEDISKROUTINES:
    AttractModeDiskRoutines();
    return;

  case TITLESCREENMODE_HARDWORLDSCHECKPOINT:
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
  DemoActionTimer = DemoActionTimer - 1;
  SavedJoypadBits[0] = DemoActionData[DemoAction - 1];
  return false;
}

// SMB:838b
// SM2MAIN:6298
// Signature: [] -> []
void VictoryMode(void) {
  VictoryModeSubroutines();
  if (OperMode_Task != 0) {
    if (SMB2J_ONLY && (WorldNumber == 7) && (OperMode_Task == 5 || OperMode_Task == 0xd)) {
      return;
    }
    ObjectOffset = 0;
    EnemiesAndLoopsCore(0);
  }
  RelativePlayerPosition();
  PlayerGfxHandler();
}


enum VictoryModeSubroutines_jumptable_item {
  VICTORYMODESUBROUTINES_BRIDGECOLLAPSE,
  VICTORYMODESUBROUTINES_SETUPVICTORYMODE,
  VICTORYMODESUBROUTINES_PLAYERVICTORYWALK,
  VICTORYMODESUBROUTINES_PRINTVICTORYMESSAGES,
#ifdef SMB2J_MODE
  VICTORYMODESUBROUTINES_ENDCASTLEAWARD,
#endif
  VICTORYMODESUBROUTINES_PLAYERENDWORLD,
};


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
  case VICTORYMODESUBROUTINES_BRIDGECOLLAPSE:
    BridgeCollapse();
    return;

  case VICTORYMODESUBROUTINES_SETUPVICTORYMODE:
    SetupVictoryMode();
    return;

  case VICTORYMODESUBROUTINES_PLAYERVICTORYWALK:
    PlayerVictoryWalk();
    return;

  case VICTORYMODESUBROUTINES_PRINTVICTORYMESSAGES:
    PrintVictoryMessages();
    return;

  case VICTORYMODESUBROUTINES_PLAYERENDWORLD:
    PlayerEndWorld();
    return;

#ifdef SMB2J_MODE
  case VICTORYMODESUBROUTINES_ENDCASTLEAWARD:
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
    CompletedWorlds = WorldBits[WorldNumber] | CompletedWorlds;
    if ((HardWorldFlag != 0) && (WorldNumber > 2)) {
      WorldNumber = 7;
    }
  #endif
  EventMusicQueue = 8;
  OperMode_Task = OperMode_Task + 1;
}


// SMB:83bd
// SM2MAIN:6334
// Signature: [] -> []
void PlayerVictoryWalk(void) {
  if ((SprObject_PageLoc[0] == VictoryDestPageLoc) && (SprObject_X_Position[0] >= 0x60)) {
    // Stop walking
    VictoryWalkControl = 0;
    AutoControlPlayer(0);
  } else {
    // Keep going right
    VictoryWalkControl = 1;
    AutoControlPlayer(1);
  }

  if (ScreenEdgeOrLeft_PageLoc[0] != VictoryDestPageLoc) {
    const bool bVar1 = ScrollFractional >= 0x80;
    ScrollFractional = ScrollFractional + 0x80;
    ScrollScreen(bVar1 + 1);
    UpdScrollVar();
    VictoryWalkControl += 1;
  }
  if (VictoryWalkControl == 0) {
    OperMode_Task = OperMode_Task + 1;
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
    OperMode_Task = 0;
    WorldNumber += 1;
    if (SMB2J_ONLY && WorldNumber >= 8) {
      WorldNumber = 8;
    }
    LoadAreaPointer();
    FetchNewGameTimerFlag += 1;
    OperMode = 1;
  }
}


// SMB:84c3
// SM2MAIN:6421
// Signature: [X] -> [X]
byte FloateyNumbersRoutine(const byte param_1) {
  if (FloateyNum_Control[param_1] == 0) {
    return param_1;
  }

  byte bVar2 = FloateyNum_Control[param_1];
  if (bVar2 >= 0xb) {
    bVar2 = 0xb;
  }
  FloateyNum_Control[param_1] = bVar2;

  const byte timer = FloateyNum_Timer[param_1];
  if (timer == 0) {
    FloateyNum_Control[param_1] = 0;
    return param_1;
  }
  FloateyNum_Timer[param_1] -= 1;

  byte tmp1 = param_1;

  if (timer == 0x2b) {
    if (bVar2 == 0xb) {
      NumberofLives += 1;
      Square2SoundQueue = 0x40;
    }
    DigitModifier[ScoreUpdateData[bVar2] >> 4] = ScoreUpdateData[bVar2] & 0xf;
    AddToScore();
    tmp1 = ObjectOffset;
  }

  const byte enemy_id = Enemy_ID[tmp1];

  bool cond = false;

  if ((enemy_id != 0x12) && (enemy_id != 0xd)) {
    if (enemy_id == 5) {
      cond = true;
    } else if ((enemy_id != 10) && (enemy_id != 0xb)) {
      if (enemy_id > 8) {
        cond = true;
      } else if (Enemy_State[tmp1] < 2) {
        cond = true;
      }
    }
  }

  const byte offset = cond ? AltOrBlock_SprDataOffset[SprDataOffset_Ctrl] : Enemy_SprDataOffset[tmp1];
  const byte tmp2 = cond ? ObjectOffset : tmp1;

  const byte ypos = FloateyNum_Y_Pos[tmp2];
  if (ypos >= 0x18) {
    FloateyNum_Y_Pos[tmp2] -= 1;
  }

  // Inlined: DumpTwoSpr
  SPRITE_Y(offset, 0) = ypos - 9;
  SPRITE_Y(offset, 1) = ypos - 9;

  const byte xpos = FloateyNum_X_Pos[tmp2];
  SPRITE_X(offset, 0) = xpos;
  SPRITE_X(offset, 1) = xpos + 8;
  SPRITE_ATTR(offset, 0) = 2;
  SPRITE_ATTR(offset, 1) = 2;

  const byte ctrl = FloateyNum_Control[tmp2];
  SPRITE_TILE(offset, 0) = FloateyNumTileData[(byte)(ctrl << 1)];
  SPRITE_TILE(offset, 1) = FloateyNumTileData[(byte)(ctrl << 1) + 1];

  return ObjectOffset;
}


enum ScreenRoutines_jumptable_item {
  SCREENROUTINES_INITSCREEN,
  SCREENROUTINES_SETUPINTERMEDIATE,
  SCREENROUTINES_WRITETOPSTATUSLINE,
  SCREENROUTINES_WRITEBOTTOMSTATUSLINE,
  SCREENROUTINES_DISPLAYTIMEUP,
  SCREENROUTINES_RESETSPRITESANDSCREENTIMER_1,
  SCREENROUTINES_DISPLAYINTERMEDIATE,
#ifdef SMB2J_MODE
  SCREENROUTINES_DEMORESET,
#endif
  SCREENROUTINES_RESETSPRITESANDSCREENTIMER_2,
  SCREENROUTINES_AREAPARSERTASKCONTROL,
  SCREENROUTINES_GETAREAPALETTE,
  SCREENROUTINES_GETBACKGROUNDCOLOR,
  SCREENROUTINES_GETALTERNATEPALETTE1,
  SCREENROUTINES_DRAWTITLESCREEN,
  SCREENROUTINES_CLEARBUFFERSDRAWICON,
  SCREENROUTINES_WRITETOPSCORE,
};


// SMB:8567
// SM2MAIN:64c5
// Signature: [] -> []
void ScreenRoutines(void) {
  switch (ScreenRoutineTask) {
  case SCREENROUTINES_INITSCREEN:
    InitScreen();
    return;

  case SCREENROUTINES_SETUPINTERMEDIATE:
    SetupIntermediate();
    return;

  case SCREENROUTINES_WRITETOPSTATUSLINE:
    WriteTopStatusLine();
    return;

  case SCREENROUTINES_WRITEBOTTOMSTATUSLINE:
    WriteBottomStatusLine();
    return;

  case SCREENROUTINES_DISPLAYTIMEUP:
    DisplayTimeUp();
    return;

  case SCREENROUTINES_RESETSPRITESANDSCREENTIMER_1:
  case SCREENROUTINES_RESETSPRITESANDSCREENTIMER_2:
    ResetSpritesAndScreenTimer();
    return;

  case SCREENROUTINES_DISPLAYINTERMEDIATE:
    DisplayIntermediate();
    return;

  case SCREENROUTINES_AREAPARSERTASKCONTROL:
    AreaParserTaskControl();
    return;

  case SCREENROUTINES_GETAREAPALETTE:
    GetAreaPalette();
    return;

  case SCREENROUTINES_GETBACKGROUNDCOLOR:
    GetBackgroundColor();
    return;

  case SCREENROUTINES_GETALTERNATEPALETTE1:
    GetAlternatePalette1();
    return;

  case SCREENROUTINES_DRAWTITLESCREEN:
    DrawTitleScreen();
    return;

  case SCREENROUTINES_CLEARBUFFERSDRAWICON:
    ClearBuffersDrawIcon();
    return;

  case SCREENROUTINES_WRITETOPSCORE:
    WriteTopScore();
    return;

#ifdef SMB2J_MODE
  case SCREENROUTINES_DEMORESET:
    DemoReset();
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
  if (OperMode != 0) {
    VRAM_Buffer_AddrCtrl = ADDRCTRL_UNDERGROUNDPALETTEDATA;
  }
  ScreenRoutineTask = ScreenRoutineTask + 1;
}


// SMB:859b
// SM2MAIN:64fb
// Signature: [] -> []
void SetupIntermediate(void) {
  const byte bVar1 = PlayerStatus;
  const byte bStack0000 = BackgroundColorCtrl;
  PlayerStatus = 0;
  BackgroundColorCtrl = 2;
  GetPlayerColors();
  PlayerStatus = bVar1;
  BackgroundColorCtrl = bStack0000;
  ScreenRoutineTask = ScreenRoutineTask + 1;
}


// SMB:85bf
// SM2MAIN:651f
// Signature: [] -> []
void GetAreaPalette(void) {
  assert_eq_assumption(AreaType < 4, true);

  byte addrctrl;

  switch (AreaType) {
  case 0: addrctrl = ADDRCTRL_WATERPALETTEDATA; break;
  case 1: addrctrl = ADDRCTRL_GROUNDPALETTEDATA; break;
  case 2: addrctrl = ADDRCTRL_UNDERGROUNDPALETTEDATA; break;
  case 3: addrctrl = ADDRCTRL_CASTLEPALETTEDATA; break;
  }

  VRAM_Buffer_AddrCtrl = addrctrl;

  ScreenRoutineTask = ScreenRoutineTask + 1;
}


// SMB:85e3
// SM2MAIN:653f
// Signature: [] -> []
void GetBackgroundColor(void) {
  if (BackgroundColorCtrl != 0) {
    assert_eq_assumption(BackgroundColorCtrl >= 4 && BackgroundColorCtrl < 8, true);

    byte addrctrl;

    switch (BackgroundColorCtrl) {
    case 4: addrctrl = ADDRCTRL_VRAM_BUFFER1; break;
    case 5: addrctrl = ADDRCTRL_DAYSNOWPALETTEDATA; break;
    case 6: addrctrl = ADDRCTRL_NIGHTSNOWPALETTEDATA; break;
    case 7: addrctrl = ADDRCTRL_CASTLEPALETTEDATA; break;
    }

    VRAM_Buffer_AddrCtrl = addrctrl;
  }

  ScreenRoutineTask += 1;
  GetPlayerColors();
}


// SMB:85f1
// SM2MAIN:654d
// Signature: [] -> []
void GetPlayerColors(void) {
  byte bVar3 = 0;
  if (SMB1_ONLY) {
    if (CurrentPlayer != 0) {
      bVar3 = 4;
    }
    if (PlayerStatus == 2) {
      bVar3 = 8;
    }
  }
  if (SMB2J_ONLY) {
    if (PlayerStatus == 2) {
      bVar3 = 4;
    }
  }

  const byte idx = BackgroundColorCtrl != 0 ? BackgroundColorCtrl : AreaType;

  VRAM1_DRAW(PPU_ADDR_PALETTE_SPR(0, 0),
             BackgroundColors[idx],
             PlayerColors[1 + bVar3],
             PlayerColors[2 + bVar3],
             PlayerColors[3 + bVar3]);
}


// SMB:8643
// SM2MAIN:6598
// Signature: [] -> []
void GetAlternatePalette1(void) {
  if (AreaStyle == 1) {
    VRAM_Buffer_AddrCtrl = ADDRCTRL_MUSHROOMPALETTEDATA;
  }
  ScreenRoutineTask = ScreenRoutineTask + 1;
}


// SMB:8652
// SM2MAIN:65a7
// Signature: [] -> []
void WriteTopStatusLine(void) {
  WriteGameText(0);
  ScreenRoutineTask = ScreenRoutineTask + 1;
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

  ScreenRoutineTask = ScreenRoutineTask + 1;
}


// SMB:8693
// SM2MAIN:65f8
// Signature: [] -> []
void DisplayTimeUp(void) {
  if (GameTimerExpiredFlag != 0) {
    GameTimerExpiredFlag = 0;
    WriteGameText(2);
    ResetScreenTimer();
    DisableScreenFlag = 0;
  } else {
    ScreenRoutineTask = ScreenRoutineTask + 2;
  }
}


// SMB:86a8
// SM2MAIN:6617
// Signature: [] -> []
void DisplayIntermediate(void) {
  if (OperMode == 3) {
#ifdef SMB1_MODE
    ScreenTimer = 0x12;
    WriteGameText(3);
    OperMode_Task += 1;
#endif
#ifdef SMB2J_MODE
    WriteGameText(3);
    if (WorldNumber != 8) {
      OperMode_Task += 1;
    } else {
      ScreenRoutineTask += 1;
    }
#endif
    return;
  }

  if (OperMode == 0 || AltEntranceControl != 0 || (AreaType != 3 && DisableIntermediate != 0)) {
    ScreenRoutineTask = ssw(8, 9);
    return;
  }

  DrawPlayer_Intermediate();
  WriteGameText(1);
  ResetScreenTimer();
  DisableScreenFlag = 0;

#ifdef SMB2J_MODE
  if (WorldNumber != 8) {
    ScreenRoutineTask += 1;
  } else {
    DisableScreenFlag += 1;
  }
#endif
}


// SMB:8732
// SM2MAIN:c573
// Signature: [] -> []
void ClearBuffersDrawIcon(void) {
  if (OperMode == 0) {
    // NES note: Zeros out pages $0300 and $0400
    for (int i = 0; i < 256; i++) {
      VRAM_Page[i] = 0;
      Objects_Page[i] = 0;
    }
    DrawMushroomIcon();
    ScreenRoutineTask += 1;
  } else {
    OperMode_Task += 1;
  }
}


// SMB:8749
// SM2MAIN:c58a
// Signature: [] -> []
void WriteTopScore(void) {
  WriteDigits(0xfa);
  OperMode_Task = OperMode_Task + 1;
}


// SMB:889d
// SM2MAIN:677a
// Signature: [] -> []
void ResetSpritesAndScreenTimer(void) {
  if (ScreenTimer == 0) {
    MoveAllSpritesOffscreen();
    ResetScreenTimer();
  }
}


// SMB:88a5
// SM2MAIN:6782
// Signature: [] -> []
void ResetScreenTimer(void) {
  ScreenTimer = 7;
  ScreenRoutineTask = ScreenRoutineTask + 1;
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

  // Note: Inlining BlankPalette, because it's tightly coupled with the code

  const byte paloff = AreaType << 2;

  // Rotate the second palette color in particular. This is the coin/block color.
  VRAM1_DRAW(PPU_ADDR_PALETTE_BG(3, 0),
             Palette3Data[paloff + 0],
             ColorRotatePalette[ColorRotateOffset],
             Palette3Data[paloff + 2],
             Palette3Data[paloff + 3]);

  ColorRotateOffset += 1;

  if (ColorRotateOffset >= 6) {
    ColorRotateOffset = 0;
  }
}


// Draw a 2x2 block at the position at x,y, where x is 0 to 15, and y is 0 to 14.
// If nt = 0, then draw on the first nametable. Otherwise draw on the second.
static inline void draw_block_metatile(const byte vramoff, const byte blockgfxidx, const byte x, const byte y, const byte nt) {
  const u16 nametable = nt == 0 ? 0x2000 : 0x2400;
  const u16 addr = nametable + (y*2*32) + x*2;

  VRAM_Page[vramoff + 0] = addr >> 8;
  VRAM_Page[vramoff + 1] = addr & 0xff;
  VRAM_Page[vramoff + 2] = 2;
  VRAM_Page[vramoff + 3] = BlockGfxData[blockgfxidx*4 + 0];
  VRAM_Page[vramoff + 4] = BlockGfxData[blockgfxidx*4 + 1];

  VRAM_Page[vramoff + 5] = addr >> 8;
  VRAM_Page[vramoff + 6] = (addr & 0xff) + 32;
  VRAM_Page[vramoff + 7] = 2;
  VRAM_Page[vramoff + 8] = BlockGfxData[blockgfxidx*4 + 2];
  VRAM_Page[vramoff + 9] = BlockGfxData[blockgfxidx*4 + 3];

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
  const byte blockgfxidx = AreaType != 0 ? 3 : 4;
  const byte vramoff = 0x41;

  const byte x  = mt_x % 16;
  const byte y  = mt_y + MT_Y_TOP_MARGIN;
  const byte nt = (mt_x & 0x10) == 0 ? 0 : 1;

  // Inlined: PutBlockMetatile
  draw_block_metatile(vramoff, blockgfxidx, x, y, nt);

  VRAM_Buffer_AddrCtrl = ADDRCTRL_VRAM_BUFFER2;
}


// SMB:8a61
// SM2MAIN:693e
void ReplaceBlockMetatile(const byte param_1, const byte param_2, const u16 mt_x, const u16 mt_y) {
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
void WriteBlockMetatile(const byte param_1, const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [A, r02, r06] -> []
  // Reworked to use metatile coordinates instead of pointer

  byte blockgfxidx;
  if (param_1 == 0) {
    blockgfxidx = 3;
  } else if (param_1 == ssw(0x51, 0x4f)) {
    blockgfxidx = 0;
  } else if (param_1 == ssw(0x52, 0x50)) {
    blockgfxidx = 1;
  } else if (param_1 == ssw(0x58, 0x56)) {
    blockgfxidx = 0;
  } else if (param_1 == ssw(0x5d, 0x5c)) {
    blockgfxidx = 1;
  } else {
    blockgfxidx = 2;
  }

  const byte vramoff = VRAM_Buffer1_Offset + 1;

  const byte x  = mt_x % 16;
  const byte y  = mt_y + MT_Y_TOP_MARGIN;
  const byte nt = (mt_x & 0x10) == 0 ? 0 : 1;

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
void WritePPUReg1(const byte param_1) {
  ppuctrl(param_1);
  Mirror_PPU_CTRL_REG1 = param_1;
}


// SMB:8f06
// SM2MAIN:6d79
// Signature: [A] -> []
void PrintStatusBarNumbers(const byte param_1) {
  OutputNumbers(param_1);
  OutputNumbers(param_1 >> 4);
}


// SMB:8f11
// SM2MAIN:6d84
// Signature: [A] -> []
void OutputNumbers(const byte param_1) {
  const u8 sbtype = (param_1 + 1) & 0xf;

  if (sbtype >= 6) {
    return;
  }

  //        SMB1  SMB2J
  // sbtype 0     0      Top score display on title screen
  // sbtype 1,2   1      Player score
  // sbtype 3,4   2      Coin tally
  // sbtype 5,6   3      Game timer

  // If the status bar type is the top score display on the title screen,
  // then place it 16 tiles lower
  const u8 hi = (sbtype == 0) ? 0x22 : 0x20;

  const u8 lo = StatusBarData[sbtype * 2];
  const u8 length = StatusBarData[sbtype * 2 + 1];

  VRAM_Buffer1[VRAM_Buffer1_Offset + 0] = hi;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 1] = lo;
  VRAM_Buffer1[VRAM_Buffer1_Offset + 2] = length;

  const u8 sboffset = StatusBarOffset[sbtype];

  const int write_length = length == 0 ? 256 : length;

  for (int i = write_length; i > 0; i--) {
    VRAM_Buffer1[VRAM_Buffer1_Offset + 3] = DisplayDigits_Or_TopScoreDisplay[(byte)(sboffset - i)];
    VRAM_Buffer1_Offset += 1;
  }

  VRAM_Buffer1[VRAM_Buffer1_Offset + 3] = 0;

  VRAM_Buffer1_Offset += 3;
}


// SMB:8f5f
// SM2MAIN:6dd2
// Signature: [Y] -> []
void DigitsMathRoutine(const byte param_1) {
  // In SMB1 and SMB2J, DigitModifier is often accessed as DigitModifier-1.

  if (OperMode != 0) {
    for (int i = 6; i >= 1; i--) {
      byte bVar1 = DigitModifier_Minus1[i] + DisplayDigits_Or_TopScoreDisplay[param_1 + i - 6];
      if (bVar1 < 0x80) {
        if (bVar1 >= 10) {
          bVar1 -= 10;
          DigitModifier_Minus1[i-1] += 1;
        }
        DisplayDigits_Or_TopScoreDisplay[param_1 + i - 6] = bVar1;
      } else {
        DigitModifier_Minus1[i-1] -= 1;
        DisplayDigits_Or_TopScoreDisplay[param_1 + i - 6] = 9;
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
void TopScoreCheck(const byte last_digit_offset) {
  // last_digit_offset is 5 or 11

  const byte off = last_digit_offset - 5;
  // scan the digits from left to right
  for (int i = 0; i < 6; i++) {
      const byte player_digit = PlayerScoreDisplay_Or_ScoreAndCoinDisplay[off + i];
      const byte top_digit = DisplayDigits_Or_TopScoreDisplay[i];
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
    DisplayDigits_Or_TopScoreDisplay[i] = PlayerScoreDisplay_Or_ScoreAndCoinDisplay[off + i];
  }
}


// SMB:8fdc
// SM2MAIN:c5d0
// Signature: [] -> []
void DemoReset(void) {
  // Note: The SMB disassembly doesn't label this
  DemoTimer = 0x18;
  LoadAreaPointer();
  InitializeArea();
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
  DemoReset();
}


// SMB:8fe4
// SM2MAIN:6e39
// Signature: [] -> []
void InitializeArea(void) {
  InitializeMemory(0x4b);
  for (int i = 0; i < 34; i++) {
    Timers[i] = 0;
  }
  ScreenEdgeOrLeft_PageLoc[0] = HalfwayPage;
  if (AltEntranceControl != 0) {
    ScreenEdgeOrLeft_PageLoc[0] = EntrancePage;
  }
  CurrentPageLoc = ScreenEdgeOrLeft_PageLoc[0];
  BackloadingFlag = ScreenEdgeOrLeft_PageLoc[0];
  const byte bVar1 = GetScreenPosition();
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
  AreaMusicQueue = 0x80;
  DisableScreenFlag = 1;
#ifdef SMB2J_MODE
  LoadPhysicsData();
#endif
  OperMode_Task = OperMode_Task + 1;
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
  Mirror_PPU_CTRL_REG1 = (Mirror_PPU_CTRL_REG1 & 0xfe) | (ScreenEdgeOrLeft_PageLoc[0] & 1);
#endif
#ifdef SMB2J_MODE
  NameTableSelect = ScreenEdgeOrLeft_PageLoc[0] & 1;
#endif
  GetAreaMusic();
  SprShuffleAmt[2] = 0x38;
  SprShuffleAmt[1] = 0x48;
  SprShuffleAmt[0] = 0x58;

  for (int i = 0; i < 0xf; i++) {
    PlayerOrSprDataOffset[i] = DefaultSprOffsets[i];
  }

#ifdef SMB1_MODE
  SPRITE_Y(0, 0)    = Sprite0Data[0];
  SPRITE_TILE(0, 0) = Sprite0Data[1];
  SPRITE_ATTR(0, 0) = Sprite0Data[2];
  SPRITE_X(0, 0)    = Sprite0Data[3];

  // NES note: there was a call here to "DoNothing2", which, well, does nothing

  Sprite0HitDetectFlag = Sprite0HitDetectFlag + 1;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag = IRQUpdateFlag + 1;
#endif

  // NES note: there was a call here to "DoNothing1" ("DoNothing" in SMB2J), which appears to set an unused variable
  // The disassembly by doppelganger claims it's residual code
  // We'll inline it here
  Misc_Collision_Flag[11] = 0xff;

  OperMode_Task = OperMode_Task + 1;
}


// SMB:90ed
// SM2MAIN:6f2d
// Signature: [] -> []
void GetAreaMusic(void) {
  byte bVar1;

  if (OperMode != 0) {
    if ((AltEntranceControl != 2) && ((PlayerEntranceCtrl == 6) || (PlayerEntranceCtrl == 7))) {
      bVar1 = 5;
    } else if (CloudTypeOverride != 0) {
      bVar1 = 4;
    } else {
      bVar1 = AreaType;
    }
    AreaMusicQueue = MusicSelectData[bVar1];
  }
}


// SMB:9131
// SM2MAIN:6f71
// Signature: [] -> []
void Entrance_GameTimerSetup(void) {
  // NES Note: $07 is technically an input to this function. However, it's a bug.
  // This function is always called from a jumptable, which sets $07 to the high byte of the function (0x91 or 0x6f depending on SMB1 or SMB2J)
  // It's eventually passed to SetupBubble.

  SprObject_PageLoc[0] = ScreenEdgeOrLeft_PageLoc[0];
  VerticalForceDown = 0x28;
  PlayerFacingDir = 1;
  SprObject_Y_HighPos[0] = 1;
  Player_State = 0;
  Player_CollisionBits -= 1;
  HalfwayPage = 0;
  SwimmingFlag = AreaType == 0;

  const byte entrance_ctrl =
    (AltEntranceControl < 2)
    ? PlayerEntranceCtrl
    : AltYPosOffset[AltEntranceControl - 2];

  SprObject_X_Position[0] = PlayerStarting_X_Pos[AltEntranceControl];
  SprObject_Y_Position[0] = PlayerStarting_Y_Pos[entrance_ctrl];
  Player_SprAttrib = PlayerBGPriorityData[entrance_ctrl];

  // NES note: The GetPlayerColors subroutine sets the X register to the vram offset.
  // The eventual call to SetupBubble is the only place that indirectly uses it.
  // We've extracted it out to the caller because it's a bug.
  // This always seems to be 0 (TODO: verify this)
  byte buggy_argument_1 = VRAM_Buffer1_Offset;

  GetPlayerColors();

  if ((GameTimerSetting != 0) && (FetchNewGameTimerFlag != 0)) {
    // Initialize the game timer

    // NES note: inlined from GameTimerData
    static const u16 times[] = {0, 401, 301, 201};

    assert_eq_assumption(GameTimerSetting <= sizeof(times)/sizeof(times[0]), true);

    const u16 time = times[GameTimerSetting];

    GameTimerDisplay[0] = (time / 100) % 10;
    GameTimerDisplay[1] = (time / 10) % 10;
    GameTimerDisplay[2] = (time) % 10;

    FetchNewGameTimerFlag = 0;
    StarInvincibleTimer = 0;
  }

  if (JoypadOverride != 0) {
    Player_State = 3;
    InitBlock_XY_Pos(0);
    Block_Y_Position[0] = 0xf0;
    Setup_Vine(5, 0);

    // The X register was set to 5 as an argument to Setup_Vine. It becomes the new buggy argument.
    // I'm unsure if this could ever be used, unless a modded ROM has Mario climbing a vine underwater or something.
    buggy_argument_1 = 5;
  }

  if (AreaType == 0) {
    // $07 is passed here.
    const byte buggy_argument_2 = ssw(0x91, 0x6f);
    SetupBubble_buggy(buggy_argument_1, buggy_argument_2);
  }

  GameEngineSubroutine = 7;
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
  EventMusicQueue = 0x80;
  NumberofLives -= 1;
  if (NumberofLives >= 0x80) {
    OperMode_Task = 0;
    OperMode = 3;
    return;
  }
  byte bVar1 = WorldNumber * 2;
  if ((LevelNumber & 2) != 0) {
    bVar1 += 1;
  }
  bVar1 = HalfwayPageNybbles[bVar1];
  if ((LevelNumber & 1) == 0) {
    bVar1 >>= 4;
  }
  HalfwayPage = bVar1 & 0xf;
  if ((HalfwayPage != ScreenEdgeOrLeft_PageLoc[0]) && (ScreenEdgeOrLeft_PageLoc[0] <= HalfwayPage)) {
    HalfwayPage = 0;
  }
#ifdef SMB1_MODE
  TransposePlayers();
#endif
  ContinueGame();
}


enum GameOverMode_jumptable_item {
  GAMEOVERMODE_SETUPGAMEOVER,
  GAMEOVERMODE_SCREENROUTINES,
  GAMEOVERMODE_RUNGAMEOVER,
};


// SMB:9218
// SM2MAIN:7057
// Signature: [] -> []
void GameOverMode(void) {
  switch (OperMode_Task) {
  case GAMEOVERMODE_SETUPGAMEOVER:
    SetupGameOver();
    return;

  case GAMEOVERMODE_SCREENROUTINES:
    ScreenRoutines();
    return;

  case GAMEOVERMODE_RUNGAMEOVER:
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
  ScreenRoutineTask = 0;
#ifdef SMB1_MODE
  Sprite0HitDetectFlag = 0;
#endif
#ifdef SMB2J_MODE
  IRQUpdateFlag = 0;
  ContinueMenuSelect = 0;
#endif
  EventMusicQueue = 2;
  DisableScreenFlag = DisableScreenFlag + 1;
  OperMode_Task = OperMode_Task + 1;
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
  EventMusicQueue = 0x80;
#ifdef SMB1_MODE
  if (!TransposePlayers()) {
    ContinueGame();
    return;
  }
  ContinueWorld = WorldNumber;
#endif
  OperMode_Task = 0;
  ScreenTimer = 0;
  OperMode = 0;
}


// SMB:9264
// SM2MAIN:709d
// Signature: [] -> []
void ContinueGame(void) {
  LoadAreaPointer();
  PlayerSize = 1;
  FetchNewGameTimerFlag = FetchNewGameTimerFlag + 1;
  TimerControl = 0;
  PlayerStatus = 0;
  GameEngineSubroutine = 0;
  OperMode_Task = 0;
  OperMode = 1;
}


// SMB:9716
// SM2MAIN:756d
// Signature: [A] -> []
void KillEnemies(const byte param_1) {
  for (int i = 0; i < 5; i++) {
    if (Enemy_ID[i] == param_1) {
      Enemy_Flag[i] = 0;
    }
  }
}


enum GameMode_jumptable_item {
#ifdef SMB2J_MODE
  GAMEMODE_GAMEMODEDISKROUTINES,
#endif
  GAMEMODE_INITIALIZEAREA,
  GAMEMODE_SCREENROUTINES,
  GAMEMODE_SECONDARYGAMESETUP,
  GAMEMODE_GAMECOREROUTINE,
};


// SMB:aedc
// SM2MAIN:7a37
// Signature: [] -> []
void GameMode(void) {
  switch (OperMode_Task) {
  case GAMEMODE_INITIALIZEAREA:
    InitializeArea();
    return;

  case GAMEMODE_SCREENROUTINES:
    ScreenRoutines();
    return;

  case GAMEMODE_SECONDARYGAMESETUP:
    SecondaryGameSetup();
    return;

  case GAMEMODE_GAMECOREROUTINE:
    GameCoreRoutine();
    return;

#ifdef SMB2J_MODE
  case GAMEMODE_GAMEMODEDISKROUTINES:
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
  if (OperMode_Task < ssw(3, 4)) {
    return;
  }
  ProcFireball_Bubble();

  for (int i = 0; i < 6; i++) {
    ObjectOffset = i;
    byte bVar1 = EnemiesAndLoopsCore(i);
    bVar1 = FloateyNumbersRoutine(bVar1);
    assert_eq_assumption(bVar1, i);
  }

  GetPlayerOffscreenBits();
  RelativePlayerPosition();
  PlayerGfxHandler();
  BlockObjMT_Updater();
  ObjectOffset = 1;
  ObjectOffset = BlockObjectsCore(1) - 1;
  BlockObjectsCore(ObjectOffset);
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
      || (0x7f < (byte)(Player_X_Scroll - 1))) {
    ScrollAmount = 0;
    ChkPOffscr();
    return;
  }
  byte bVar1 = Player_X_Scroll;
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
  const byte bits = GetXOffscreenBits(0);
  byte i;

  if (bits & 0x80) {
    i = 0;
  } else if (bits & 0x20) {
    i = 1;
  } else {
    Platform_X_Scroll = 0;
    return;
  }

  SprObject_X_Position[0] = ScreenEdgeOrLeft_X_Pos[i] - X_SubtracterData[i];
  SprObject_PageLoc[0] = ScreenEdgeOrLeft_PageLoc[i] - (ScreenEdgeOrLeft_X_Pos[i] < X_SubtracterData[i]);

  if (Left_Right_Buttons != OffscrJoypadBitsData[i]) {
    PlayerSpriteVarData1[0] = 0;
  }

  Platform_X_Scroll = 0;
}


// SMB:b038
// SM2MAIN:7b90
// Signature: [] -> [A]
byte GetScreenPosition(void) {
  ScreenRight_X_Pos = ScreenEdgeOrLeft_X_Pos[0] - 1;
  ScreenRight_PageLoc = ScreenEdgeOrLeft_PageLoc[0] + (ScreenEdgeOrLeft_X_Pos[0] != 0);
  return ScreenRight_PageLoc;
}


enum GameRoutines_jumptable_item {
  GAMEROUTINES_ENTRANCE_GAMETIMERSETUP,
  GAMEROUTINES_VINE_AUTOCLIMB,
  GAMEROUTINES_SIDEEXITPIPEENTRY,
  GAMEROUTINES_VERTICALPIPEENTRY,
  GAMEROUTINES_FLAGPOLESLIDE,
  GAMEROUTINES_PLAYERENDLEVEL,
  GAMEROUTINES_PLAYERLOSELIFE,
  GAMEROUTINES_PLAYERENTRANCE,
  GAMEROUTINES_PLAYERCTRLROUTINE,
  GAMEROUTINES_PLAYERCHANGESIZE,
  GAMEROUTINES_PLAYERINJURYBLINK,
  GAMEROUTINES_PLAYERDEATH,
  GAMEROUTINES_PLAYERFIREFLOWER,
};


// SMB:b04a
// SM2MAIN:7ba2
// Signature: [] -> []
void GameRoutines(void) {
  switch (GameEngineSubroutine) {
  case GAMEROUTINES_ENTRANCE_GAMETIMERSETUP:
    Entrance_GameTimerSetup();
    return;

  case GAMEROUTINES_VINE_AUTOCLIMB:
    Vine_AutoClimb();
    return;

  case GAMEROUTINES_SIDEEXITPIPEENTRY:
    SideExitPipeEntry();
    return;

  case GAMEROUTINES_VERTICALPIPEENTRY:
    VerticalPipeEntry();
    return;

  case GAMEROUTINES_FLAGPOLESLIDE:
    FlagpoleSlide();
    return;

  case GAMEROUTINES_PLAYERENDLEVEL:
    PlayerEndLevel();
    return;

  case GAMEROUTINES_PLAYERLOSELIFE:
    PlayerLoseLife();
    return;

  case GAMEROUTINES_PLAYERENTRANCE:
    PlayerEntrance();
    return;

  case GAMEROUTINES_PLAYERCTRLROUTINE:
    PlayerCtrlRoutine();
    return;

  case GAMEROUTINES_PLAYERCHANGESIZE:
    PlayerChangeSize();
    return;

  case GAMEROUTINES_PLAYERINJURYBLINK:
    PlayerInjuryBlink();
    return;

  case GAMEROUTINES_PLAYERDEATH:
    PlayerDeath();
    return;

  case GAMEROUTINES_PLAYERFIREFLOWER:
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
  byte bVar1;

  if (AltEntranceControl == 2) {
    if (JoypadOverride == 0) {
      MovePlayerYAxis(0xff);
      if (SprObject_Y_Position[0] > 0x90) {
        return;
      }
    } else {
      if (VineHeight != 0x60) {
        return;
      }
      DisableCollisionDet = SprObject_Y_Position[0] > 0x98;
      bVar1 = 1;
      if (DisableCollisionDet != 0) {
        Player_State = 3;
        bVar1 = 8;
        Block_Buffers[BLOCK_BUFFER_1_OFFSET + 0xb4] = 8;
      }
      AutoControlPlayer(bVar1);
      if (SprObject_X_Position[0] < 0x48) {
        return;
      }
    }
  } else {
    if (SprObject_Y_Position[0] < 0x30) {
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
  GameEngineSubroutine = 8;
}


// SMB:b0e6
// SM2MAIN:7c3e
// Signature: [A] -> []
void AutoControlPlayer(const byte param_1) {
  SavedJoypadBits[0] = param_1;
  PlayerCtrlRoutine();
}


// SMB:b0e9
// SM2MAIN:7c41
// Signature: [] -> []
void PlayerCtrlRoutine(void) {
  char cVar1;
  char cVar2;

  if (GameEngineSubroutine != 0xb) {
    if ((AreaType == 0) && ((SprObject_Y_HighPos[0] != 1 || (SprObject_Y_Position[0] >= 0xd0)))) {
      SavedJoypadBits[0] = 0;
    }
    A_B_Buttons = SavedJoypadBits[0] & (BUTTON_A | BUTTON_B);
    Up_Down_Buttons = SavedJoypadBits[0] & (BUTTON_U | BUTTON_D);
    Left_Right_Buttons = SavedJoypadBits[0] & (BUTTON_L | BUTTON_R);
    if ((((SavedJoypadBits[0] & BUTTON_D) != 0) && (Player_State == 0)) && (Left_Right_Buttons != 0)) {
      Left_Right_Buttons = 0;
      Up_Down_Buttons = 0;
    }
  }
  PlayerMovementSubs();
  PlayerOrSprObj_BoundBoxCtrl[0] = 1;
  if (PlayerSize == 0) {
    PlayerOrSprObj_BoundBoxCtrl[0] = 0;
    if (CrouchingFlag != 0) {
      PlayerOrSprObj_BoundBoxCtrl[0] = 2;
    }
  }
  if ((PlayerSpriteVarData1[0] != 0)) {
    Player_MovingDir = (PlayerSpriteVarData1[0] < 0x80) ? 1 : 2;
  }
  ScrollHandler();
  GetPlayerOffscreenBits();
  const byte bVar3 = RelativePlayerPosition();
  BoundingBoxCore(0, bVar3);
  PlayerBGCollision();
  if ((((SprObject_Y_Position[0] >= 0x40) && (GameEngineSubroutine != 5)) && (GameEngineSubroutine != 7))
      && (GameEngineSubroutine >= 4)) {
    Player_SprAttrib &= 0xdf;
  }
  if ((byte)(SprObject_Y_HighPos[0] - 2) < 0x80) {
    ScrollLock = 1;
    cVar1 = 4;
    cVar2 = 0;
    if (((GameTimerExpiredFlag != 0) || (CloudTypeOverride == 0))) {
      cVar2 = 1;
      if (GameEngineSubroutine != 0xb) {
        if (DeathMusicLoaded == 0) {
          EventMusicQueue = 1;
          DeathMusicLoaded = 1;
        }
        cVar1 = 6;
      }
    }
    if ((byte)(SprObject_Y_HighPos[0] - cVar1) < 0x80) {
      if (0x7f < (byte)(cVar2 - 1U)) {
        JoypadOverride = 0;
        SetEntr();
        AltEntranceControl = AltEntranceControl + 1;
        return;
      }
      if (EventMusicBuffer == 0) {
        GameEngineSubroutine = 6;
      }
    }
  }
}


// SMB:b1c7
// SM2MAIN:7d1f
// Signature: [] -> []
void Vine_AutoClimb(void) {
  if ((SprObject_Y_HighPos[0] == 0) && (SprObject_Y_Position[0] < 0xe4)) {
    SetEntr();
  } else {
    JoypadOverride = 8;
    Player_State = 3;
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
    } else if (AreaType != 3) {
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
void MovePlayerYAxis(const byte param_1) {
  SprObject_Y_Position[0] = param_1 + SprObject_Y_Position[0];
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
byte ChgAreaMode(void) {
  DisableScreenFlag = DisableScreenFlag + 1;
  OperMode_Task = 0;
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
  PlayerSpriteVarData1[0] = 8;
  const bool bVar1 = (SprObject_X_Position[0] & 0xf) == 0;
  if (bVar1) {
    PlayerSpriteVarData1[0] = 0;
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
  GameEngineSubroutine = 8;
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
void CyclePlayerPalette(const byte param_1) {
  Player_SprAttrib = (Player_SprAttrib & 0xfc) | (param_1 & 3);
}


// SMB:b29a
// SM2MAIN:7df2
// Signature: [] -> []
void ResetPalStar(void) {
  Player_SprAttrib = Player_SprAttrib & 0xfc;
}


// SMB:b2a4
// SM2MAIN:7dfb
// Signature: [] -> []
void FlagpoleSlide(void) {
  byte bVar1;

  if (Enemy_ID[5] == 0x30) {
    Square1SoundQueue = FlagpoleSoundQueue;
    bVar1 = 0;
    FlagpoleSoundQueue = 0;
    if (SprObject_Y_Position[0] < 0x9e) {
      bVar1 = 4;
    }
    AutoControlPlayer(bVar1);
  } else {
    GameEngineSubroutine = GameEngineSubroutine + 1;
  }
}


// SMB:b2ca
// SM2MAIN:7e19
// Signature: [] -> []
void PlayerEndLevel(void) {
  AutoControlPlayer(1);
#ifdef SMB1_MODE
  if ((SprObject_Y_Position[0] >= 0xae) && (ScrollLock != 0)) {
    EventMusicQueue = 0x20;
    ScrollLock = 0;
  }
#endif
#ifdef SMB2J_MODE
  if ((SprObject_Y_Position[0] >= 0xae)) {
    ScrollLock = 0;
    if (FlagpoleMusicFlag == 0) {
      EventMusicQueue = 0x20;
      FlagpoleMusicFlag = 1;
    }
  }
#endif
  if ((Player_CollisionBits & 1) == 0) {
    if (StarFlagTaskControl == 0) {
      StarFlagTaskControl = 1;
    }
    Player_SprAttrib = 0x20;
  }
  if (StarFlagTaskControl != 5) {
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
  EventMusicQueue = 0x80;
}


enum PlayerMovementSubs_jumptable_item {
  PLAYERMOVEMENTSUBS_ONGROUNDSTATESUB,
  PLAYERMOVEMENTSUBS_JUMPSWIMSUB,
  PLAYERMOVEMENTSUBS_FALLINGSUB,
  PLAYERMOVEMENTSUBS_CLIMBINGSUB,
};


// SMB:b329
// SM2MAIN:7e90
// Signature: [] -> []
void PlayerMovementSubs(void) {
  byte bVar1 = 0;
  if (PlayerSize == 0) {
    bVar1 = CrouchingFlag;
    if (Player_State == 0) {
      bVar1 = Up_Down_Buttons & BUTTON_D;
    }
  }
  CrouchingFlag = bVar1;
  PlayerPhysicsSub();
  if (PlayerChangeSizeFlag != 0) {
    return;
  }
  if (Player_State != 3) {
    ClimbSideTimer = 0x18;
  }

  switch (Player_State) {
  case PLAYERMOVEMENTSUBS_ONGROUNDSTATESUB:
    OnGroundStateSub();
    return;

  case PLAYERMOVEMENTSUBS_JUMPSWIMSUB:
    JumpSwimSub();
    return;

  case PLAYERMOVEMENTSUBS_FALLINGSUB:
    FallingSub();
    return;

  case PLAYERMOVEMENTSUBS_CLIMBINGSUB:
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
  if ((PlayerSpriteVarData2[0] < 0x80)
      || (((A_B_Buttons & BUTTON_A & PreviousA_B_Buttons) == 0
           && (DiffToHaltJump <= (byte)(JumpOrigin_Y_Position - SprObject_Y_Position[0]))))) {
    VerticalForce = VerticalForceDown;
  }
  if (SwimmingFlag != 0) {
    GetPlayerAnimSpeed();
    if (SprObject_Y_Position[0] < 0x14) {
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
  if (GameEngineSubroutine == 0xb) {
    VerticalForce = 0x28;
  }
  MovePlayerVertically();
}


// SMB:b3cf
// SM2MAIN:7f3b
// Signature: [] -> []
void ClimbingSub(void) {
  ADD_SIGNED_24_16(SprObject_Y_HighPos[0], SprObject_Y_Position[0], SprObject_YMF_Dummy[0],
                   PlayerSpriteVarData2[0], SprObject_Y_MoveForce[0]);

  const byte bVar3 = Left_Right_Buttons & Player_CollisionBits;
  if (bVar3 != 0) {
    if (ClimbSideTimer == 0) {
      ClimbSideTimer = 0x18;
      byte bVar4 = (bVar3 & 1) == 0 ? 2 : 0;
      if (PlayerFacingDir != 1) {
        bVar4 += 1;
      }
      ADD_16_16(SprObject_PageLoc[0], SprObject_X_Position[0],
                ClimbAdderHigh[bVar4], ClimbAdderLow[bVar4]);
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
  if (Player_State == 3) {
    byte bVar1 = 0;
    if (((Up_Down_Buttons & Player_CollisionBits) != 0)) {
      bVar1 = 1;
      if ((Up_Down_Buttons & Player_CollisionBits & BUTTON_U) == 0) {
        bVar1 = 2;
      }
    }
    SprObject_Y_MoveForce[0] = Climb_Y_MForceData[bVar1];
    PlayerAnimTimerSet = 8;
    PlayerSpriteVarData2[0] = Climb_Y_SpeedData[bVar1];
    if (Climb_Y_SpeedData[bVar1] < 0x80) {
      PlayerAnimTimerSet = 4;
    }
    return;
  }

  const bool button_a_newly_pressed = ((A_B_Buttons & BUTTON_A) != 0) && ((A_B_Buttons & BUTTON_A & PreviousA_B_Buttons) == 0);
  if ((JumpspringAnimCtrl == 0) && button_a_newly_pressed) {
    if (Player_State == 0 || (SwimmingFlag != 0 && (JumpSwimTimer != 0 || (PlayerSpriteVarData2[0] < 0x80)))) {
      JumpSwimTimer = 0x20;
      SprObject_YMF_Dummy[0] = 0;
      JumpOrigin_Y_HighPos = SprObject_Y_HighPos[0];
      JumpOrigin_Y_Position = SprObject_Y_Position[0];
      Player_State = 1;

      byte bVar1;
      if (SwimmingFlag == 0) {
        const byte xs = Player_XSpeedAbsolute;
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
        bVar1 = (Cannon_Timer_Or_Whirlpool_Flag[0] == 0) ? 5 : 6;
      }

      DiffToHaltJump = 1;

      VerticalForce = JumpMForceData[bVar1];
      VerticalForceDown = FallMForceData[bVar1];
      SprObject_Y_MoveForce[0] = InitMForceData[bVar1];
      PlayerSpriteVarData2[0] = PlayerYSpdData[bVar1];

      if (SwimmingFlag == 0) {
        Square1SoundQueue = (PlayerSize != 0) ? 0x80 : 1;
      } else {
        Square1SoundQueue = 4;
        if (SprObject_Y_Position[0] < 0x14) {
          PlayerSpriteVarData2[0] = 0;
        }
      }
    }
  }

  byte bVar2 = 0;
  byte bVar1 = 1;

  const bool same_direction = Left_Right_Buttons == Player_MovingDir;
  const bool holding_b = (A_B_Buttons & BUTTON_B) != 0;
  const bool running = same_direction && holding_b;

  if (Player_State == 0) {
    // ProcPRun
    if ((AreaType != 0)) {
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

  bVar2 = (Player_State == 0 && AreaType == 0) ? 1 : 0;

  if (bVar1) {
    bVar2 += 1;
    if ((RunningSpeed != 0) || (Player_XSpeedAbsolute > 0x20)) {
      bVar1 = 2;
    }
  }

  // GetXPhy
  MaximumLeftSpeed = MaxLeftXSpdData[bVar2];
  MaximumRightSpeed = MaxRightXSpdData[GameEngineSubroutine == 7 ? 3 : bVar2];
  FrictionAdderLow = FrictionData[bVar1];
  FrictionAdderHigh = 0;
  if (PlayerFacingDir != Player_MovingDir) {
#ifdef SMB2J_MODE
    // either 0x0e (ASL) or 0x60 (RTS)
    if (PhysicsInstructionOpcode == 0x60) {
      return;
    }
#endif

    // FrictionAdder *= 2
    FrictionAdderHigh = FrictionAdderLow >= 128 ? 1 : 0;
    FrictionAdderLow *= 2;
  }
}


// SMB:b58f
// SM2MAIN:80fb
// Signature: [] -> []
void GetPlayerAnimSpeed(void) {
  byte bVar2 = 0;
  byte bVar1 = Player_XSpeedAbsolute;
  if (Player_XSpeedAbsolute < 0x1c) {
    bVar2 = 1;
    if (Player_XSpeedAbsolute < 0xe) {
      bVar2 = 2;
    }
    bVar1 = RunningSpeed;
    if ((SavedJoypadBits[0] & ~(BUTTON_A)) != 0) {
      if ((SavedJoypadBits[0] & (BUTTON_L | BUTTON_R)) == Player_MovingDir) {
        bVar1 = 0;
      } else if (Player_XSpeedAbsolute < 0xb) {
        Player_MovingDir = PlayerFacingDir;
        PlayerSpriteVarData1[0] = 0;
        Player_X_MoveForce = 0;
      }
    }
  }
  RunningSpeed = bVar1;
  PlayerAnimTimerSet = PlayerAnimTmrData[bVar2];
}


// SMB:b5cc
// SM2MAIN:8138
// Signature: [A] -> []
void ImposeFriction(const byte param_1) {
  const byte tmp1 = param_1 & Player_CollisionBits;

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

    if ((byte)(Player_X_Speed - MaximumRightSpeed) < 0x80) {
      Player_X_Speed = MaximumRightSpeed;
      Player_XSpeedAbsolute = MaximumRightSpeed;
      return;
    }
  } else {
    // RghtFrict
    SUB_16_16(Player_X_Speed, Player_X_MoveForce,
              FrictionAdderHigh, FrictionAdderLow);

    if ((byte)(Player_X_Speed - MaximumLeftSpeed) >= 0x80) {
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
  if (PlayerStatus > 1) {
    if ((A_B_Buttons & BUTTON_B) != 0) {
      if ((A_B_Buttons & BUTTON_B & PreviousA_B_Buttons) == 0) {
        if (Fireball_State[FireballCounter & 1] == 0) {
          if (SprObject_Y_HighPos[0] == 1) {
            if (CrouchingFlag == 0) {
              if (Player_State != 3) {
                Square1SoundQueue = 0x20;
                Fireball_State[FireballCounter & 1] = 2;
                FireballThrowingTimer = PlayerAnimTimerSet;
                PlayerAnimTimer = PlayerAnimTimerSet - 1;
                FireballCounter += 1;
              }
            }
          }
        }
      }
    }
    FireballObjCore(0);
    FireballObjCore(1);
  }

  if (AreaType == 0) {
    for (int i = 2; i >= 0; i--) {
      ObjectOffset = i;
      BubbleCheck(i);
      RelativeBubblePosition(i);
      GetBubbleOffscreenBits(ObjectOffset);
      DrawBubble(ObjectOffset);
    }
  }
}


// SMB:b689
// SM2MAIN:81f5
// Signature: [X] -> []
void FireballObjCore(const byte param_1) {
  // param_1 is always 0 or 1

  ObjectOffset = param_1;

  if ((Fireball_State[param_1] & 0x80) != 0) {
    RelativeFireballPosition(param_1);
    const byte bVar2 = ObjectOffset;
    DrawExplosion_Fireball(bVar2);
    return;
  }

  if (Fireball_State[param_1] != 0) {
    if (Fireball_State[param_1] != 1) {
      ADD_UNSIGNED_16_16_8(Fireball_PageLoc[param_1], Fireball_X_Position[param_1],
                           SprObject_PageLoc[0], SprObject_X_Position[0],
                           4);

      Fireball_Y_Position[param_1] = SprObject_Y_Position[0];
      Fireball_Y_HighPos[param_1] = 1;

      // PlayerFacingDir may = 0 or 3 sometimes, so this goes out of bounds
      // The original lookup is FireballXSpdData[(byte)(PlayerFacingDir - 1)].
      const byte xspd_lookup[4] = { FireballXSpdData_Bug0, FireballXSpdData[0], FireballXSpdData[1], FireballXSpdData[2] };
      assert_eq_assumption(PlayerFacingDir < 4, true);

      Fireball_X_Speed[param_1] = xspd_lookup[PlayerFacingDir];
      Fireball_Y_Speed[param_1] = 4;

      Fireball_BoundBoxCtrl[param_1] = 7;
      Fireball_State[param_1] = Fireball_State[param_1] - 1;
    }

    const byte bVar4 = param_1 + 7;

    const byte in_r01 = 0;
    ImposeGravity(0, bVar4, 0x50, in_r01, 3);

    MoveObjectHorizontally(bVar4);

    RelativeFireballPosition(ObjectOffset);
    byte bVar2 = ObjectOffset;
    GetFireballOffscreenBits(bVar2);
    GetFireballBoundBox(ObjectOffset);
    bVar2 = ObjectOffset;
    bVar2 = FireballBGCollision(bVar2);
    if ((FBall_OffscreenBits & 0xcc) == 0) {
      FireballEnemyCollision(bVar2);
      bVar2 = ObjectOffset;
      DrawFireball(bVar2);
      return;
    }
    Fireball_State[bVar2] = 0;
  }
}

static inline void check_and_setup_bubble(const byte param_1, const bool random, const bool docheck, const bool bug) {
  bool setup_bubble = true;

  if (docheck) {
    if (Bubble_Y_Position[param_1] != SPRITE_Y_OFFSCREEN) {
      setup_bubble = false;
    } else if (AirBubbleTimer != 0) {
      return;
    }
  }

  const byte air_bubble_timer = bug ? BubbleTimerData_Bug : BubbleTimerData[random];
  const byte bubble_mforce_data = bug ? Bubble_MForceData_Bug : Bubble_MForceData[random];

  if (setup_bubble) {
    const bool c = (PlayerFacingDir & 1) != 0;
    // NES note: The carry flag causes the constant to be incremented by 1
    const byte a = c ? (8 + 1) : 0;

    SET_16_16(Bubble_PageLoc[param_1], Bubble_X_Position[param_1],
              SprObject_PageLoc[0], SprObject_X_Position[0]);

    ADD_UNSIGNED_16_8(Bubble_PageLoc[param_1], Bubble_X_Position[param_1],
                      a);

    Bubble_Y_Position[param_1] = SprObject_Y_Position[0] + 8;
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
void BubbleCheck(const byte param_1) {
  const bool docheck = true;
  const bool bug = false;
  check_and_setup_bubble(param_1, PseudoRandomBitReg[param_1 + 1] & 1, docheck, bug);
}


// SMB:b70b
// SM2MAIN:8277
// Signature: [X, r07] -> []
void SetupBubble_buggy(const byte buggy_argument_1, const byte buggy_argument_2) {
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
  byte bVar1;

  bool cond = SprObject_Y_HighPos[0] < 2;
  cond = cond || ssw(false, SprObject_Y_HighPos[0] >= 0x82);

  if ((((OperMode != 0) && (GameEngineSubroutine >= 8)) && (GameEngineSubroutine != 0xb))
      && ((cond && (GameTimerCtrlTimer == 0)))) {
    bVar1 = GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2];
    if (bVar1 != 0) {
      if ((GameTimerDisplay[0] == 1) && ((GameTimerDisplay[1] | GameTimerDisplay[2]) == 0)) {
        EventMusicQueue = 0x40;
      }
      GameTimerCtrlTimer = 0x18;
      DigitModifier[5] = 0xff;
      DigitsMathRoutine(ssw(0x23, 0x17));
      PrintStatusBarNumbers(ssw(0xa4, 0xa2));
      return;
    }
    PlayerStatus = bVar1;
    ForceInjury(0);
    GameTimerExpiredFlag += 1;
  }
}


// SMB:b7a4
// SM2MAIN:8310
// Signature: [X] -> []
void WarpZoneObject(const byte param_1) {
  if ((ScrollLock != 0) && ((SprObject_Y_Position[0] & SprObject_Y_HighPos[0]) == 0)) {
    if (SMB1_ONLY) {
      WarpZoneControl += 1;
    }
    ScrollLock = SprObject_Y_Position[0] & SprObject_Y_HighPos[0];
    EraseEnemyObject(param_1);
  }
}


// SMB:b7b8
// SM2MAIN:8321
// Signature: [] -> []
void ProcessWhirlpools(void) {
  if (AreaType != 0) {
    return;
  }

  Cannon_Timer_Or_Whirlpool_Flag[0] = 0;

  if (TimerControl != 0) {
    return;
  }

  for (int i = 4; i >= 0; i--) {
    const byte whirlpool_x_hi = Cannon_Or_Whirlpool_PageLoc[i];
    const byte whirlpool_x_lo = Cannon_X_Position_Or_Whirlpool_LeftExtent[i];

    const byte player_x_hi = SprObject_PageLoc[0];
    const byte player_x_lo = SprObject_X_Position[0];

    const byte length = Cannon_Y_Position_Or_Whirlpool_Length[i];

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
          SUB_UNSIGNED_16_8(SprObject_PageLoc[0], SprObject_X_Position[0],
                            1);
        } else if ((Player_CollisionBits & 1) != 0) {
          // On the left side of the whirlpool, with collision bit
          // Pull the player to the right
          ADD_UNSIGNED_16_8(SprObject_PageLoc[0], SprObject_X_Position[0],
                            1);
        }
      }

      Cannon_Timer_Or_Whirlpool_Flag[0] = 1;

      const byte in_r01 = 0;
      ImposeGravity(0, 0, 0x10, in_r01, 1);

      return;
    }
  }
}


// SMB:b855
// SM2MAIN:83be
// Signature: [] -> []
void FlagpoleRoutine(void) {
  byte bVar1;
  bool bVar3;

  byte bVar2 = 5;
  ObjectOffset = 5;
  if (Enemy_ID[5] == 0x30) {
    if ((GameEngineSubroutine == 4) && (Player_State == 3)) {
      if ((Enemy_Y_Position[5] >= 0xaa) || (SprObject_Y_Position[0] >= 0xa2)) {
        if (SMB2J_ONLY && FlagpoleScore == 5) {
          NumberofLives += 1;
          Square2SoundQueue = 0x40;
        } else {
          DigitModifier[FlagpoleScoreDigits[FlagpoleScore]] = FlagpoleScoreMods[FlagpoleScore];
          AddToScore();
          bVar2 = ObjectOffset;
        }
        GameEngineSubroutine = 5;
      } else {
        bVar3 = SprObject_Y_Position[0] >= 0xa2;
        bVar1 = (BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] - 1) + bVar3;
        Enemy_Y_Position[5] = Enemy_Y_Position[5] + 1 + ((BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] != 0) || (bVar3 && bVar1 == 0));
        FlagpoleFNum_Y_Pos = (FlagpoleFNum_Y_Pos - 1) - (FlagpoleFNum_YMFDummy != 0xff);
        FlagpoleFNum_YMFDummy = FlagpoleFNum_YMFDummy + 1;
        BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[5] = bVar1;
      }
    }
    GetEnemyOffscreenBits(bVar2);
    RelativeEnemyPosition(ObjectOffset);
    FlagpoleGfxHandler(ObjectOffset);
  }
}


// SMB:b8ba
// SM2MAIN:8431
// Signature: [X] -> [X]
byte JumpspringHandler(const byte param_1) {
  byte bVar2;

  GetEnemyOffscreenBits(param_1);
  byte bVar1 = ObjectOffset;
  if ((TimerControl == 0) && (JumpspringAnimCtrl != 0)) {
    bVar2 = JumpspringAnimCtrl - 1;
    if ((bVar2 & 2) == 0) {
      SprObject_Y_Position[0] += 2;
    } else {
      SprObject_Y_Position[0] -= 2;
    }
    Enemy_Y_Position[bVar1] = SpriteVarData1[bVar1] + Jumpspring_Y_PosData[bVar2];
    if ((((bVar2 != 0) && ((A_B_Buttons & BUTTON_A) != 0)) && ((A_B_Buttons & BUTTON_A & PreviousA_B_Buttons) == 0))) {
      JumpspringForce = 0xf4;
      if (SMB2J_ONLY && (WorldNumber == 1 || WorldNumber == 2 || WorldNumber == 6)) {
        JumpspringForce = 0xe0;
      }
    }
    if (bVar2 == 3) {
      PlayerSpriteVarData2[0] = JumpspringForce;
      JumpspringAnimCtrl = 0;
    }
  }
  RelativeEnemyPosition(bVar1);
  EnemyGfxHandler(ObjectOffset);
  bVar1 = ObjectOffset;
  OffscreenBoundsCheck(bVar1);
  if ((JumpspringAnimCtrl != 0) && (JumpspringTimer == 0)) {
    JumpspringTimer = 4;
    JumpspringAnimCtrl += 1;
  }
  return bVar1;
}


// SMB:b91e
// SM2MAIN:84aa
// Signature: [X, Y] -> []
void Setup_Vine(const byte param_1, const byte param_2) {
  // NES note: Y=0x60 is passed by CheckpointEnemyID. This is a bug.
  const bool bug = param_2 == 0x60;

  assert_eq_assumption(param_2 == 0 || param_2 == 1 || param_2 == 0x60, true);

  Enemy_ID[param_1] = 0x2f;
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
  Square2SoundQueue = 4;
}


// SMB:b94b
// SM2MAIN:84d7
// Signature: [X] -> []
void VineObjectHandler(const byte objoff) {
  if (objoff != 5) {
    return;
  }

  if (VineHeight != VineHeightData[(byte)(VineFlagOffset - 1)]) {
    if ((FrameCounter & 2) != 0) {
      Enemy_Y_Position[5] -= 1;
      VineHeight += 1;
    }
  }

  if (VineHeight >= 8) {
    RelativeEnemyPosition(5);
    GetEnemyOffscreenBits(objoff);

    // There are loops in the original that loop 256 times if 0, or only once if the decrement is negative,
    // so it's easier if we just assume this is true.
    // VineFlagOffset should only be 1 or 2, but the loops in this port are accurate for the following range.
    assert_eq_assumption(VineFlagOffset >= 1 && VineFlagOffset <= 129, true);

    for (int i = 0; i < VineFlagOffset; i++) {
      DrawVine(i);
    }

    if ((Enemy_OffscreenBits & 0xc) != 0) {
      for (int i = VineFlagOffset-1; i >= 0; i--) {
        const byte vineobjoff = VineObjOffset[i];
        EraseEnemyObject(vineobjoff);
      }

      // NES note: these are set to 0 because EraseEnemyObject always set the A register to 0
      VineHeight = 0;
      VineFlagOffset = 0;
    }

    if (VineHeight >= 0x20) {
      const struct blockbuffer_colli_result sVar6 = BlockBufferCollision(1, 6, 0x1b);
      const u16 mt_x = sVar6.mt_x;
      const u16 mt_y = sVar6.mt_y;

      if (mt_y < 13) {
        const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);

        if (Block_Buffers[blockoff] == 0) {
          Block_Buffers[blockoff] = ssw(0x26, 0x23);
        }
      }
    }
  }

#ifdef SMB2J_MODE
  const byte cmpA = (byte)((Enemy_PageLoc[5] - ScreenEdgeOrLeft_PageLoc[0]) - (Enemy_X_Position[5] < ScreenEdgeOrLeft_X_Pos[0]));
  const byte cmpB = (byte)(Enemy_X_Position[5] - ScreenEdgeOrLeft_X_Pos[0]);
  if ((cmpA >= 0x80) || (cmpB < 9)) {
    Enemy_Flag[5] = 0;

    const bool even_page = (Enemy_PageLoc[5] & 1) == 0;

    const u16 blockoff = even_page ? BLOCK_BUFFER_1_OFFSET : BLOCK_BUFFER_2_OFFSET;

    const byte x = Enemy_X_Position[5] >> 4;

    for (int i = 0; i < 13; i++) {
      if (Block_Buffers[blockoff + i*0x10 + x] == 0x23) {
        Block_Buffers[blockoff + i*0x10 + x] = 0;
      }
    }
  }
#endif
}


// SMB:b9bc
// SM2MAIN:8587
// Signature: [] -> []
void ProcessCannons(void) {
  if (AreaType == 0) {
    return;
  }

  for (int i = 2; i >= 0; i--) {
    ObjectOffset = i;

    bool chk_bb = true;

    if (Enemy_Flag[i] == 0) {
      const byte rng = PseudoRandomBitReg[i + 1] & (SecondaryHardMode == 0 ? 15 : 7);

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
            Enemy_ID[i] = 0x33;

            chk_bb = false;
          }
        }
      }
    }

    if (chk_bb) {
      if (Enemy_ID[i] == 0x33) {
        OffscreenBoundsCheck(i);
        if (Enemy_Flag[i] != 0) {
          GetEnemyOffscreenBits(i);

          assert_eq_assumption(ObjectOffset, i);

          const byte res = BulletBillHandler(i);

          assert_eq_assumption(res, i);
        }
      }
    }
  }
}


// SMB:ba33
// SM2MAIN:85fe
// Signature: [X] -> [X]
byte BulletBillHandler(const byte param_1) {
  struct_ncr00 sVar2;

  byte arg;
  if (TimerControl == 0) {
    if (Enemy_State[param_1] == 0) {
      if ((Enemy_OffscreenBits & 0xc) == 0xc) {
        EraseEnemyObject(param_1);
        return param_1;
      }
      byte bVar1 = 1;
      sVar2 = PlayerEnemyDiff(param_1);
      if (!sVar2.n) {
        bVar1 += 1;
      }
      Enemy_MovingDir[param_1] = bVar1;
      SpriteVarData1[param_1] = BulletBillXSpdData[(byte)(bVar1 - 1)];
      if ((byte)(sVar2.r00 + 0x28 + sVar2.c) < 0x50) {
        EraseEnemyObject(param_1);
        return param_1;
      }
      Enemy_State[param_1] = 1;
      EnemyFrameTimer[param_1] = 10;
      Square2SoundQueue = 8;
    }
    if ((Enemy_State[param_1] & 0x20) != 0) {
      MoveD_EnemyVertically(param_1);
      MoveEnemyHorizontally(ObjectOffset);
    } else {
      MoveEnemyHorizontally(param_1);
    }
    arg = ObjectOffset;
  } else {
    arg = param_1;
  }
  GetEnemyOffscreenBits(arg);
  byte objoff = ObjectOffset;
  RelativeEnemyPosition(objoff);
  GetEnemyBoundBox(objoff);
  PlayerEnemyCollision(objoff);
  EnemyGfxHandler(objoff);
  return ObjectOffset;
}


// SMB:ba94
// SM2MAIN:865f
// Signature: [] -> [X, C]
struct_xc SpawnHammerObj(void) {
  struct_xc sVar3;
  struct_xc sVar4;

  const byte bVar1 = ObjectOffset;
  byte bVar2 = PseudoRandomBitReg[1] & 7;
  if (bVar2 == 0) {
    bVar2 = PseudoRandomBitReg[1] & 8;
  }
  if ((Misc_State[bVar2] == 0) && (Enemy_Flag[HammerEnemyOfsData[bVar2]] == 0)) {
    HammerEnemyOffset[bVar2] = ObjectOffset;
    Misc_State[bVar2] = 0x90;
    Misc_BoundBoxCtrl[bVar2] = 7;
    sVar3.c = true;
    sVar3.x = bVar1;
    return sVar3;
  }
  sVar4.c = false;
  sVar4.x = ObjectOffset;
  return sVar4;
}


// SMB:bb38
// SM2MAIN:8703
// Signature: [X] -> []
void CoinBlock(const byte param_1) {
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
  ObjectOffset = param_1;
}


// SMB:bb6c
// SM2MAIN:8737
// Signature: [X, Y] -> []
void JCoinC(const byte param_1, const byte param_2) {
  Misc_Y_Speed[param_2] = 0xfb;
  Misc_Y_HighPos[param_2] = 1;
  Misc_State[param_2] = 1;
  Square2SoundQueue = 1;
  GiveOneCoin();
  CoinTallyFor1Ups = CoinTallyFor1Ups + 1;
}


// SMB:bac3
// SM2MAIN:868e
// Signature: [X] -> []
static inline void ProcHammerObj(const int i) {
  assert_eq_assumption(i, ObjectOffset);

  if (TimerControl == 0) {
    if ((Misc_State[i] & 0x7f) < 2) {
      const byte bVar2 = i + 0xd;

      const byte in_r01 = 0xf;
      ImposeGravity(0, bVar2, 0x10, in_r01, 4);

      MoveObjectHorizontally(bVar2);
      const byte x = PlayerHammerCollision(ObjectOffset);
      assert_eq_assumption(x, i);
    } else {
      const byte bVar2 = HammerEnemyOffset[i];
      if ((Misc_State[i] & 0x7f) == 2) {
        // SetHSpd
        Misc_Y_Speed[i] = 0xfe;
        Enemy_State[bVar2] = Enemy_State[bVar2] & 0xf7;

        assert_eq_assumption(i, ObjectOffset);

        Misc_X_Speed[i] = HammerXSpdData[(byte)(Enemy_MovingDir[bVar2] - 1)];
      }

      // SetHPos
      Misc_State[i] -= 1;

      ADD_UNSIGNED_16_16_8(Misc_PageLoc[i], Misc_X_Position[i],
                           Enemy_PageLoc[bVar2], Enemy_X_Position[bVar2],
                           2);

      Misc_Y_Position[i] = Enemy_Y_Position[bVar2] - 10;
      Misc_Y_HighPos[i] = 1;
    }
  }

  byte x = i;
  GetMiscOffscreenBits(x);
  RelativeMiscPosition(ObjectOffset);
  x = ObjectOffset;
  GetMiscBoundBox(x);
  DrawHammer(ObjectOffset, ObjectOffset);

  assert_eq_assumption(ObjectOffset, i);
}

// SMB:bba7
// SM2MAIN:8772
// Signature: [X] -> []
static inline void ProcJumpCoin(const int i) {
  assert_eq_assumption(i, ObjectOffset);

  if (Misc_State[i] == 1) {
    // JCoinRun
    const byte in_r01 = 3;
    ImposeGravity(0, i + 0xd, 0x50, in_r01, 6);

    assert_eq_assumption(i, ObjectOffset);

    if (Misc_Y_Speed[i] == 5) {
      Misc_State[i] += 1;
    }
  } else {
    Misc_State[i] += 1;

    ADD_UNSIGNED_16_8(Misc_PageLoc[i], Misc_X_Position[i],
                      ScrollAmount);

    if (Misc_State[i] == 0x30) {
      Misc_State[i] = 0;
      return;
    }
  }

  assert_eq_assumption(i, ObjectOffset);

  byte x = i;
  RelativeMiscPosition(x);
  x = ObjectOffset;
  GetMiscOffscreenBits(x);
  GetMiscBoundBox(ObjectOffset);
  x = JCoinGfxHandler(ObjectOffset);

  assert_eq_assumption(x, i);
}

// SMB:bb96
// SM2MAIN:8761
// Signature: [] -> []
void MiscObjectsCore(void) {
  // Note: Some of the array accesses of [i] are really [ObjectOffset] in the NES version,
  // but it's way simpler to convey as the former.
  // ObjectOffset shares the loop index, and shouldn't change during functions.
  // We use asserts to make sure functions behave and return the expected values.
  //
  // There are _possible_ edge cases (unsure) where buffer overflows to arrays
  // could wraparound the zero page and set ObjectOffset, but that's such an
  // annoying possibility that we're just not handling it.
  // (and it would possibly mangle the temporary registers $00-$07 anyway, so whatever)

  for (int i = 8; i >= 0; i--) {
    if (Misc_State[i] == 0) {
      continue;
    }

    ObjectOffset = i;

    if ((i8)Misc_State[i] < 0) {
      ProcHammerObj(i);
    } else {
      ProcJumpCoin(i);
    }
  }

  ObjectOffset = 0;
}


// SMB:bbfe
// SM2MAIN:87c3
// Signature: [] -> []
void GiveOneCoin(void) {
  DigitModifier[5] = 1;

#ifdef SMB1_MODE
  DigitsMathRoutine(CoinTallyOffsets[CurrentPlayer]);
#endif
#ifdef SMB2J_MODE
  DigitsMathRoutine(0x11);
#endif

  CoinTally += 1;
  if (CoinTally == 100) {
    CoinTally = 0;
    NumberofLives += 1;
    Square2SoundQueue = 0x40;
  }
  DigitModifier[4] = 2;
  AddToScore();
}


// SMB:bc27
// SM2MAIN:87e8
// Signature: [] -> []
void AddToScore(void) {
#ifdef SMB1_MODE
  DigitsMathRoutine(ScoreOffsets[CurrentPlayer]);
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
    WriteDigits(StatusBarNybbles[CurrentPlayer]);
  #endif

  #ifdef SMB2J_MODE
    WriteDigits(1);
  #endif
}


// SMB:bc36
// SM2MAIN:87ef
// Signature: [A] -> []
void WriteDigits(const byte param_1) {
  PrintStatusBarNumbers(param_1);
  if (VRAM_Buffer1[VRAM_Buffer1_Offset - 6] == 0) {
    VRAM_Buffer1[VRAM_Buffer1_Offset - 6] = 0x24;
  }
}


// SMB:bc49
// SM2MAIN:8802
// Signature: [X] -> []
void SetupPowerUp(const byte param_1) {
  Enemy_ID[5] = 0x2e;
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
  if ((PowerUpType < 2)) {
    PowerUpType = PlayerStatus;
    if (PlayerStatus > 1) {
      PowerUpType = PlayerStatus >> 1;
    }
  }
  Enemy_SprAttrib[5] = 0x20;
  Square2SoundQueue = 2;
}


// SMB:bc85
// SM2MAIN:883e
// Signature: [] -> [X]
byte PowerUpObjHandler(void) {
  bool bVar2;

  byte bVar1 = 5;
  ObjectOffset = 5;
  if (Enemy_State[5] != 0) {
    if ((char)Enemy_State[5] < 0) {
      if (TimerControl == 0) {
        const bool smb2j_powerups = SMB2J_ONLY && (PowerUpType == 4 || PowerUpType == 5);
        if (PowerUpType == 0 || PowerUpType == 3 || smb2j_powerups) {
          bVar1 = MoveNormalEnemy(5);
          bVar1 = EnemyToBGCollisionDet(bVar1);
        } else if (PowerUpType == 2) {
          MoveJumpingEnemy(5);
          bVar1 = ObjectOffset;
          bVar1 = EnemyJump(bVar1);
        }
      }
    } else {
      if ((FrameCounter & 3) == 0) {
        Enemy_Y_Position[5] -= 1;
        bVar2 = Enemy_State[5] > 0x10;
        Enemy_State[5] = Enemy_State[5] + 1;
        if (bVar2) {
          SpriteVarData1[5] = 0x10;
          Enemy_State[5] = 0x80;
          Enemy_SprAttrib[5] = 0;
          Enemy_MovingDir[5] = 1;
        }
      }
      if (Enemy_State[5] < 6) {
        ObjectOffset = 5;
        return 5;
      }
    }
    RelativeEnemyPosition(bVar1);
    GetEnemyOffscreenBits(ObjectOffset);
    GetEnemyBoundBox(ObjectOffset);
    DrawPowerUp();
    bVar1 = ObjectOffset;
    PlayerEnemyCollision(bVar1);
    OffscreenBoundsCheck(bVar1);
  }
  return bVar1;
}


// SMB:bced
// SM2MAIN:88ae
void PlayerHeadCollision(const byte param_1, const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [A, r02, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);

  Block_State[SprDataOffset_Ctrl] = (PlayerSize == 0) ? 0x12 : 0x11;
  DestroyBlockMetatile(mt_x, mt_y);

  const byte sprdataoff = SprDataOffset_Ctrl;

  // These are only read from BlockObjMT_Updater.
  Block_Orig_YPos[sprdataoff] = mt_y * 16;
  Block_BBuf_Low[sprdataoff] = MTX_TO_R06(mt_x);

  byte bVar4 = Block_Buffers[blockoff];

  const struct_yc sVar5 = BlockBumpedChk(bVar4);
  byte bVar2 = (PlayerSize == 0) ? 0 : bVar4;
  if (sVar5.c) {
    Block_State[sprdataoff] = 0x11;
    if ((bVar4 == ssw(0x58, 0x56)) || (bVar4 == ssw(0x5d, 0x5c))) {
      if (BrickCoinTimerFlag == 0) {
        BrickCoinTimer = 0xb;
        BrickCoinTimerFlag = 1;
      }
      bVar2 = (BrickCoinTimer == 0) ? ssw(0xc4, 0xc5) : bVar4;
    } else {
      bVar2 = ssw(0xc4, 0xc5);
    }
  }
  Block_Metatile[sprdataoff] = bVar2;
  InitBlock_XY_Pos(sprdataoff);

  Block_Buffers[blockoff] = ssw(0x23, 0x20);

  BlockBounceTimer = 0x10;
  bVar4 = ((CrouchingFlag != 0) || (PlayerSize != 0)) ? 1 : 0;
  Block_Y_Position[sprdataoff] = (SprObject_Y_Position[0] + BlockYPosAdderData[bVar4]) & 0xf0;

  if (Block_State[sprdataoff] == 0x11) {
    BumpBlock(mt_x, mt_y, param_1);
  } else {
    BrickShatter(mt_x, mt_y);
  }
  SprDataOffset_Ctrl = SprDataOffset_Ctrl ^ 1;
}


// SMB:bd84
// SM2MAIN:8945
// Signature: [X] -> []
void InitBlock_XY_Pos(const byte param_1) {
  ADD_UNSIGNED_16_16_8(Block_PageLoc[param_1], Block_X_Position[param_1],
                       SprObject_PageLoc[0], SprObject_X_Position[0],
                       8);

  Block_X_Position[param_1] &= 0xf0;
  Block_PageLoc2[param_1] = Block_PageLoc[param_1];

  Block_Y_HighPos[param_1] = SprObject_Y_HighPos[0];
}


enum BumpBlock_jumptable_item {
  BUMPBLOCK_MUSHFLOWERBLOCK_1,
#ifdef SMB2J_MODE
  BUMPBLOCK_POISONMUSHBLOCK_1,
#endif
  BUMPBLOCK_COINBLOCK_1,
  BUMPBLOCK_COINBLOCK_2,
  BUMPBLOCK_EXTRALIFEMUSHBLOCK_1,
#ifdef SMB2J_MODE
  BUMPBLOCK_POISONMUSHBLOCK_2,
#endif
#ifdef SMB2J_MODE
  BUMPBLOCK_MUSHFLOWERBLOCK_3,
#endif
  BUMPBLOCK_MUSHFLOWERBLOCK_2,
#ifdef SMB2J_MODE
  BUMPBLOCK_POISONMUSHBLOCK_3,
#endif
  BUMPBLOCK_VINEBLOCK,
  BUMPBLOCK_STARBLOCK,
  BUMPBLOCK_COINBLOCK_3,
  BUMPBLOCK_EXTRALIFEMUSHBLOCK_2,

  BUMPBLOCK_COUNT
};


// SMB:bd9b
// SM2MAIN:895c
void BumpBlock(const u16 mt_x, const u16 mt_y, const byte param_2) {
  // Note: Old signature was [r02, r05, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  bool bug = false;
  byte bug_addr_hi = 0;

  // NES note: We're reimplementing a bug here.
  // The call to `CheckTopOfBlock` might set $05 to a value between 0x20 and 0x28 inclusive.
  // The value in $05 is later used as an argument to `BlockBumpedChk`:
  //   LDA $05
  //   JSR BlockBumpedChk
  //
  // Unmodded ROMs for SMB1 and SMB2J will never match anything in `BlockBumpedChk` in this case,
  // because all values in the BrickQBlockMetatiles table are >= 0x52.
  // However, because I'm unsure whether to hardcode that table or not (is it sufficiently code-like?), I'm moving the bug here.
#if 1
  // Start bug reimplementation here

  // -> CheckTopOfBlock
  if (mt_y > 0) {
    const u16 mt_y_above = mt_y - 1;
    const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y_above);
    if (Block_Buffers[blockoff] == ssw(0xc2, 0xc3)) {
      // -> RemoveCoin_Axe
      //   -> PutBlockMetatile

      const byte x  = mt_x % 16;
      const byte y  = mt_y_above + MT_Y_TOP_MARGIN;
      const byte nt = (mt_x & 0x10) == 0 ? 0 : 1;
      const u16 nametable = nt == 0 ? 0x2000 : 0x2400;
      const u16 addr = nametable + (y*2*32) + x*2;

      // The theorerical range for addr is 0x2080 to 0x289a inclusive.

      bug = true;
      bug_addr_hi = addr >> 8;
    }
  }

  // End bug reimplementation here
#endif

  const byte bVar2 = CheckTopOfBlock(mt_x, mt_y);
  Square1SoundQueue = 2;
  Block_X_Speed[bVar2] = 0;
  Block_Y_MoveForce[bVar2] = 0;
  PlayerSpriteVarData2[0] = 0;
  Block_Y_Speed[bVar2] = 0xfe;

  struct_yc sVar4;

  if (bug) {
    sVar4 = BlockBumpedChk(bug_addr_hi);
  } else {
    sVar4 = BlockBumpedChk(param_2);
  }

  byte bVar1 = sVar4.y;
  if (!sVar4.c) {
    return;
  }

  // If the block goes over the block count in the lookup, wrap around back to a previous item
  if (bVar1 >= BUMPBLOCK_COUNT) {
    bVar1 -= BUMPBLOCK_COUNT;
    bVar1 += BUMPBLOCK_MUSHFLOWERBLOCK_2;
  }

  switch (bVar1) {
  case BUMPBLOCK_MUSHFLOWERBLOCK_1:
  case BUMPBLOCK_MUSHFLOWERBLOCK_2:
    MushFlowerBlock(bVar2);
    return;

  case BUMPBLOCK_COINBLOCK_1:
  case BUMPBLOCK_COINBLOCK_2:
  case BUMPBLOCK_COINBLOCK_3:
    CoinBlock(bVar2);
    return;

  case BUMPBLOCK_EXTRALIFEMUSHBLOCK_1:
  case BUMPBLOCK_EXTRALIFEMUSHBLOCK_2:
    ExtraLifeMushBlock(bVar2);
    return;

  case BUMPBLOCK_VINEBLOCK:
    VineBlock();
    return;

  case BUMPBLOCK_STARBLOCK:
    StarBlock(bVar2);
    return;

#ifdef SMB2J_MODE
  case BUMPBLOCK_MUSHFLOWERBLOCK_3:
    MushFlowerBlock(bVar2);
    return;

  case BUMPBLOCK_POISONMUSHBLOCK_1:
  case BUMPBLOCK_POISONMUSHBLOCK_2:
  case BUMPBLOCK_POISONMUSHBLOCK_3:
    PoisonMushBlock(bVar2);
    return;
#endif

  default:
    jmpengine_overflow(bVar1);
  }
}


// SMB:bdd2
// SM2MAIN:899b
// Signature: [X] -> []
void MushFlowerBlock(const byte param_1) {
  PowerUpType = 0;
  SetupPowerUp(param_1);
}


// SMB:bdd5
// SM2MAIN:899e
// Signature: [X] -> []
void StarBlock(const byte param_1) {
  PowerUpType = 2;
  SetupPowerUp(param_1);
}


// SMB:bdd8
// SM2MAIN:89a4
// Signature: [X] -> []
void ExtraLifeMushBlock(const byte param_1) {
  PowerUpType = 3;
  SetupPowerUp(param_1);
}


// SMB:bddf
// SM2MAIN:89ab
// Signature: [] -> []
void VineBlock(void) {
  Setup_Vine(5, SprDataOffset_Ctrl);
}


// SMB:bdf6
// SM2MAIN:89c7
// Signature: [A] -> [Y, C]
struct_yc BlockBumpedChk(const byte param_1) {
  struct_yc sVar3;

  for (int i = ssw(13, 18); i >= 0; i--) {
    if (param_1 == BrickQBlockMetatiles[i]) {
      sVar3.c = true;
      sVar3.y = i;
      return sVar3;
    }
  }

  // NES Note: "y" value is unused if c = false
  sVar3.c = false;
  sVar3.y = -1;
  return sVar3;
}


// SMB:be02
// SM2MAIN:89d3
void BrickShatter(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  const byte sVar1 = CheckTopOfBlock(mt_x, mt_y);
  Block_RepFlag[sVar1] = 1;
  NoiseSoundQueue = 1;
  SpawnBrickChunks(sVar1);
  PlayerSpriteVarData2[0] = 0xfe;
  DigitModifier[5] = 5;
  AddToScore();
}


// SMB:be1f
// SM2MAIN:89f0
byte CheckTopOfBlock(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06, r07] -> [X]
  // Reworked to use metatile coordinates instead of pointer

  if (mt_y == 0) {
    return SprDataOffset_Ctrl;
  }

  const u16 mt_y_above = mt_y - 1;
  const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y_above);
  if (Block_Buffers[blockoff] != ssw(0xc2, 0xc3)) {
    return SprDataOffset_Ctrl;
  }

  Block_Buffers[blockoff] = 0;
  RemoveCoin_Axe(mt_x, mt_y_above);

  const byte sprdataoffset_ctrl = SprDataOffset_Ctrl;

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
  ObjectOffset = sprdataoffset_ctrl;
  return ObjectOffset;
}


// SMB:be41
// SM2MAIN:8a12
// Signature: [X] -> []
void SpawnBrickChunks(const byte param_1) {
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
// Signature: [X] -> [X]
byte BlockObjectsCore(const byte param_1) {
  byte bStack0000 = Block_State[param_1];
  if (bStack0000 == 0) {
    Block_State[param_1] = 0;
    return param_1;
  }
  bStack0000 &= 0xf;
  if (bStack0000 == 1) {
    ImposeGravityBlock(param_1 + 9);
    RelativeBlockPosition(ObjectOffset);
    GetBlockOffscreenBits(ObjectOffset);
    DrawBlock(ObjectOffset);
    const byte tmp1 = ObjectOffset;
    if (4 < (Block_Y_Position[tmp1] & 0xf)) {
      Block_State[tmp1] = 1;
      return tmp1;
    }
    Block_RepFlag[tmp1] = 1;
    Block_State[tmp1] = 0;
    return tmp1;
  } else {
    ImposeGravityBlock(param_1 + 9);
    MoveObjectHorizontally(param_1 + 9);
    ImposeGravityBlock(param_1 + 9 + 2);
    MoveObjectHorizontally(param_1 + 9 + 2);
    RelativeBlockPosition(ObjectOffset);
    GetBlockOffscreenBits(ObjectOffset);
    const byte objoff = ObjectOffset;
    DrawBrickChunks(objoff);
    if (Block_Y_HighPos[objoff] == 0) {
      Block_State[objoff] = bStack0000;
      return objoff;
    }
    if (Block_Y_Position[objoff + 2] > 0xf0) {
      Block_Y_Position[objoff + 2] = 0xf0;
    }
    if (Block_Y_Position[objoff] < 0xf0) {
      Block_State[objoff] = bStack0000;
      return objoff;
    }
    Block_State[objoff] = 0;
    return objoff;
  }
}


// SMB:bed4
// SM2MAIN:8aa5
// Signature: [] -> []
void BlockObjMT_Updater(void) {
  for (int i = 1; i >= 0; i--) {
    ObjectOffset = i;

    if (VRAM_Buffer1[0] != 0) {
      continue;
    }

    if (Block_RepFlag[i] == 0) {
      continue;
    }

    // These are only written from PlayerHeadCollision.
    const byte bbuf_lo = Block_BBuf_Low[i];
    const byte ypos = Block_Orig_YPos[i];
    const byte metatile = Block_Metatile[i];

    const u16 mt_x = R06_TO_MTX_lossy(bbuf_lo);
    const u16 mt_y = R02_TO_MTY(ypos);
    const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);

    Block_Buffers[blockoff] = metatile;

    ReplaceBlockMetatile(metatile, i, mt_x, mt_y);

    Block_RepFlag[i] = 0;
  }
}


// SMB:bf02
// SM2MAIN:8ad3
// Signature: [X] -> [A]
byte MoveEnemyHorizontally(const byte param_1) {
  return MoveObjectHorizontally(param_1 + 1);
}


// SMB:bf09
// SM2MAIN:8ada
// Signature: [] -> [A]
byte MovePlayerHorizontally(void) {
  if (JumpspringAnimCtrl == 0) {
    return MoveObjectHorizontally(0);
  }
  return JumpspringAnimCtrl;
}


// SMB:bf0f
// SM2MAIN:8ae0
// Signature: [X] -> [A]
byte MoveObjectHorizontally(const byte param_1) {
  // NES note: the original sign-extends the high nibble (ORA #$F0), but we just cast it to signed here.
  const i16 b = ((i16)(i8)PlayerSpriteVarData1[param_1]) << 4;

  const byte old_x = SprObject_X_Position[param_1];

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
void MoveD_EnemyVertically(const byte param_1) {
  if (Enemy_State[param_1] == 5) {
    MoveFallingPlatform(param_1);
  } else {
    SetXMoveAmt(3, param_1, 0x3d);
  }
}


// SMB:bf6b
// SM2MAIN:8b3c
// Signature: [X] -> []
void MoveFallingPlatform(const byte param_1) {
  SetXMoveAmt(3, param_1, 0x20);
}


// SMB:bf70
// SM2MAIN:8b41
// Signature: [X] -> []
void MoveRedPTroopaDown(const byte param_1) {
  ImposeGravity(0, param_1 + 1, 3, 6, 2);
}


// SMB:bf75
// SM2MAIN:8b46
// Signature: [X] -> []
void MoveRedPTroopaUp(const byte param_1) {
  ImposeGravity(1, param_1 + 1, 3, 6, 2);
}


// SMB:bf88
// SM2MAIN:8b59
// Signature: [X] -> []
void MoveDropPlatform(const byte param_1) {
  SetXMoveAmt(2, param_1, 0x7f);
}


// SMB:bf8c
// SM2MAIN:8b5d
// Signature: [X] -> []
void MoveEnemySlowVert(const byte param_1) {
  SetXMoveAmt(2, param_1, 0xf);
}


// SMB:bf92
// SM2MAIN:8b63
// Signature: [X] -> []
void MoveJ_EnemyVertically(const byte param_1) {
  SetXMoveAmt(3, param_1, 0x1c);
}


// SMB:bf96
// SM2MAIN:8b67
// Signature: [A, X, Y] -> []
void SetXMoveAmt(const byte param_1, const byte param_2, const byte param_3) {
  ImposeGravitySprObj(param_1, param_2 + 1, param_3);
}


// SMB:bfa4
// SM2MAIN:8b75
// Signature: [X] -> []
void ImposeGravityBlock(const byte param_1) {
  const byte in_r01 = 0;

  ImposeGravity(0, param_1, 0x50, in_r01, MaxSpdBlockData[1]);
}


// SMB:bfad
// SM2MAIN:8b7e
// Signature: [A, X, r00] -> []
void ImposeGravitySprObj(const byte param_1, const byte param_2, const byte param_3) {
  const byte in_r01 = 0;

  ImposeGravity(0, param_2, param_3, in_r01, param_1);
}


// SMB:bfb4
// SM2MAIN:8b85
// Signature: [X] -> []
void MovePlatformDown(const byte param_1) {
  const byte bVar1 = (Enemy_ID[param_1] == 0x29) ? 9 : 5;
  ImposeGravity(0, param_1 + 1, bVar1, 10, 3);
}


// SMB:bfb7
// SM2MAIN:8b88
// Signature: [X] -> []
void MovePlatformUp(const byte param_1) {
  const byte bVar1 = (Enemy_ID[param_1] == 0x29) ? 9 : 5;
  ImposeGravity(1, param_1 + 1, bVar1, 10, 3);
}


// SMB:bfd7
// SM2MAIN:8ba8
// Signature: [A, X, r00, r01, r02] -> []
void ImposeGravity(const byte param_1, const byte param_2, const byte param_3, const byte param_4, const byte param_5) {
  ADD_SIGNED_24_16(SprObject_Y_HighPos[param_2], SprObject_Y_Position[param_2], SprObject_YMF_Dummy[param_2],
                   SprObject_Y_Speed[param_2], SprObject_Y_MoveForce[param_2]);

  ADD_UNSIGNED_16_8(SprObject_Y_Speed[param_2], SprObject_Y_MoveForce[param_2],
                    param_3);

  const byte q = param_5;
  const byte h = SprObject_Y_Speed[param_2];
  const byte r = SprObject_Y_MoveForce[param_2];

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

    const byte s = SprObject_Y_Speed[param_2];
    const byte t = SprObject_Y_MoveForce[param_2];

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
// Signature: [X] -> [X]
byte EnemiesAndLoopsCore(const byte param_1) {
  if (Enemy_Flag[param_1] & 0x80) {
    if (Enemy_Flag[Enemy_Flag[param_1] & 0xf] == 0) {
      Enemy_Flag[param_1] = 0;
    }
  } else {
    if (Enemy_Flag[param_1] != 0) {
      return RunEnemyObjectsCore();
    }
    if ((AreaParserTaskNum & 7) != 7) {
      return ProcLoopCommand(param_1);
    }
  }
  return param_1;
}


// SMB:c08c
// SM2MAIN:8c77
// Signature: [Y] -> []
void ExecGameLoopback(const byte param_1) {
  SprObject_PageLoc[0] = SprObject_PageLoc[0] - 4;
  CurrentPageLoc = CurrentPageLoc - 4;
  ScreenEdgeOrLeft_PageLoc[0] = ScreenEdgeOrLeft_PageLoc[0] - 4;
  ScreenRight_PageLoc = ScreenRight_PageLoc - 4;
  AreaObjectPageLoc = AreaObjectPageLoc - 4;
  EnemyObjectPageSel = 0;
  AreaObjectPageSel = 0;
  EnemyDataOffset = 0;
  EnemyObjectPageLoc = 0;
  AreaDataOffset = AreaDataOfsLoopback[param_1];
}


// SMB:c0cc
// SM2MAIN:8cb7
// Signature: [X] -> [X]
byte ProcLoopCommand(const byte param_1) {
  byte bVar3;
  bool bVar6;

  byte tmp1 = param_1;

  do {
    if (LoopCommand != 0 && CurrentColumnPos == 0) {
      for (int idx = ssw(0xb,0xc)-1; idx >= 0; idx--) {
        if (WorldNumber != LoopCmdWorldNumber[idx] || CurrentPageLoc != LoopCmdPageNumber[idx]) {
          continue;
        }

        if (SprObject_Y_Position[0] == LoopCmdYPosition[idx] && Player_State == 0) {
          MultiLoopCorrectCntr += 1;
        }

        if (SMB1_ONLY && WorldNumber != 6) {
          if (SprObject_Y_Position[0] != LoopCmdYPosition[idx] || Player_State != 0) {
            ExecGameLoopback(idx);
            KillAllEnemies();
            tmp1 = ObjectOffset;
          }
          MultiLoopPassCntr = 0;
          MultiLoopCorrectCntr = 0;
          LoopCommand = 0;
          break;
        }

        MultiLoopPassCntr += 1;
    #ifdef SMB1_MODE
        const byte cmp_val = 3;
    #endif
    #ifdef SMB2J_MODE
        const byte cmp_val = MultiLoopCount[idx];
    #endif
        if (MultiLoopPassCntr == cmp_val) {
          if (MultiLoopCorrectCntr != cmp_val) {
            ExecGameLoopback(idx);
            KillAllEnemies();
            tmp1 = ObjectOffset;
          }
          MultiLoopPassCntr = 0;
          MultiLoopCorrectCntr = 0;
        }
        LoopCommand = 0;
        break;
      }
    }

    byte bVar4 = EnemyDataOffset;
    if (EnemyFrenzyQueue != 0) {
      Enemy_ID[tmp1] = EnemyFrenzyQueue;
      Enemy_Flag[tmp1] = 1;
      Enemy_State[tmp1] = 0;
      EnemyFrenzyQueue = 0;
      InitEnemyObject(tmp1);
      return tmp1;
    }

    if (EnemyData[EnemyDataOffset] == 0xff) {
      // CheckFrenzyBuffer
      bVar4 = EnemyFrenzyBuffer;
      if (EnemyFrenzyBuffer == 0) {
        if (VineFlagOffset != 1) {
          return tmp1;
        }
        bVar4 = 0x2f;
      }
      Enemy_ID[tmp1] = bVar4;
      InitEnemyObject(tmp1);
      return tmp1;
    }

    if ((((EnemyData[EnemyDataOffset] & 0xf) != 0xe) && (tmp1 >= 5))
        && ((EnemyData[(byte)(EnemyDataOffset + 1)] & 0x3f) != 0x2e)) {
      return tmp1;
    }

    byte bVar1 = ScreenRight_X_Pos + 0x30;
    const byte bVar2 = ScreenRight_PageLoc + (ScreenRight_X_Pos >= 0xd0);
    const byte bVar5 = EnemyDataOffset + 1;
    if (((char)EnemyData[bVar5] < 0) && (EnemyObjectPageSel == 0)) {
      EnemyObjectPageSel = 1;
      EnemyObjectPageLoc += 1;
    }

    if (((EnemyData[EnemyDataOffset] & 0xf) != 0xf) || (EnemyObjectPageSel != 0)) {
      Enemy_PageLoc[tmp1] = EnemyObjectPageLoc;
      bVar3 = EnemyData[bVar4] & 0xf0;
      Enemy_X_Position[tmp1] = bVar3;
      if ((ScreenRight_X_Pos <= bVar3 && ScreenRight_PageLoc <= Enemy_PageLoc[tmp1])
          || (ScreenRight_X_Pos > bVar3 && ScreenRight_PageLoc < Enemy_PageLoc[tmp1])) {
        bVar6 = (bVar1 & 0xf0) < Enemy_X_Position[tmp1];
        if ((bVar6 || bVar2 < Enemy_PageLoc[tmp1]) && (!bVar6 || bVar2 <= Enemy_PageLoc[tmp1])) {
          // CheckFrenzyBuffer
          bVar4 = EnemyFrenzyBuffer;
          if (EnemyFrenzyBuffer == 0) {
            if (VineFlagOffset != 1) {
              return tmp1;
            }
            bVar4 = 0x2f;
          }
          Enemy_ID[tmp1] = bVar4;
          InitEnemyObject(tmp1);
          return tmp1;
        }
        Enemy_Y_HighPos[tmp1] = 1;
        bVar1 = EnemyData[bVar4];
        Enemy_Y_Position[tmp1] = bVar1 * 0x10;
        if ((byte)(bVar1 * 0x10) != 0xe0) {
          if (((EnemyData[bVar5] & 0x40) != 0) && (SecondaryHardMode == 0)) {
            EnemyDataOffset = EnemyDataOffset + 2;
            EnemyObjectPageSel = 0;
            return ObjectOffset;
          }
          bVar4 = EnemyData[bVar5] & 0x3f;
          if ((bVar4 > 0x36) && (bVar4 < 0x3f)) {
            return HandleGroupEnemies(bVar4);
          }
          if ((bVar4 == 6) && (PrimaryHardMode != 0)) {
            bVar4 = 2;
          }
          Enemy_ID[tmp1] = bVar4;
          Enemy_Flag[tmp1] = 1;
          InitEnemyObject(tmp1);
          if (Enemy_Flag[tmp1] == 0) {
            return tmp1;
          }
          EnemyDataOffset = EnemyDataOffset + 2;
          EnemyObjectPageSel = 0;
          return ObjectOffset;
        }
      } else if ((EnemyData[bVar4] & 0xf) != 0xe) {
        CheckThreeBytes();
        return ObjectOffset;
      }
      if ((SMB2J_ONLY && WorldNumber == 8) || (EnemyData[(byte)(bVar4 + 2)] >> 5 == WorldNumber)) {
        AreaPointer = EnemyData[(byte)(bVar4 + 1)];
        EntrancePage = EnemyData[(byte)(bVar4 + 2)] & 0x1f;
      }
      EnemyDataOffset += 1;
      EnemyDataOffset = EnemyDataOffset + 2;
      EnemyObjectPageSel = 0;
      return ObjectOffset;
    }

    EnemyObjectPageLoc = EnemyData[bVar5] & 0x3f;
    EnemyDataOffset += 2;
    EnemyObjectPageSel = 1;
  } while (true);
}


// SMB:c226
// SM2MAIN:8e03
// Signature: [X] -> []
void InitEnemyObject(const byte param_1) {
  Enemy_State[param_1] = 0;
  CheckpointEnemyID(param_1);
}


// SMB:c250
// SM2MAIN:8e34
// Signature: [] -> []
void CheckThreeBytes(void) {
  if ((EnemyData[EnemyDataOffset] & 0xf) == 0xe) {
    EnemyDataOffset += 1;
  }
  EnemyDataOffset = EnemyDataOffset + 2;
  EnemyObjectPageSel = 0;
}


enum CheckpointEnemyID_jumptable_item {
  CHECKPOINTENEMYID_INITNORMALENEMY_1,
  CHECKPOINTENEMYID_INITNORMALENEMY_2,
  CHECKPOINTENEMYID_INITNORMALENEMY_3,
  CHECKPOINTENEMYID_INITREDKOOPA,
  CHECKPOINTENEMYID_INITPARANHAPLANT_SMB2J,
  CHECKPOINTENEMYID_INITHAMMERBRO,
  CHECKPOINTENEMYID_INITGOOMBA,
  CHECKPOINTENEMYID_INITBLOOBER,
  CHECKPOINTENEMYID_INITBULLETBILL,
  CHECKPOINTENEMYID_NOOP_1,
  CHECKPOINTENEMYID_INITCHEEPCHEEP_1,
  CHECKPOINTENEMYID_INITCHEEPCHEEP_2,
  CHECKPOINTENEMYID_INITPODOBOO,
  CHECKPOINTENEMYID_INITPIRANHAPLANT,
  CHECKPOINTENEMYID_INITJUMPGPTROOPA,
  CHECKPOINTENEMYID_INITREDPTROOPA,
  CHECKPOINTENEMYID_INITHORIZFLYSWIMENEMY,
  CHECKPOINTENEMYID_INITLAKITU,
  CHECKPOINTENEMYID_INITENEMYFRENZY_1,
  CHECKPOINTENEMYID_NOOP_2,
  CHECKPOINTENEMYID_INITENEMYFRENZY_2,
  CHECKPOINTENEMYID_INITENEMYFRENZY_3,
  CHECKPOINTENEMYID_INITENEMYFRENZY_4,
  CHECKPOINTENEMYID_INITENEMYFRENZY_5,
  CHECKPOINTENEMYID_ENDFRENZY,
  CHECKPOINTENEMYID_NOOP_3,
  CHECKPOINTENEMYID_NOOP_4,
  CHECKPOINTENEMYID_INITSHORTFIREBAR_1,
  CHECKPOINTENEMYID_INITSHORTFIREBAR_2,
  CHECKPOINTENEMYID_INITSHORTFIREBAR_3,
  CHECKPOINTENEMYID_INITSHORTFIREBAR_4,
  CHECKPOINTENEMYID_INITLONGFIREBAR,
  CHECKPOINTENEMYID_NOOP_5,
  CHECKPOINTENEMYID_NOOP_6,
  CHECKPOINTENEMYID_NOOP_7,
  CHECKPOINTENEMYID_NOOP_8,
  CHECKPOINTENEMYID_INITBALPLATFORM,
  CHECKPOINTENEMYID_INITVERTPLATFORM,
  CHECKPOINTENEMYID_LARGELIFTUP,
  CHECKPOINTENEMYID_LARGELIFTDOWN,
  CHECKPOINTENEMYID_INITHORIPLATFORM_1,
  CHECKPOINTENEMYID_INITDROPPLATFORM,
  CHECKPOINTENEMYID_INITHORIPLATFORM_2,
  CHECKPOINTENEMYID_PLATLIFTUP,
  CHECKPOINTENEMYID_PLATLIFTDOWN,
  CHECKPOINTENEMYID_INITBOWSER,
  CHECKPOINTENEMYID_PWRUPJMP,
  CHECKPOINTENEMYID_SETUP_VINE,
  CHECKPOINTENEMYID_NOOP_9,
  CHECKPOINTENEMYID_NOOP_10,
  CHECKPOINTENEMYID_NOOP_11,
  CHECKPOINTENEMYID_NOOP_12,
  CHECKPOINTENEMYID_NOOP_13,
  CHECKPOINTENEMYID_INITRETAINEROBJ,
  CHECKPOINTENEMYID_NOOP_14,
};


// SMB:c26c
// SM2MAIN:8e50
// Signature: [X] -> []
void CheckpointEnemyID(const byte param_1) {
  const byte bVar1 = Enemy_ID[param_1];
  if (bVar1 <= 0x14) {
    Enemy_Y_Position[param_1] += 8;
    EnemyOffscrBitsMasked[param_1] = 1;
  }

  switch (bVar1) {
  case CHECKPOINTENEMYID_INITNORMALENEMY_1:
  case CHECKPOINTENEMYID_INITNORMALENEMY_2:
  case CHECKPOINTENEMYID_INITNORMALENEMY_3:
    InitNormalEnemy(param_1);
    return;

  case CHECKPOINTENEMYID_INITREDKOOPA:
    InitRedKoopa(param_1);
    return;

  case CHECKPOINTENEMYID_INITPARANHAPLANT_SMB2J:
    if (SMB2J_ONLY) {
      InitPiranhaPlant(param_1);
    }
    return;

  case CHECKPOINTENEMYID_INITHAMMERBRO:
    InitHammerBro(param_1);
    return;

  case CHECKPOINTENEMYID_INITGOOMBA:
    InitGoomba(param_1);
    return;

  case CHECKPOINTENEMYID_INITBLOOBER:
    InitBloober(param_1);
    return;

  case CHECKPOINTENEMYID_INITBULLETBILL:
    InitBulletBill(param_1);
    return;

  case CHECKPOINTENEMYID_NOOP_1:
  case CHECKPOINTENEMYID_NOOP_2:
  case CHECKPOINTENEMYID_NOOP_3:
  case CHECKPOINTENEMYID_NOOP_4:
  case CHECKPOINTENEMYID_NOOP_5:
  case CHECKPOINTENEMYID_NOOP_6:
  case CHECKPOINTENEMYID_NOOP_7:
  case CHECKPOINTENEMYID_NOOP_8:
  case CHECKPOINTENEMYID_NOOP_9:
  case CHECKPOINTENEMYID_NOOP_10:
  case CHECKPOINTENEMYID_NOOP_11:
  case CHECKPOINTENEMYID_NOOP_12:
  case CHECKPOINTENEMYID_NOOP_13:
    // NES note: goes to "NoInitCode" (a no-op)
    return;

  case CHECKPOINTENEMYID_NOOP_14:
    // NES note: goes to "EndOfEnemyInitCode" (a no-op)
    return;

  case CHECKPOINTENEMYID_INITCHEEPCHEEP_1:
  case CHECKPOINTENEMYID_INITCHEEPCHEEP_2:
    InitCheepCheep(param_1);
    return;

  case CHECKPOINTENEMYID_INITPODOBOO:
    InitPodoboo(param_1);
    return;

  case CHECKPOINTENEMYID_INITPIRANHAPLANT:
    InitPiranhaPlant(param_1);
    return;

  case CHECKPOINTENEMYID_INITJUMPGPTROOPA:
    InitJumpGPTroopa(param_1);
    return;

  case CHECKPOINTENEMYID_INITREDPTROOPA:
    InitRedPTroopa(param_1, false);
    return;

  case CHECKPOINTENEMYID_INITHORIZFLYSWIMENEMY:
    InitHorizFlySwimEnemy(param_1);
    return;

  case CHECKPOINTENEMYID_INITLAKITU:
    InitLakitu(param_1);
    return;

  case CHECKPOINTENEMYID_INITENEMYFRENZY_1:
  case CHECKPOINTENEMYID_INITENEMYFRENZY_2:
  case CHECKPOINTENEMYID_INITENEMYFRENZY_3:
  case CHECKPOINTENEMYID_INITENEMYFRENZY_4:
  case CHECKPOINTENEMYID_INITENEMYFRENZY_5:
    InitEnemyFrenzy(param_1);
    return;

  case CHECKPOINTENEMYID_ENDFRENZY:
    EndFrenzy(param_1);
    return;

  case CHECKPOINTENEMYID_INITSHORTFIREBAR_1:
  case CHECKPOINTENEMYID_INITSHORTFIREBAR_2:
  case CHECKPOINTENEMYID_INITSHORTFIREBAR_3:
  case CHECKPOINTENEMYID_INITSHORTFIREBAR_4:
    InitShortFirebar(param_1);
    return;

  case CHECKPOINTENEMYID_INITLONGFIREBAR:
    InitLongFirebar(param_1);
    return;

  case CHECKPOINTENEMYID_INITBALPLATFORM:
    InitBalPlatform(param_1);
    return;

  case CHECKPOINTENEMYID_INITVERTPLATFORM:
    InitVertPlatform(param_1);
    return;

  case CHECKPOINTENEMYID_LARGELIFTUP:
    LargeLiftUp(param_1);
    return;

  case CHECKPOINTENEMYID_LARGELIFTDOWN:
    LargeLiftDown(param_1);
    return;

  case CHECKPOINTENEMYID_INITHORIPLATFORM_1:
  case CHECKPOINTENEMYID_INITHORIPLATFORM_2:
    InitHoriPlatform(param_1);
    return;

  case CHECKPOINTENEMYID_INITDROPPLATFORM:
    InitDropPlatform(param_1);
    return;

  case CHECKPOINTENEMYID_PLATLIFTUP:
    PlatLiftUp(param_1);
    return;

  case CHECKPOINTENEMYID_PLATLIFTDOWN:
    PlatLiftDown(param_1);
    return;

  case CHECKPOINTENEMYID_INITBOWSER:
    InitBowser(param_1);
    return;

  case CHECKPOINTENEMYID_PWRUPJMP:
    PwrUpJmp();
    return;

  case CHECKPOINTENEMYID_SETUP_VINE:
    // NES note: Y is set to 0x60 by the jump engine and used by Setup_Vine. This is a bug.
    // The bug is worked around in Setup_Vine.
    Setup_Vine(param_1, 0x60);
    return;

  case CHECKPOINTENEMYID_INITRETAINEROBJ:
    InitRetainerObj(param_1);
    return;

  default:
    jmpengine_overflow(bVar1);
  }
}


// SMB:c2f1
// SM2MAIN:8ed5
// Signature: [X] -> []
void InitGoomba(const byte param_1) {
  InitNormalEnemy(param_1);
  SmallBBox(param_1);
}


// SMB:c2f7
// SM2MAIN:8edb
// Signature: [X] -> []
void InitPodoboo(const byte param_1) {
  Enemy_Y_HighPos[param_1] = 2;
  Enemy_Y_Position[param_1] = 2;
  EnemyIntervalTimer[param_1] = 1;
  Enemy_State[param_1] = 0;
  SmallBBox(param_1);
}


// SMB:c307
// SM2MAIN:8eeb
// Signature: [X] -> []
void InitRetainerObj(const byte param_1) {
  Enemy_Y_Position[param_1] = 0xb8;
}


// SMB:c30e
// SM2MAIN:8ef2
// Signature: [X] -> []
void InitNormalEnemy(const byte param_1) {
  SpriteVarData1[param_1] = NormalXSpdData[PrimaryHardMode != 0];
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
}


// SMB:c31e
// SM2MAIN:8f02
// Signature: [X] -> []
void InitRedKoopa(const byte param_1) {
  InitNormalEnemy(param_1);
  Enemy_State[param_1] = 1;
}


// SMB:c328
// SM2MAIN:8f0c
// Signature: [X] -> []
void InitHammerBro(const byte param_1) {
  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0;
  SpriteVarData1[param_1] = 0;
  if (SMB1_ONLY || (SMB2J_ONLY && WorldNumber < 6)) {
    EnemyIntervalTimer[param_1] = HBroWalkingTimerData[SecondaryHardMode];
  }
  Enemy_BoundBoxCtrl[param_1] = 0xb;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
}


// SMB:c33d
// SM2MAIN:8f28
// Signature: [X] -> []
void InitHorizFlySwimEnemy(const byte param_1) {
  SpriteVarData1[param_1] = 0;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
}


// SMB:c342
// SM2MAIN:8f2d
// Signature: [X] -> []
void InitBloober(const byte param_1) {
  SpriteVarData1[param_1] = 0;
  SmallBBox(param_1);
}


// SMB:c346
// SM2MAIN:8f31
// Signature: [X] -> [A]
byte SmallBBox(const byte param_1) {
  Enemy_BoundBoxCtrl[param_1] = 9;
  Enemy_MovingDir[param_1] = 2;
  return InitVStf(param_1);
}


// SMB:c34a
// SM2MAIN:8f35
// Signature: [X, C] -> []
void InitRedPTroopa(const byte param_1, const bool param_2) {
  char cVar1 = 0x30;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = Enemy_Y_Position[param_1];
  if (Enemy_Y_Position[param_1] >= 0x80) {
    cVar1 = -0x20;
  }
  SpriteVarData1[param_1] = cVar1 + Enemy_Y_Position[param_1] + param_2;
  Enemy_BoundBoxCtrl[param_1] = 3;
  Enemy_MovingDir[param_1] = 2;
  InitVStf(param_1);
}


// SMB:c363
// SM2MAIN:8f4e
// Signature: [X] -> [A]
byte InitVStf(const byte param_1) {
  SpriteVarData2[param_1] = 0;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0;
  return 0;
}


// SMB:c36b
// SM2MAIN:8f56
// Signature: [X] -> []
void InitBulletBill(const byte param_1) {
  Enemy_MovingDir[param_1] = 2;
  Enemy_BoundBoxCtrl[param_1] = 9;
}


// SMB:c375
// SM2MAIN:8f60
// Signature: [X] -> []
void InitCheepCheep(const byte param_1) {
  SmallBBox(param_1);
  SpriteVarData1[param_1] = PseudoRandomBitReg[param_1] & 0x10;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = Enemy_Y_Position[param_1];
}


// SMB:c385
// SM2MAIN:8f70
// Signature: [X] -> []
void InitLakitu(const byte param_1) {
  if (EnemyFrenzyBuffer == 0) {
    SetupLakitu(param_1);
  } else {
    EraseEnemyObject(param_1);
  }
}


// SMB:c38a
// SM2MAIN:8f75
// Signature: [X] -> []
void SetupLakitu(const byte param_1) {
  LakituReappearTimer = 0;
  InitHorizFlySwimEnemy(param_1);
  Enemy_BoundBoxCtrl[param_1] = 3;
}


// SMB:c3a4
// SM2MAIN:8f8f
// Signature: [X] -> []
void LakituAndSpinyHandler(const byte param_1) {
  byte bVar1;
  byte bVar2;
  byte bVar3;

  if ((FrenzyEnemyTimer == 0) && (param_1 < 5)) {
    FrenzyEnemyTimer = 0x80;
    for (int i = 4; i >= 0; i--) {
      if (Enemy_ID[i] == 0x11) {
        if (SprObject_Y_Position[0] < 0x2c) {
          FrenzyEnemyTimer = 0x80;
          return;
        }
        if (Enemy_State[i] != 0) {
          FrenzyEnemyTimer = 0x80;
          return;
        }
        Enemy_PageLoc[param_1] = Enemy_PageLoc[i];
        Enemy_X_Position[param_1] = Enemy_X_Position[i];
        Enemy_Y_HighPos[param_1] = 1;
        Enemy_Y_Position[param_1] = Enemy_Y_Position[i] - 8;
        bVar1 = PseudoRandomBitReg[param_1] & 3;
        bVar2 = ObjectOffset;
        PlayerLakituDiff(ObjectOffset, PRDiffAdjustData[bVar1], PRDiffAdjustData[bVar1 + 4],
                         PRDiffAdjustData[bVar1 + 8]);
        bVar1 = SmallBBox(bVar2);
        bVar3 = 2;
        SpriteVarData1[bVar2] = bVar1;
        if (bVar1 < 0x80) {
          bVar3 = 1;
        }
        Enemy_MovingDir[bVar2] = bVar3;
        SpriteVarData2[bVar2] = 0xfd;
        Enemy_Flag[bVar2] = 1;
        Enemy_State[bVar2] = 5;
        return;
      }
    }
    LakituReappearTimer += 1;
    if (LakituReappearTimer > ssw(6, 2)) {
      for (int i = 4; i >= 0; i--) {
        if (Enemy_Flag[i] == 0) {
          Enemy_State[i] = 0;
          Enemy_ID[i] = 0x11;
          SetupLakitu(i);
          bVar1 = 0x20;
          if (SMB2J_ONLY && (HardWorldFlag != 0 || WorldNumber >= 6)) {
            bVar1 = 0x60;
          }
          PutAtRightExtent(bVar1, i);
          return;
        }
      }
    }
  }
}


// SMB:c459
// SM2MAIN:9052
// Signature: [X] -> []
void InitLongFirebar(const byte param_1) {
  DuplicateEnemyObj(param_1);
  InitShortFirebar(param_1);
}


// SMB:c45c
// SM2MAIN:9055
// Signature: [X] -> []
void InitShortFirebar(const byte param_1) {
  SpriteVarData1[param_1] = 0;
  FirebarSpinSpeed[param_1] = FirebarSpinSpdData[(byte)(Enemy_ID[param_1] - 0x1b)];
  FirebarSpinDirection[param_1] = FirebarSpinDirData[(byte)(Enemy_ID[param_1] - 0x1b)];
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 4;

  ADD_UNSIGNED_16_8(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
                    4);

  Enemy_BoundBoxCtrl[param_1] = 3;
}


// SMB:c4a8
// SM2MAIN:90a1
// Signature: [X] -> []
void InitFlyingCheepCheep(const byte param_1) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }

  assert_eq_assumption(param_1 <= 5, true);

  const byte rng0 = PseudoRandomBitReg[param_1];
  const byte rng1 = PseudoRandomBitReg[param_1 + 1];

  SmallBBox(param_1);

  FrenzyEnemyTimer = FlyCCTimerData[rng1 & 3];

  if (param_1 >= ((SecondaryHardMode != 0) ? 4 : 3)) {
    return;
  }

  // This access would be out of bounds if defined earlier
  const byte rng2 = PseudoRandomBitReg[param_1 + 2];

  SpriteVarData2[param_1] = 0xfb;

  byte currng = rng0 & 3;

  if (PlayerSpriteVarData1[0] == 0) {
    currng += 0;
  } else if (PlayerSpriteVarData1[0] <= 0x18) {
    currng += 4;
  } else {
    currng += 8;
  }

  SpriteVarData1[param_1] = FlyCCXSpeedData[currng];
  Enemy_MovingDir[param_1] = 1;

  if (PlayerSpriteVarData1[0] == 0) {
    if ((rng1 & 3) != 0) {
      currng = rng2 & 0xf;
    }

    if ((currng & 2) != 0) {
      SpriteVarData1[param_1] *= 1;
      Enemy_MovingDir[param_1] += 1;
    }
  }

  SET_16_16(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
            SprObject_PageLoc[0], SprObject_X_Position[0]);

  if ((currng & 2) == 0) {
    SUB_UNSIGNED_16_8(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
                      FlyCCXPositionData[currng]);
  } else {
    ADD_UNSIGNED_16_8(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
                      FlyCCXPositionData[currng]);
  }

  Enemy_Flag[param_1] = 1;
  Enemy_Y_HighPos[param_1] = 1;
  Enemy_Y_Position[param_1] = SPRITE_Y_OFFSCREEN;
}


// SMB:c549
// SM2MAIN:9142
// Signature: [X] -> []
void InitBowser(const byte param_1) {
  if (SMB2J_ONLY) {
    for (int i = 0; i < 5; i++) {
      if (i == ObjectOffset) {
        continue;
      }
      if (Enemy_ID[i] == 0x2d) {
        Enemy_ID[i] = 0;
        Enemy_Flag[i] = 0;
      }
    }
  }

  DuplicateEnemyObj(param_1);
  BowserBodyControls = 0;
  BridgeCollapseOffset = 0;
  BowserOrigXPos = Enemy_X_Position[param_1];
  BowserFireBreathTimer = 0xdf;
  BowserFront_Offset = param_1;
  Enemy_MovingDir[param_1] = 0xdf;
  BowserFeetCounter = 0x20;
  EnemyFrameTimer[param_1] = 0x20;
  BowserHitPoints = 5;
  BowserMovementSpeed = 2;
}


// SMB:c575
// SM2MAIN:9186
// Signature: [X] -> []
void DuplicateEnemyObj(const byte param_1) {
  int i;
  for (i = 0; Enemy_Flag[i] != 0; i++) {
  }

  // i = first offset with flag=0

  DuplicateObj_Offset = i;
  Enemy_Flag[i] = param_1 | 0x80;
  Enemy_PageLoc[i] = Enemy_PageLoc[param_1];
  Enemy_X_Position[i] = Enemy_X_Position[param_1];
  Enemy_Flag[param_1] = 1;
  Enemy_Y_HighPos[i] = 1;
  Enemy_Y_Position[i] = Enemy_Y_Position[param_1];
}


// SMB:c5a3
// SM2MAIN:91b4
// Signature: [X] -> []
void InitBowserFlame(const byte param_1) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0;
  byte bVar1 = BowserFront_Offset;
  NoiseSoundQueue |= 2;
  if (Enemy_ID[BowserFront_Offset] != 0x2d) {
    bVar1 = SetFlameTimer();
    FrenzyEnemyTimer = bVar1 + 0x20;
    if (SecondaryHardMode != 0) {
      FrenzyEnemyTimer = bVar1 + 0x10;
    }
    BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = PseudoRandomBitReg[param_1] & 3;
    PutAtRightExtent(FlameYPosData[PseudoRandomBitReg[param_1] & 3], param_1);
    return;
  }
  Enemy_X_Position[param_1] = Enemy_X_Position[BowserFront_Offset] - 0xe;
  Enemy_PageLoc[param_1] = Enemy_PageLoc[bVar1];
  Enemy_Y_Position[param_1] = Enemy_Y_Position[bVar1] + 8;
  BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = PseudoRandomBitReg[param_1] & 3;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]
      = FlameYMFAdderData[Enemy_Y_Position[param_1] <= FlameYPosData[PseudoRandomBitReg[param_1] & 3]];
  EnemyFrenzyBuffer = 0;
  Enemy_BoundBoxCtrl[param_1] = 8;
  Enemy_Y_HighPos[param_1] = 1;
  Enemy_Flag[param_1] = 1;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = 0;
  Enemy_State[param_1] = 0;
}


// SMB:c5d8
// SM2MAIN:91e9
// Signature: [A, X] -> []
void PutAtRightExtent(const byte param_1, const byte param_2) {
  Enemy_Y_Position[param_2] = param_1;
  const bool bVar1 = ScreenRight_X_Pos >= 0xe0;
  Enemy_X_Position[param_2] = ScreenRight_X_Pos + 0x20;
  Enemy_PageLoc[param_2] = ScreenRight_PageLoc + bVar1;
  Enemy_BoundBoxCtrl[param_2] = 8;
  Enemy_Y_HighPos[param_2] = 1;
  Enemy_Flag[param_2] = 1;
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_2] = 0;
  Enemy_State[param_2] = 0;

  // NES note: The "A" register is set to 0 here. Used by BulletBillCheepCheep
}


// SMB:c63d
// SM2MAIN:924e
// Signature: [X] -> []
void InitFireworks(const byte param_1) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }

  FrenzyEnemyTimer = 0x20;
  FireworksCounter -= 1;

  int i;

  // Find the star flag object
  for (i = 5; i >= 0; i--) {
    if (Enemy_ID[i] == 0x31) {
      break;
    }
  }

  assert_smb_crashbug(i >= 0, "A star flag object should exist. If not, the original game would loop infinitely or do something weird here");

  const byte bVar3 = FireworksCounter + Enemy_State[i];

  u16 x = LOAD_16(Enemy_PageLoc[i], Enemy_X_Position[i]);

  x -= 0x30;
  x += FireworksXPosData[bVar3];

  STORE_16(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
           x);

  Enemy_Y_Position[param_1] = FireworksYPosData[bVar3];
  Enemy_Y_HighPos[param_1] = 1;

  Enemy_Flag[param_1] = 1;

  SpriteVarData1[param_1] = 0;
  SpriteVarData2[param_1] = 8;
}


// Implements a bag of numbers between 0 and 7 inclusive.
static inline u8 random_from_bag(const u8 seed, u8 * const set) {
  // If all numbers are taken, refill the bag

  if (*set == 0xff) {
    *set = 0;
  }

  byte i = seed;

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
void BulletBillCheepCheep(const byte param_1) {
  if (FrenzyEnemyTimer != 0) {
    return;
  }

  if (AreaType == 0) {
    // Auto-appearing cheep cheeps (in SMB1 2-2 and 7-2)

    if (param_1 >= 3) {
      return;
    }

    // Spawn a random cheep-cheep

    bool red_cheepcheep = PseudoRandomBitReg[param_1] >= 0xaa;

    if (WorldNumber != 1) {
      red_cheepcheep = !red_cheepcheep;
    }

    Enemy_ID[param_1] = red_cheepcheep ? 0xb : 0xa;
  } else {
    // Auto-appearing bullet bills (in SMB1 5-3 and 6-3)

    // Prevent too many bullet bills from being spawned
    for (int i = 0; i < 5; i++) {
      if ((Enemy_Flag[i] != 0) && (Enemy_ID[i] == 8)) {
        return;
      }
    }

    // Bullet sound
    Square2SoundQueue |= 8;

    // Spawn a bullet bill
    Enemy_ID[param_1] = 8;
  }

  const u8 rng_bag = random_from_bag(PseudoRandomBitReg[param_1], &BitMFilter);

  // Inlining Enemy17YPosData, because it's only used in this subroutine
  static const u8 ypos_lookup[8] = {
    0x40, 0x30, 0x90, 0x50, 0x20, 0x60, 0xa0, 0x70
  };

  PutAtRightExtent(ypos_lookup[rng_bag], param_1);
  Enemy_YMF_Dummy[param_1] = 0;

  FrenzyEnemyTimer = 0x20;
  CheckpointEnemyID(param_1);
}


// SMB:c71b
// SM2MAIN:932c
// Signature: [A] -> [X]
byte HandleGroupEnemies(const byte param_1) {
  const byte bStack0000 = param_1 - 0x37;
  byte id;
  if (bStack0000 >= 4) {
    id = 0;
  } else if (PrimaryHardMode != 0) {
    id = 2;
  } else {
    id = 6;
  }

  byte ypos;
  if ((bStack0000 & 2) != 0) {
    ypos = 0x70;
  } else {
    ypos = 0xb0;
  }

  if ((bStack0000 & 1) != 0) {
    NumberofGroupEnemies = 3;
  } else {
    NumberofGroupEnemies = 2;
  }

  byte xpos = ScreenRight_X_Pos;
  byte pageloc = ScreenRight_PageLoc;

  do {
    int k;
    for (k = 0; ; k++) {
      if (k == 5) {
        // exit
        EnemyDataOffset = EnemyDataOffset + 2;
        EnemyObjectPageSel = 0;
        return ObjectOffset;
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

  EnemyDataOffset = EnemyDataOffset + 2;
  EnemyObjectPageSel = 0;
  return ObjectOffset;
}


// SMB:c787
// SM2MAIN:9398
// Signature: [X] -> []
void InitPiranhaPlant(const byte param_1) {
  #ifdef SMB2J_MODE
    EnemyAttributeData[13] = 0x22;
    PiranhaPlantCompareOperand = 0x13;
    if ((HardWorldFlag == 0) && (WorldNumber < 3)) {
      EnemyAttributeData[13] = 0x21;
      PiranhaPlantCompareOperand = 0x21;
    }
  #endif
  SpriteVarData1[param_1] = 1;
  Enemy_State[param_1] = 0;
  SpriteVarData2[param_1] = 0;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = Enemy_Y_Position[param_1];
  BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = Enemy_Y_Position[param_1] - 0x18;
  Enemy_BoundBoxCtrl[param_1] = 9;
}


enum InitEnemyFrenzy_jumptable_item {
  INITENEMYFRENZY_LAKITUANDSPINYHANDLER,
  INITENEMYFRENZY_NOOP,
  INITENEMYFRENZY_INITFLYINGCHEEPCHEEP,
  INITENEMYFRENZY_INITBOWSERFLAME,
  INITENEMYFRENZY_INITFIREWORKS,
  INITENEMYFRENZY_BULLETBILLCHEEPCHEEP,
};


// SMB:c7a0
// SM2MAIN:93d5
// Signature: [X] -> []
void InitEnemyFrenzy(const byte param_1) {
  EnemyFrenzyBuffer = Enemy_ID[param_1];

  switch (Enemy_ID[param_1] - 0x12) {
  case INITENEMYFRENZY_LAKITUANDSPINYHANDLER:
    LakituAndSpinyHandler(param_1);
    return;

  case INITENEMYFRENZY_NOOP:
    // NES note: goes to "NoFrenzyCode" (a no-op)
    return;

  case INITENEMYFRENZY_INITFLYINGCHEEPCHEEP:
    InitFlyingCheepCheep(param_1);
    return;

  case INITENEMYFRENZY_INITBOWSERFLAME:
    InitBowserFlame(param_1);
    return;

  case INITENEMYFRENZY_INITFIREWORKS:
    InitFireworks(param_1);
    return;

  case INITENEMYFRENZY_BULLETBILLCHEEPCHEEP:
    BulletBillCheepCheep(param_1);
    return;

  default:
    jmpengine_overflow(Enemy_ID[param_1] - 0x12);
  }
}


// SMB:c7b8
// SM2MAIN:93ed
// Signature: [X] -> []
void EndFrenzy(const byte param_1) {
  for (int i = 0; i < 6; i++) {
    if (Enemy_ID[i] == 0x11) {
      Enemy_State[i] = 1;
    }
  }

  EnemyFrenzyBuffer = 0;
  Enemy_Flag[param_1] = 0;
}


// SMB:c7d1
// SM2MAIN:9406
// Signature: [X] -> []
void InitJumpGPTroopa(const byte param_1) {
  Enemy_MovingDir[param_1] = 2;
  SpriteVarData1[param_1] = ssw(0xf8, 0xf4);
  Enemy_BoundBoxCtrl[param_1] = 3;
}


// SMB:c7df
// SM2MAIN:9414
// Signature: [X] -> []
void InitBalPlatform(const byte param_1) {
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  if (SecondaryHardMode == 0) {
    PosPlatform(param_1, 2);
  }
  const bool bVar1 = BalPlatformAlignment >= 0x80;
  Enemy_State[param_1] = BalPlatformAlignment;
  BalPlatformAlignment = 0xff;
  if (bVar1) {
    BalPlatformAlignment = param_1;
  }
  Enemy_MovingDir[param_1] = 0;
  PosPlatform(param_1, 0);
  InitDropPlatform(param_1);
}


// SMB:c803
// SM2MAIN:9438
// Signature: [X] -> []
void InitDropPlatform(const byte param_1) {
  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0xff;
  InitVStf(param_1);
  SPBBox(param_1);
}


// SMB:c80b
// SM2MAIN:9440
// Signature: [X] -> []
void InitHoriPlatform(const byte param_1) {
  SpriteVarData1[param_1] = 0;
  InitVStf(param_1);
  SPBBox(param_1);
}


// SMB:c812
// SM2MAIN:9447
// Signature: [X] -> []
void InitVertPlatform(const byte param_1) {
  char cVar2 = 0x40;
  byte bVar1 = Enemy_Y_Position[param_1];
  if (bVar1 >= 0x80) {
    bVar1 = NEGATE(bVar1);
    cVar2 = -0x40;
  }
  Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] = bVar1;
  SpriteVarData1[param_1] = cVar2 + Enemy_Y_Position[param_1];
  InitVStf(param_1);
  SPBBox(param_1);
}


// SMB:c82b
// SM2MAIN:9460
// Signature: [X] -> []
void SPBBox(const byte param_1) {
  Enemy_BoundBoxCtrl[param_1] = ((AreaType != 3) && (SecondaryHardMode == 0)) ? 6 : 5;
}


// SMB:c83f
// SM2MAIN:9474
// Signature: [X] -> []
void LargeLiftUp(const byte param_1) {
  PlatLiftUp(param_1);
  SPBBox(param_1);
}


// SMB:c845
// SM2MAIN:947a
// Signature: [X] -> []
void LargeLiftDown(const byte param_1) {
  PlatLiftDown(param_1);
  SPBBox(param_1);
}


// SMB:c84b
// SM2MAIN:9480
// Signature: [X] -> []
void PlatLiftUp(const byte param_1) {
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0x10;
  SpriteVarData2[param_1] = 0xff;
  PosPlatform(param_1, 1);
  Enemy_BoundBoxCtrl[param_1] = 4;
}


// SMB:c857
// SM2MAIN:948c
// Signature: [X] -> []
void PlatLiftDown(const byte param_1) {
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = 0xf0;
  SpriteVarData2[param_1] = 0;
  PosPlatform(param_1, 1);
  Enemy_BoundBoxCtrl[param_1] = 4;
}


// SMB:c871
// SM2MAIN:94a6
// Signature: [X, Y] -> []
void PosPlatform(const byte param_1, const byte param_2) {
  ADD_16_16(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
            PlatPosDataHigh[param_2], PlatPosDataLow[param_2]);
}


enum RunEnemyObjectsCore_jumptable_item {
  RUNENEMYOBJECTSCORE_RUNNORMALENEMIES,
  RUNENEMYOBJECTSCORE_RUNBOWSERFLAME,
  RUNENEMYOBJECTSCORE_RUNFIREWORKS,
  RUNENEMYOBJECTSCORE_NOOP_1,
  RUNENEMYOBJECTSCORE_NOOP_2,
  RUNENEMYOBJECTSCORE_NOOP_3,
  RUNENEMYOBJECTSCORE_NOOP_4,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_1,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_2,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_3,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_4,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_5,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_6,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_7,
  RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_8,
  RUNENEMYOBJECTSCORE_NOOP_5,
  RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_1,
  RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_2,
  RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_3,
  RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_4,
  RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_5,
  RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_6,
  RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_7,
  RUNENEMYOBJECTSCORE_RUNSMALLPLATFORM_1,
  RUNENEMYOBJECTSCORE_RUNSMALLPLATFORM_2,
  RUNENEMYOBJECTSCORE_RUNBOWSER,
  RUNENEMYOBJECTSCORE_POWERUPOBJHANDLER,
  RUNENEMYOBJECTSCORE_VINEOBJECTHANDLER,
  RUNENEMYOBJECTSCORE_NOOP_6,
  RUNENEMYOBJECTSCORE_RUNSTARFLAGOBJ,
  RUNENEMYOBJECTSCORE_JUMPSPRINGHANDLER,
  RUNENEMYOBJECTSCORE_NOOP_7,
  RUNENEMYOBJECTSCORE_WARPZONEOBJECT,
  RUNENEMYOBJECTSCORE_RUNRETAINEROBJ,
};


// SMB:c882
// SM2MAIN:94b7
// Signature: [] -> [X]
byte RunEnemyObjectsCore(void) {
  byte bVar1 = 0;
  if (Enemy_ID[ObjectOffset] >= 0x15) {
    bVar1 = Enemy_ID[ObjectOffset] - 0x14;
  }

  switch (bVar1) {
  case RUNENEMYOBJECTSCORE_RUNNORMALENEMIES:
    return RunNormalEnemies(ObjectOffset);

  case RUNENEMYOBJECTSCORE_RUNBOWSERFLAME:
    return RunBowserFlame(ObjectOffset);

  case RUNENEMYOBJECTSCORE_RUNFIREWORKS:
    RunFireworks(ObjectOffset);
    return ObjectOffset;

  case RUNENEMYOBJECTSCORE_NOOP_1:
  case RUNENEMYOBJECTSCORE_NOOP_2:
  case RUNENEMYOBJECTSCORE_NOOP_3:
  case RUNENEMYOBJECTSCORE_NOOP_4:
  case RUNENEMYOBJECTSCORE_NOOP_5:
  case RUNENEMYOBJECTSCORE_NOOP_6:
  case RUNENEMYOBJECTSCORE_NOOP_7:
    // NES note: goes to "NoRunCode" (a no-op)
    return ObjectOffset;

  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_1:
  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_2:
  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_3:
  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_4:
  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_5:
  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_6:
  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_7:
  case RUNENEMYOBJECTSCORE_RUNFIREBAROBJ_8:
    return RunFirebarObj(ObjectOffset);

  case RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_1:
  case RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_2:
  case RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_3:
  case RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_4:
  case RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_5:
  case RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_6:
  case RUNENEMYOBJECTSCORE_RUNLARGEPLATFORM_7:
    return RunLargePlatform(ObjectOffset);

  case RUNENEMYOBJECTSCORE_RUNSMALLPLATFORM_1:
  case RUNENEMYOBJECTSCORE_RUNSMALLPLATFORM_2:
    return RunSmallPlatform(ObjectOffset);

  case RUNENEMYOBJECTSCORE_RUNBOWSER:
    return RunBowser(ObjectOffset);

  case RUNENEMYOBJECTSCORE_POWERUPOBJHANDLER:
    return PowerUpObjHandler();

  case RUNENEMYOBJECTSCORE_VINEOBJECTHANDLER:
    VineObjectHandler(ObjectOffset);
    return ObjectOffset;

  case RUNENEMYOBJECTSCORE_RUNSTARFLAGOBJ:
    return RunStarFlagObj(ObjectOffset);

  case RUNENEMYOBJECTSCORE_JUMPSPRINGHANDLER:
    return JumpspringHandler(ObjectOffset);

  case RUNENEMYOBJECTSCORE_WARPZONEOBJECT:
    {
      const byte old_object_offset = ObjectOffset;
      WarpZoneObject(ObjectOffset);
      return old_object_offset;
    }

  case RUNENEMYOBJECTSCORE_RUNRETAINEROBJ:
    RunRetainerObj(ObjectOffset);
    return ObjectOffset;

  default:
    jmpengine_overflow(bVar1);
    return ObjectOffset;
  }
}


// SMB:c8d7
// SM2MAIN:950c
// Signature: [X] -> []
void RunRetainerObj(const byte param_1) {
  GetEnemyOffscreenBits(param_1);
  RelativeEnemyPosition(ObjectOffset);
  EnemyGfxHandler(ObjectOffset);
}


// SMB:c8e0
// SM2MAIN:9515
// Signature: [X] -> [X]
byte RunNormalEnemies(const byte param_1) {
  Enemy_SprAttrib[param_1] = 0;
  GetEnemyOffscreenBits(param_1);
  RelativeEnemyPosition(ObjectOffset);
  EnemyGfxHandler(ObjectOffset);
  byte bVar1 = ObjectOffset;
  GetEnemyBoundBox(bVar1);
  bVar1 = ObjectOffset;
  bVar1 = EnemyToBGCollisionDet(bVar1);
  bVar1 = EnemiesCollision(bVar1);
  PlayerEnemyCollision(bVar1);
  if (TimerControl == 0) {
    bVar1 = EnemyMovementSubs(bVar1);
  }
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}


enum EnemyMovementSubs_jumptable_item {
  ENEMYMOVEMENTSUBS_MOVENORMALENEMY_1,
  ENEMYMOVEMENTSUBS_MOVENORMALENEMY_2,
  ENEMYMOVEMENTSUBS_MOVENORMALENEMY_3,
  ENEMYMOVEMENTSUBS_MOVENORMALENEMY_4,
  ENEMYMOVEMENTSUBS_MOVEUPSIDEDOWNPIRANHAP,
  ENEMYMOVEMENTSUBS_PROCHAMMERBRO,
  ENEMYMOVEMENTSUBS_MOVENORMALENEMY_5,
  ENEMYMOVEMENTSUBS_MOVEBLOOBER,
  ENEMYMOVEMENTSUBS_MOVEBULLETBILL,
  ENEMYMOVEMENTSUBS_NOOP_1,
  ENEMYMOVEMENTSUBS_MOVESWIMMINGCHEEPCHEEP_1,
  ENEMYMOVEMENTSUBS_MOVESWIMMINGCHEEPCHEEP_2,
  ENEMYMOVEMENTSUBS_MOVEPODOBOO,
  ENEMYMOVEMENTSUBS_MOVEPIRANHAPLANT,
  ENEMYMOVEMENTSUBS_MOVEJUMPINGENEMY,
  ENEMYMOVEMENTSUBS_PROCMOVEREDPTROOPA,
  ENEMYMOVEMENTSUBS_MOVEFLYGREENPTROOPA,
  ENEMYMOVEMENTSUBS_MOVELAKITU,
  ENEMYMOVEMENTSUBS_MOVENORMALENEMY_6,
  ENEMYMOVEMENTSUBS_NOOP_2,
  ENEMYMOVEMENTSUBS_MOVEFLYINGCHEEPCHEEP,
};


// SMB:c905
// SM2MAIN:953a
// Signature: [X] -> [X]
byte EnemyMovementSubs(const byte param_1) {
  switch (Enemy_ID[param_1]) {
  case ENEMYMOVEMENTSUBS_MOVENORMALENEMY_1:
  case ENEMYMOVEMENTSUBS_MOVENORMALENEMY_2:
  case ENEMYMOVEMENTSUBS_MOVENORMALENEMY_3:
  case ENEMYMOVEMENTSUBS_MOVENORMALENEMY_4:
  case ENEMYMOVEMENTSUBS_MOVENORMALENEMY_5:
  case ENEMYMOVEMENTSUBS_MOVENORMALENEMY_6:
    return MoveNormalEnemy(param_1);

  case ENEMYMOVEMENTSUBS_MOVEUPSIDEDOWNPIRANHAP:
    #ifdef SMB2J_MODE
    MoveUpsideDownPiranhaP(param_1);
    return param_1;
    #else
    return MoveNormalEnemy(param_1);
    #endif

  case ENEMYMOVEMENTSUBS_PROCHAMMERBRO:
    return ProcHammerBro(param_1);

  case ENEMYMOVEMENTSUBS_MOVEBLOOBER:
    return MoveBloober(param_1, false);

  case ENEMYMOVEMENTSUBS_MOVEBULLETBILL:
    MoveBulletBill(param_1);
    return ObjectOffset;

  case ENEMYMOVEMENTSUBS_NOOP_1:
  case ENEMYMOVEMENTSUBS_NOOP_2:
    // NES note: goes to "NoMoveCode" (a no-op)
    return param_1;

  case ENEMYMOVEMENTSUBS_MOVESWIMMINGCHEEPCHEEP_1:
  case ENEMYMOVEMENTSUBS_MOVESWIMMINGCHEEPCHEEP_2:
    return MoveSwimmingCheepCheep(param_1);

  case ENEMYMOVEMENTSUBS_MOVEPODOBOO:
    MovePodoboo(param_1);
    return ObjectOffset;

  case ENEMYMOVEMENTSUBS_MOVEPIRANHAPLANT:
    MovePiranhaPlant(param_1);
    return param_1;

  case ENEMYMOVEMENTSUBS_MOVEJUMPINGENEMY:
    MoveJumpingEnemy(param_1);
    return ObjectOffset;

  case ENEMYMOVEMENTSUBS_PROCMOVEREDPTROOPA:
    ProcMoveRedPTroopa(param_1);
    return ObjectOffset;

  case ENEMYMOVEMENTSUBS_MOVEFLYGREENPTROOPA:
    return MoveFlyGreenPTroopa(param_1);

  case ENEMYMOVEMENTSUBS_MOVELAKITU:
    MoveLakitu(param_1);
    return ObjectOffset;

  case ENEMYMOVEMENTSUBS_MOVEFLYINGCHEEPCHEEP:
    MoveFlyingCheepCheep(param_1);
    return ObjectOffset;

  default:
    jmpengine_overflow(Enemy_ID[param_1]);
    return param_1;
  }
}


// SMB:c935
// SM2MAIN:956a
// Signature: [X] -> [X]
byte RunBowserFlame(const byte param_1) {
  ProcBowserFlame(param_1);
  byte bVar1 = ObjectOffset;
  GetEnemyOffscreenBits(bVar1);
  RelativeEnemyPosition(ObjectOffset);
  GetEnemyBoundBox(ObjectOffset);
  bVar1 = ObjectOffset;
  PlayerEnemyCollision(bVar1);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}


// SMB:c947
// SM2MAIN:957c
// Signature: [X] -> [X]
byte RunFirebarObj(const byte param_1) {
  const byte bVar1 = ProcFirebar(param_1);
  OffscreenBoundsCheck(bVar1);
  return bVar1;
}


// SMB:c94d
// SM2MAIN:9582
// Signature: [X] -> [X]
byte RunSmallPlatform(const byte param_1) {
  GetEnemyOffscreenBits(param_1);
  RelativeEnemyPosition(ObjectOffset);
  SmallPlatformBoundBox(ObjectOffset);
  const byte d = SmallPlatformCollision(ObjectOffset);
  RelativeEnemyPosition(d);
  DrawSmallPlatform(ObjectOffset);
  const byte f = ObjectOffset;
  MoveSmallPlatform(f);
  OffscreenBoundsCheck(f);
  return f;
}


// SMB:c965
// SM2MAIN:959a
// Signature: [X] -> [X]
byte RunLargePlatform(const byte param_1) {
  GetEnemyOffscreenBits(param_1);
  RelativeEnemyPosition(ObjectOffset);
  const byte c = LargePlatformBoundBox(ObjectOffset);
  const byte d = LargePlatformCollision(c);
  const byte e = (TimerControl == 0) ? LargePlatformSubroutines(d) : d;
  RelativeEnemyPosition(e);
  DrawLargePlatform(ObjectOffset);
  const byte g = ObjectOffset;
  OffscreenBoundsCheck(g);
  return g;
}


enum LargePlatformSubroutines_jumptable_item {
  LARGEPLATFORMSUBROUTINES_BALANCEPLATFORM,
  LARGEPLATFORMSUBROUTINES_YMOVINGPLATFORM,
  LARGEPLATFORMSUBROUTINES_MOVELARGELIFTPLAT_1,
  LARGEPLATFORMSUBROUTINES_MOVELARGELIFTPLAT_2,
  LARGEPLATFORMSUBROUTINES_XMOVINGPLATFORM,
  LARGEPLATFORMSUBROUTINES_DROPPLATFORM,
  LARGEPLATFORMSUBROUTINES_RIGHTPLATFORM,
};


// SMB:c982
// SM2MAIN:95b7
// Signature: [X] -> [X]
byte LargePlatformSubroutines(const byte param_1) {
  switch (Enemy_ID[param_1] - 0x24) {
  case LARGEPLATFORMSUBROUTINES_BALANCEPLATFORM:
    return BalancePlatform(param_1);

  case LARGEPLATFORMSUBROUTINES_YMOVINGPLATFORM:
    return YMovingPlatform(param_1);

  case LARGEPLATFORMSUBROUTINES_MOVELARGELIFTPLAT_1:
  case LARGEPLATFORMSUBROUTINES_MOVELARGELIFTPLAT_2:
    MoveLargeLiftPlat(param_1);
    return param_1;

  case LARGEPLATFORMSUBROUTINES_XMOVINGPLATFORM:
    XMovingPlatform(param_1, ObjectOffset);
    return ObjectOffset;

  case LARGEPLATFORMSUBROUTINES_DROPPLATFORM:
    return DropPlatform(param_1);

  case LARGEPLATFORMSUBROUTINES_RIGHTPLATFORM:
    RightPlatform(param_1, ObjectOffset);
    return ObjectOffset;

  default:
    jmpengine_overflow(Enemy_ID[param_1] - 0x24);
    return param_1;
  }
}


// SMB:c998
// SM2MAIN:95cd
// Signature: [X] -> []
void EraseEnemyObject(const byte param_1) {
  Enemy_Flag[param_1] = 0;
  Enemy_ID[param_1] = 0;
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
void MovePodoboo(const byte param_1) {
  byte bVar1;

  if (EnemyIntervalTimer[param_1] == 0) {
    InitPodoboo(param_1);
    bVar1 = PseudoRandomBitReg[param_1 + 1];
    CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1 | 0x80;
    EnemyIntervalTimer[param_1] = (bVar1 & 0xf) | 6;
    SpriteVarData2[param_1] = 0xf9;
  }
  MoveJ_EnemyVertically(param_1);
}


// SMB:c9d8
// SM2MAIN:960d
// Signature: [X] -> [X]
byte ProcHammerBro(const byte param_1) {
  if ((Enemy_State[param_1] & 0x20) != 0) {
    MoveDefeatedEnemy(param_1);
    return ObjectOffset;
  }
  if (HammerBroJumpTimer[param_1] != 0) {
    HammerBroJumpTimer[param_1] = HammerBroJumpTimer[param_1] - 1;
    if ((Enemy_OffscreenBits & 0xc) != 0) {
      return MoveHammerBroXDir(param_1);
    }
    if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] == 0) {
      HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = HammerThrowTmrData[SecondaryHardMode];
      struct_xc sVar2 = SpawnHammerObj();
      if (sVar2.c) {
        Enemy_State[sVar2.x] = Enemy_State[sVar2.x] | 8;
        return MoveHammerBroXDir(sVar2.x);
      }
      HammerThrowingTimer_Or_PlatformCollisionFlag[sVar2.x] = HammerThrowingTimer_Or_PlatformCollisionFlag[sVar2.x] - 1;
      return MoveHammerBroXDir(sVar2.x);
    }
    HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] - 1;
    return MoveHammerBroXDir(param_1);
  }
  if ((Enemy_State[param_1] & 7) == 1) {
    return MoveHammerBroXDir(param_1);
  }
  if (Enemy_Y_Position[param_1] >= 0x80) {
    return SetHJ(param_1, 0xfa, 0);
  }
  if (Enemy_Y_Position[param_1] < 0x70) {
    return SetHJ(param_1, 0xfd, 1);
  }
  if ((PseudoRandomBitReg[param_1 + 1] & 1) != 0) {
    return SetHJ(param_1, 0xfd, 0);
  }
  return SetHJ(param_1, 0xfa, 0);
}


// SMB:ca37
// SM2MAIN:966c
// Signature: [X, Y, r00] -> [X]
byte SetHJ(const byte param_1, const byte param_2, const byte param_3) {
  SpriteVarData2[param_1] = param_2;
  Enemy_State[param_1] = Enemy_State[param_1] | 1;
  byte bVar1 = param_3 & PseudoRandomBitReg[param_1 + 2];
  if (SecondaryHardMode == 0) {
    bVar1 = 0;
  }
  EnemyFrameTimer[param_1] = HammerBroJumpLData[bVar1];
  HammerBroJumpTimer[param_1] = PseudoRandomBitReg[param_1 + 1] | 0xc0;
  return MoveHammerBroXDir(param_1);
}


// SMB:ca58
// SM2MAIN:968d
// Signature: [X] -> [X]
byte MoveHammerBroXDir(const byte param_1) {
  SpriteVarData1[param_1] = ((FrameCounter & 0x40) == 0) ? 4 : 0xfc;;
  const struct_ncr00 sVar2 = PlayerEnemyDiff(param_1);
  if (!sVar2.n) {
    if (EnemyIntervalTimer[param_1] == 0) {
      SpriteVarData1[param_1] = 0xf8;
    }
  }
  Enemy_MovingDir[param_1] = (sVar2.n) ? 1 : 2;
  return MoveNormalEnemy(param_1);
}


// SMB:ca77
// SM2MAIN:96ac
// Signature: [X] -> [X]
byte MoveNormalEnemy(const byte param_1) {
  bool fall_e = true;

  if ((Enemy_State[param_1] & 0x40) == 0) {
    const byte bVar1 = Enemy_State[param_1] & 7;

    if (Enemy_State[param_1] & 0x80) {
      fall_e = false;
    } else if ((Enemy_State[param_1] & 0x20) != 0) {
      MoveDefeatedEnemy(param_1);
      return ObjectOffset;
    } else if (bVar1 == 0) {
      fall_e = false;
    } else if (bVar1 == 3 || bVar1 == 4 || bVar1 == 6 || bVar1 == 7) {
      if (EnemyIntervalTimer[param_1] == 0) {
        Enemy_State[param_1] = 0;
        byte bVar2 = FrameCounter & 1;
        Enemy_MovingDir[param_1] = bVar2 + 1;
        if (PrimaryHardMode != 0) {
          bVar2 += 2;
        }
        Enemy_X_Speed[param_1] = RevivedXSpeed[bVar2];
        return param_1;
      }
      if ((EnemyIntervalTimer[param_1] == 0xe) && (Enemy_ID[param_1] == 6)) {
        EraseEnemyObject(param_1);
      }
      return param_1;
    }
  }

  byte bVar2 = 0;

  // FallE
  if (fall_e) {
    MoveD_EnemyVertically(param_1);
    const byte tmp1 = ObjectOffset;
    assert_eq_assumption(tmp1, param_1);

    if (Enemy_State[param_1] == 2) {
      // MEHor
      MoveEnemyHorizontally(param_1);
      return ObjectOffset;
    }

    if (((Enemy_State[param_1] & 0x40) != 0) && (Enemy_ID[param_1] != 0x2e)) {
      bVar2 = 1;
    }
  }

  const byte old_enemy_speed = Enemy_X_Speed[param_1];
  if (old_enemy_speed >= 0x80) {
    bVar2 += 2;
  }
  Enemy_X_Speed[param_1] += XSpeedAdderData[bVar2];

  MoveEnemyHorizontally(param_1);
  // TODO - remove this once we're sure
  assert_eq_assumption(ObjectOffset, param_1);

  Enemy_X_Speed[param_1] = old_enemy_speed;
  return param_1;
}


// SMB:cae5
// SM2MAIN:971a
// Signature: [X] -> []
void MoveDefeatedEnemy(const byte param_1) {
  MoveD_EnemyVertically(param_1);
  const byte bVar1 = ObjectOffset;
  MoveEnemyHorizontally(bVar1);
}


// SMB:caf9
// SM2MAIN:972e
// Signature: [X] -> []
void MoveJumpingEnemy(const byte param_1) {
  MoveJ_EnemyVertically(param_1);
  const byte bVar1 = ObjectOffset;
  MoveEnemyHorizontally(bVar1);
}


// SMB:caff
// SM2MAIN:9734
// Signature: [X] -> [X]
byte ProcMoveRedPTroopa(const byte param_1) {
  if (((SpriteVarData2[param_1] | CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]) == 0)) {
    BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = 0;
    if (Enemy_Y_Position[param_1] < Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1]) {
      if ((FrameCounter & 7) == 0) {
        Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
      }
      return param_1;
    }
  }
  if (SpriteVarData1[param_1] <= Enemy_Y_Position[param_1]) {
    MoveRedPTroopaUp(param_1);
    return ObjectOffset;
  }
  MoveRedPTroopaDown(param_1);
  return ObjectOffset;
}


// SMB:cb25
// SM2MAIN:975a
// Signature: [X] -> [X]
byte MoveFlyGreenPTroopa(const byte param_1) {
  XMoveCntr_GreenPTroopa(param_1);
  const byte objoff = ObjectOffset;
  MoveWithXMCntrs(param_1, objoff);
  char cVar2 = 1;
  if ((FrameCounter & 3) == 0) {
    if ((FrameCounter & 0x40) == 0) {
      cVar2 = -1;
    }
    Enemy_Y_Position[objoff] = Enemy_Y_Position[objoff] + cVar2;
  }
  return objoff;
}


// SMB:cb45
// SM2MAIN:977a
// Signature: [X] -> []
void XMoveCntr_GreenPTroopa(const byte param_1) {
  XMoveCntr_Platform(0x13, param_1);
}


// SMB:cb47
// SM2MAIN:977c
// Signature: [A, X] -> []
void XMoveCntr_Platform(const byte param_1, const byte param_2) {
  if ((FrameCounter & 3) != 0) {
    return;
  }
  if ((SpriteVarData2[param_2] & 1) != 0) {
    if (SpriteVarData1[param_2] != 0) {
      SpriteVarData1[param_2] = SpriteVarData1[param_2] - 1;
      return;
    }
  } else if (SpriteVarData1[param_2] != param_1) {
    SpriteVarData1[param_2] = SpriteVarData1[param_2] + 1;
    return;
  }
  SpriteVarData2[param_2] = SpriteVarData2[param_2] + 1;
}


// SMB:cb66
// SM2MAIN:979b
// Signature: [X, r08] -> [r00]
byte MoveWithXMCntrs(const byte param_1, const byte objoff) {
  const byte bStack0000 = SpriteVarData1[param_1];
  byte bVar1 = 1;
  if ((SpriteVarData2[param_1] & 2) == 0) {
    SpriteVarData1[param_1] = NEGATE(SpriteVarData1[param_1]);
    bVar1 = 2;
  }
  Enemy_MovingDir[param_1] = bVar1;
  const byte sVar2 = MoveEnemyHorizontally(param_1);
  SpriteVarData1[objoff] = bStack0000;
  return sVar2;
}


// SMB:cb89
// SM2MAIN:97be
// Signature: [X, C] -> [X]
byte MoveBloober(const byte param_1, const bool param_2) {
  if ((Enemy_State[param_1] & 0x20) != 0) {
    MoveEnemySlowVert(param_1);
    return ObjectOffset;
  }

  const byte rng = PseudoRandomBitReg[param_1 + 1] & (SecondaryHardMode == 0 ? 63 : 3);

  if (rng == 0) {
    byte bVar2;
    bool tmp2;

    if ((param_1 & 1) != 0) {
      bVar2 = Player_MovingDir;
      tmp2 = true;
    } else {
      const struct_ncr00 sVar3 = PlayerEnemyDiff(param_1);
      bVar2 = sVar3.n ? 1 : 2;
      tmp2 = sVar3.c;
    }
    Enemy_MovingDir[param_1] = bVar2;
    ProcSwimmingB(param_1, tmp2);
  } else {
    ProcSwimmingB(param_1, param_2);
  }

  const byte ydiff = Enemy_Y_Position[param_1] - CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];

  if (ydiff >= 0x20) {
    Enemy_Y_Position[param_1] = ydiff;
  }

  if (Enemy_MovingDir[param_1] == 1) {
    ADD_UNSIGNED_16_8(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
                      SpriteVarData1[param_1]);
  } else {
    SUB_UNSIGNED_16_8(Enemy_PageLoc[param_1], Enemy_X_Position[param_1],
                      SpriteVarData1[param_1]);
  }
  return param_1;
}


// SMB:cbdf
// SM2MAIN:9814
// Signature: [X, C] -> []
void ProcSwimmingB(const byte param_1, const bool param_2) {
  if ((SpriteVarData2[param_1] & 2) == 0) {
    if ((SpriteVarData2[param_1] & 1) == 0) {
      if ((FrameCounter & 7) == 0) {
        const byte bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] + 1;
        CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1;
        SpriteVarData1[param_1] = bVar1;
        if (bVar1 == 2) {
          SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
        }
      }
    } else if ((FrameCounter & 7) == 0) {
      const byte bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] - 1;
      CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1] = bVar1;
      SpriteVarData1[param_1] = bVar1;
      if (bVar1 == 0) {
        SpriteVarData2[param_1] = SpriteVarData2[param_1] + 1;
        EnemyIntervalTimer[param_1] = 2;
      }
    }
  } else if ((EnemyIntervalTimer[param_1] == 0)
      && (SprObject_Y_Position[0] <= (byte)(Enemy_Y_Position[param_1] + 0x10 + param_2))) {
    SpriteVarData2[param_1] = 0;
  } else if ((FrameCounter & 1) == 0) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
  }
}


// SMB:cc36
// SM2MAIN:986b
// Signature: [X] -> []
void MoveBulletBill(const byte param_1) {
  if ((Enemy_State[param_1] & 0x20) != 0) {
    MoveJ_EnemyVertically(param_1);
  } else {
    SpriteVarData1[param_1] = 0xe8;
    MoveEnemyHorizontally(param_1);
  }
}


// SMB:cc4a
// SM2MAIN:987f
// Signature: [X] -> [X]
byte MoveSwimmingCheepCheep(const byte param_1) {
  if ((Enemy_State[param_1] & 0x20) != 0) {
    MoveEnemySlowVert(param_1);
    return ObjectOffset;
  }

  const u8 cheepcheep_speed = Enemy_ID[param_1] == 0xa ? 0x40 : 0x80;

  SUB_24_24(Enemy_PageLoc[param_1], Enemy_X_Position[param_1], Enemy_X_MoveForce[param_1],
            0, 0, cheepcheep_speed);

  if (param_1 > 1) {
    if (SpriteVarData1[param_1] < 0x10) {
      SUB_24_24(Enemy_Y_HighPos[param_1], Enemy_Y_Position[param_1], Enemy_YMF_Dummy[param_1],
                0, 0, ssw(0x20, 0x40));
    } else {
      ADD_24_24(Enemy_Y_HighPos[param_1], Enemy_Y_Position[param_1], Enemy_YMF_Dummy[param_1],
                0, 0, ssw(0x20, 0x40));
    }

    const i8 bVar3 = Enemy_Y_Position[param_1] - Enemy_Y_MoveForce[param_1];

    if (bVar3 > 0xe) {
      SpriteVarData1[param_1] = 0;
    } else if (bVar3 < -0xe) {
      SpriteVarData1[param_1] = 0x10;
    }
  }

  return param_1;
}


// SMB:cd3c
// SM2MAIN:9971
// Signature: [X] -> [X]
byte ProcFirebar(const byte param_1) {
  GetEnemyOffscreenBits(param_1);
  const byte objoff = ObjectOffset;

  if ((Enemy_OffscreenBits & 8) != 0) {
    return objoff;
  }

  if (TimerControl == 0) {
    // Inlined: FirebarSpin
    // NES note: it's only called once, and inlining reveals a full 16-bit addition and subtraction

    u16 val = LOAD_16(SpriteVarData2[objoff], SpriteVarData1[objoff]);

    if (FirebarSpinDirection[objoff] == 0) {
      val += FirebarSpinSpeed[objoff];
    } else {
      val -= FirebarSpinSpeed[objoff];
    }

    val = val & 0x1fff;

    STORE_16(SpriteVarData2[objoff], SpriteVarData1[objoff],
        val);
  }


  byte tmp1 = SpriteVarData2[objoff];
  if ((Enemy_ID[objoff] > 0x1e) && ((tmp1 == 8) || (tmp1 == 0x18))) {
    tmp1 += 1;
    SpriteVarData2[objoff] = tmp1;
  }

  RelativeEnemyPosition(objoff);
  // NES note: There's normally a call to GetFirebarPosition right after RelativeEnemyPosition,
  // but it does nothing. The results are unused.
  // This port omits it.

  const byte bVar4 = Enemy_Rel_YPos;
  const byte sproff = Enemy_SprDataOffset[ObjectOffset];
  SPRITE_Y(sproff, 0) = Enemy_Rel_YPos;
  SPRITE_X(sproff, 0) = Enemy_Rel_XPos;

  byte bVar2 = FirebarCollision(sproff, Enemy_Rel_XPos, bVar4);

  const byte tmpred = (Enemy_ID[ObjectOffset] > 0x1e) ? 11 : 5;

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

  // returns the X register from DrawFirebar_Collision
  return ObjectOffset;
}


// SMB:cdbb
// SM2MAIN:99f0
// Signature: [r01, r02, r03, r06] -> [r06]
byte DrawFirebar_Collision(const byte param_2, const byte param_3, const byte param_4, const byte param_5) {
  const byte bVar1 = Enemy_Rel_XPos + ((param_4 & 1) != 0 ? param_2 : -param_2);

  SPRITE_X(param_5, 0) = bVar1;

  byte bVar3;
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
byte FirebarCollision(const byte param_1, const byte param_3, const byte param_4) {
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
struct_r01r02r03 GetFirebarPosition(const byte param_1, const byte param_2) {
  struct_r01r02r03 sVar3;

  // bVar1 = 0123456787654321 ...
  // bVar2 = 8765432101234567 ...
  byte bVar1 = param_1 % 16;
  if (bVar1 > 8) {
    bVar1 = 16 - bVar1;
  }
  byte bVar2 = (param_1 + 8) % 16;
  if (bVar2 > 8) {
    bVar2 = 16 - bVar2;
  }

  sVar3.r02 = FirebarPosLookupTbl[(byte)(FirebarTblOffsets[param_2] + bVar2)];
  sVar3.r01 = FirebarPosLookupTbl[(byte)(FirebarTblOffsets[param_2] + bVar1)];
  sVar3.r03 = FirebarMirrorData[param_1 >> 3];
  return sVar3;
}


// SMB:cedf
// SM2MAIN:9b14
// Signature: [X] -> []
void MoveFlyingCheepCheep(const byte param_1) {
  if ((Enemy_State[param_1] & 0x20) != 0) {
    Enemy_SprAttrib[param_1] = 0;
    MoveJ_EnemyVertically(param_1);
    return;
  }
  MoveEnemyHorizontally(param_1);
  SetXMoveAmt(5, ObjectOffset, 0xd);
  const byte bVar2 = ObjectOffset;
  byte bVar3 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar2] >> 4;
  byte bVar1 = Enemy_Y_Position[bVar2] - PRandomSubtracter[bVar3];
  if (bVar1 >= 0x80) {
    bVar1 = NEGATE(bVar1);
  }
  if (bVar1 < 8) {
    bVar1 = CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar2];
    CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[bVar2] = bVar1 + 0x10;
    bVar3 = (byte)(bVar1 + 0x10) >> 4;
  }
  Enemy_SprAttrib[bVar2] = FlyCCBPriority[bVar3];
}


// SMB:cf28
// SM2MAIN:9b5d
// Signature: [X] -> []
void MoveLakitu(const byte param_1) {
  byte bVar1;

  if ((Enemy_State[param_1] & 0x20) == 0) {
    if (Enemy_State[param_1] == 0) {
      EnemyFrenzyBuffer = 0x12;
      bVar1 = PlayerLakituDiff(param_1, LakituDiffAdj[0], LakituDiffAdj[1], LakituDiffAdj[2]);
    } else {
      SpriteVarData2[param_1] = 0;
      EnemyFrenzyBuffer = 0;
      bVar1 = 0x10;
    }
    SpriteVarData1[param_1] = bVar1;
    bVar1 = 1;
    if ((SpriteVarData2[param_1] & 1) == 0) {
      SpriteVarData1[param_1] = NEGATE(SpriteVarData1[param_1]);
      bVar1 = 2;
    }
    Enemy_MovingDir[param_1] = bVar1;
    MoveEnemyHorizontally(param_1);
  } else {
    MoveD_EnemyVertically(param_1);
  }
}


// SMB:cf6c
// SM2MAIN:9ba1
// Signature: [X, r01, r02, r03] -> [A]
byte PlayerLakituDiff(const byte param_1, const byte param_2, const byte param_3, const byte param_4) {
  byte bVar2 = 0;
  const struct_ncr00 sVar4 = PlayerEnemyDiff(param_1);
  byte bVar1 = sVar4.r00;
  if (sVar4.n) {
    bVar2 += 1;
    bVar1 = NEGATE(bVar1);
  }

  if (bVar1 >= 0x3c) {
    bVar1 = 0x3c;
    if (Enemy_ID[param_1] == 0x11) {
      if (bVar2 != SpriteVarData2[param_1]) {
        if (SpriteVarData2[param_1] != 0) {
          SpriteVarData1[param_1] = SpriteVarData1[param_1] - 1;
          if (SpriteVarData1[param_1] != 0) {
            return SpriteVarData1[param_1];
          }
        }
        SpriteVarData2[param_1] = bVar2;
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
  } else if ((Enemy_ID[param_1] != 0x12) && (SpriteVarData2[param_1] == 0)) {
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
  byte bVar1;

  if (Enemy_ID[BowserFront_Offset] == 0x2d) {
    ObjectOffset = BowserFront_Offset;
    if (Enemy_State[BowserFront_Offset] == 0) {
      BowserFeetCounter -= 1;
      bVar1 = BowserFront_Offset;
      if (BowserFeetCounter == 0) {
        BowserFeetCounter = 4;
        BowserBodyControls ^= 1;

        const byte data = BridgeCollapseData[BridgeCollapseOffset];
        const byte x = data % 32;
        const byte y = data / 32;

        // x and y should be multiples of 2
        assert_eq_assumption(x % 2, 0);
        assert_eq_assumption(y % 2, 0);

        const byte vramoff = VRAM_Buffer1_Offset + 1;

        // Inlined: RemBridge
        draw_block_metatile(vramoff, 3, x/2, (y/2)+8, 0);

        bVar1 = ObjectOffset;

        // Inlined: MoveVOffset
        VRAM_Buffer1_Offset += 10;

        Square2SoundQueue = 8;
        NoiseSoundQueue = 1;
        BridgeCollapseOffset += 1;
        if (BridgeCollapseOffset == 0xf) {
          InitVStf(bVar1);
          Enemy_State[bVar1] = 0x40;
          Square2SoundQueue = 0x80;
        }
      }
      BowserGfxHandler(bVar1);
      return;
    }
    if (((Enemy_State[BowserFront_Offset] & 0x40) != 0) && (Enemy_Y_Position[BowserFront_Offset] < 0xe0)) {
      MoveD_Bowser(BowserFront_Offset);
      return;
    }
  }
  EventMusicQueue = 0x80;
  OperMode_Task += 1;
  KillAllEnemies();
}


// SMB:d00f
// SM2MAIN:9c44
// Signature: [X] -> [X]
byte MoveD_Bowser(const byte param_1) {
  MoveEnemySlowVert(param_1);
  const byte bVar1 = ObjectOffset;
  return BowserGfxHandler(bVar1);
}


// SMB:d065
// SM2MAIN:9c9a
// Signature: [X] -> [X]
byte RunBowser(const byte param_1) {
  byte bVar1;
  byte bVar2;
  struct_xc sVar3;
  struct_ncr00 sVar4;

  byte tmp1 = param_1;

  if ((Enemy_State[tmp1] & 0x20) != 0) {
    if (Enemy_Y_Position[tmp1] >= 0xe0) {
      KillAllEnemies();
      return ObjectOffset;
    }
    return MoveD_Bowser(tmp1);
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
      Enemy_MovingDir[tmp1] = 2;
    }
    if ((EnemyFrameTimer[tmp1] != 0)) {
      sVar4 = PlayerEnemyDiff(tmp1);
      if (sVar4.n) {
        Enemy_MovingDir[tmp1] = 1;
        BowserMovementSpeed = 2;
        EnemyFrameTimer[tmp1] = 0x20;
        BowserFireBreathTimer = 0x20;
        if (199 < Enemy_X_Position[tmp1]) {
          goto HammerChk;
        }
      }
    }
    if ((FrameCounter & 3) == 0) {
      if (Enemy_X_Position[tmp1] == BowserOrigXPos) {
        MaxRangeFromOrigin = PRandomRange[PseudoRandomBitReg[tmp1] & 3];
      }
      bVar1 = Enemy_X_Position[tmp1] + BowserMovementSpeed;
      Enemy_X_Position[tmp1] = bVar1;
      if (Enemy_MovingDir[tmp1] != 1) {
        bVar2 = 0xff;
        bVar1 -= BowserOrigXPos;
        if (bVar1 >= 0x80) {
          bVar1 = NEGATE(bVar1);
          bVar2 = 1;
        }
        if (MaxRangeFromOrigin <= bVar1) {
          BowserMovementSpeed = bVar2;
        }
      }
    }
  }
HammerChk:
  if (EnemyFrameTimer[tmp1] == 0) {
    MoveEnemySlowVert(tmp1);
    tmp1 = ObjectOffset;
    if ((WorldNumber >= 5) && ((FrameCounter & 3) == 0)) {
      sVar3 = SpawnHammerObj();
      tmp1 = sVar3.x;
    }
    if (Enemy_Y_Position[tmp1] >= 0x80) {
      EnemyFrameTimer[tmp1] = PRandomRange[PseudoRandomBitReg[tmp1] & 3];
    }
  } else if (EnemyFrameTimer[tmp1] == 1) {
    Enemy_Y_Position[tmp1] = Enemy_Y_Position[tmp1] - 1;
    InitVStf(tmp1);
    SpriteVarData2[tmp1] = 0xfe;
  }
ChkFireB:

  if ((WorldNumber != 7) && (WorldNumber >= 5)) {
    return BowserGfxHandler(tmp1);
  }
  if (BowserFireBreathTimer != 0) {
    return BowserGfxHandler(tmp1);
  }
  BowserFireBreathTimer = 0x20;
  BowserBodyControls ^= 0x80;

  if ((BowserBodyControls & 0x80) == 0) {
    return BowserGfxHandler(tmp1);
  }

  BowserFireBreathTimer = SetFlameTimer();

  if (SecondaryHardMode != 0) {
    BowserFireBreathTimer -= 0x10;
  }
  EnemyFrenzyBuffer = 0x15;
  return BowserGfxHandler(tmp1);
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


// SMB:d17b
// SM2MAIN:9db0
// Signature: [X] -> [X]
byte BowserGfxHandler(const byte param_1) {
  const byte bVar2 = ProcessBowserHalf(param_1);
  const char cVar3 = ((Enemy_MovingDir[bVar2] & 1) != 0) ? -0x10 : 0x10;
  Enemy_X_Position[DuplicateObj_Offset] = cVar3 + Enemy_X_Position[bVar2];
  Enemy_Y_Position[DuplicateObj_Offset] = Enemy_Y_Position[bVar2] + 8;
  Enemy_State[DuplicateObj_Offset] = Enemy_State[bVar2];
  Enemy_MovingDir[DuplicateObj_Offset] = Enemy_MovingDir[bVar2];

  const byte bStack0000 = ObjectOffset;
  ObjectOffset = DuplicateObj_Offset;
  Enemy_ID[DuplicateObj_Offset] = 0x2d;
  ProcessBowserHalf(DuplicateObj_Offset);
  ObjectOffset = bStack0000;
  BowserGfxFlag = 0;
  return bStack0000;
}


// SMB:d1bc
// SM2MAIN:9df1
// Signature: [X] -> [X]
byte ProcessBowserHalf(const byte param_1) {
  BowserGfxFlag += 1;
  RunRetainerObj(param_1);
  byte bVar1 = ObjectOffset;
  if (Enemy_State[bVar1] == 0) {
    Enemy_BoundBoxCtrl[bVar1] = 10;
    GetEnemyBoundBox(bVar1);
    bVar1 = ObjectOffset;
    PlayerEnemyCollision(bVar1);
    return bVar1;
  }
  return bVar1;
}


// SMB:d1d9
// SM2MAIN:9e0e
// Signature: [] -> [A]
byte SetFlameTimer(void) {
  const byte bVar1 = BowserFlameTimerCtrl;
  BowserFlameTimerCtrl = (BowserFlameTimerCtrl + 1) & 7;
  return FlameTimerData[bVar1];
}


// SMB:d1eb
// SM2MAIN:9e20
// Signature: [X] -> []
void ProcBowserFlame(const byte param_1) {
  if (TimerControl == 0) {
    const byte bVar33 = (SecondaryHardMode != 0) ? 0x60 : 0x40;
    const bool bVar1 = Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] < bVar33;
    Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1]
        = Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1] - bVar33;

    const byte bVar3 = Enemy_X_Position[param_1];
    Enemy_X_Position[param_1] = (bVar3 - 1) - bVar1;
    Enemy_PageLoc[param_1] = Enemy_PageLoc[param_1] - ((bVar1 || bVar3 == 0) && (!bVar1 || bVar3 < 2));
    if (Enemy_Y_Position[param_1]
        != FlameYPosData[BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1]]) {
      Enemy_Y_Position[param_1]
          = Enemy_Y_Position[param_1] + CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];
    }
  }

  RelativeEnemyPosition(param_1);

  if (Enemy_State[ObjectOffset] != 0) {
    return;
  }

  const byte bVar55 = ((FrameCounter & 2) != 0) ? 0x82 : 2;
  const byte offset = Enemy_SprDataOffset[ObjectOffset];
  for (int i = 0; i < 3; i++) {
    SPRITE_Y_strict(offset, i) = Enemy_Rel_YPos;
    SPRITE_TILE_semistrict(offset, i) = 0x51 + i;
    SPRITE_ATTR_semistrict(offset, i) = bVar55;
    SPRITE_X_semistrict(offset, i) = Enemy_Rel_XPos;
    Enemy_Rel_XPos += 8;
  }

  GetEnemyOffscreenBits(ObjectOffset);
  const byte objoff = ObjectOffset;
  const byte bVar3 = Enemy_SprDataOffset[objoff];

  const byte bits = Enemy_OffscreenBits;

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
void RunFireworks(const byte param_1) {
  const byte bVar1 = SpriteVarData2[param_1] - 1;
  SpriteVarData2[param_1] = bVar1;
  if (bVar1 == 0) {
    SpriteVarData2[param_1] = 8;
    SpriteVarData1[param_1] = SpriteVarData1[param_1] + 1;
    if (SpriteVarData1[param_1] > 2) {
      Enemy_Flag[param_1] = 0;
      Square2SoundQueue = 8;
      DigitModifier[4] = 5;
      EndAreaPoints();
      return;
    }
  }
  RelativeEnemyPosition(param_1);
  Fireball_Rel_YPos = Enemy_Rel_YPos;
  Fireball_Rel_XPos = Enemy_Rel_XPos;
  DrawExplosion_Fireworks(SpriteVarData1[ObjectOffset], Enemy_SprDataOffset[ObjectOffset]);
}


enum RunStarFlagObj_jumptable_item {
  RUNSTARFLAGOBJ_NOOP,
  RUNSTARFLAGOBJ_GAMETIMERFIREWORKS,
  RUNSTARFLAGOBJ_AWARDGAMETIMERPOINTS,
  RUNSTARFLAGOBJ_RAISEFLAGSETOFFFWORKS,
  RUNSTARFLAGOBJ_DELAYTOAREAEND,
};


// SMB:d2d9
// SM2MAIN:9f0e
// Signature: [X] -> [X]
byte RunStarFlagObj(const byte param_1) {
  EnemyFrenzyBuffer = 0;

  switch (StarFlagTaskControl) {
  case RUNSTARFLAGOBJ_NOOP:
    // NES note: goes to "StarFlagExit" (a no-op)
    return param_1;

  case RUNSTARFLAGOBJ_GAMETIMERFIREWORKS:
    GameTimerFireworks(param_1);
    return param_1;

  case RUNSTARFLAGOBJ_AWARDGAMETIMERPOINTS:
    return AwardGameTimerPoints(param_1);

  case RUNSTARFLAGOBJ_RAISEFLAGSETOFFFWORKS:
    return RaiseFlagSetoffFWorks(param_1);

  case RUNSTARFLAGOBJ_DELAYTOAREAEND:
    return DelayToAreaEnd(param_1);

  default:
    // No jmpengine_overflow() warning here, because the original NES version takes care of it!
    return param_1;
  }
}


// SMB:d2f2
// SM2MAIN:9f27
// Signature: [X] -> []
void GameTimerFireworks(const byte param_1) {
  const byte last_digit = GameTimerDisplay[2];

  Enemy_State[param_1] = 0;
  FireworksCounter = 0xff;

#ifdef SMB1_MODE
  if (last_digit == 1) {
    Enemy_State[param_1] = 5;
    FireworksCounter = 1;
  } else if (last_digit == 3) {
    Enemy_State[param_1] = 3;
    FireworksCounter = 3;
  } else if (last_digit == 6) {
    Enemy_State[param_1] = 0;
    FireworksCounter = 6;
  }
#endif
#ifdef SMB2J_MODE
  if (last_digit == CoinDisplay[1]) {
    // only show fireworks if the last digit of the timer
    // is the last digit of the coins

    if ((last_digit & 1) == 0) {
      // timer is even
      Enemy_State[param_1] = 0;
      FireworksCounter = 6;
    } else {
      // timer is odd
      Enemy_State[param_1] = 3;
      FireworksCounter = 3;
    }
  }
#endif

  StarFlagTaskControl += 1;
}


// SMB:d312
// SM2MAIN:9f4c
// Signature: [X] -> [X]
byte AwardGameTimerPoints(const byte param_1) {
  if ((GameTimerDisplay[0] | GameTimerDisplay[1] | GameTimerDisplay[2]) != 0) {
    AwardTimerCastle();
    return ObjectOffset;
  }
  StarFlagTaskControl = StarFlagTaskControl + 1;
  return param_1;
}


// SMB:d31d
// SM2MAIN:9f57
// Signature: [] -> []
void AwardTimerCastle(void) {
  if ((FrameCounter & 4) != 0) {
    Square2SoundQueue = 0x10;
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


// SMB:d34e
// SM2MAIN:9f7a
// Signature: [X] -> [X]
byte RaiseFlagSetoffFWorks(const byte param_1) {
  if (Enemy_Y_Position[param_1] >= 0x72) {
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
    DrawStarFlag(param_1);
    return ObjectOffset;
  }
  if ((FireworksCounter != 0) && (FireworksCounter < 0x80)) {
    EnemyFrenzyBuffer = 0x16;
    DrawStarFlag(param_1);
    return ObjectOffset;
  }
  DrawStarFlag(param_1);
  const byte bVar1 = ObjectOffset;
  EnemyIntervalTimer[bVar1] = 6;
  StarFlagTaskControl = StarFlagTaskControl + 1;
  return bVar1;
}


// SMB:d365
// SM2MAIN:9f91
// Signature: [X] -> []
void DrawStarFlag(const byte param_1) {
  RelativeEnemyPosition(param_1);
  const byte bVar2 = Enemy_SprDataOffset[ObjectOffset];

  for (int i = 0; i < 4; i++) {
    SPRITE_Y_strict(bVar2, i) = Enemy_Rel_YPos + StarFlagYPosAdder[3 - i];
    SPRITE_TILE_semistrict(bVar2, i) = StarFlagTileData[3 - i];
    SPRITE_ATTR_semistrict(bVar2, i) = 0x22;
    SPRITE_X_semistrict(bVar2, i) = Enemy_Rel_XPos + StarFlagXPosAdder[3 - i];
  }

}


// SMB:d3a2
// SM2MAIN:9fce
// Signature: [X] -> [X]
byte DelayToAreaEnd(const byte param_1) {
  DrawStarFlag(param_1);
  const byte bVar1 = ObjectOffset;
  if ((EnemyIntervalTimer[bVar1] == 0) && (EventMusicBuffer == 0)) {
    StarFlagTaskControl = StarFlagTaskControl + 1;
    return bVar1;
  }
  return bVar1;
}


// SMB:d3b0
// SM2MAIN:9fdc
// Signature: [X] -> []
void MovePiranhaPlant(const byte param_1) {
  if ((Enemy_State[param_1] == 0) && (EnemyFrameTimer[param_1] == 0)) {
    if (SpriteVarData2[param_1] == 0) {
      if (SpriteVarData1[param_1] < 0x80) {
        const struct_ncr00 sVar4 = PlayerEnemyDiff(param_1);
        const byte bVar3 = sVar4.n ? -sVar4.r00 : sVar4.r00;

        if (bVar3 < PiranhaPlantCompareOperand) {
          // PutinPipe
          Enemy_SprAttrib[param_1] = 0x20;
          return;
        }
      }

      SpriteVarData1[param_1] *= -1;
      SpriteVarData2[param_1] += 1;
    }

    const byte bVar3 = SpriteVarData1[param_1] >= 0x80
      ? BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1]
      : CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1];

    if (TimerControl == 0) {
      const bool cond1 = (SMB2J_ONLY && EnemyAttributeData[13] == 0x22) || ((FrameCounter & 1) != 0);

      if (cond1) {
        Enemy_Y_Position[param_1] += SpriteVarData1[param_1];

        if (Enemy_Y_Position[param_1] == bVar3) {
          SpriteVarData2[param_1] = 0;
          EnemyFrameTimer[param_1] = 0x40;
        }
      }
    }
  }

  // PutinPipe
  Enemy_SprAttrib[param_1] = 0x20;
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
// Signature: [X] -> [X]
byte BalancePlatform(const byte param_1) {
  if (Enemy_Y_HighPos[param_1] == 3) {
    EraseEnemyObject(param_1);
    return param_1;
  }

  const byte enemy_state = Enemy_State[param_1];

#ifdef SMB2J_MODE
  if (Enemy_ID[enemy_state] != 0x24) {
    return param_1;
  }
#endif

  if (enemy_state >= 0x80) {
    return param_1;
  }

  if (Enemy_MovingDir[param_1] != 0) {
    PlatformFall(param_1, enemy_state);
    return ObjectOffset;
  }

  if (Enemy_Y_Position[param_1] < 0x2e) {
    if (enemy_state != PlatformCollisionFlag[param_1]) {
      Enemy_Y_Position[param_1] = 0x2f;
      StopPlatforms(param_1, enemy_state);
      return param_1;
    }
    InitPlatformFall(enemy_state, ObjectOffset);
    return ObjectOffset;
  }

  if (Enemy_Y_Position[enemy_state] < 0x2e) {
    if (param_1 != PlatformCollisionFlag[param_1]) {
      Enemy_Y_Position[enemy_state] = 0x2f;
      StopPlatforms(param_1, enemy_state);
      return param_1;
    }
    InitPlatformFall(enemy_state, ObjectOffset);
    return ObjectOffset;
  }

  // 0 = stop
  // 1 = up
  // 2 = down
  int platform_mode = 1;

  const byte bVar2 = PlatformCollisionFlag[param_1];

  if ((bVar2 & 0x80) == 0) {
    if (bVar2 == ObjectOffset) {
      platform_mode = 2;
    }
  } else {
    u16 yvel = LOAD_16(Enemy_Y_Speed[param_1], Enemy_Y_MoveForce[param_1]);
    yvel += 5;

    if ((i16)yvel < 0) {
      platform_mode = 2;
    }
    if (yvel <= 10) {
      platform_mode = 0;
    }
  }

  const byte bStack0000 = Enemy_Y_Position[param_1];

  byte tmp1 = param_1;

  switch (platform_mode) {
  case 0:
    StopPlatforms(param_1, enemy_state);
    break;

  case 1:
    MovePlatformUp(param_1);
    tmp1 = ObjectOffset;
    break;

  case 2:
    MovePlatformDown(param_1);
    tmp1 = ObjectOffset;
    break;
  }

  Enemy_Y_Position[Enemy_State[tmp1]] = (bStack0000 - Enemy_Y_Position[tmp1]) + Enemy_Y_Position[Enemy_State[tmp1]];

  if ((PlatformCollisionFlag[tmp1] & 0x80) == 0) {
    PositionPlayerOnVPlat(PlatformCollisionFlag[tmp1]);
  }

  const u8 objoff = ObjectOffset;

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

  return ObjectOffset;
}


// SMB:d598
// SM2MAIN:a1d2
// Signature: [Y, r08] -> []
void InitPlatformFall(const byte param_1, const byte objoff) {
  GetEnemyOffscreenBits(param_1);

  SetupFloateyNumber(6, objoff);
  FloateyNum_X_Pos[objoff] = SprObject_Rel_XPos[0];
  FloateyNum_Y_Pos[objoff] = SprObject_Y_Position[0];
  Enemy_MovingDir[objoff] = 1;

  // NES note: GetEnemyOffscreenBits sets Y=1. This is later used by StopPlatforms.
  // This is either a bug, or just a way to reuse the value. Either way, it's best extracted out to the caller (here).
  StopPlatforms(objoff, 1);
}


// SMB:d5b1
// SM2MAIN:a1eb
// Signature: [X, Y] -> []
void StopPlatforms(const byte param_1, const byte param_2) {
  const byte bVar1 = InitVStf(param_1);
  SpriteVarData2[param_2] = bVar1;
  CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_2] = bVar1;
}


// SMB:d5bb
// SM2MAIN:a1f5
// Signature: [X, Y] -> []
void PlatformFall(const byte param_1, const byte param_2) {
  const byte bStack0000 = param_2;
  MoveFallingPlatform(param_1);
  MoveFallingPlatform(bStack0000);
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset] < 0x80) {
    PositionPlayerOnVPlat(HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset]);
  }
}


// SMB:d5d3
// SM2MAIN:a20d
// Signature: [X] -> [X]
byte YMovingPlatform(const byte param_1) {
  if (((SpriteVarData2[param_1] | CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]) == 0)) {
    BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1] = 0;
    if (Enemy_Y_Position[param_1] < Enemy_X_MoveForce_Or_RedPTroopaOrigXPos_Or_YPlatformTopYPos[param_1]) {
      if ((FrameCounter & 7) == 0) {
        Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 1;
      }
      ChkYPCollision(param_1);
      return param_1;
    }
  }
  if (SpriteVarData1[param_1] <= Enemy_Y_Position[param_1]) {
    MovePlatformUp(param_1);
    const byte bVar1 = ObjectOffset;
    ChkYPCollision(bVar1);
    return bVar1;
  }
  MovePlatformDown(param_1);
  const byte bVar1 = ObjectOffset;
  ChkYPCollision(bVar1);
  return bVar1;
}


// SMB:d5fe
// SM2MAIN:a238
// Signature: [X] -> []
void ChkYPCollision(const byte param_1) {
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] < 0x80) {
    PositionPlayerOnVPlat(param_1);
  }
}


// SMB:d607
// SM2MAIN:a241
// Signature: [X, r08] -> []
void XMovingPlatform(const byte param_1, const byte objoff) {
  XMoveCntr_Platform(0xe, param_1);
  const byte sVar2 = MoveWithXMCntrs(param_1, objoff);
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[objoff] < 0x80) {
    PositionPlayerOnHPlat(objoff, sVar2);
  }
}


// SMB:d614
// SM2MAIN:a24e
// Signature: [X, r00] -> []
void PositionPlayerOnHPlat(const byte param_1, const byte param_2) {
  ADD_SIGNED_16_8(SprObject_PageLoc[0], SprObject_X_Position[0], param_2);

  Platform_X_Scroll = param_2;
  PositionPlayerOnVPlat(param_1);
}


// SMB:d631
// SM2MAIN:a26b
// Signature: [X] -> [X]
byte DropPlatform(const byte param_1) {
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] >= 0x80) {
    return param_1;
  }

  MoveDropPlatform(param_1);
  byte tmp = ObjectOffset;
  PositionPlayerOnVPlat(tmp);
  return tmp;
}


// SMB:d63d
// SM2MAIN:a277
// Signature: [X, r08] -> []
void RightPlatform(const byte param_1, const byte objoff) {
  const byte sVar2 = MoveEnemyHorizontally(param_1);
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[objoff] < 0x80) {
    SpriteVarData1[objoff] = 0x10;
    PositionPlayerOnHPlat(objoff, sVar2);
  }
}


// SMB:d64f
// SM2MAIN:a289
// Signature: [X] -> []
void MoveLargeLiftPlat(const byte param_1) {
  MoveLiftPlatforms(param_1);
  ChkYPCollision(param_1);
}


// SMB:d655
// SM2MAIN:a28f
// Signature: [X] -> []
void MoveSmallPlatform(const byte param_1) {
  MoveLiftPlatforms(param_1);
  ChkSmallPlatCollision(param_1);
}


// SMB:d65b
// SM2MAIN:a295
// Signature: [X] -> []
void MoveLiftPlatforms(const byte param_1) {
  if (TimerControl != 0) {
    return;
  }

  ADD_16_16(Enemy_Y_Position[param_1], BowserFlamePRandomOfs_Or_Enemy_YMF_Dummy_Or_PiranhaPlantUpYPos[param_1],
            SpriteVarData2[param_1], CheepCheepOrigYPos_Or_Enemy_Y_MoveForce_Or_PiranhaPlantDownYPos[param_1]);
}


// SMB:d671
// SM2MAIN:a2ab
// Signature: [X] -> []
void ChkSmallPlatCollision(const byte param_1) {
  if (HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] != 0) {
    PositionPlayerOnS_Plat(HammerThrowingTimer_Or_PlatformCollisionFlag[param_1], param_1);
  }
}


// SMB:d67a
// SM2MAIN:a2b4
// Signature: [X] -> []
void OffscreenBoundsCheck(const byte param_1) {
  if (Enemy_ID[param_1] == 0x14) {
    return;
  }
  const byte bVar1 = Enemy_ID[param_1];
  bool bVar7;
  byte abVar5;
  if (bVar1 == 5 || bVar1 == 0xd || ssw(false, bVar1 == 4)) {
    abVar5 = ScreenEdgeOrLeft_X_Pos[0] + 0x38 + 1;
    bVar7 = ScreenEdgeOrLeft_X_Pos[0] >= 200 || abVar5 == 0;
  } else {
    abVar5 = ScreenEdgeOrLeft_X_Pos[0];
    bVar7 = bVar1 >= 0xd;
  }
  const bool bVar2 = abVar5 >= 0x48;
  const bool bVar3 = !bVar7;
  const bool bVar4 = abVar5 > 0x48;
  const bool nk = (bVar7 && bVar2) || (bVar3 && bVar4);
  const bool k = !nk;
  const bool bVar8 = nk || (!nk && ScreenEdgeOrLeft_PageLoc[0] != 0);
  const byte bVar6 = ScreenRight_X_Pos + 0x48 + bVar8;

  const byte e_ploc = Enemy_PageLoc[param_1];
  const byte e_xp = Enemy_X_Position[param_1];
  const bool p = (ScreenRight_X_Pos >= 0xb8) || (bVar8 && bVar6 == 0);
  const byte q = (byte)(abVar5 + 0xb8 - !bVar7);
  const byte sl_ploc = ScreenEdgeOrLeft_PageLoc[0];
  const byte sr_ploc = ScreenRight_PageLoc;

  const bool A = (byte)(e_ploc - sl_ploc + k - (e_xp < q)) >= 0x80;
  const bool B = (byte)(e_ploc - sr_ploc - p - (e_xp < bVar6)) >= 0x80;

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
  if (bVar1 == 0xd) { return; }
  if (bVar1 == 0x30) { return; }
  if (bVar1 == 0x31) { return; }
  if (bVar1 == 0x32) { return; }
  if (SMB2J_ONLY && bVar1 == 0x4) { return; }

  EraseEnemyObject(param_1);
}


// SMB:d6d9
// SM2MAIN:a319
// Signature: [X] -> []
void FireballEnemyCollision(const byte param_1) {
  byte bVar1;
  byte bVar2;
  bool bVar3;
  byte bStack0000;

  if (((Fireball_State[param_1] != 0) && ((Fireball_State[param_1] & 0x80) == 0)) && ((FrameCounter & 1) == 0)) {
    bStack0000 = param_1 * 4 + 0x1c;
    for (int i = 4; i >= 0; i--) {
      bVar2 = i;
      if (((Enemy_State[bVar2] & 0x20) == 0) && (Enemy_Flag[bVar2] != 0)) {
        bVar1 = Enemy_ID[bVar2];
        if ((bVar1 < 0x24) || (bVar1 > 0x2a)) {
          if ((bVar1 != 6 || (Enemy_State[bVar2] < 2))) {
            if (EnemyOffscrBitsMasked[bVar2] == 0) {
              bVar3 = SprObjectCollisionCore(bVar2 * 4 + 4, bStack0000);
              if (bVar3) {
                Fireball_State[ObjectOffset] = 0x80;
                HandleEnemyFBallCol(bVar2, bVar2);
              }
            }
          }
        }
      }
    }
  }
}


// SMB:d73e
// SM2MAIN:a37f
// Signature: [X, r01] -> []
void HandleEnemyFBallCol(const byte param_1, const byte param_2) {
  byte bVar2;
  RelativeEnemyPosition(param_1);
  if ((Enemy_Flag[param_2] < 0x80) || (Enemy_ID[Enemy_Flag[param_2] & 0xf] != 0x2d)) {
    const byte bVar1 = Enemy_ID[param_2];
    if (bVar1 == 2) {
      return;
    }
    bVar2 = param_2;
    if (bVar1 != 0x2d) {
      if (bVar1 == 8) {
        return;
      }
      if (bVar1 == 0xc) {
        return;
      }
      if (bVar1 > 0x14) {
        return;
      }
      ShellOrBlockDefeat(param_2);
      return;
    }
  } else {
    bVar2 = Enemy_Flag[param_2] & 0xf;
  }
  BowserHitPoints -= 1;
  if (BowserHitPoints != 0) {
    return;
  }
  EnemyFrenzyBuffer = InitVStf(bVar2);
  SpriteVarData1[bVar2] = EnemyFrenzyBuffer;
  SpriteVarData2[bVar2] = 0xfe;
  Enemy_ID[bVar2] = BowserIdentities[WorldNumber];
  Enemy_State[bVar2] = (WorldNumber < 3) ? 0x23 : 0x20;
  Square2SoundQueue = 0x80;
  EnemySmackScore(9, param_2);
}


// SMB:d795
// SM2MAIN:a3d6
// Signature: [X] -> []
void ShellOrBlockDefeat(const byte param_1) {
  byte enemy_id = Enemy_ID[param_1];

#ifdef SMB2J_MODE
  if (enemy_id == 4) {
    // +1 is possible oversight in original game, didn't clc before adc
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 0x18 + 1 - 0x31;
  }
#endif

  if (enemy_id == 0xd) {
    // +1 is possible oversight in original game, didn't clc before adc
    Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] + 0x18 + 1;
  }

#ifdef SMB1_MODE
  if (enemy_id == 0xd) {
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
  if (Enemy_ID[param_1] == 6) {
    EnemySmackScore(1, param_1);
  } else if (Enemy_ID[param_1] == 5) {
    EnemySmackScore(6, param_1);
  } else {
    EnemySmackScore(2, param_1);
  }
}


// SMB:d7bc
// SM2MAIN:a408
// Signature: [A, X] -> []
void EnemySmackScore(const byte param_1, const byte param_2) {
  SetupFloateyNumber(param_1, param_2);
  Square1SoundQueue = 8;
}


// SMB:d7c4
// SM2MAIN:a410
// Signature: [X] -> [X]
byte PlayerHammerCollision(const byte param_1) {
  bool bVar2;

  const byte smb2j_sprobj = SMB2J_ONLY ? SprObject_OffscrBits[0] : 0;

  if (((FrameCounter & 1) != 0) && ((smb2j_sprobj | TimerControl | Misc_OffscreenBits) == 0)) {
    bVar2 = PlayerCollisionCore(param_1 * 4 + 0x24);
    byte tmp1 = ObjectOffset;
    if (bVar2) {
      if (Misc_Collision_Flag[ObjectOffset] == 0) {
        Misc_Collision_Flag[ObjectOffset] = 1;
        Misc_X_Speed[tmp1] = NEGATE(Misc_X_Speed[tmp1]);
        if (StarInvincibleTimer == 0) {
          InjurePlayer();
          return ObjectOffset;
        }
      }
    } else {
      Misc_Collision_Flag[ObjectOffset] = 0;
    }
    return tmp1;
  } else {
    return param_1;
  }
}


// SMB:d800
// SM2MAIN:a44f
// Signature: [X] -> []
void HandlePowerUpCollision(const byte objoff) {
  // note: the caller always set X to r08

  EraseEnemyObject(objoff);
  if (SMB2J_ONLY && PowerUpType == 4) {
    InjurePlayer();
    return;
  }
  SetupFloateyNumber(6, objoff);
  Square2SoundQueue = 0x20;
  if (PowerUpType >= 2) {
    if (PowerUpType == 3) {
      FloateyNum_Control[objoff] = 0xb;
    } else {
      StarInvincibleTimer = 0x23;
      AreaMusicQueue = 0x40;
    }
  } else if (PlayerStatus == 0) {
    PlayerStatus = 1;
    SetPRout(9, 0);
  } else if (PlayerStatus != 1) {
    Square2SoundQueue = 0x20;
  } else {
    PlayerStatus = 2;
    GetPlayerColors();
    SetPRout(0xc, 0);
  }
}


// SMB:d853
// SM2MAIN:a4ab
// Signature: [X] -> []
void PlayerEnemyCollision(const byte objoff) {
  // Note: X is always equal to r08 at the caller

  byte bVar1;
  byte bVar2;
  byte bStack0000;

  // TODO: remove
  assert_eq_assumption(objoff, ObjectOffset);

  if (FrameCounter & 1) {
    return;
  }
  if (CheckPlayerVertical()) {
    return;
  }
  if (EnemyOffscrBitsMasked[objoff] != 0) {
    return;
  }
  if (GameEngineSubroutine != 8) {
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

  if (Enemy_ID[objoff] == 0x2e) {
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

  if (Enemy_ID[objoff] == 0xc || Enemy_ID[objoff] == 0xd) {
    InjurePlayer();
    return;
  }

#ifdef SMB2J_MODE
  if (Enemy_ID[objoff] == 4) {
    InjurePlayer();
    return;
  }
#endif

  if ((Enemy_ID[objoff] != 0x12) && (Enemy_ID[objoff] != 0x33)) {
    if (Enemy_ID[objoff] > 0x14) {
      InjurePlayer();
      return;
    }
    if (AreaType == 0) {
      InjurePlayer();
      return;
    }

    if (((Enemy_State[objoff] & 0x80) == 0) && ((Enemy_State[objoff] & 6) != 0)) {
      if (Enemy_ID[objoff] == 6) {
        return;
      }
      Square1SoundQueue = 8;
      Enemy_State[objoff] |= 0x80;
      SpriteVarData1[objoff] = KickedShellXSpdData[EnemyFacePlayer(objoff)];
      if (EnemyIntervalTimer[objoff] < 3) {
        bVar1 = KickedShellPtsData[EnemyIntervalTimer[objoff]];
      } else {
        bVar1 = StompChainCounter + 3;
      }
      SetupFloateyNumber(bVar1, objoff);
      return;
    }
  }

  if (StompTimer == 0) {
    if ((Enemy_ID[objoff] < 7) || (Enemy_Y_Position[objoff] <= (byte)(SprObject_Y_Position[0] + 0xC))) {

#ifdef SMB1_MODE
      const bool cond2 = (PlayerSpriteVarData2[0] == 0) || (PlayerSpriteVarData2[0] >= 0x80);
#endif
#ifdef SMB2J_MODE
      const bool cond2 = (PlayerSpriteVarData2[0] == 0) || (PlayerSpriteVarData2[0] > 0x80);
#endif

      if (cond2) {
        if (InjuryTimer != 0) {
          return;
        }

        if (SprObject_Rel_XPos[0] < Enemy_Rel_XPos) {
          if (Enemy_MovingDir[objoff] == 1) {
            LInj(objoff);
            return;
          }
          InjurePlayer();
          return;
        }
        ChkEnemyFaceRight(objoff);
        return;
      }
    }
  }

  if (Enemy_ID[objoff] == 0x12) {
    InjurePlayer();
    return;
  }
  Square1SoundQueue = 4;

  bool cond = true;

  switch (Enemy_ID[objoff]) {
    case 5:
      bVar2 = StompedEnemyPtsData[1];
      cond = false;
      break;

    case 7:
      bVar2 = StompedEnemyPtsData[3];
      cond = false;
      break;

    case 8:
    case 12:
    case 20:
    case 51:
      bVar2 = StompedEnemyPtsData[0];
      cond = false;
      break;

    case 17:
      bVar2 = StompedEnemyPtsData[2];
      cond = false;
      break;
  }

  if (cond) {
    if (Enemy_ID[objoff] < 9) {
      Enemy_State[objoff] = 4;
      StompChainCounter += 1;
      SetupFloateyNumber(StompChainCounter + StompTimer, objoff);
      StompTimer += 1;
      EnemyIntervalTimer[objoff] = RevivalRateData[PrimaryHardMode];
#ifdef SMB1_MODE
      PlayerSpriteVarData2[0] = 0xfc;
#endif
#ifdef SMB2J_MODE
      SetBounce(objoff);
#endif
    } else {
#ifdef SMB2J_MODE
      Enemy_ID[objoff] = SetBounce(objoff);
#endif
      Enemy_ID[objoff] &= 1;
      Enemy_State[objoff] = 0;
      SetupFloateyNumber(3, objoff);
      InitVStf(objoff);
      SpriteVarData1[objoff] = DemotedKoopaXSpdData[EnemyFacePlayer(objoff)];
#ifdef SMB1_MODE
      PlayerSpriteVarData2[0] = 0xfc;
#endif
    }
  } else {
    SetupFloateyNumber(bVar2, objoff);
    bStack0000 = Enemy_MovingDir[objoff];
#ifdef SMB1_MODE
    // Inlined: SetStun
    Enemy_State[objoff] = (Enemy_State[objoff] & 0xf0) | 2;
#endif
#ifdef SMB2J_MODE
    // Inlined: NoDemote
    if ((bStack0000 != 0x2e) && (bStack0000 != 6)) {
      Enemy_State[objoff] = 2;
    }
#endif
    SetStun2(objoff);
    Enemy_MovingDir[objoff] = bStack0000;
    Enemy_State[objoff] = 0x20;
    SpriteVarData1[objoff] = InitVStf(objoff);
#ifdef SMB1_MODE
    PlayerSpriteVarData2[0] = 0xfd;
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
      ForceInjury(0);
    }
  }
}


// SMB:d931
// SM2MAIN:a58f
// Signature: [A] -> []
void ForceInjury(const byte param_1) {
  byte bVar1;

  if (PlayerStatus == 0) {
    EventMusicQueue = 1;
    PlayerSpriteVarData2[0] = 0xfc;
    bVar1 = 0xb;
    PlayerSpriteVarData1[0] = PlayerStatus;
  } else {
    InjuryTimer = 8;
    Square1SoundQueue = 0x10;
    PlayerStatus = param_1;
    GetPlayerColors();
    bVar1 = 10;
  }
  SetPRout(bVar1, 1);
}


// SMB:d948
// SM2MAIN:a5a6
// Signature: [A, Y] -> []
void SetPRout(const byte param_1, const byte param_2) {
  GameEngineSubroutine = param_1;
  Player_State = param_2;
  TimerControl = 0xff;
  ScrollAmount = 0;
}


// SMB:d9f6
// SM2MAIN:a65f
// Signature: [X] -> []
void ChkEnemyFaceRight(const byte param_1) {
  if (Enemy_MovingDir[param_1] != 1) {
    LInj(param_1);
  } else {
    InjurePlayer();
  }
}


// SMB:d9ff
// SM2MAIN:a668
// Signature: [X] -> []
void LInj(const byte param_1) {
  EnemyTurnAround(param_1);
  InjurePlayer();
}


// SMB:da05
// SM2MAIN:a66e
// Signature: [X] -> [Y]
byte EnemyFacePlayer(const byte param_1) {
  byte bVar1 = 1;
  const struct_ncr00 sVar2 = PlayerEnemyDiff(param_1);
  if (sVar2.n) {
    bVar1 += 1;
  }
  Enemy_MovingDir[param_1] = bVar1;
  return bVar1 - 1;
}


// SMB:da11
// SM2MAIN:a67a
// Signature: [A, X] -> []
void SetupFloateyNumber(const byte param_1, const byte param_2) {
  FloateyNum_Control[param_2] = param_1;
  FloateyNum_Timer[param_2] = 0x30;
  FloateyNum_Y_Pos[param_2] = Enemy_Y_Position[param_2];
  FloateyNum_X_Pos[param_2] = Enemy_Rel_XPos;
}


static inline bool EnemiesCollision_condition(const u8 enemyoff) {
  const u8 enemy_id = Enemy_ID[enemyoff];

  if (enemy_id >= 0x15) { return true; }
  if (enemy_id == 0x11) { return true; }
  if (enemy_id == 0xd) { return true; }

#ifdef SMB2J_MODE
  if (enemy_id == 4) { return true; }
#endif

  if (EnemyOffscrBitsMasked[enemyoff] != 0) { return true; }

  return false;
}

// SMB:da33
// SM2MAIN:a69c
// Signature: [X] -> [X]
byte EnemiesCollision(const byte param_1) {
  if ((FrameCounter & 1) == 0) {
    return param_1;
  }

  if (AreaType == 0) {
    return param_1;
  }

  assert_eq_assumption(param_1 < 0x80, true);

  if (EnemiesCollision_condition(param_1)) {
    return ObjectOffset;
  }

  // Inlined: GetEnemyBoundBoxOfs
  const u8 bStack0000 = ObjectOffset * 4 + 4;

  for (int i = param_1 - 1; i >= 0; i--) {
    if (Enemy_Flag[i] == 0) {
      continue;
    }

    if (EnemiesCollision_condition(i)) {
      continue;
    }

    const bool bVar2 = SprObjectCollisionCore(i * 4 + 4, bStack0000);

    const u8 objoff = ObjectOffset;

    // objectoffset must be between 0 and 6 inclusive

    assert_eq_assumption(objoff >= 0 && objoff <= 6, true);

    const u8 bitsmask = 1 << (7 - objoff);

    if (!bVar2) {
      Enemy_CollisionBits[i] &= ~bitsmask;
    } else if ((Enemy_State[objoff] & 0x80) != 0 || (Enemy_State[i] & 0x80) != 0) {
      ProcEnemyCollisions(objoff, i, i);
    } else if ((Enemy_CollisionBits[i] & bitsmask) == 0) {
      Enemy_CollisionBits[i] |= bitsmask;
      ProcEnemyCollisions(objoff, i, i);
    }
  }

  return ObjectOffset;
}


// SMB:dab4
// SM2MAIN:a725
// Signature: [X, Y, r01] -> []
void ProcEnemyCollisions(const byte param_1, const byte param_2, const byte param_3) {
  if (((Enemy_State[param_2] | Enemy_State[param_1]) & 0x20) == 0) {
    if (Enemy_State[param_1] < 6) {
      if (Enemy_State[param_2] < 6) {
        EnemyTurnAround(param_2);
        EnemyTurnAround(ObjectOffset);
        return;
      }
      if (Enemy_ID[param_2] != 5) {
        ShellOrBlockDefeat(param_1);
        SetupFloateyNumber(ShellChainCounter[param_3] + 4, ObjectOffset);
        ShellChainCounter[param_3] = ShellChainCounter[param_3] + 1;
        return;
      }
    } else if (Enemy_ID[param_1] != 5) {
      if ((char)Enemy_State[param_2] < 0) {
        SetupFloateyNumber(6, param_1);
        ShellOrBlockDefeat(param_1);
        ShellOrBlockDefeat(param_3);
      } else {
        ShellOrBlockDefeat(param_2);
      }
      SetupFloateyNumber(ShellChainCounter[ObjectOffset] + 4, param_3);
      ShellChainCounter[ObjectOffset] = ShellChainCounter[ObjectOffset] + 1;
    }
  }
}


// SMB:db1c
// SM2MAIN:a78d
// Signature: [X] -> []
void EnemyTurnAround(const byte param_1) {
  const byte bVar1 = Enemy_ID[param_1];
  if (bVar1 != 0xd && ssw(true, bVar1 != 4) && bVar1 != 0x11 && bVar1 != 5) {
    if (bVar1 == 0x12) {
      RXSpd(param_1);
    }
    if (bVar1 == 0xe) {
      RXSpd(param_1);
    }
    if (bVar1 < 7) {
      RXSpd(param_1);
    }
  }
}


// SMB:db36
// SM2MAIN:a7ab
// Signature: [X] -> []
void RXSpd(const byte param_1) {
  SpriteVarData1[param_1] = NEGATE(SpriteVarData1[param_1]);
  Enemy_MovingDir[param_1] = Enemy_MovingDir[param_1] ^ 3;
}


// SMB:db45
// SM2MAIN:a7ba
// Signature: [X] -> [X]
byte LargePlatformCollision(const byte param_1) {
  byte bVar1;

  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0xff;
  if ((TimerControl == 0) && (Enemy_State[param_1] < 0x80)) {
    if (Enemy_ID[param_1] != 0x24) {
      return ChkForPlayerC_LargeP(param_1);
    }
    bVar1 = ChkForPlayerC_LargeP(Enemy_State[param_1]);
    return ChkForPlayerC_LargeP(bVar1);
  }
  return ObjectOffset;
}


// SMB:db5f
// SM2MAIN:a7d4
// Signature: [X] -> [X]
byte ChkForPlayerC_LargeP(const byte param_1) {
  if (CheckPlayerVertical()) {
    return ObjectOffset;
  }

  // Inlined: GetEnemyBoundBoxOfs
  const byte bVar2 = (param_1 + 1) * 4;

  const byte bVar1 = Enemy_Y_Position[param_1];
  const bool bVar3 = PlayerCollisionCore(bVar2);
  if (bVar3) {
    ProcLPlatCollisions(param_1, bVar2, bVar1);
  }

  return ObjectOffset;
}


// SMB:db7b
// SM2MAIN:a7f0
// Signature: [X] -> [X]
byte SmallPlatformCollision(const byte param_1) {
  if (TimerControl != 0) {
    return ObjectOffset;
  }

  HammerThrowingTimer_Or_PlatformCollisionFlag[param_1] = 0;

  if (CheckPlayerVertical()) {
    return ObjectOffset;
  }

  for (int i = 2; i > 0; i--) {
    // Inlined: GetEnemyBoundBoxOfs
    // NES note: (Enemy_OffscreenBits & 0x2) came from GetEnemyBoundBoxOfs. We're inlining it here.
    if ((Enemy_OffscreenBits & 0x2) != 0) {
      return ObjectOffset;
    }
    const byte bVar1 = ObjectOffset + 1;
    if ((BBOX_TOPLEFT_Y(bVar1) >= 0x20)) {
      const bool bVar3 = PlayerCollisionCore(bVar1 * 4);
      if (bVar3) {
        ProcLPlatCollisions(ObjectOffset, bVar1 * 4, i);
        return ObjectOffset;
      }
    }
    BBOX_TOPLEFT_Y(bVar1) += 0x80;
    BBOX_BOTRIGHT_Y(bVar1) += 0x80;
  }

  return ObjectOffset;
}


// SMB:dbbc
// SM2MAIN:a831
// Signature: [X, Y, r00] -> []
void ProcLPlatCollisions(const byte param_1, const byte param_2, const byte param_3) {
  // This is always the case in the original
  // TODO: check if any other values would make sense and if param_2 should be eliminated
  assert_eq_assumption(param_2, (param_1+1)*4);
  const byte param_2_div4 = param_2 / 4;

  if (((byte)(BBOX_BOTRIGHT_Y(param_2_div4) - BBOX_TOPLEFT_Y(0)) < 4) && (PlayerSpriteVarData2[0] >= 0x80)) {
    PlayerSpriteVarData2[0] = 1;
  }
  if (((byte)(BBOX_BOTRIGHT_Y(0) - BBOX_TOPLEFT_Y(param_2_div4)) < 6) && (PlayerSpriteVarData2[0] < 0x80)) {
    byte tmp3 = param_3;
    if ((Enemy_ID[param_1] != 0x2b) && (Enemy_ID[param_1] != 0x2c)) {
      tmp3 = param_1;
    }
    HammerThrowingTimer_Or_PlatformCollisionFlag[ObjectOffset] = tmp3;
    Player_State = 0;
    return;
  }

  if ((byte)(BBOX_BOTRIGHT_X(0) - BBOX_TOPLEFT_X(param_2_div4)) <= 7) {
    ImpedePlayerMove(1);
  } else {
    if ((byte)(BBOX_BOTRIGHT_X(param_2_div4) - BBOX_TOPLEFT_X(0) - 1) <= 8) {
      ImpedePlayerMove(2);
    }
  }
}


// SMB:dc19
// SM2MAIN:a88e
// Signature: [A, X] -> []
void PositionPlayerOnS_Plat(const byte param_1, const byte param_2) {
  const byte bVar1 = Enemy_Y_Position[param_2] + PlayerPosSPlatData[param_1 - 1];
  if ((GameEngineSubroutine != 0xb) && (Enemy_Y_HighPos[param_2] == 1)) {
    SprObject_Y_Position[0] = bVar1 - 0x20;
    SprObject_Y_HighPos[0] = 1 - (bVar1 < 0x20);
    PlayerSpriteVarData2[0] = 0;
    SprObject_Y_MoveForce[0] = 0;
  }
}


// SMB:dc21
// SM2MAIN:a896
// Signature: [X] -> []
void PositionPlayerOnVPlat(const byte param_1) {
  if ((GameEngineSubroutine != 0xb) && (Enemy_Y_HighPos[param_1] == 1)) {
    SprObject_Y_Position[0] = Enemy_Y_Position[param_1] - 0x20;
    SprObject_Y_HighPos[0] = 1 - (Enemy_Y_Position[param_1] < 0x20);
    PlayerSpriteVarData2[0] = 0;
    SprObject_Y_MoveForce[0] = 0;
  }
}


// SMB:dc41
// SM2MAIN:a8b6
// Signature: [] -> [C]
bool CheckPlayerVertical(void) {
#ifdef SMB1_MODE
  return SprObject_OffscrBits[0] >= 0xf0 || (SprObject_Y_HighPos[0] == 1 && SprObject_Y_Position[0] >= 0xd0);
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

  const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);
  Block_Buffers[blockoff] = 0;

  RemoveCoin_Axe(mt_x, mt_y);

  CoinTallyFor1Ups += 1;
  GiveOneCoin();
}


// SMB:de0e
// SM2MAIN:aa7c
static void HandleAxeMetatile(const u16 mt_x, const u16 mt_y) {
  // Note: Old signature was [r02, r06, r07] -> []
  // Reworked to use metatile coordinates instead of pointer

  OperMode_Task = 0;
  OperMode = 2;
#ifdef SMB2J_MODE
  LoadMarioPhysics();
#endif
  PlayerSpriteVarData1[0] = 0x18;

  const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);
  Block_Buffers[blockoff] = 0;

  RemoveCoin_Axe(mt_x, mt_y);
}

// SMB:dc64
// SM2MAIN:a8d2
// Signature: [] -> []
void PlayerBGCollision(void) {
  byte bVar2;
  byte bVar5;
  byte bVar7;
  bool bVar8;
  struct blockbuffer_colli_result sVar11;

  if (DisableCollisionDet != 0) {
    return;
  }
  if (GameEngineSubroutine == 0xb) {
    return;
  }
  if (GameEngineSubroutine < 4) {
    return;
  }

  if (SwimmingFlag == 0) {
    if ((Player_State == 0) || (Player_State == 3)) {
      Player_State = 2;
    }
  } else {
    Player_State = 1;
  }

  if (SprObject_Y_HighPos[0] != 1) {
    return;
  }

  Player_CollisionBits = 0xff;

  if (SprObject_Y_Position[0] > 0xce) {
    return;
  }

  byte tmp1;

  if ((CrouchingFlag == 0) && (PlayerSize == 0)) {
    if (SwimmingFlag == 0) {
      tmp1 = BlockBufferAdderData[0];
    } else {
      tmp1 = BlockBufferAdderData[1];
    }
  } else {
    tmp1 = BlockBufferAdderData[2];
  }


  const byte bVar6 = PlayerSize + ((CrouchingFlag != 0) ? 1 : 0);

  if (PlayerBGUpperExtent[bVar6] <= SprObject_Y_Position[0]) {
    const struct blockbuffer_colli_result sVar9 = BlockBufferColli_Head(tmp1);
    const byte bVar1 = sVar9.r04;
    if (!sVar9.z) {
      if (CheckForCoinMTiles(sVar9.a)) {
        HandleCoinMetatile(sVar9.mt_x, sVar9.mt_y);
        return;
      }
      bVar7 = sVar9.a;
      if ((PlayerSpriteVarData2[0] >= 0x80) && (bVar1 >= 4)) {
        bVar8 = CheckForSolidMTiles(bVar7);

        bool myspd = true;

        if (bVar8) {
          if (bVar7 != ssw(0x26, 0x23)) {
            Square1SoundQueue = 2;
          }
        } else if ((AreaType != 0) && (BlockBounceTimer == 0)) {
          const u16 mt_x = sVar9.mt_x;
          const u16 mt_y = sVar9.mt_y;
          PlayerHeadCollision(bVar7, mt_x, mt_y);
          myspd = false;
        }

        if (myspd) {
          // MYSpd
          PlayerSpriteVarData2[0] = 1;
        }
      }
    }
  }

  // DoFootCheck

  if (SprObject_Y_Position[0] < 0xcf) {
    sVar11 = BlockBufferColli_Feet(tmp1);
    if (CheckForCoinMTiles(sVar11.a)) {
      HandleCoinMetatile(sVar11.mt_x, sVar11.mt_y);
      return;
    }
    const byte bVar1 = sVar11.a;
    sVar11 = BlockBufferColli_Feet(tmp1 + 1);
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
      if ((!bVar8) && (PlayerSpriteVarData2[0] < 0x80)) {
        if (bVar7 == ssw(0xc5, 0xc6)) {
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
            SprObject_Y_Position[0] &= 0xf0;
            HandlePipeEntry(bVar2, bVar1);
            PlayerSpriteVarData2[0] = 0;
            SprObject_Y_MoveForce[0] = 0;
            StompChainCounter = 0;
          }
          Player_State = 0;
        }
      }
    }
  }

  // DoPlayerSideCheck

  u16 mt_x = 0;
  u16 mt_y = 0;

  int i;
  for (i = 2; i >= 1; i--) {
    tmp1 += i;
    tmp1 += 1;
    // +3, +2

    if (SprObject_Y_Position[0] >= 0x20) {
      if (SprObject_Y_Position[0] >= 0xe4) {
        return;
      }
      const struct blockbuffer_colli_result sVar9 = BlockBufferColli_Side(tmp1);
      mt_x = sVar9.mt_x;
      mt_y = sVar9.mt_y;
      bVar2 = sVar9.r04;
      bVar5 = sVar9.a;
      const bool cond = (sVar9.z) || (bVar5 == ssw(0x1c, 0x19)) || (bVar5 == ssw(0x6b, 0x6d)) || CheckForClimbMTiles(bVar5);
      if (!cond) {
        break;
      }
    }

    // BHalf

    if (SprObject_Y_Position[0] < 8) {
      return;
    }
    if (SprObject_Y_Position[0] >= 0xd0) {
      return;
    }
    const struct blockbuffer_colli_result sVar9 = BlockBufferColli_Side(tmp1 + 1);
    mt_x = sVar9.mt_x;
    mt_y = sVar9.mt_y;
    bVar2 = sVar9.r04;
    bVar5 = sVar9.a;
    const bool cond = sVar9.z;
    if (!cond) {
      break;
    }
  }

  if (i == 0) {
    return;
  }

  const byte bVar1 = i;

  // bVar1 = 2 or bVar1 = 1

  // CheckSideMTiles

  if (!ChkInvisibleMTiles(bVar5)) {
    if (CheckForClimbMTiles(bVar5)) {
      HandleClimbing(bVar5, bVar2, mt_x);
      return;
    }

    if (CheckForCoinMTiles(bVar5)) {
      HandleCoinMetatile(mt_x, mt_y);
      return;
    }
    bVar7 = bVar5;

    if (ChkJumpspringMetatiles(bVar7)) {
      if (JumpspringAnimCtrl != 0) {
        return;
      }
    } else if (((Player_State == 0) && (PlayerFacingDir == 1)) && ((bVar7 == ssw(0x6c, 0x6e) || (bVar7 == ssw(0x1f, 0x1c))))) {
      if (Player_SprAttrib == 0) {
        Square1SoundQueue = 0x10;
      }
      Player_SprAttrib |= 0x20;
      if ((SprObject_X_Position[0] & 0xf) != 0) {
        ChangeAreaTimer = AreaChangeTimerData[ScreenEdgeOrLeft_PageLoc[0] != 0];
      }

      // 7 != 8, so this seems redundant. But it's in the assembly.
      // We'll keep it in in case it's semantically meaningful in later refactor efforts.
      if (GameEngineSubroutine == 7) {
        return;
      }
      if (GameEngineSubroutine != 8) {
        return;
      }
      GameEngineSubroutine = 2;
      return;
    }

    // bVar1 = 2 or bVar1 = 1
    ImpedePlayerMove(bVar1);
  }
}


// SMB:de2e
// SM2MAIN:aa9f
void HandleClimbing(const byte param_1, const byte param_2, const u16 mt_x) {
  // Note: Old signature was [A, r04, r06] -> []
  // Reworked to use metatile coordinates instead of pointer

  if ((param_2 < 6) || (param_2 >= 10)) {
    return;
  }

  if ((param_1 == ssw(0x24, 0x21)) || (param_1 == ssw(0x25, 0x22))) {
    if (GameEngineSubroutine != 5) {
      PlayerFacingDir = 1;
      ScrollLock += 1;
      if (GameEngineSubroutine != 4) {
        KillEnemies(0x33);
        EventMusicQueue = 0x80;
        FlagpoleSoundQueue = 0x40;
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
      GameEngineSubroutine = 4;
    }
  } else if ((param_1 == ssw(0x26, 0x23)) && (Player_Y_Position < 0x20)) {
    GameEngineSubroutine = 1;
  }
  Player_State = 3;
  PlayerSpriteVarData1[0] = 0;
  Player_X_MoveForce = 0;
  if ((byte)(Player_X_Position - ScreenLeft_X_Pos) < 0x10) {
    PlayerFacingDir = 2;
  }

  // NES note: The game assumes PlayerFacingDir is >= 1, but that's not always the case.
  // It can = 0, and when it is, it references a 6502 instruction operand ($8A in SMB1, $69 in SMB2J).
  // It occurs in level 2-1 in this SMB1 TAS: https://tasvideos.org/6913S
  //
  // It sometimes = 3 as well.
  // It occurs in level 8-2 in this SMB2J TAS: https://tasvideos.org/5394S

  Player_X_Position = (u8)(mt_x * 16) + ClimbXPosAdder_Minus1[PlayerFacingDir];

  if ((mt_x % 32) == 0) {
    // mt_x is the first column of an even page

    Player_PageLoc = ScreenRight_PageLoc + ClimbPLocAdder_Minus1[PlayerFacingDir];
  }
}


// SMB:debd
// SM2MAIN:ab40
// Signature: [A] -> [Z]
bool ChkInvisibleMTiles(const byte mtile) {
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
void ChkForLandJumpSpring(const byte param_1) {
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
bool ChkJumpspringMetatiles(const byte param_1) {
  bool bVar1;

  if (param_1 == ssw(0x67, 0x68)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
    if (param_1 == ssw(0x68, 0x69)) {
      bVar1 = true;
    }
  }
  return bVar1;
}


// SMB:dee8
// SM2MAIN:ab76
// Signature: [r00, r01] -> []
void HandlePipeEntry(const byte param_1, const byte param_2) {
  byte bVar1;

  if ((((Up_Down_Buttons & BUTTON_D) != 0) && (param_1 == 0x11)) && (param_2 == 0x10)) {
    ChangeAreaTimer = 0x30;
    GameEngineSubroutine = 3;
    Square1SoundQueue = 0x10;
    Player_SprAttrib = 0x20;
    if (WarpZoneControl != 0) {
      if (SMB1_ONLY) {
        if (SprObject_X_Position[0] < 0x60) {
          bVar1 = WarpZoneNumbers[(WarpZoneControl & 3) * 4];
        } else if (SprObject_X_Position[0] < 0xa0) {
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
      EventMusicQueue = 0x80;
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
void ImpedePlayerMove(const byte param_1) {
  byte bVar1;
  byte bVar2;
  bool nxspd;

  if (param_1 == 1) {
    nxspd = PlayerSpriteVarData1[0] < 0x80;
    bVar2 = 1;
    bVar1 = -1;
  } else {
    nxspd = (byte)(PlayerSpriteVarData1[0] - 1) >= 0x80;
    bVar2 = 2;
    bVar1 = 1;
  }

  if (nxspd) {
    // NXSpd

    SideCollisionTimer = 0x10;
    PlayerSpriteVarData1[0] = 0;

    ADD_SIGNED_16_8(SprObject_PageLoc[0], SprObject_X_Position[0],
                    bVar1);
  }

  // ExIPM
  Player_CollisionBits = (bVar2 ^ 0xff) & Player_CollisionBits;
}


// SMB:df8f
// SM2MAIN:ac18
// Signature: [A] -> [C]
bool CheckForSolidMTiles(const byte param_1) {
  const byte bVar1 = GetMTileAttrib(param_1);
  return SolidMTileUpperExt[bVar1] <= param_1;
}


// SMB:df9a
// SM2MAIN:ac23
// Signature: [A] -> [C]
bool CheckForClimbMTiles(const byte param_1) {
  const byte bVar1 = GetMTileAttrib(param_1);
  return ClimbMTileUpperExt[bVar1] <= param_1;
}


// SMB:dfa1
// SM2MAIN:ac2a
// Signature: [A] -> [C]
bool CheckForCoinMTiles(const byte param_1) {
  const byte regular_coin_mtile = ssw(0xc2, 0xc3);
  const byte underwater_coin_mtile = ssw(0xc3, 0xc4);

  if (param_1 == regular_coin_mtile) {
    Square2SoundQueue = 1;
    return true;
  }

  if (param_1 == underwater_coin_mtile) {
    Square2SoundQueue = 1;
    return true;
  }

  return false;
}


// SMB:dfb0
// SM2MAIN:ac39
// Signature: [A] -> [X]
byte GetMTileAttrib(const byte x) {
  return x >> 6;
}


// SMB:e1ae
// SM2MAIN:ae44
// Signature: [X] -> [A, Z, r04]
struct_azr04 ChkUnderEnemy(const byte param_1) {
  // Inlined: BlockBufferChk_Enemy

  struct_azr04 sVar1;

  const struct blockbuffer_colli_result sVar2 = BlockBufferCollision(0, param_1 + 1, 0x15);
  sVar1.a = sVar2.a;
  sVar1.z = sVar2.a == 0;
  sVar1.r04 = sVar2.r04;
  return sVar1;
}


// SMB:e1ae
// Signature: [X] -> [A, Z, r02, r04, r06, r07]
static inline struct_azr04 ChkUnderEnemy_Ext(const byte param_1, u16 *blockoff) {
  // Inlined: BlockBufferChk_Enemy

  struct_azr04 sVar1;

  const struct blockbuffer_colli_result sVar2 = BlockBufferCollision(0, param_1 + 1, 0x15);

  sVar1.a = sVar2.a;
  sVar1.z = sVar2.a == 0;
  sVar1.r04 = sVar2.r04;

  *blockoff = MTX_MTY_TO_BLOCKOFF(sVar2.mt_x, sVar2.mt_y);

  return sVar1;
}

// SMB:dfc1
// SM2MAIN:ac4a
// Signature: [X] -> [X]
byte EnemyToBGCollisionDet(const byte param_1) {
  struct_ncr00 sVar5;

  if ((Enemy_State[param_1] & 0x20) != 0) {
    return param_1;
  }

  const bool bVarDD = SubtEnemyYPos(param_1);
  if (!bVarDD) {
    return param_1;
  }

  byte bVarAA = Enemy_ID[param_1];
  if ((bVarAA == 0x12) && (Enemy_Y_Position[param_1] < 0x25)) {
    return param_1;
  }

  if (bVarAA == 0xe) {
    return EnemyJump(param_1);
  }
  if (bVarAA == 5) {
    return HammerBroBGColl(param_1);
  }
  if ((bVarAA != 0x12) && (bVarAA != 0x2e) && (ssw(false, bVarAA == 4) || (bVarAA > 6))) {
    return param_1;
  }

#ifdef SMB1_MODE
  u16 chkunderenemy_blockoff = 0;
  const struct_azr04 sVar6 = ChkUnderEnemy_Ext(param_1, &chkunderenemy_blockoff);
#endif
#ifdef SMB2J_MODE
  const struct_azr04 sVar6 = ChkUnderEnemy(param_1);
#endif

  const u8 objoff = ObjectOffset;

  if (sVar6.z || ChkForNonSolids(sVar6.a)) {
    return ChkForRedKoopa(objoff);
  }

  byte bVarCC = objoff;

  if (sVar6.a == ssw(0x23, 0x20)) {
#ifdef SMB1_MODE
    Block_Buffers[chkunderenemy_blockoff] = 0;
#endif

    byte enemy_id = Enemy_ID[objoff];
    if (enemy_id < 0x15) {
      if (enemy_id == 6) {
        KillEnemyAboveBlock(objoff);
      }
      SetupFloateyNumber(1, objoff);

#ifdef SMB1_MODE
      // this reimplements a bug in SMB1
      // NES note: The "A" register is overwritten by the call to SetupFloateyNumber.
      // The value happens to be Enemy_Rel_XPos
      enemy_id = Enemy_Rel_XPos;
#endif
    }

#ifdef SMB1_MODE
    ChkToStunEnemies(enemy_id, objoff);
#endif
#ifdef SMB2J_MODE
    ChkToStunEnemies(objoff);
#endif

    return objoff;
  }

  if ((byte)(sVar6.r04 - 8) > 4) {
    return ChkForRedKoopa(objoff);
  }
  if ((Enemy_State[objoff] & 0x40) == 0) {
    if (((char)Enemy_State[objoff] < 0)) {
      return DoEnemySideCheck(objoff);
    }
    else {
      bVarAA = Enemy_State[objoff];
      if (bVarAA == 0) {
        return DoEnemySideCheck(objoff);
      }
    }
    if (bVarAA != 5) {
      if (bVarAA > 2) {
        return objoff;
      }
      if (Enemy_State[objoff] == 2) {
        EnemyIntervalTimer[objoff] = (Enemy_ID[objoff] == 0x12) ? 0 : 0x10;
        Enemy_State[objoff] = 3;
        EnemyLanding(objoff);
        return objoff;
      }
    }
    if (Enemy_ID[objoff] != 6) {
      if (Enemy_ID[objoff] == 0x12) {
        Enemy_MovingDir[objoff] = 1;
        SpriteVarData1[objoff] = 8;
        if ((FrameCounter & 7) == 0) {
          goto LandEnemyInitState;
        }
      }
      bVarAA = 1;
      sVar5 = PlayerEnemyDiff(objoff);
      if (sVar5.n) {
        bVarAA += 1;
      }
      if (bVarAA == Enemy_MovingDir[objoff]) {
        bVarCC = ChkForBump_HammerBroJ(objoff);
      }
    }
  }
LandEnemyInitState:
  EnemyLanding(bVarCC);
  if ((Enemy_State[bVarCC] & 0x80) != 0) {
    Enemy_State[bVarCC] = Enemy_State[bVarCC] & 0xbf;
    return bVarCC;
  }
  Enemy_State[bVarCC] = 0;
  return bVarCC;
}


// SMB:e037
// SM2MAIN:accd
// Signature: [X] -> []
void SetStun2(const byte param_1) {
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;
  Enemy_Y_Position[param_1] = Enemy_Y_Position[param_1] - 1;

  if ((Enemy_ID[param_1] == 7) || (AreaType == 0)) {
    SpriteVarData2[param_1] = 0xff;
  } else {
    SpriteVarData2[param_1] = 0xfd;
  }

  const struct_ncr00 sVar2 = PlayerEnemyDiff(param_1);

  if ((Enemy_ID[param_1] != 0x33) && (Enemy_ID[param_1] != 8)) {
    Enemy_MovingDir[param_1] = sVar2.n ? 2 : 1;
  }
  SpriteVarData1[param_1] = EnemyBGCXSpdData[sVar2.n ? 1 : 0];
}


// SMB:e0e2
// SM2MAIN:ad78
// Signature: [X] -> [X]
byte ChkForRedKoopa(const byte param_1) {
  byte bVar1;

  if ((Enemy_ID[param_1] == 3) && (Enemy_State[param_1] == 0)) {
    return ChkForBump_HammerBroJ(param_1);
  }
  if ((char)Enemy_State[param_1] < 0) {
    bVar1 = Enemy_State[param_1] | 0x40;
  } else {
    bVar1 = EnemyBGCStateData[Enemy_State[param_1]];
  }
  Enemy_State[param_1] = bVar1;
  return DoEnemySideCheck(param_1);
}


// SMB:e0fe
// SM2MAIN:ad94
// Signature: [X] -> [X]
byte DoEnemySideCheck(const byte param_1) {
  if (Enemy_Y_Position[param_1] < 0x20) {
    return param_1;
  }

  byte tmp1 = param_1;
  for (int i = 0x16; i < 0x18; i++) {
    const byte tmp2 = 0x18 - i;
    if (tmp2 == Enemy_MovingDir[tmp1]) {
      const struct_axzr04 sVar3 = BlockBufferChk_Enemy(1, tmp1, i);
      tmp1 = sVar3.x;
      if (!sVar3.z) {
        if (!ChkForNonSolids(sVar3.a)) {
          return ChkForBump_HammerBroJ(tmp1);
        }
      }
    }
  }

  return tmp1;
}


// SMB:e124
// SM2MAIN:adba
// Signature: [X] -> [X]
byte ChkForBump_HammerBroJ(const byte param_1) {
  if ((param_1 != 5) && ((char)Enemy_State[param_1] < 0)) {
    Square1SoundQueue = 2;
  }
  if (Enemy_ID[param_1] == 5) {
    return SetHJ(param_1, 0xfa, 0);
  }
  RXSpd(param_1);
  return param_1;
}


// SMB:e143
// SM2MAIN:add9
// Signature: [X] -> [N, C, r00]
struct_ncr00 PlayerEnemyDiff(const byte param_1) {
  const u16 player_pos = (SprObject_PageLoc[0] << 8) | (SprObject_X_Position[0]);
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
void EnemyLanding(const byte param_1) {
  InitVStf(param_1);
  Enemy_Y_Position[param_1] = (Enemy_Y_Position[param_1] & 0xf0) | 8;
}


// SMB:e15b
// SM2MAIN:adf1
// Signature: [X] -> [C]
bool SubtEnemyYPos(const byte param_1) { return 0x43 < (byte)(Enemy_Y_Position[param_1] + 0x3e); }


// SMB:e163
// SM2MAIN:adf9
// Signature: [X] -> [X]
byte EnemyJump(const byte param_1) {
  bool bVar2 = SubtEnemyYPos(param_1);
  if ((bVar2) && (2 < (byte)(SpriteVarData2[param_1] + 2))) {
    const struct_azr04 sVar3 = ChkUnderEnemy(param_1);
    const byte objoff = ObjectOffset;
    if (!sVar3.z) {
      bVar2 = ChkForNonSolids(sVar3.a);
      if (!bVar2) {
        EnemyLanding(objoff);
        SpriteVarData2[objoff] = 0xfd;
      }
    }
    return DoEnemySideCheck(objoff);
  } else {
    return DoEnemySideCheck(param_1);
  }
}


// SMB:e185
// SM2MAIN:ae1b
// Signature: [X] -> [X]
byte HammerBroBGColl(const byte param_1) {
  const struct_azr04 sVar2 = ChkUnderEnemy(param_1);
  const byte objoff = ObjectOffset;
  if (!sVar2.z) {
    if (sVar2.a == ssw(0x23, 0x20)) {
      KillEnemyAboveBlock(objoff);
      return objoff;
    }
    if (EnemyFrameTimer[objoff] == 0) {
      Enemy_State[objoff] = Enemy_State[objoff] & 0x88;
      EnemyLanding(objoff);
      return DoEnemySideCheck(objoff);
    }
  }
  Enemy_State[objoff] = Enemy_State[objoff] | 1;
  return objoff;
}


// SMB:e18e
// SM2MAIN:ae24
// Signature: [X] -> []
void KillEnemyAboveBlock(const byte param_1) {
  ShellOrBlockDefeat(param_1);
  SpriteVarData2[param_1] = 0xfc;
}


// SMB:e1b5
// SM2MAIN:ae4b
// Signature: [A] -> [Z]
bool ChkForNonSolids(const byte v) {
  if (SMB1_ONLY) {
    return v == 0x26 || v == 0x5f || v == 0x60 || v == 0xc2 || v == 0xc3;
  } else if (SMB2J_ONLY) {
    return v == 0x23 || v == 0x5e || v == 0x5f || v == 0x60 || v == 0x61 || v == 0xc3 || v == 0xc4;
  }
  return false;
}


// SMB:e1c8
// SM2MAIN:ae66
// Signature: [X] -> [X]
byte FireballBGCollision(const byte param_1) {
  bool bVar1;
  struct_axz sVar2;

  if (Fireball_Y_Position[param_1] >= 0x18) {
    sVar2 = BlockBufferChk_FBall(param_1);
    const byte tmp1 = sVar2.x;
    if (!sVar2.z) {
      bVar1 = ChkForNonSolids(sVar2.a);
      if (!bVar1) {
        if ((Fireball_Y_Speed[tmp1] < 0x80) && (FireballBouncingFlag[tmp1] == 0)) {
          Fireball_Y_Speed[tmp1] = 0xfd;
          FireballBouncingFlag[tmp1] = 1;
          Fireball_Y_Position[tmp1] = Fireball_Y_Position[tmp1] & 0xf8;
          return tmp1;
        }
        Fireball_State[tmp1] = 0x80;
        Square1SoundQueue = 2;
        return tmp1;
      }
    }
    FireballBouncingFlag[tmp1] = 0;
    return tmp1;
  } else {
    FireballBouncingFlag[param_1] = 0;
    return param_1;
  }
}


// SMB:e22d
// SM2MAIN:aecb
// Signature: [X] -> []
void GetFireballBoundBox(const byte param_1) {
  const byte bVar1 = param_1 + 7;
  BoundingBoxCore(bVar1, 2);
  CheckRightScreenBBox(bVar1);
}


// SMB:e236
// SM2MAIN:aed4
// Signature: [X] -> []
void GetMiscBoundBox(const byte param_1) {
  const byte bVar1 = param_1 + 9;
  BoundingBoxCore(bVar1, 6);
  CheckRightScreenBBox(bVar1);
}


// SMB:e243
// SM2MAIN:aee1
// Signature: [X] -> []
void GetEnemyBoundBox(const byte objoff) {
  GetMaskedOffScrBits(objoff, 0x44, 0x48);
}


// SMB:e24c
// SM2MAIN:aeea
// Signature: [X] -> []
void SmallPlatformBoundBox(const byte objoff) {
  GetMaskedOffScrBits(objoff, 4, 8);
}


// SMB:e252
// SM2MAIN:aef0
// Signature: [X, Y, r00] -> []
void GetMaskedOffScrBits(const byte objoff, const byte param_2, const byte param_3) {
  assert_eq_assumption(objoff, ObjectOffset);
  byte bVar1 = (Enemy_PageLoc[objoff] - ScreenEdgeOrLeft_PageLoc[0]) - (Enemy_X_Position[objoff] < ScreenEdgeOrLeft_X_Pos[0]);
  if ((bVar1 < 0x80) && ((byte)(bVar1 | (Enemy_X_Position[objoff] - ScreenEdgeOrLeft_X_Pos[0])) != 0)) {
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
// Signature: [X] -> [X]
byte LargePlatformBoundBox(const byte param_1) {
  const byte bVar1 = GetXOffscreenBits(param_1 + 1);
  if (bVar1 >= 0xfe) {
    MoveBoundBoxOffscreen(param_1);
    return param_1;
  }
  SetupEOffsetFBBox(param_1);
  return ObjectOffset;
}


// SMB:e27c
// SM2MAIN:af1a
// Signature: [X] -> []
void SetupEOffsetFBBox(const byte param_1) {
  const byte bVar1 = param_1 + 1;
  BoundingBoxCore(bVar1, 1);
  CheckRightScreenBBox(bVar1);
}


// SMB:e289
// SM2MAIN:af27
// Signature: [X] -> []
void MoveBoundBoxOffscreen(const byte param_1) {
  // This condition being false would create wraparound behavior with the bounding box arrays,
  // so assume it never happens
  assert_eq_assumption(param_1 % 64 != 63, true);

  BBOX_TOPLEFT_X(param_1 + 1)  = 0xff;
  BBOX_TOPLEFT_Y(param_1 + 1)  = 0xff;
  BBOX_BOTRIGHT_X(param_1 + 1) = 0xff;
  BBOX_BOTRIGHT_Y(param_1 + 1) = 0xff;
}


// SMB:e29c
// SM2MAIN:af3a
// Signature: [X, Y] -> []
void BoundingBoxCore(const byte param_1, const byte param_2) {
  const byte bVar1 = SprObject_Rel_YPos[param_2];
  const byte bVar2 = SprObject_Rel_XPos[param_2];
  const byte bVar4 = PlayerOrSprObj_BoundBoxCtrl[param_1] * 4;

  BBOX_TOPLEFT_X(param_1) = bVar2 + BoundBoxCtrlData[bVar4];
  BBOX_BOTRIGHT_X(param_1)= bVar2 + BoundBoxCtrlData[bVar4 + 2];
  BBOX_TOPLEFT_Y(param_1) = bVar1 + BoundBoxCtrlData[(byte)(bVar4 + 1)];
  BBOX_BOTRIGHT_Y(param_1)= bVar1 + BoundBoxCtrlData[(byte)(bVar4 + 1) + 2];

  // NES note: The "Y" register is param_1*4, and may eventually be used in CheckRightScreenBBox.
  // The ports omits it for clarity.
}


// SMB:e2de
// SM2MAIN:af7c
// Signature: [X] -> []
void CheckRightScreenBBox(const byte param_1) {
  // NES note: The "Y" register is technically an input, but's always X*4 (param_1*4) in practice.
  // This value comes from BoundingBoxCore.

  const u16 screen_left_pos = (ScreenEdgeOrLeft_PageLoc[0] << 8) | ScreenEdgeOrLeft_X_Pos[0];
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
bool PlayerCollisionCore(const byte param_1) {
  return SprObjectCollisionCore(0, param_1);
}


// SMB:e327
// SM2MAIN:afc5
// Signature: [X, Y] -> [C]
bool SprObjectCollisionCore(const byte param_1, const byte param_2) {
  assert_eq_assumption(param_1 % 4, 0);
  assert_eq_assumption(param_2 % 4, 0);

  // Iterate on both the X and Y axes
  for (int i = 0; i < 2; i++) {
    const byte tl1 = BoundingBoxCoords[param_1+i];
    const byte tl2 = BoundingBoxCoords[param_2+i];
    const byte br1 = BoundingBoxCoords[param_1+i + 2];
    const byte br2 = BoundingBoxCoords[param_2+i + 2];

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


// SMB:e388
// SM2MAIN:b026
// Signature: [A, X, Y] -> [A, X, Z, r04]
struct_axzr04 BlockBufferChk_Enemy(const byte param_1, const byte param_2, const byte param_3) {
  struct_axzr04 sVar1;

  const struct blockbuffer_colli_result sVar2 = BlockBufferCollision(param_1, param_2 + 1, param_3);
  sVar1.a = sVar2.a;
  sVar1.x = ObjectOffset;
  sVar1.z = sVar2.a == 0;
  sVar1.r04 = sVar2.r04;
  return sVar1;
}


// SMB:e39c
// SM2MAIN:b03a
// Signature: [X] -> [A, X, Z]
struct_axz BlockBufferChk_FBall(const byte param_1) {
  struct_axz sVar1;

  const struct blockbuffer_colli_result sVar2 = BlockBufferCollision(0, param_1 + 7, 0x1a);
  sVar1.a = sVar2.a;
  sVar1.z = sVar1.a == 0;
  sVar1.x = ObjectOffset;
  return sVar1;
}


// SMB:e3e8
// SM2MAIN:b086
// Signature: [Y] -> [A, Y, r02, r04, r06, r07]
struct blockbuffer_colli_result BlockBufferColli_Feet(const byte param_1) {
  // the original implementation returned Y (increments the Y parameter by 1)
  // but we decided to move that to the caller for this port

  return BlockBufferCollision(0, 0, param_1 + 1);
}


// SMB:e3e9
// SM2MAIN:b087
// Signature: [Y] -> [A, Z, r02, r04, r06, r07]
struct blockbuffer_colli_result BlockBufferColli_Head(const byte param_1) {
  return BlockBufferCollision(0, 0, param_1);
}


// SMB:e3ec
// SM2MAIN:b08a
// Signature: [Y] -> [A, Z, r02, r04, r06, r07]
struct blockbuffer_colli_result BlockBufferColli_Side(const byte param_1) {
  return BlockBufferCollision(1, 0, param_1);
}


// SMB:e3f0
// SM2MAIN:b08e
struct blockbuffer_colli_result BlockBufferCollision(const byte use_x, const byte param_2, const byte param_3) {
  // Note: Old signature was [A, X, Y] -> [A, Z, r02, r04, r06, r07]
  // Reworked to use metatile coordinates instead of pointer

  const u16 xpos = LOAD_16(SprObject_PageLoc[param_2], SprObject_X_Position[param_2]);
  const u8 xadder = BlockBuffer_X_Adder[param_3];

  const u8 ypos = SprObject_Y_Position[param_2];
  const u8 yadder = BlockBuffer_Y_Adder[param_3];

  const u16 mt_x = (xpos + xadder) / 16;
  const u16 mt_y = (ypos + yadder) / 16 - MT_Y_TOP_MARGIN;

  const u16 blockoff = MTX_MTY_TO_BLOCKOFF(mt_x, mt_y);

  struct blockbuffer_colli_result res;

  res.a = Block_Buffers[blockoff];
  res.z = Block_Buffers[blockoff] == 0;
  res.r04 = (use_x ? xpos : ypos) & 0xf;
  res.mt_x = mt_x;
  res.mt_y = mt_y;

  return res;
}


// Draws a row of two sprites. Implements what happens in DrawSpriteObject.
//
// The original games would call DrawSpriteObject/DrawOneSpriteRow/DrawEnemyObjRow,
// which also took the responsibility of controlling the caller's loops by feeding incremented
// paramers to the caller.
// This port eliminates the feeback in favor of providing a `row` argument, because it's easier to understand at a glance.
static void draw_sprite_row(const byte row,
                            const byte sproff,
                            const byte left_tileidx,
                            const byte right_tileidx,
                            const byte xpos,
                            const byte ypos,
                            const byte attrs,
                            const bool flip_horz)
{
  const byte effective_attrs = attrs | (flip_horz ? 0x40 : 0);

  const byte off = SPRITE_calculate_wrap(sproff, 2*row);

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
void DrawVine(const byte param_1) {
  const byte sproff = Enemy_SprDataOffset[VineObjOffset[param_1]];

  const byte xpos = Enemy_Rel_XPos;
  const byte ypos = Enemy_Rel_YPos + VineYPosAdder[param_1];

  for (int i = 0; i < 6; i++) {
    const bool even = i % 2 == 0;

    // Inlined: SixSpriteStacker (for the sprite's Y component)
    SPRITE_Y_strict(sproff, i)        = ypos + i*8;
    SPRITE_X(sproff, i)               = xpos + (even ? 0 : 6);
    SPRITE_ATTR(sproff, i)            = 0x21 | (even ? 0 : 0x40);
    SPRITE_TILE_semistrict(sproff, i) = 0xe1;
  }

  if (param_1 == 0) {
    SPRITE_TILE(sproff, 0) = 0xe0;
  }

  for (int i = 0; i < 6; i++) {
    const byte diff = VineStart_Y_Position - SPRITE_Y(sproff, i);
    if (diff >= 100) {
      SPRITE_Y_strict(sproff, i) = SPRITE_Y_OFFSCREEN;
    }
  }
}


// SMB:e4dc
// SM2MAIN:b180
// Signature: [X, r08] -> []
void DrawHammer(const byte param_1, const byte objoff) {
  const byte bVar1 = Misc_SprDataOffset[param_1];
  byte bVar3;
  if ((TimerControl == 0) && ((Misc_State[param_1] & 0x7f) == 1)) {
    bVar3 = FrameCounter >> 2 & 3;
  } else {
    bVar3 = 0;
  }
  byte bVar2 = Misc_Rel_YPos + FirstSprYPos[bVar3];
  SPRITE_Y(bVar1, 0) = bVar2;
  SPRITE_Y(bVar1, 1) = bVar2 + SecondSprYPos[bVar3];
  bVar2 = Misc_Rel_XPos + FirstSprXPos[bVar3];
  SPRITE_X(bVar1, 0) = bVar2;
  SPRITE_X(bVar1, 1) = bVar2 + SecondSprXPos[bVar3];
  SPRITE_TILE(bVar1, 0) = FirstSprTilenum[bVar3];
  SPRITE_TILE(bVar1, 1) = SecondSprTilenum[bVar3];
  bVar3 = HammerSprAttrib[bVar3];
  SPRITE_ATTR(bVar1, 0) = bVar3;
  SPRITE_ATTR(bVar1, 1) = bVar3;
  if ((Misc_OffscreenBits & 0xfc) != 0) {
    Misc_State[objoff] = 0;

    // Inlined: DumpTwoSpr
    SPRITE_Y(bVar1, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(bVar1, 1) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:e54b
// SM2MAIN:b1f1
// Signature: [X] -> []
void FlagpoleGfxHandler(const byte param_1) {
  const byte off = Enemy_SprDataOffset[param_1];

  const byte xpos = Enemy_Rel_XPos;
  const byte ypos = Enemy_Y_Position[param_1];
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

  if (FlagpoleCollisionYPos != 0) {
    // Inlined: DrawOneSpriteRow

    const byte bVar1 = FlagpoleScore*2;
    const byte left_tileidx  = FlagpoleScoreNumTiles[bVar1];
    const byte right_tileidx = FlagpoleScoreNumTiles[bVar1 + 1];
    const byte xposN = xpos + 20;
    const byte yposN = FlagpoleFNum_Y_Pos;
    const byte attrs = 1;
    const bool flip_horz = false;
    draw_sprite_row(0, off + 3*4, left_tileidx, right_tileidx, xposN, yposN, attrs, flip_horz);
  }

  if ((Enemy_OffscreenBits & 0xe) != 0) {
    // Inlined: MoveSixSpritesOffscreen
    const byte sprite_offset = Enemy_SprDataOffset[ObjectOffset];
    for (int i = 0; i < 6; i++) {
      SPRITE_Y(sprite_offset, i) = SPRITE_Y_OFFSCREEN;
    }
  }
}


// SMB:e5c8
// SM2MAIN:b26e
// Signature: [X] -> []
void DrawLargePlatform(const byte param_1) {
  const byte sproff1 = Enemy_SprDataOffset[param_1];

  // Inlined: SixSpriteStacker
  for (int i = 0; i < 6; i++) {
    SPRITE_X_strict(sproff1, i) = Enemy_Rel_XPos + i*8;
  }

  const byte ypos = Enemy_Y_Position[ObjectOffset];

  // Inlined: DumpFourSpr
  SPRITE_Y(sproff1, 0) = ypos;
  SPRITE_Y(sproff1, 1) = ypos;
  SPRITE_Y(sproff1, 2) = ypos;
  SPRITE_Y(sproff1, 3) = ypos;

  byte bVar11 = ypos;
  if ((AreaType == 3) || (SecondaryHardMode != 0)) {
    bVar11 = SPRITE_Y_OFFSCREEN;
  }

  const byte bVar3 = Enemy_SprDataOffset[ObjectOffset];

  // NES note: If the offset is 254 or 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpSixSpr.
  // This port assumes it can't happen.
  assert_eq_assumption(bVar3 <= 253, true);

  SPRITE_Y(bVar3, 4) = bVar11;
  SPRITE_Y(bVar3, 5) = bVar11;

  const byte tile = (CloudTypeOverride != 0) ? 0x75 : 0x5b;

  // Inlined: DumpSixSpr
  for (int i = 0; i < 6; i++) {
    SPRITE_TILE(bVar3, i) = tile;
    SPRITE_ATTR(bVar3, i) = 2;
  }

  const byte xoffscrbits = GetXOffscreenBits(ObjectOffset+1);
  const byte bVar1 = Enemy_SprDataOffset[ObjectOffset];

  // NES version is unrolled. We rolled up the loop in this port
  for (int i = 0; i < 6; i++) {
    // 0x80, 0x40, 0x20, 0x10, 0x08, 0x04
    const byte mask = 1 << (7-i);
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
// Signature: [X] -> [X]
byte JCoinGfxHandler(const byte param_1) {
  byte bVar2 = Misc_SprDataOffset[param_1];
  if (Misc_State[param_1] < 2) {
    byte bVar1 = Misc_Y_Position[param_1];
    SPRITE_Y(bVar2, 0) = bVar1;
    SPRITE_Y(bVar2, 1) = bVar1 + 8;
    bVar1 = Misc_Rel_XPos;
    SPRITE_X(bVar2, 0) = Misc_Rel_XPos;
    SPRITE_X(bVar2, 1) = bVar1;

    // Inlined: DumpTwoSpr
    // NES note: If the offset is 255, this wraparounds the sprite page
    // because it's incremented before passing to DumpTwoSpr.
    // This port assumes it can't happen.
    assert_eq_assumption(bVar2 != 255, true);
    const byte tile = JumpingCoinTiles[FrameCounter >> 1 & 3];
    SPRITE_TILE(bVar2, 0) = tile;
    SPRITE_TILE(bVar2, 1) = tile;

    SPRITE_ATTR(bVar2, 0) = 2;
    SPRITE_ATTR(bVar2, 1) = 0x82;
    return ObjectOffset;
  } else {
    if ((FrameCounter & 1) == 0) {
      Misc_Y_Position[param_1] = Misc_Y_Position[param_1] - 1;
    }

    // Inlined: DumpTwoSpr
    SPRITE_Y(bVar2, 0) = Misc_Y_Position[param_1];
    SPRITE_Y(bVar2, 1) = Misc_Y_Position[param_1];

    const byte bVar1 = Misc_Rel_XPos;
    SPRITE_X(bVar2, 0) = Misc_Rel_XPos;
    SPRITE_X(bVar2, 1) = bVar1 + 8;
    SPRITE_ATTR(bVar2, 0) = 2;
    SPRITE_ATTR(bVar2, 1) = 2;
    SPRITE_TILE(bVar2, 0) = 0xf7;
    SPRITE_TILE(bVar2, 1) = 0xfb;
    return param_1;
  }
}


// SMB:e6d2
// SM2MAIN:b37d
// Signature: [] -> []
void DrawPowerUp(void) {
  const byte sproff = Enemy_SprDataOffset[5];

  {
    // Inlined: DrawOneSpriteRow

    const byte idx = PowerUpType << 2;
    const byte left_tileidx_1  = PowerUpGfxTable[idx];
    const byte right_tileidx_1 = PowerUpGfxTable[idx + 1];
    const byte left_tileidx_2  = PowerUpGfxTable[(byte)(idx + 2)];
    const byte right_tileidx_2 = PowerUpGfxTable[(byte)(idx + 2) + 1];

    const byte xpos = Enemy_Rel_XPos;
    const byte ypos = Enemy_Rel_YPos + 8;
    const byte attrs = PowerUpAttributes[PowerUpType] | Enemy_SprAttrib[5];

    const bool flip_horz = false;

    draw_sprite_row(0, sproff, left_tileidx_1, right_tileidx_1, xpos, ypos, attrs, flip_horz);
    draw_sprite_row(1, sproff, left_tileidx_2, right_tileidx_2, xpos, ypos, attrs, flip_horz);
  }

  if ((PowerUpType != 0) && (PowerUpType != 3) && ssw(true, PowerUpType != 4)) {
    // Flicker the powerup by cycling its palette

    const byte attrs = ((FrameCounter >> 1) & 3) | Enemy_SprAttrib[5];

    SPRITE_ATTR(sproff, 0) = attrs;
    SPRITE_ATTR(sproff, 1) = attrs;

    // If it's a fire flower, only flicker the top half
    if (PowerUpType != 1) {
      SPRITE_ATTR(sproff, 2) = attrs;
      SPRITE_ATTR(sproff, 3) = attrs;
    }

    // Flip the right half horizontally
    SPRITE_ATTR(sproff, 1) |= 0x40;
    SPRITE_ATTR(sproff, 3) |= 0x40;
  }

  SprObjectOffscrChk(ObjectOffset);
}


// SMB:e87d
// SM2MAIN:b52c
// Signature: [X] -> []
void EnemyGfxHandler(const byte objoff) {
#ifdef SMB2J_MODE
  EnemyAttributeData[24] = 2;
  if (((WorldNumber == 1) || (WorldNumber == 2)) || (WorldNumber == 6)) {
    EnemyAttributeData[24] = 1;
  }
  EnemyAttributeData[25] = EnemyAttributeData[24];
  EnemyAttributeData[26] = EnemyAttributeData[24];
#endif

  byte ypos = Enemy_Y_Position[objoff];

  // sproff @ $eb
  const byte sproff = Enemy_SprDataOffset[objoff];

  VerticalFlipFlag = 0;
  byte movingdir = Enemy_MovingDir[objoff];
  byte attrs = Enemy_SprAttrib[objoff];
  if (((Enemy_ID[objoff] == 0xd) && (SpriteVarData1[objoff] < 0x80)) && (EnemyFrameTimer[objoff] != 0)) {
    return;
  }

  // tmprEC @ $ec
  byte tmprEC = Enemy_State[objoff] & 0x1f;

  // enemy_id @ $ef
  byte enemy_id = Enemy_ID[objoff];

  if (enemy_id == 0x35) {
    tmprEC = 0;
    movingdir = 1;
    enemy_id = 0x15;
  }

  // enemy_state @ $ed
  const byte enemy_state = enemy_id != 0x33 ? Enemy_State[objoff] : 0;

  if (enemy_id == 0x33) {
    ypos -= 1;
    attrs = (EnemyFrameTimer[objoff] != 0) ? 0x23 : 3;
    tmprEC = 0;
    // enemy_state = 0;
    enemy_id = 8;
  }
  if (enemy_id == 0x32) {
    tmprEC = 3;
    enemy_id = JumpspringFrameOffsets[JumpspringAnimCtrl];
  }
  if ((enemy_id == 0xc) && (SpriteVarData2[objoff] < 0x80)) {
    VerticalFlipFlag = 1;
  }
  if (BowserGfxFlag != 0) {
    enemy_id = (BowserGfxFlag != 1) ? 0x17 : 0x16;
  }
  if (enemy_id == 6) {
    if (Enemy_State[objoff] > 1) {
      tmprEC = 4;
    }
    if ((((Enemy_State[objoff] & 0x20) | TimerControl) == 0) && ((FrameCounter & 8) == 0)) {
      movingdir ^= 3;
    }
  }
  attrs = EnemyAttributeData[enemy_id] | attrs;
  byte tableoff = EnemyGfxTableOffsets[enemy_id];

  if (BowserGfxFlag != 0) {
    if (BowserGfxFlag == 1) {
      if (BowserBodyControls >= 0x80) {
        tableoff = 0xde;
      }
    } else {
      if ((BowserBodyControls & 1) != 0) {
        tableoff = 0xe4;
      }
      if ((enemy_state & 0x20) != 0) {
        ypos -= 0x10;
      }
    }
    if ((enemy_state & 0x20) != 0) {
      VerticalFlipFlag = tableoff;
    }
    // DrawBowser
    DrawEnemyObject(tableoff, Enemy_Rel_XPos, ypos, attrs, movingdir, objoff, sproff, tmprEC, enemy_id);
    return;
  }

  if (tableoff == 0x24) {
    if (tmprEC == 5) {
      tableoff = 0x30;
      movingdir = 2;
      tmprEC = 5;
    }
  } else {
    if (tableoff == 0x90) {
      if (((enemy_state & 0x20) == 0) && (FrenzyEnemyTimer < 0x10)) {
        tableoff = 0x96;
      }
      goto CheckDefeatedState;
    }
    if ((enemy_id < 4) && (tmprEC > 1)) {
      tableoff = 0x5a;
      if (enemy_id == 2) {
        tableoff = 0x7e;
        ypos += 1;
      }
    }
    if (tmprEC == 4) {
      tableoff = 0x72;
      byte bVar1 = ypos + 1;
      if (enemy_id != 2) {
        tableoff = 0x66;
        bVar1 = ypos + 2;
      }
      ypos = bVar1;
      if (enemy_id == 6) {
        tableoff = 0x54;
        if ((enemy_state & 0x20) == 0) {
          tableoff = 0x8a;
          ypos -= 1;
        }
      }
    }
  }
  if (enemy_id == 5) {
    if (enemy_state != 0) {
      if ((enemy_state & 8) == 0) {
        goto CheckDefeatedState;
      }
      tableoff = 0xb4;
    }
CheckToAnimateEnemy:
    if ((enemy_id == 6) || (enemy_id == 8) || (enemy_id == 0xc) || (enemy_id >= 0x18)) {
      goto CheckDefeatedState;
    }
    if (enemy_id == 0x15) {
      if (ssw(WorldNumber < 7, true)) {
        tmprEC = 3;
      }
      if (WorldNumber < 7) {
        tableoff = 0xa2;
      }
      goto CheckDefeatedState;
    }
    if ((FrameCounter & EnemyAnimTimingBMask[0]) != 0) {
      goto CheckDefeatedState;
    }
  } else {
    if (tableoff == 0x48) {
      goto CheckToAnimateEnemy;
    }
    if (EnemyIntervalTimer[objoff] >= 5) {
      goto CheckDefeatedState;
    }
    if (tableoff != 0x3c) {
      goto CheckToAnimateEnemy;
    }
    if (EnemyIntervalTimer[objoff] == 1) {
      goto CheckDefeatedState;
    }
    ypos += 3;
  }
  if ((enemy_state & 0xa0) == 0) {
    if (TimerControl == 0) {
      tableoff += 6;
    }
  }
CheckDefeatedState:
  if (ssw(true, enemy_id != 4)) {
    if ((enemy_state & 0x20) == 0) {
      DrawEnemyObject(tableoff, Enemy_Rel_XPos, ypos, attrs, movingdir, objoff, sproff, tmprEC, enemy_id);
      return;
    }
  }
  if (enemy_id <= 3) {
    DrawEnemyObject(tableoff, Enemy_Rel_XPos, ypos, attrs, movingdir, objoff, sproff, tmprEC, enemy_id);
    return;
  }

  VerticalFlipFlag = 1;

  DrawEnemyObject(tableoff, Enemy_Rel_XPos, ypos, attrs, movingdir, objoff, sproff, 0, enemy_id);
}


// SMB:ea4b
// SM2MAIN:b71b
// Signature: [X, r05, r02, r04, r03, r08, rEB, rEC, rEF] -> []
void DrawEnemyObject(const byte tableoff, const byte xpos, const byte ypos, const byte attrs, const byte movingdir,
    const byte objoff,
    const byte sproff, const byte tmprEC, const byte enemy_id) {
  {
    // Inlined: DrawEnemyObjRow

    byte tableoff_tmp = tableoff;

    const byte left_tileidx_1  = EnemyGraphicsTable[tableoff_tmp];
    const byte right_tileidx_1 = EnemyGraphicsTable[tableoff_tmp + 1];
    tableoff_tmp += 2;
    const byte left_tileidx_2  = EnemyGraphicsTable[tableoff_tmp];
    const byte right_tileidx_2 = EnemyGraphicsTable[tableoff_tmp + 1];
    tableoff_tmp += 2;
    const byte left_tileidx_3  = EnemyGraphicsTable[tableoff_tmp];
    const byte right_tileidx_3 = EnemyGraphicsTable[tableoff_tmp + 1];

    const bool flip_horz = (movingdir & 2) != 0;

    draw_sprite_row(0, sproff, left_tileidx_1, right_tileidx_1, xpos, ypos, attrs, flip_horz);
    draw_sprite_row(1, sproff, left_tileidx_2, right_tileidx_2, xpos, ypos, attrs, flip_horz);
    draw_sprite_row(2, sproff, left_tileidx_3, right_tileidx_3, xpos, ypos, attrs, flip_horz);
  }

  // Workaround for CheckpointEnemyID() -> Setup_Vine() bug
  rEF = enemy_id;

  const byte bVar3 = Enemy_SprDataOffset[objoff];

  if (enemy_id == 8) {
    SprObjectOffscrChk(objoff);
    return;
  }

  if (VerticalFlipFlag != 0) {
    // NES note: If the offset is 254 or 255, this wraparounds the sprite page
    // because it's incremented before passing to DumpSixSpr.
    // This port assumes it can't happen.
    assert_eq_assumption(bVar3 <= 253, true);

    const byte tmpattr = SPRITE_ATTR(bVar3, 0) | 0x80;

    // Inlined: DumpSixSpr
    for (int i =  0; i < 6; i++) {
      SPRITE_ATTR(bVar3, i) = tmpattr;
    }

    byte bVar2 = bVar3;
    if ((enemy_id != 5) && ssw(true, (enemy_id != 4)) && (enemy_id != 0x11) && (enemy_id < 0x15)) {
      bVar2 = SPRITE_calculate_wrap(bVar3, 2);
    }

    SWAP(SPRITE_TILE(bVar2, 0), SPRITE_TILE(bVar3, 4));
    SWAP(SPRITE_TILE(bVar2, 1), SPRITE_TILE(bVar3, 5));
  }

  if (BowserGfxFlag != 0) {
    SprObjectOffscrChk(objoff);
    return;
  }
  if (enemy_id == 5) {
    SprObjectOffscrChk(objoff);
    return;
  }
  if ((enemy_id != 7) && (enemy_id != 0xd) && ssw(true, (enemy_id != 4)) && (enemy_id != 0xc)) {
    if ((enemy_id == 0x12) && (tmprEC != 5)) {
      goto CheckToMirrorLakitu;
    }
    if (enemy_id == 0x15) {
      SPRITE_ATTR(bVar3, 5) = 0x42;
    }
    if (tmprEC < 2) {
      goto CheckToMirrorLakitu;
    }
  }
  if (BowserGfxFlag == 0) {
    const byte bVar4 = SPRITE_ATTR(bVar3, 0) & 0xa3;
    SPRITE_ATTR(bVar3, 0) = bVar4;
    SPRITE_ATTR(bVar3, 2) = bVar4;
    SPRITE_ATTR(bVar3, 4) = bVar4;
    byte bVar1 = bVar4 | 0x40;
    if (tmprEC == 5) {
      bVar1 = bVar4 | 0xc0;
    }
    SPRITE_ATTR(bVar3, 1) = bVar1;
    SPRITE_ATTR(bVar3, 3) = bVar1;
    SPRITE_ATTR(bVar3, 5) = bVar1;
    if (tmprEC == 4) {
      const byte bVar9 = SPRITE_ATTR(bVar3, 2);
      SPRITE_ATTR(bVar3, 2) = bVar9 | 0x80;
      SPRITE_ATTR(bVar3, 4) = bVar9 | 0x80;
      SPRITE_ATTR(bVar3, 3) = bVar9 | 0xc0;
      SPRITE_ATTR(bVar3, 5) = bVar9 | 0xc0;
    }
  }
CheckToMirrorLakitu:
  if (enemy_id == 0x11) {
    if (VerticalFlipFlag == 0) {
      SPRITE_ATTR(bVar3, 4) &= 0x81;
      SPRITE_ATTR(bVar3, 5) |= 0x41;
      if (FrenzyEnemyTimer < 0x10) {
        const byte bVar9 = SPRITE_ATTR(bVar3, 5);
        SPRITE_ATTR(bVar3, 3) = bVar9;
        SPRITE_ATTR(bVar3, 2) = bVar9 & 0x81;
      }
      SprObjectOffscrChk(objoff);
      return;
    }
    SPRITE_ATTR(bVar3, 0) = SPRITE_ATTR(bVar3, 0) & 0x81;
    SPRITE_ATTR(bVar3, 1) = SPRITE_ATTR(bVar3, 1) | 0x41;
  }
  if (enemy_id < 0x18) {
    SprObjectOffscrChk(objoff);
    return;
  }
  const byte ead = ssw(0x02, EnemyAttributeData[24]);
  SPRITE_ATTR(bVar3, 2) = ead | 0x80;
  SPRITE_ATTR(bVar3, 4) = ead | 0x80;
  SPRITE_ATTR(bVar3, 3) = ead | 0xc0;
  SPRITE_ATTR(bVar3, 5) = ead | 0xc0;
  SprObjectOffscrChk(objoff);
}


// SMB:eb64
// SM2MAIN:b83f
// Signature: [r08] -> []
void SprObjectOffscrChk(const byte objoff) {
  const byte original_bits = Enemy_OffscreenBits;

  if ((original_bits & 4) != 0) {
    // Inlined: MoveESprColOffscreen
    const byte offset = SPRITE_calculate_wrap(Enemy_SprDataOffset[objoff], 1);
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 2) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 4) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 8) != 0) {
    // Inlined: MoveESprColOffscreen
    const byte offset = Enemy_SprDataOffset[objoff];
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 2) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 4) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 0x20) != 0) {
    // Inlined: MoveESprRowOffscreen
    const byte offset = SPRITE_calculate_wrap(Enemy_SprDataOffset[objoff], 4);
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 1) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 0x40) != 0) {
    // Inlined: MoveESprRowOffscreen
    const byte offset = SPRITE_calculate_wrap(Enemy_SprDataOffset[objoff], 2);
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 1) = SPRITE_Y_OFFSCREEN;
  }

  if ((original_bits & 0x80) != 0) {
    // Inlined: MoveESprRowOffscreen
    const byte offset = Enemy_SprDataOffset[objoff];
    SPRITE_Y(offset, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(offset, 1) = SPRITE_Y_OFFSCREEN;

    if ((Enemy_ID[objoff] != 0xc) && (Enemy_Y_HighPos[objoff] == 2)) {
      EraseEnemyObject(objoff);
    }
  }
}


// SMB:ebaa
// SM2MAIN:b885
// Signature: [X, Y, r05, r02, r04, r03] -> [X, Y, r02]
struct_xyr02 DrawEnemyObjRow(const byte table_idx, const byte sproff, const byte xpos, const byte ypos, const byte attrs, const byte flags) {
  const byte left_tileidx  = EnemyGraphicsTable[table_idx];
  const byte right_tileidx = EnemyGraphicsTable[table_idx + 1];

  return DrawSpriteObject(table_idx, sproff, left_tileidx, right_tileidx, xpos, ypos, attrs, flags);
}


// SMB:ebb2
// SM2MAIN:b88d
// Signature: [X, Y, r00, A, r05, r02, r04, r03] -> [X, Y, r02]
struct_xyr02 DrawOneSpriteRow(const byte tile_counter, const byte sproff, const byte left_tileidx, const byte right_tileidx, const byte xpos, const byte ypos, const byte attrs, const byte flags) {
  // This is really just DrawSpriteObject with the right_tileidx parameter assigned to A instead of r01. A shortcut to avoid a "STA" instruction.

  return DrawSpriteObject(tile_counter, sproff, left_tileidx, right_tileidx, xpos, ypos, attrs, flags);
}


// SMB:ebd1
// SM2MAIN:b8ac
// Signature: [X] -> []
void DrawBlock(const byte param_1) {
  {
    // Inlined: DrawOneSpriteRow

    const byte left_tileidx_1  = DefaultBlockObjTiles[0];
    const byte right_tileidx_1 = DefaultBlockObjTiles[1];
    const byte left_tileidx_2  = DefaultBlockObjTiles[2];
    const byte right_tileidx_2 = DefaultBlockObjTiles[3];

    const byte sproff = AltOrBlock_SprDataOffset[param_1];
    const byte xpos = Block_Rel_XPos;
    const byte ypos = Block_Rel_YPos;
    const byte attrs = 3;
    const bool flip_horz = false;

    draw_sprite_row(0, sproff, left_tileidx_1, right_tileidx_1, xpos, ypos, attrs, flip_horz);
    draw_sprite_row(1, sproff, left_tileidx_2, right_tileidx_2, xpos, ypos, attrs, flip_horz);
  }

  byte bVar7 = AltOrBlock_SprDataOffset[ObjectOffset];
  if (AreaType != 1) {
    SPRITE_TILE(bVar7, 0) = 0x86;
    SPRITE_TILE(bVar7, 1) = 0x86;
  }
  if (Block_Metatile[ObjectOffset] == ssw(0xc4, 0xc5)) {
    // Inlined: DumpFourSpr
    // NES note: If the offset is 255, this wraparounds the sprite page
    // because it's incremented before passing to DumpFourSpr.
    // This port assumes it can't happen.
    assert_eq_assumption(bVar7 != 255, true);
    SPRITE_TILE(bVar7, 0) = 0x87;
    SPRITE_TILE(bVar7, 1) = 0x87;
    SPRITE_TILE(bVar7, 2) = 0x87;
    SPRITE_TILE(bVar7, 3) = 0x87;


    const byte bVar4 = (AreaType != 1) ? 1 : 3;
    SPRITE_ATTR(bVar7, 0) = bVar4;
    SPRITE_ATTR(bVar7, 1) = bVar4 | 0x40;
    SPRITE_ATTR(bVar7, 2) = bVar4 | 0x80;
    SPRITE_ATTR(bVar7, 3) = bVar4 | 0xc0;
  }

  if ((Block_OffscreenBits & 4) != 0) {
    SPRITE_Y(bVar7, 1) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(bVar7, 3) = SPRITE_Y_OFFSCREEN;
  }

  // Inlined: ChkLeftCo
  if ((Block_OffscreenBits & 8) != 0) {
    SPRITE_Y(bVar7, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(bVar7, 2) = SPRITE_Y_OFFSCREEN;
  }
}


// SMB:ec53
// SM2MAIN:b92e
// Signature: [X] -> []
void DrawBrickChunks(const byte param_1) {
  const byte tilepalette = GameEngineSubroutine != 5 ? 3 : 2;
  const byte tileidx = GameEngineSubroutine != 5 ? 0x84 : 0x75;

  const byte off = AltOrBlock_SprDataOffset[param_1];

  // NES note: If the sprite offset is 254 or 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpFourSpr.
  // This port assumes it can't happen.
  assert_eq_assumption(off <= 253, true);

  // Set tile indices for all 4 sprites
  // Inlined: DumpFourSpr
  SPRITE_TILE(off, 0) = tileidx;
  SPRITE_TILE(off, 1) = tileidx;
  SPRITE_TILE(off, 2) = tileidx;
  SPRITE_TILE(off, 3) = tileidx;

  // Set attributes for all 4 sprites
  // Cycle through flipping them vertically and horizontally based on the frame counter
  // None -> Horz -> Vert -> Vert+Horz -> None -> ...
  const byte tileflipattr = (FrameCounter & 0xc) << 4;
  const byte attr = tileflipattr | tilepalette;
  // Inlined: DumpFourSpr
  SPRITE_ATTR(off, 0) = attr;
  SPRITE_ATTR(off, 1) = attr;
  SPRITE_ATTR(off, 2) = attr;
  SPRITE_ATTR(off, 3) = attr;

  // Set Y for sprites +0, +1

  // Inlined: DumpTwoSpr
  SPRITE_Y(off, 0) = Block_Rel_YPos;
  SPRITE_Y(off, 1) = Block_Rel_YPos;

  const byte x1 = Block_Rel_XPos;
  const byte x2 = Block_Rel_XPos_2;

  const byte b = Block_Orig_XPos[param_1] - ScreenEdgeOrLeft_X_Pos[0];

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
void DrawFireball(const byte param_1) {
  const byte bVar1 = FBall_SprDataOffset[param_1];
  SPRITE_Y(bVar1, 0) = Fireball_Rel_YPos;
  SPRITE_X(bVar1, 0) = Fireball_Rel_XPos;
  DrawFirebar(bVar1);
}


// SMB:eced
// SM2MAIN:b9c8
// Signature: [Y] -> []
void DrawFirebar(const byte param_1) {
  SPRITE_TILE(param_1, 0) = ((FrameCounter >> 2) & 1) ^ 100;
  SPRITE_ATTR(param_1, 0) = ((FrameCounter >> 3 & 1) != 0) ? 0xc2 : 2;
}


// SMB:ed09
// SM2MAIN:b9e4
// Signature: [X] -> []
void DrawExplosion_Fireball(const byte param_1) {
  byte bVar1 = Fireball_State[param_1];
  Fireball_State[param_1] = Fireball_State[param_1] + 1;
  bVar1 = bVar1 >> 1 & 7;
  if (bVar1 < 3) {
    DrawExplosion_Fireworks(bVar1, AltOrBlock_SprDataOffset[param_1]);
  } else {
    Fireball_State[param_1] = 0;
  }
}


// SMB:ed17
// SM2MAIN:b9f2
// Signature: [A, Y] -> []
void DrawExplosion_Fireworks(const byte param_1, const byte param_2) {
  // NES note: If the offset is 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpFourSpr.
  // This port assumes it can't happen.
  assert_eq_assumption(param_2 != 255, true);

  // Inlined: DumpFourSpr
  SPRITE_TILE(param_2, 0) = ExplosionTiles[param_1];
  SPRITE_TILE(param_2, 1) = ExplosionTiles[param_1];
  SPRITE_TILE(param_2, 2) = ExplosionTiles[param_1];
  SPRITE_TILE(param_2, 3) = ExplosionTiles[param_1];

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
void DrawSmallPlatform(const byte param_1) {
  const byte bVar2 = Enemy_SprDataOffset[param_1];

  // NES note: If the offset is 254 or 255, this wraparounds the sprite page
  // because it's incremented before passing to DumpSixSpr.
  // This port assumes it can't happen.
  assert_eq_assumption(bVar2 <= 253, true);

  // Inlined: DumpSixSpr
  for (int i = 0; i < 6; i++) {
    SPRITE_TILE(bVar2, i) = 0x5b;
    SPRITE_ATTR(bVar2, i) = 2;
  }

  byte bVar1 = Enemy_Rel_XPos;
  SPRITE_X(bVar2, 0) = Enemy_Rel_XPos;
  SPRITE_X(bVar2, 3) = bVar1;
  SPRITE_X(bVar2, 1) = bVar1 + 8;
  SPRITE_X(bVar2, 4) = bVar1 + 8;
  SPRITE_X(bVar2, 2) = bVar1 + 0x10;
  SPRITE_X(bVar2, 5) = bVar1 + 0x10;
  byte bStack0000 = Enemy_Y_Position[param_1];
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
void DrawBubble(const byte param_1) {
  byte bVar1;

  if ((SprObject_Y_HighPos[0] == 1) && ((Bubble_OffscreenBits & 8) == 0)) {
    bVar1 = Bubble_SprDataOffset[param_1];
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
  byte bVar1;
  byte abVar2;

  if ((InjuryTimer == 0) || ((FrameCounter & 1) == 0)) {
    if (GameEngineSubroutine == 0xb) {
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
    if (Player_State == 0) {
      FindPlayerAction();
      return;
    }
    FindPlayerAction();
    if ((FrameCounter & 4) == 0) {
      abVar2 = PlayerOrSprDataOffset[0];
      if ((PlayerFacingDir & 1) == 0) {
        abVar2 = PlayerOrSprDataOffset[0] + 4;
      }
      bVar1 = 0;
      if (PlayerSize != 0) {
        if (SPRITE_TILE(abVar2, 6) == PlayerGraphicsTable[158]) {
          return;
        }
        bVar1 = 1;
      }
      SPRITE_TILE(abVar2, 6) = SwimKickTileNum[bVar1];
    }
  }
}


// SMB:ef34
// SM2MAIN:bc0f
// Signature: [] -> []
void FindPlayerAction(void) {
  const byte bVar1 = ProcessPlayerAction();
  PlayerGfxProcessing(bVar1);
}


// SMB:ef45
// SM2MAIN:bc20
// Signature: [A] -> []
void PlayerGfxProcessing(const byte param_1) {
  PlayerGfxOffset = param_1;
  RenderPlayerSub(4);
  ChkForPlayerAttrib();
  if (FireballThrowingTimer != 0) {
    if (PlayerAnimTimer < FireballThrowingTimer) {
      FireballThrowingTimer = PlayerAnimTimer;
      PlayerGfxOffset = PlayerGfxTblOffsets[7];
      const byte bVar3 = ((PlayerSpriteVarData1[0] | Left_Right_Buttons) != 0) ? 3 : 4;
      RenderPlayerSub(bVar3);
    } else {
      FireballThrowingTimer = 0;
    }
  }

  const byte sprite_offset = PlayerOrSprDataOffset[0];

  if (SprObject_OffscrBits[0] & 0x10) {
    // Inlined: DumpTwoSpr
    const byte off = SPRITE_calculate_wrap(sprite_offset, 6);
    SPRITE_Y(off, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 1) = SPRITE_Y_OFFSCREEN;
  }

  if (SprObject_OffscrBits[0] & 0x20) {
    // Inlined: DumpTwoSpr
    const byte off = SPRITE_calculate_wrap(sprite_offset, 4);
    SPRITE_Y(off, 0) = SPRITE_Y_OFFSCREEN;
    SPRITE_Y(off, 1) = SPRITE_Y_OFFSCREEN;
  }

  if (SprObject_OffscrBits[0] & 0x40) {
    // Inlined: DumpTwoSpr
    const byte off = SPRITE_calculate_wrap(sprite_offset, 2);
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
  DrawPlayerLoop(0xb8, 4, IntermediatePlayerData[0], IntermediatePlayerData[1], IntermediatePlayerData[2],
                 IntermediatePlayerData[3], IntermediatePlayerData[5]);
  SPRITE_ATTR(0, 8) = SPRITE_ATTR(0, 9) | 0x40;
}


// SMB:efbe
// SM2MAIN:bc99
// Signature: [A] -> []
void RenderPlayerSub(const byte param_1) {
  Player_Pos_ForScroll = SprObject_Rel_XPos[0];
  DrawPlayerLoop(PlayerGfxOffset, PlayerOrSprDataOffset[0], SprObject_Rel_YPos[0], PlayerFacingDir,
                 Player_SprAttrib, SprObject_Rel_XPos[0], param_1);
}


// SMB:efdc
// SM2MAIN:bcb7
// Signature: [X, Y, r02, r03, r04, r05, r07] -> []
void DrawPlayerLoop(const byte param_1, const byte sproff, const byte ypos, const byte flags, const byte attrs, const byte xpos, const byte num_rows) {
  // NES note: The loop in the original checks at the end. If num_rows = 0, it loops 256 times.
  // This never occurs in unmodified ROMS, but it might in modified ones via DrawPlayer_Intermediate.
  // TODO: have a setting to disable this silly mostly-irrelevant workaround
  const int actual_num_rows = num_rows != 0 ? num_rows : 256;

  // Inlined: DrawOneSpriteRow

  const bool flip_horz = (flags & 2) != 0;

  byte table_idx = param_1;

  for (int i = 0; i < actual_num_rows; i++) {
    const byte left_tileidx  = PlayerGraphicsTable[table_idx];
    const byte right_tileidx = PlayerGraphicsTable[table_idx + 1];

    draw_sprite_row(i, sproff, left_tileidx, right_tileidx, xpos, ypos, attrs, flip_horz);

    table_idx += 2;
  }
}


// SMB:efec
// SM2MAIN:bcc7
// Signature: [] -> [A]
byte ProcessPlayerAction(void) {
  byte bVar1;

  if (Player_State == 3) {
    bVar1 = 5;
    if (PlayerSpriteVarData2[0] != 0) {
      return ThreeFrameExtent(GetGfxOffsetAdder(5));
    }
  } else {
    if (Player_State == 2) {
      return GetCurrentAnimOffset(GetGfxOffsetAdder(4));
    }
    if (Player_State == 1) {
      if (SwimmingFlag != 0) {
        const byte gfxoffsetadder = GetGfxOffsetAdder(1);
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
        if ((PlayerSpriteVarData1[0] | Left_Right_Buttons) != 0) {
          if ((Player_XSpeedAbsolute < 9) || ((Player_MovingDir & PlayerFacingDir) != 0)) {
            return FourFrameExtent(GetGfxOffsetAdder(4));
          }
          if (SMB2J_ONLY && GameEngineSubroutine < 9) {
            NoiseSoundQueue = 0x80;
          }
          bVar1 = 3;
        }
      }
    }
  }

  const byte gfxoffsetadder = GetGfxOffsetAdder(bVar1);
  PlayerAnimCtrl = 0;
  return PlayerGfxTblOffsets[gfxoffsetadder];
}


// SMB:f062
// SM2MAIN:bd47
// Signature: [Y] -> [A]
byte GetCurrentAnimOffset(const byte param_1) {
  return GetOffsetFromAnimCtrl(PlayerAnimCtrl, param_1);
}


// SMB:f068
// SM2MAIN:bd4d
// Signature: [Y] -> [A]
byte FourFrameExtent(const byte param_1) {
  return AnimationControl(3, param_1);
}


// SMB:f06d
// SM2MAIN:bd52
// Signature: [Y] -> [A]
byte ThreeFrameExtent(const byte param_1) {
  return AnimationControl(2, param_1);
}


// SMB:f06f
// SM2MAIN:bd54
// Signature: [A, Y] -> [A]
byte AnimationControl(const byte param_1, const byte param_2) {
  const byte bVar1 = GetCurrentAnimOffset(param_2);
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
byte GetGfxOffsetAdder(const byte param_1) {
  if (PlayerSize != 0) {
    return param_1 + 8;
  } else {
    return param_1;
  }
}


// SMB:f0b0
// SM2MAIN:bd95
// Signature: [] -> [A]
byte HandleChangeSize(void) {
  if (((FrameCounter & 3) == 0)) {
    PlayerAnimCtrl += 1;
    if (PlayerAnimCtrl >= 10) {
      PlayerAnimCtrl = 0;
      PlayerChangeSizeFlag = 0;
    }
  }
  if (PlayerSize != 0) {
    const byte idx = (ChangeSizeOffsetAdder[(byte)(PlayerAnimCtrl + 10)] == 0) ? 1 : 9;
    return PlayerGfxTblOffsets[idx];
  }
  return GetOffsetFromAnimCtrl(ChangeSizeOffsetAdder[PlayerAnimCtrl], 0xf);
}


// SMB:f0d0
// SM2MAIN:bdb5
// Signature: [A, Y] -> [A]
byte GetOffsetFromAnimCtrl(const byte param_1, const byte param_2) {
  byte o = param_1 * 8 + PlayerGfxTblOffsets[param_2];

  // param_1 is likely never >= 0x20, but the original game computes it this way
  // TODO: verify one way or the other
  o += ((param_1 & 0x20) != 0);

  return o;
}


// SMB:f0e9
// SM2MAIN:bdce
// Signature: [] -> []
void ChkForPlayerAttrib(void) {
  const byte abVar1 = PlayerOrSprDataOffset[0];
  if (GameEngineSubroutine != 0xb) {
    if (((PlayerGfxOffset == 0x50) || (PlayerGfxOffset == 0xb8)) || (PlayerGfxOffset == 0xc0)) {
      goto C_S_IGAtt;
    }
    if (PlayerGfxOffset != 200) {
      return;
    }
  }

  SPRITE_ATTR(PlayerOrSprDataOffset[0], 4) &= 0x3f;

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
byte RelativePlayerPosition(void) {
  GetObjRelativePosition(0, 0);
  return 0;
}


// SMB:f131
// SM2MAIN:be16
// Signature: [X] -> []
void RelativeBubblePosition(const byte param_1) {
  const byte bVar1 = GetProperObjOffset(param_1, 1);
  GetObjRelativePosition(bVar1, 3);
}


// SMB:f13b
// SM2MAIN:be20
// Signature: [X] -> []
void RelativeFireballPosition(const byte param_1) {
  const byte bVar1 = GetProperObjOffset(param_1, 0);
  GetObjRelativePosition(bVar1, 2);
}


// SMB:f148
// SM2MAIN:be2d
// Signature: [X] -> []
void RelativeMiscPosition(const byte param_1) {
  const byte bVar1 = GetProperObjOffset(param_1, 2);
  GetObjRelativePosition(bVar1, 6);
}


// SMB:f152
// SM2MAIN:be37
// Signature: [X] -> []
void RelativeEnemyPosition(const byte param_1) {
  GetObjRelativePosition(1 + param_1, 1);
}


// SMB:f159
// SM2MAIN:be3e
// Signature: [X] -> []
void RelativeBlockPosition(const byte param_1) {
  GetObjRelativePosition(9 + param_1, 4);
  GetObjRelativePosition(9 + ObjectOffset + 2, 5);
}


// SMB:f171
// SM2MAIN:be56
// Signature: [X, Y] -> []
void GetObjRelativePosition(const byte param_1, const byte param_2) {
  SprObject_Rel_YPos[param_2] = SprObject_Y_Position[param_1];
  SprObject_Rel_XPos[param_2] = SprObject_X_Position[param_1] - ScreenEdgeOrLeft_X_Pos[0];
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
void GetFireballOffscreenBits(const byte param_1) {
  const byte bVar1 = GetProperObjOffset(param_1, 0);
  GetOffScreenBitsSet(bVar1, 2);
}


// SMB:f191
// SM2MAIN:be76
// Signature: [X] -> []
void GetBubbleOffscreenBits(const byte param_1) {
  const byte bVar1 = GetProperObjOffset(param_1, 1);
  GetOffScreenBitsSet(bVar1, 3);
}


// SMB:f19b
// SM2MAIN:be80
// Signature: [X] -> []
void GetMiscOffscreenBits(const byte param_1) {
  const byte bVar1 = GetProperObjOffset(param_1, 2);
  GetOffScreenBitsSet(bVar1, 6);
}


// SMB:f1a8
// SM2MAIN:be8d
// Signature: [X, Y] -> [X]
byte GetProperObjOffset(const byte param_1, const byte param_2) { return param_1 + ObjOffsetData[param_2]; }


// SMB:f1af
// SM2MAIN:be94
// Signature: [X] -> []
void GetEnemyOffscreenBits(const byte param_1) {
  // NES note: GetEnemyOffscreenBits sets Y=1. Used by InitPlatformFall.
  GetOffScreenBitsSet(param_1 + 1, 1);
}


// SMB:f1b6
// SM2MAIN:be9b
// Signature: [X] -> []
void GetBlockOffscreenBits(const byte param_1) {
  GetOffScreenBitsSet(param_1 + 9, 4);
}


// SMB:f1c0
// SM2MAIN:bea5
// Signature: [X, Y] -> []
void GetOffScreenBitsSet(const byte param_1, const byte param_2) {
  // Inlined: RunOffscrBitsSubs (only used once in the original games)
  const byte xbits = GetXOffscreenBits(param_1);
  const byte ybits = GetYOffscreenBits(param_1);

  SprObject_OffscrBits[param_2] = (ybits << 4) | (xbits >> 4);
}


// keeping the original version for now, in case of regressions (though I made extra sure there aren't any)
static inline byte original_xoff_f(const byte param_1, byte bVar3) {
  const byte bVar1 = (ScreenEdgeOrLeft_PageLoc[bVar3] - SprObject_PageLoc[param_1]) - (ScreenEdgeOrLeft_X_Pos[bVar3] < SprObject_X_Position[param_1]);
  byte bVar2 = DefaultXOnscreenOfs[bVar3];
  if ((bVar1 < 0x80)) {
    bVar2 = DefaultXOnscreenOfs[bVar3 + 1];
    if (0x7f < (byte)(bVar1 - 1)) {
      bVar2 = DividePDiff(8, bVar2, bVar3, 0x38,
                          ScreenEdgeOrLeft_X_Pos[bVar3] - SprObject_X_Position[param_1]);
    }
  }
  return bVar2;
}

static byte xoff_f(const byte param_1, byte a) {
  // a seriously inlined/simplified version of the original.
  // part of GetXOffscreenBits

  const int j = ScreenEdgeOrLeft_PageLoc[a] - SprObject_PageLoc[param_1];
  const int ik = ScreenEdgeOrLeft_X_Pos[a] - SprObject_X_Position[param_1];

  int z = ik + j*256;

  // wraparound as a signed 16-bit number to achieve the same glitchy behavior
  if (z >= 0x8000) { z -= 0x10000; }
  if (z < -0x8000) { z += 0x10000; }

  byte v;
  if (z < 0) {
    v = 0x7;
  } else if (z < 56) {
    // 8 to e
    v = z/8 + 8;
  } else  {
    v = 0xf;
  }

  if (a) {
    v = (v+8)%16;
  }
  return v;
}

// SMB:f1f6
// SM2MAIN:bedb
// Signature: [X] -> [A]
byte GetXOffscreenBits(const byte param_1) {
  byte i = xoff_f(param_1, 1);
  if (XOffscreenBitsData[i] != 0) {
    return XOffscreenBitsData[i];
  }
  i = xoff_f(param_1, 0);
  return XOffscreenBitsData[i];
}

// keeping the original version for now, in case of regressions (though I made extra sure there aren't any)
static byte original_yoff_f(const byte param_1, byte bVar3) {
  const byte bVar1 = (1 - SprObject_Y_HighPos[param_1]) - (HighPosUnitData[bVar3] < SprObject_Y_Position[param_1]);
  byte bVar2 = DefaultYOnscreenOfs[bVar3];
  if ((bVar1 < 0x80)) {
    bVar2 = DefaultYOnscreenOfs[bVar3 + 1];
    if (0x7f < (byte)(bVar1 - 1)) {
      bVar2 = DividePDiff(4, bVar2, bVar3, 0x20,
                          HighPosUnitData[bVar3] - SprObject_Y_Position[param_1]);
    }
  }
  return bVar2;
}

static byte yoff_f(const byte param_1, bool a) {
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

  byte v;
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
byte GetYOffscreenBits(const byte param_1) {
  byte i = yoff_f(param_1, 1);
  assert_eq_regressiontest(original_yoff_f(param_1, 1), i);
  if (YOffscreenBitsData[i] != 0) {
    return YOffscreenBitsData[i];
  }
  i = yoff_f(param_1, 0);
  assert_eq_regressiontest(original_yoff_f(param_1, 0), i);
  return YOffscreenBitsData[i];
}


// SMB:f26d
// SM2MAIN:bf52
// Signature: [A, X, Y, r06, r07] -> [X]
byte DividePDiff(const byte param_1, const byte param_2, const bool param_3, const byte param_4, const byte param_5) {
  // note: to be removed once other old code is removed
  if (param_5 >= param_4) {
    return param_2;
  }
  byte a = (param_5 / 8) % 8;
  if (!param_3) {
    a = a + param_1;
  }
  return a;
}


// SMB:f282
// SM2MAIN:bf67
// Signature: [X, Y, r00, r01, r05, r02, r04, r03] -> [X, Y, r02]
struct_xyr02 DrawSpriteObject(const byte tile_counter, const byte sproff, const byte left_tileidx, const byte right_tileidx, const byte xpos, const byte ypos, const byte attrs, const byte flags) {
  struct_xyr02 result;

  const bool flip_horz = (flags & 2) != 0;
  draw_sprite_row(0, sproff, left_tileidx, right_tileidx, xpos, ypos, attrs, flip_horz);

  result.x = tile_counter + 2;
  result.y = sproff + 8;
  result.r02 = ypos + 8;
  return result;
}


