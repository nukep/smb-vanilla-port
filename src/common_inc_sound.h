// The sound engine for SMB1 for SMB2J are nearly identical, with the exception of SMB2J's Wind and Skid sfxs.
// There's also the FDS alternate sound engine, but that's only used for SMB2J's ending (not included here).

#ifdef SMB2J_MODE
static void PlaySkidSfx(void);
static void ContinueSkidSfx(void);
static void PlayWindSfx(void);
static void ContinueWindSfx(void);
#endif

static void SoundEngine(void);
static void SkipSoundSubroutines(void);
static void Dump_Squ1_Regs(byte param_1,byte param_2);
static bool PlaySqu1Sfx(byte param_1,byte param_2,byte param_3);
static struct_axyz SetFreq_Squ1(byte param_1);
static struct_ayz Dump_Freq_Regs(byte param_1, byte channel);
static void Dump_Sq2_Regs(byte param_1,byte param_2);
static void PlaySqu2Sfx(byte param_1,byte param_2,byte param_3);
static struct_axyz SetFreq_Squ2(byte param_1);
static void SetFreq_Tri(byte param_1);
static void PlayFlagpoleSlide(void);
static void PlaySmallJump(void);
static void PlayBigJump(void);
static void ContinueSndJump(void);
static void PlayFireballThrow(void);
static void PlayBump(void);
static void ContinueBumpThrow(void);
static void Square1SfxHandler(void);
static void PlaySwimStomp(void);
static void ContinueSwimStomp(void);
static void PlaySmackEnemy(void);
static void ContinueSmackEnemy(void);
static void StopSquare1Sfx(void);
static void PlayPipeDownInj(void);
static void ContinuePipeDownInj(void);
static void PlayCoinGrab(void);
static void PlayTimerTick(void);
static void ContinueCGrabTTick(void);
static void PlayBlast(void);
static void ContinueBlast(void);
static void PlayPowerUpGrab(void);
static void ContinuePowerUpGrab(void);
static void DecrementSfx2Length(void);
static void StopSquare2Sfx(void);
static void Square2SfxHandler(void);
static void PlayBowserFall(void);
static void ContinueBowserFall(void);
static void PlayExtraLife(void);
static void ContinueExtraLife(void);
static void PlayGrowPowerUp(void);
static void PlayGrowVine(void);
static void ContinueGrowItems(void);

static void PlayBrickShatter(void);
static void ContinueBrickShatter(void);
static void PlayNoiseSfx(byte vol, byte noise_period);
static void DecrementSfx3Length(void);
static void NoiseSfxHandler(void);
static void PlayBowserFlame(void);
static void ContinueBowserFlame(void);

static void ContinueMusic(void);
static void MusicHandler(void);
static void LoadEventMusic(byte param_1);
static void LoadAreaMusic(byte param_1);
static void HandleAreaMusicLoopB(byte param_1);
static void FindAreaMusicHeader(byte param_1);
static void FindEventMusicHeader(byte param_1,byte param_2);
static void LoadHeader(byte param_1);
static void HandleSquare2Music(void);
static void HandleSquare1Music(void);
static void HandleTriangleMusic(void);
static void HandleNoiseMusic(void);
static void PlayBeat(byte param_1,byte param_2,byte param_3);
static struct_axy AlternateLengthHandler(byte param_1);
static struct_ayi ProcessLengthData(byte param_1);
static struct_axy LoadControlRegs(void);
static byte LoadEnvelopeData(byte param_1);


#define BIT(v, n) (((v) & (1 << n)) != 0)

// SMB:f38d, SM2MAIN:d35d
// Signature: [A, X] -> [A, Y, Z]

struct_ayz Dump_Freq_Regs(byte param_1, byte channel) {
  // channel is always 0, 4, or 8

  struct_ayz ret;

  // apu_sq1_lo, apu_sq1_hi
  // apu_sq2_lo, apu_sq2_hi
  // apu_tri_lo, apu_tri_hi

  if (FreqRegLookupTbl[param_1 + 1] != 0) {
    byte a = FreqRegLookupTbl[param_1 + 1];
    byte b = FreqRegLookupTbl[param_1] | 8;

    switch (channel) {
    case 0: apu_sq1_lo(a); apu_sq1_hi(b); break;
    case 4: apu_sq2_lo(a); apu_sq2_hi(b); break;
    case 8: apu_tri_lo(a); apu_tri_hi(b); break;
    default:
      break;
    }
    ret.a = b;
    ret.y = param_1;
    ret.z = false;
    return ret;
  } else {
    ret.a = FreqRegLookupTbl[param_1 + 1];
    ret.y = param_1;
    ret.z = true;
    return ret;
  }
}


// SMB:f63b, SM2MAIN:d644
// Signature: [] -> []
void PlayBrickShatter(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 0x20;
  ContinueBrickShatter();
}

// SMB:f640, SM2MAIN:d64b
// Signature: [] -> []
void ContinueBrickShatter(void) {
  if ((Noise_SfxLenCounter & 1) == 0) {
    DecrementSfx3Length();
  } else {
    PlayNoiseSfx(BrickShatterEnvData[Noise_SfxLenCounter >> 1],
                 BrickShatterFreqData[Noise_SfxLenCounter >> 1]);
  }
}

// SMB:f64d, SM2MAIN:d658
// Signature: [A, X] -> []
void PlayNoiseSfx(byte vol, byte noise_period) {
  apu_noise_vol(vol);
  apu_noise_lo(noise_period);
  apu_noise_hi(0x18);
  DecrementSfx3Length();
}

// SMB:f658, SM2MAIN:d663
// Signature: [] -> []
void DecrementSfx3Length(void) {
  Noise_SfxLenCounter -= 1;
  if (Noise_SfxLenCounter == 0) {
    apu_noise_vol(0xf0);
    if (SMB2J_ONLY) {
      apu_tri_linear(0);
    }
    NoiseSoundBuffer = 0;
  }
}

// SMB:f680, SM2MAIN:d695
// Signature: [] -> []
void PlayBowserFlame(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 0x40;
  ContinueBowserFlame();
}

// SMB:f685, SM2MAIN:d69c
// Signature: [] -> []
void ContinueBowserFlame(void) {
  byte vol = WaterEventMusEnvData[(Noise_SfxLenCounter >> 1) + 0x27];
  if (SMB1_ONLY && vol == 0) {
    ContinueMusic();
    return;
  }
  PlayNoiseSfx(vol, 0xf);
}

#ifdef SMB2J_MODE

// SM2MAIN:d629
// Signature: [] -> []
void PlaySkidSfx(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 6;
  ContinueSkidSfx();
}

// SM2MAIN:d630
// Signature: [] -> []
void ContinueSkidSfx(void) {
  apu_tri_lo(BrickShatterFreqData[Noise_SfxLenCounter + 0xf]);
  apu_tri_linear(0x18);
  apu_tri_hi(0x18);
  DecrementSfx3Length();
}

// SM2MAIN:d6a8
// Signature: [] -> []
void PlayWindSfx(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 0xc0;

  if (BIT(NoiseSoundQueue, 3)) {
    // This branch never happens in practice
    ContinueWindSfx();
  }
}

// SM2MAIN:d6af
// Signature: [] -> []
void ContinueWindSfx(void) {
  // SMBJ tested for the NoiseSoundQueue bit here, but it tests for either bit 2 or 3, depending on who called it.
  // We moved these checks to the callers
  PlayNoiseSfx(WindFreqEnvData[Noise_SfxLenCounter >> 3] >> 4 | 0x10,
               WindFreqEnvData[Noise_SfxLenCounter >> 3] & 0xf | 0x10);
}
#endif

#ifdef SMB1_MODE

// SMB:f667
// Signature: [] -> []
void NoiseSfxHandler(void) {
  byte nsq = NoiseSoundQueue;

  // The original game modified (bit-shifted) NoiseSoundQueue to test the bits, but the caller resets the value to 0 anyway, so we ignore changing it here

  if (nsq != 0) {
    NoiseSoundBuffer = nsq;
    if (BIT(nsq, 0)) { return PlayBrickShatter(); }
    if (BIT(nsq, 1)) { return PlayBowserFlame(); }
  }
  byte nsb = NoiseSoundBuffer;
  if (nsb != 0) {
    if (BIT(nsb, 0)) { return ContinueBrickShatter(); }
    if (BIT(nsb, 1)) { return ContinueBowserFlame(); }
  }
  return;
}

#else

// SM2MAIN:d677
// Signature: [] -> []
void NoiseSfxHandler(void) {
  byte nsb = NoiseSoundBuffer;
  byte nsq = NoiseSoundQueue;

  if (BIT(nsb, 7)) { return ContinueSkidSfx(); }
  if (BIT(nsq, 7)) {
    NoiseSoundBuffer = nsq;
    return PlaySkidSfx();
  }

  // The original game modified (bit-shifted) NoiseSoundQueue to test the bits, but the caller resets the value to 0 anyway, so we ignore changing it here

  if (BIT(nsq, 0)) {
    NoiseSoundBuffer = nsq;
    return PlayBrickShatter();
  }
  if (BIT(nsb, 0)) { return ContinueBrickShatter(); }

  if (BIT(nsq, 1)) {
    NoiseSoundBuffer = nsq;
    return PlayBowserFlame();
  }
  if (BIT(nsb, 1)) { return ContinueBowserFlame(); }

  // yes, these are in the opposite order
  if (BIT(nsb, 2) && BIT(nsq, 2)) { return ContinueWindSfx(); }
  if (BIT(nsq, 2)) {
    NoiseSoundBuffer = nsq;
    return PlayWindSfx();
  }
}

#endif


// SMB:f2d0
// SM2MAIN:d2a0
// Signature: [] -> []
void SoundEngine(void) {
  if (OperMode == 0) {
    apu_snd_chn(0);
    return;
  }
  apu_framecounter_ctrl(0xff);
  apu_snd_chn(0xf);
  if ((PauseModeFlag == 0) && (PauseSoundQueue != 1)) {
    Square1SfxHandler();
    Square2SfxHandler();
    NoiseSfxHandler();
    MusicHandler();
    AreaMusicQueue = 0;
    EventMusicQueue = 0;
    SkipSoundSubroutines();
    return;
  }
  if (PauseSoundBuffer == 0) {
    if (PauseSoundQueue == 0) {
      SkipSoundSubroutines();
      return;
    }
    PauseSoundBuffer = PauseSoundQueue;
    PauseModeFlag = PauseSoundQueue;
    Square1SoundBuffer = 0;
    Square2SoundBuffer = 0;
    NoiseSoundBuffer = 0;
    apu_snd_chn(0);
    apu_snd_chn(0xf);
    Squ1_SfxLenCounter = 0x2a;

    // Pause sound, 1/4 (E note)
    PlaySqu1Sfx(0x44, 0x84, 0x7f);
  } else if (Squ1_SfxLenCounter == 0x24) {
    // Pause sound, 2/4 (C note)
    PlaySqu1Sfx(0x64, 0x84, 0x7f);
  } else if (Squ1_SfxLenCounter == 0x1e) {
    // Pause sound, 3/4 (E note)
    PlaySqu1Sfx(0x44, 0x84, 0x7f);
  } else if (Squ1_SfxLenCounter == 0x18) {
    // Pause sound, 4/4 (C note)
    PlaySqu1Sfx(0x64, 0x84, 0x7f);
  }

  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter != 0) {
    SkipSoundSubroutines();
    return;
  }
  apu_snd_chn(0);
  if (PauseSoundBuffer == 2) {
    PauseModeFlag = 0;
  }
  PauseSoundBuffer = 0;
  SkipSoundSubroutines();
  return;
}

// SMB:f35d
// SM2MAIN:d32d
// Signature: [] -> []
void SkipSoundSubroutines(void) {
  Square1SoundQueue = 0;
  Square2SoundQueue = 0;
  NoiseSoundQueue = 0;
  PauseSoundQueue = 0;

  byte prev_counter = DAC_Counter;

  if ((AreaMusicBuffer & 3) != 0 && DAC_Counter < 0x30) {
    DAC_Counter += 1;
  } else if ((AreaMusicBuffer & 3) == 0 && DAC_Counter > 0) {
    DAC_Counter -= 1;
  }

  apu_dmc_raw(prev_counter);
}

// SMB:f381
// SM2MAIN:d351
// Signature: [X, Y] -> []
void Dump_Squ1_Regs(byte param_1, byte param_2) {
  apu_sq1_sweep(param_2);
  apu_sq1_vol(param_1);
  return;
}

// SMB:f388
// SM2MAIN:d358
// Signature: [A, X, Y] -> [Z]
bool PlaySqu1Sfx(byte param_1, byte param_2, byte param_3) {
  struct_axyz sVar1;

  Dump_Squ1_Regs(param_2, param_3);
  sVar1 = SetFreq_Squ1(param_1);
  return sVar1.z;
}

// SMB:f38b
// SM2MAIN:d35b
// Signature: [A] -> [A, X, Y, Z]
struct_axyz SetFreq_Squ1(byte param_1) {
  struct_axyz sVar2;
  struct_ayz sVar3;
  undefined uVar1;

  uVar1 = 0;
  sVar3 = Dump_Freq_Regs(param_1, 0);
  sVar2.a = sVar3.a;
  sVar2.x = uVar1;
  sVar2.y = (char)SUBPIECE(sVar3, 1, 2);
  sVar2.z = (bool)(char)((ushort)SUBPIECE(sVar3, 1, 2) >> 8);
  return sVar2;
}

// SMB:f39f
// SM2MAIN:d36f
// Signature: [X, Y] -> []
void Dump_Sq2_Regs(byte param_1, byte param_2) {
  apu_sq2_vol(param_1);
  apu_sq2_sweep(param_2);
  return;
}

// SMB:f3a6
// SM2MAIN:d376
// Signature: [A, X, Y] -> []
void PlaySqu2Sfx(byte param_1, byte param_2, byte param_3) {
  Dump_Sq2_Regs(param_2, param_3);
  SetFreq_Squ2(param_1);
  return;
}

// SMB:f3a9
// SM2MAIN:d379
// Signature: [A] -> [A, X, Y, Z]
struct_axyz SetFreq_Squ2(byte param_1) {
  struct_axyz sVar2;
  struct_ayz sVar3;

  sVar3 = Dump_Freq_Regs(param_1, 4);
  sVar2.a = sVar3.a;
  sVar2.x = 4;
  sVar2.y = sVar3.y;
  sVar2.z = sVar3.z;
  return sVar2;
}

// SMB:f3ad
// SM2MAIN:d37d
// Signature: [A] -> []
void SetFreq_Tri(byte param_1) {
  Dump_Freq_Regs(param_1, 8);
  return;
}

// SMB:f3bf
// SM2MAIN:d38f
// Signature: [] -> []
void PlayFlagpoleSlide(void) {
  char cVar1;

  Squ1_SfxLenCounter = 0x40;
  SetFreq_Squ1(0x62);
  cVar1 = 0;
  Dump_Squ1_Regs(0x99, 0xbc);
  if (cVar1 != 0) {
    PlayFireballThrow();
    return;
  }
  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter == 0) {
    StopSquare1Sfx();
    return;
  }
  return;
}

// SMB:f3cd
// SM2MAIN:d39d
// Signature: [] -> []
void PlaySmallJump(void) {
  PlaySqu1Sfx(0x26, 0x82, 0xa7);
  Squ1_SfxLenCounter = 0x28;
  ContinueSndJump();
  return;
}

// SMB:f3d1
// SM2MAIN:d3a1
// Signature: [] -> []
void PlayBigJump(void) {
  PlaySqu1Sfx(0x18, 0x82, 0xa7);
  Squ1_SfxLenCounter = 0x28;
  ContinueSndJump();
  return;
}

// SMB:f3df
// SM2MAIN:d3af
// Signature: [] -> []
void ContinueSndJump(void) {
  byte bVar1;
  byte bVar2;
  char cVar3;

  if (Squ1_SfxLenCounter == 0x25) {
    bVar1 = 0x5f;
    bVar2 = 0xf6;
  } else {
    if (Squ1_SfxLenCounter != 0x20) {
      goto DecJpFPS;
    }
    bVar1 = 0x48;
    bVar2 = 0xbc;
  }
  cVar3 = 0;
  Dump_Squ1_Regs(bVar1, bVar2);
  if (cVar3 != 0) {
    PlayFireballThrow();
    return;
  }
DecJpFPS:
  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter != 0) {
    return;
  }
  StopSquare1Sfx();
  return;
}

// SMB:f3f9
// SM2MAIN:d3c9
// Signature: [] -> []
void PlayFireballThrow(void) {
  Squ1_SfxLenCounter = 5;
  PlaySqu1Sfx(0xc, 0x9e, 0x99);
  ContinueBumpThrow();
  return;
}

// SMB:f3ff
// SM2MAIN:d3cf
// Signature: [] -> []
void PlayBump(void) {
  Squ1_SfxLenCounter = 10;
  PlaySqu1Sfx(0xc, 0x9e, 0x93);
  ContinueBumpThrow();
  return;
}

// SMB:f40d
// SM2MAIN:d3dd
// Signature: [] -> []
void ContinueBumpThrow(void) {
  if (Squ1_SfxLenCounter == 6) {
    apu_sq1_sweep(0xbb);
  }
  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter == 0) {
    StopSquare1Sfx();
    return;
  }
  return;
}

// SMB:f41b
// SM2MAIN:d3eb
// Signature: [] -> []
void Square1SfxHandler(void) {
  byte ssq = Square1SoundQueue;

  // The original game modified (bit-shifted) Square1SoundQueue to test the bits, but the caller resets the value to 0 anyway, so we ignore changing it here

  if (ssq != 0) {
    Square1SoundBuffer = ssq;
    if (BIT(ssq, 7)) { return PlaySmallJump(); }
    if (BIT(ssq, 0)) { return PlayBigJump(); }
    if (BIT(ssq, 1)) { return PlayBump(); }
    if (BIT(ssq, 2)) { return PlaySwimStomp(); }
    if (BIT(ssq, 3)) { return PlaySmackEnemy(); }
    if (BIT(ssq, 4)) { return PlayPipeDownInj(); }
    if (BIT(ssq, 5)) { return PlayFireballThrow(); }
    if (BIT(ssq, 6)) { return PlayFlagpoleSlide(); }
    return;
  }

  // Square1SoundQueue is 0
  // Continuing to play previous sfx

  byte ssb = Square1SoundBuffer;
  if (ssb != 0) {
    if (BIT(ssb, 7)) { return ContinueSndJump(); }
    if (BIT(ssb, 0)) { return ContinueSndJump(); }
    if (BIT(ssb, 1)) { return ContinueBumpThrow(); }
    if (BIT(ssb, 2)) { return ContinueSwimStomp(); }
    if (BIT(ssb, 3)) { return ContinueSmackEnemy(); }
    if (BIT(ssb, 4)) { return ContinuePipeDownInj(); }
    if (BIT(ssb, 5)) { return ContinueBumpThrow(); }
    if (BIT(ssb, 6)) {
      Squ1_SfxLenCounter -= 1;
      if (Squ1_SfxLenCounter == 0) {
        StopSquare1Sfx();
      }
    }
  }
}

// SMB:f45b
// SM2MAIN:d42b
// Signature: [] -> []
void PlaySwimStomp(void) {
  Squ1_SfxLenCounter = 0xe;
  PlaySqu1Sfx(0x26, 0x9e, 0x9c);
  ContinueSwimStomp();
  return;
}

// SMB:f469
// SM2MAIN:d439
// Signature: [] -> []
void ContinueSwimStomp(void) {
  apu_sq1_vol(SwimStompEnvelopeData[Squ1_SfxLenCounter - 1]);
  if (Squ1_SfxLenCounter == 6) {
    apu_sq1_lo(0x9e);
  }
  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter == 0) {
    StopSquare1Sfx();
    return;
  }
  return;
}

// SMB:f47d
// SM2MAIN:d44d
// Signature: [] -> []
void PlaySmackEnemy(void) {
  bool bVar1;

  Squ1_SfxLenCounter = 0xe;
  bVar1 = PlaySqu1Sfx(0x28, 0x9f, 0xcb);
  if (bVar1) {
    ContinueSmackEnemy();
    return;
  }
  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter == 0) {
    StopSquare1Sfx();
    return;
  }
  return;
}

// SMB:f48d
// SM2MAIN:d45d
// Signature: [] -> []
void ContinueSmackEnemy(void) {
  byte bVar1;

  if (Squ1_SfxLenCounter == 8) {
    apu_sq1_lo(0xa0);
    bVar1 = 0x9f;
  } else {
    bVar1 = 0x90;
  }
  apu_sq1_vol(bVar1);
  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter != 0) {
    return;
  }
  StopSquare1Sfx();
  return;
}

// SMB:f4a7
// SM2MAIN:d477
// Signature: [] -> []
void StopSquare1Sfx(void) {
  Square1SoundBuffer = 0;
  apu_snd_chn(0xe);
  apu_snd_chn(0xf);
  return;
}

// SMB:f4b6
// SM2MAIN:d486
// Signature: [] -> []
void PlayPipeDownInj(void) {
  Squ1_SfxLenCounter = 0x2f;
  ContinuePipeDownInj();
  return;
}

// SMB:f4bb
// SM2MAIN:d48b
// Signature: [] -> []
void ContinuePipeDownInj(void) {
  if (((!(bool)(Squ1_SfxLenCounter & 1)) && (!(bool)(Squ1_SfxLenCounter >> 1 & 1)))
      && ((Squ1_SfxLenCounter >> 2 & 2) != 0)) {
    PlaySqu1Sfx(0x44, 0x9a, 0x91);
  }
  Squ1_SfxLenCounter -= 1;
  if (Squ1_SfxLenCounter == 0) {
    StopSquare1Sfx();
    return;
  }
  return;
}

// SMB:f518
// SM2MAIN:d4e8
// Signature: [] -> []
void PlayCoinGrab(void) {
  Squ2_SfxLenCounter = 0x35;
  PlaySqu2Sfx(0x42, 0x8d, 0x7f);
  ContinueCGrabTTick();
  return;
}

// SMB:f51e
// SM2MAIN:d4ee
// Signature: [] -> []
void PlayTimerTick(void) {
  Squ2_SfxLenCounter = 6;
  PlaySqu2Sfx(0x42, 0x98, 0x7f);
  ContinueCGrabTTick();
  return;
}

// SMB:f52c
// SM2MAIN:d4fc
// Signature: [] -> []
void ContinueCGrabTTick(void) {
  if (Squ2_SfxLenCounter == 0x30) {
    apu_sq2_lo(0x54);
  }
  DecrementSfx2Length();
  return;
}

// SMB:f53a
// SM2MAIN:d50a
// Signature: [] -> []
void PlayBlast(void) {
  Squ2_SfxLenCounter = 0x20;
  PlaySqu2Sfx(0x5e, 0x9f, 0x94);
  DecrementSfx2Length();
  return;
}

// SMB:f545
// SM2MAIN:d515
// Signature: [] -> []
void ContinueBlast(void) {
  if (Squ2_SfxLenCounter != 0x18) {
    DecrementSfx2Length();
    return;
  }
  PlaySqu2Sfx(0x18, 0x9f, 0x93);
  DecrementSfx2Length();
  return;
}

// SMB:f552
// SM2MAIN:d522
// Signature: [] -> []
void PlayPowerUpGrab(void) {
  Squ2_SfxLenCounter = 0x36;
  ContinuePowerUpGrab();
  return;
}

// SMB:f557
// SM2MAIN:d527
// Signature: [] -> []
void ContinuePowerUpGrab(void) {
  if ((bool)(Squ2_SfxLenCounter & 1)) {
    DecrementSfx2Length();
    return;
  }
  PlaySqu2Sfx(ExtraLifeFreqData[(Squ2_SfxLenCounter >> 1) + 5], 0x5d, 0x7f);
  DecrementSfx2Length();
  return;
}

// SMB:f568
// SM2MAIN:d538
// Signature: [] -> []
void DecrementSfx2Length(void) {
  Squ2_SfxLenCounter -= 1;
  if (Squ2_SfxLenCounter == 0) {
    Square2SoundBuffer = 0;
    StopSquare2Sfx();
    return;
  }
  return;
}

// SMB:f571
// SM2MAIN:d541
// Signature: [] -> []
void StopSquare2Sfx(void) {
  apu_snd_chn(0xd);
  apu_snd_chn(0xf);
  return;
}

// SMB:f57c
// SM2MAIN:d54c
// Signature: [] -> []
void Square2SfxHandler(void) {
  if (BIT(Square2SoundBuffer, 6)) { return ContinueExtraLife(); }

  // The original game modified (bit-shifted) Square2SoundQueue to test the bits, but the caller resets the value to 0 anyway, so we ignore changing it here

  byte ssq = Square2SoundQueue;

  if (ssq != 0) {
    Square2SoundBuffer = ssq;
    if (BIT(ssq, 7)) { return PlayBowserFall(); }
    if (BIT(ssq, 0)) { return PlayCoinGrab(); }
    if (BIT(ssq, 1)) { return PlayGrowPowerUp(); }
    if (BIT(ssq, 2)) { return PlayGrowVine(); }
    if (BIT(ssq, 3)) { return PlayBlast(); }
    if (BIT(ssq, 4)) { return PlayTimerTick(); }
    if (BIT(ssq, 5)) { return PlayPowerUpGrab(); }
    if (BIT(ssq, 6)) { return PlayExtraLife(); }
  }

  byte ssb = Square2SoundBuffer;

  if (ssb == 0) {
    return;
  }
  if (BIT(ssb, 7)) { return ContinueBowserFall(); }
  if (BIT(ssb, 0)) { return ContinueCGrabTTick(); }
  if (BIT(ssb, 1)) { return ContinueGrowItems(); }
  if (BIT(ssb, 2)) { return ContinueGrowItems(); }
  if (BIT(ssb, 3)) { return ContinueBlast(); }
  if (BIT(ssb, 4)) { return ContinueCGrabTTick(); }
  if (BIT(ssb, 5)) { return ContinuePowerUpGrab(); }
  if (BIT(ssb, 6)) { return ContinueExtraLife(); }
}

// SMB:f5c8
// SM2MAIN:d598
// Signature: [] -> []
void PlayBowserFall(void) {
  Squ2_SfxLenCounter = 0x38;
  PlaySqu2Sfx(0x18, 0x9f, 0xc4);
  DecrementSfx2Length();
  return;
}

// SMB:f5d3
// SM2MAIN:d5a3
// Signature: [] -> []
void ContinueBowserFall(void) {
  if (Squ2_SfxLenCounter != 8) {
    DecrementSfx2Length();
    return;
  }
  PlaySqu2Sfx(0x5a, 0x9f, 0xa4);
  DecrementSfx2Length();
  return;
}

// SMB:f5e2
// SM2MAIN:d5b2
// Signature: [] -> []
void PlayExtraLife(void) {
  Squ2_SfxLenCounter = 0x30;
  ContinueExtraLife();
  return;
}

// SMB:f5e7
// SM2MAIN:d5b7
// Signature: [] -> []
void ContinueExtraLife(void) {
  byte bVar1;
  char cVar2;
  bool bVar3;

  cVar2 = 3;
  bVar1 = Squ2_SfxLenCounter;
  do {
    bVar3 = (bool)(bVar1 & 1);
    bVar1 >>= 1;
    if (bVar3) {
      DecrementSfx2Length();
      return;
    }
    cVar2 += -1;
  } while (cVar2 != 0);
  PlaySqu2Sfx(ExtraLifeFreqData[bVar1 - 1], 0x82, 0x7f);
  DecrementSfx2Length();
  return;
}

// SMB:f5fc
// SM2MAIN:d5cc
// Signature: [] -> []
void PlayGrowPowerUp(void) {
  Squ2_SfxLenCounter = 0x10;
  apu_sq2_sweep(0x7f);
  Sfx_SecondaryCounter = 0;
  ContinueGrowItems();
  return;
}

// SMB:f600
// SM2MAIN:d5d0
// Signature: [] -> []
void PlayGrowVine(void) {
  Squ2_SfxLenCounter = 0x20;
  apu_sq2_sweep(0x7f);
  Sfx_SecondaryCounter = 0;
  ContinueGrowItems();
  return;
}

// SMB:f60f
// SM2MAIN:d5df
// Signature: [] -> []
void ContinueGrowItems(void) {
  Sfx_SecondaryCounter += 1;
  if (Sfx_SecondaryCounter >> 1 != Squ2_SfxLenCounter) {
    apu_sq2_vol(0x9d);
    SetFreq_Squ2(PUp_VGrow_FreqData[Sfx_SecondaryCounter >> 1]);
    return;
  }
  Square2SoundBuffer = 0;
  StopSquare2Sfx();
  return;
}

// SMB:f691
// SM2MAIN:d6cd
// Signature: [] -> []
void ContinueMusic(void) {
  HandleSquare2Music();
  return;
}

// SMB:f694
// SM2MAIN:d6d0
// Signature: [] -> []
void MusicHandler(void) {
  if (EventMusicQueue != 0) {
    LoadEventMusic(EventMusicQueue);
    return;
  }
  if (AreaMusicQueue != 0) {
    LoadAreaMusic(AreaMusicQueue);
    return;
  }
  if ((EventMusicBuffer | AreaMusicBuffer) != 0) {
    ContinueMusic();
    return;
  }
  return;
}

// SMB:f6a4
// SM2MAIN:d6e0
// Signature: [A] -> []
void LoadEventMusic(byte param_1) {
  EventMusicBuffer = param_1;
  if (param_1 == 1) {
    StopSquare1Sfx();
    StopSquare2Sfx();
  }
  AreaMusicBuffer_Alt = AreaMusicBuffer;
  NoteLengthTblAdder = 0;
  AreaMusicBuffer = 0;

  if (param_1 == 0x40) {
    // The time-running-out music. Make the music play faster!
    NoteLengthTblAdder = 8;
  }
  FindEventMusicHeader(param_1, 0);
}

// SMB:f6c8
// SM2MAIN:d704
// Signature: [A] -> []
void LoadAreaMusic(byte param_1) {
  if (param_1 == 4) {
    StopSquare1Sfx();
  }
  GroundMusicHeaderOfs = 0x10;
  HandleAreaMusicLoopB(param_1);
  return;
}

// SMB:f6d4
// SM2MAIN:d710
// Signature: [A] -> []
void HandleAreaMusicLoopB(byte param_1) {
  EventMusicBuffer = 0;
  AreaMusicBuffer = param_1;
  if (param_1 != 1) {
    FindAreaMusicHeader(param_1);
    return;
  }
  GroundMusicHeaderOfs += 1;
  if (GroundMusicHeaderOfs != 0x32) {
    LoadHeader(GroundMusicHeaderOfs);
    return;
  }
  GroundMusicHeaderOfs = 0x11;
  HandleAreaMusicLoopB(1);
  return;
}

// SMB:f6ed
// SM2MAIN:d729
// Signature: [A] -> []
void FindAreaMusicHeader(byte param_1) {
  MusicOffset_Square2 = 8;
  FindEventMusicHeader(param_1, 8);
  return;
}

// SMB:f6f1
// SM2MAIN:d72d
// Signature: [A, Y] -> []
void FindEventMusicHeader(byte param_1, byte param_2) {
  // The second argument is either 0 or 8 in practice.

  assert_smb_crashbug(param_1 != 0, "An infinite loop would've occurred in the original game");

  while (1) {
    param_2 += 1;
    if (param_1 & 1) {
      break;
    }
    param_1 >>= 1;
  }

  // 1 to 16 (inclusive) in practice
  LoadHeader(param_2);
}

// SMB:f6f5
// SM2MAIN:d731
// Signature: [Y] -> []
void LoadHeader(byte param_1) {
  byte bVar1;

  bVar1 = MusicHeaderData[param_1 - 1];
  NoteLenLookupTblOfs = MusicHeaderData[bVar1];
  MusicData.lo = MusicHeaderData[bVar1 + 1];
  MusicData.hi = MusicHeaderData[bVar1 + 2];
  MusicOffset_Triangle = MusicHeaderData[bVar1 + 3];
  MusicOffset_Square1 = MusicHeaderData[bVar1 + 4];
  MusicOffset_Noise = MusicHeaderData[bVar1 + 5];
  Squ2_NoteLenCounter = 1;
  Squ1_NoteLenCounter = 1;
  Tri_NoteLenCounter = 1;
  Noise_BeatLenCounter = 1;
  MusicOffset_Square2 = 0;
  AltRegContentFlag = 0;
  apu_snd_chn(0xb);
  apu_snd_chn(0xf);
  NoiseDataLoopbackOfs = MusicOffset_Noise;
  HandleSquare2Music();
  return;
}

// SMB:f73a
// SM2MAIN:d776
// Signature: [] -> []
void HandleSquare2Music(void) {
  byte bVar1;
  struct_ayi sVar4;
  struct_axyz sVar5;
  struct_axy sVar6;

  Squ2_NoteLenCounter -= 1;
  if (Squ2_NoteLenCounter == 0) {
    bVar1 = MusicData[MusicOffset_Square2++];
    if (bVar1 == 0) {
      bVar1 = EventMusicBuffer;
      if ((EventMusicBuffer != 0x40) || (bVar1 = AreaMusicBuffer_Alt, AreaMusicBuffer_Alt == 0)) {
        if ((bVar1 & 4) != 0) {
          LoadEventMusic(bVar1 & 4);
          return;
        }
        bVar1 = AreaMusicBuffer & 0x5f;
        if (bVar1 == 0) {
          AreaMusicBuffer = 0;
          EventMusicBuffer = 0;
          apu_tri_linear(0);
          apu_sq1_vol(0x90);
          apu_sq2_vol(0x90);
          return;
        }
      }
      HandleAreaMusicLoopB(bVar1);
      return;
    }
    if (bVar1 >= 0x80) {
      sVar4 = ProcessLengthData(bVar1);
      Squ2_NoteLenBuffer = sVar4.a;
      bVar1 = MusicData[MusicOffset_Square2++];
    }
    if (Square2SoundBuffer == 0) {
      sVar5 = SetFreq_Squ2(bVar1);
      if (!sVar5.z) {
        sVar6 = LoadControlRegs();
        Squ2_EnvelopeDataCtrl = sVar6.a;
        Dump_Sq2_Regs(sVar6.x, sVar6.y);
      } else {
        Squ2_EnvelopeDataCtrl = sVar5.a;
        Dump_Sq2_Regs(sVar5.x, sVar5.y);
      }
    }
    Squ2_NoteLenCounter = Squ2_NoteLenBuffer;
  }
  if (Square2SoundBuffer != 0) {
    HandleSquare1Music();
    return;
  }
  if ((EventMusicBuffer & 0x91) != 0) {
    HandleSquare1Music();
    return;
  }
  apu_sq2_vol(LoadEnvelopeData(Squ2_EnvelopeDataCtrl));
  apu_sq2_sweep(0x7f);
  if (Squ2_EnvelopeDataCtrl != 0) {
    Squ2_EnvelopeDataCtrl -= 1;
  }
  HandleSquare1Music();
  return;
}

// SMB:f7bc
// SM2MAIN:d7f8
// Signature: [] -> []
void HandleSquare1Music(void) {
  byte bVar2;
  byte bVar3;
  byte bVar4;
  struct_axyz sVar5;
  struct_axy sVar6;

  if (MusicOffset_Square1 == 0) {
    HandleTriangleMusic();
    return;
  }
  Squ1_NoteLenCounter -= 1;
  if (Squ1_NoteLenCounter == 0) {
    while (MusicData[MusicOffset_Square1] == 0) {
      apu_sq1_vol(0x83);
      apu_sq1_sweep(0x94);
      AltRegContentFlag = 0x94;
      MusicOffset_Square1 += 1;
    }
    sVar6 = AlternateLengthHandler(MusicData[MusicOffset_Square1++]);
    Squ1_NoteLenCounter = sVar6.a;
    if (Square1SoundBuffer != 0) {
      HandleTriangleMusic();
      return;
    }
    sVar5 = SetFreq_Squ1(sVar6.x & 0x3e);
    if (!sVar5.z) {
      sVar6 = LoadControlRegs();
      Squ1_EnvelopeDataCtrl = sVar6.a;
      Dump_Squ1_Regs(sVar6.x, sVar6.y);
    } else {
      Squ1_EnvelopeDataCtrl = sVar5.a;
      Dump_Squ1_Regs(sVar5.x, sVar5.y);
    }
  }
  if (Square1SoundBuffer != 0) {
    HandleTriangleMusic();
    return;
  }
  if ((EventMusicBuffer & 0x91) == 0) {
    apu_sq1_vol(LoadEnvelopeData(Squ1_EnvelopeDataCtrl));
    if (Squ1_EnvelopeDataCtrl != 0) {
      Squ1_EnvelopeDataCtrl -= 1;
    }
  }
  if (AltRegContentFlag == 0) {
    apu_sq1_sweep(0x7f);
  } else {
    apu_sq1_sweep(AltRegContentFlag);
  }
  HandleTriangleMusic();
  return;
}

// SMB:f81a
// SM2MAIN:d856
// Signature: [] -> []
void HandleTriangleMusic(void) {
  byte bVar1;
  byte bVar2;
  struct_ayi sVar3;

  Tri_NoteLenCounter -= 1;
  if (Tri_NoteLenCounter != 0) {
    HandleNoiseMusic();
    return;
  }
  bVar2 = MusicData[MusicOffset_Triangle++];
  if (bVar2 == 0) {
    apu_tri_linear(0);
    HandleNoiseMusic();
    return;
  }
  if (bVar2 >= 0x80) {
    sVar3 = ProcessLengthData(bVar2);
    Tri_NoteLenBuffer = sVar3.a;
    apu_tri_linear(0x1f);
    bVar2 = MusicData[MusicOffset_Triangle++];
    if (bVar2 == 0) {
      apu_tri_linear(0);
      HandleNoiseMusic();
      return;
    }
  }
  SetFreq_Tri(bVar2);
  Tri_NoteLenCounter = Tri_NoteLenBuffer;
  if (((EventMusicBuffer & 0x6e) == 0) && ((AreaMusicBuffer & 10) == 0)) {
    HandleNoiseMusic();
    return;
  }
  if (Tri_NoteLenBuffer >= 0x12){
    apu_tri_linear(0xff);
  } else if ((EventMusicBuffer & 8) == 0) {
    apu_tri_linear(0x1f);
  } else {
    apu_tri_linear(0x0f);
  }
  HandleNoiseMusic();
}

// SMB:f86d
// SM2MAIN:d8a9
// Signature: [] -> []
void HandleNoiseMusic(void) {
  struct_axy sVar3;

  if ((AreaMusicBuffer & 0xf3) == 0) {
    return;
  }

  Noise_BeatLenCounter -= 1;

  if (Noise_BeatLenCounter != 0) {
    return;
  }

  // the original game would loop here forever if MusicData[MusicOffset_Noise] == 0 and MusicData[NoiseDataLoopbackOfs] == 0
  // we're getting rid of the loop for readability

  if (MusicData[MusicOffset_Noise] == 0) {
    assert_smb_crashbug(MusicData[NoiseDataLoopbackOfs] != 0, "An infinite loop would've occurred in the original game");

    MusicOffset_Noise = NoiseDataLoopbackOfs;
  }

  sVar3 = AlternateLengthHandler(MusicData[MusicOffset_Noise++]);

  Noise_BeatLenCounter = sVar3.a;
  if ((sVar3.x & 0x3e) == 0x30) {
    PlayBeat(0x1c, 3, 0x58);
  } else if ((sVar3.x & 0x3e) == 0x20) {
    PlayBeat(0x1c, 0xc, 0x18);
  } else if ((sVar3.x & 0x10) != 0) {
    PlayBeat(0x1c, 3, 0x18);
  } else {
    PlayBeat(0x10, sVar3.x, sVar3.y);
  }
}

// SMB:f8bb
// SM2MAIN:d8f7
// Signature: [A, X, Y] -> []
void PlayBeat(byte param_1, byte param_2, byte param_3) {
  apu_noise_vol(param_1);
  apu_noise_lo(param_2);
  apu_noise_hi(param_3);
}

// SMB:f8c5
// SM2MAIN:d901
// Signature: [A] -> [A, X, Y]
struct_axy AlternateLengthHandler(byte param_1) {
  struct_ayi sVar1;
  struct_axy sVar2;

  // Given the bitfield: abcdefgh
  // computes the value: 00000hab

  sVar1 = ProcessLengthData((param_1 << 2)&0x04 | (param_1 >> 6)&0x03);
  sVar2.y = sVar1.y;
  sVar2.a = sVar1.a;
  sVar2.x = param_1;
  return sVar2;
}

// SMB:f8cb
// SM2MAIN:d907
// Signature: [A] -> [A, Y]
struct_ayi ProcessLengthData(byte param_1) {
  byte offset;

  struct_ayi sVar2;

  // normally, the addition never carries. but we're keeping the oversight in, in case of glitches (confirm this?).
  // NoteLenLookupTblOffs is meant to be 0x00, 08, 10, 18, or 20.
  // NoteLengthTblAdder is either 0 or 8 (8 is when time is running out)

  offset = (param_1 & 7) + NoteLenLookupTblOfs + NoteLengthTblAdder;
  offset += CARRY1(param_1 & 7, NoteLenLookupTblOfs);

  sVar2.a = MusicLengthLookupTbl[offset];
  sVar2.y = offset;
  sVar2.i = (bool)0;
  return sVar2;
}

// SMB:f8d8
// SM2MAIN:d914
// Signature: [] -> [A, X, Y]
struct_axy LoadControlRegs(void) {
  struct_axy ret;

  ret.a = 0x04;
  ret.x = 0x82;
  ret.y = 0x7f;

  if ((EventMusicBuffer & 8) == 0) {
    if ((AreaMusicBuffer & 0x7d) == 0) {
      ret.a = 0x28;
    } else {
      ret.a = 0x08;
    }
  }

  return ret;
}

// SMB:f8f4
// SM2MAIN:d930
// Signature: [Y] -> [A]
byte LoadEnvelopeData(byte param_1) {
  if ((EventMusicBuffer & 8) != 0) {
    return EndOfCastleMusicEnvData[param_1];
  } else if ((AreaMusicBuffer & 0x7d) != 0) {
    return AreaMusicEnvData[param_1];
  } else {
    return WaterEventMusEnvData[param_1];
  }
}

#undef BIT