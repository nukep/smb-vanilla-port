// SMB:f38d, SM2MAIN:d35d
// Signature: [A, X] -> [A, Y, Z]

static struct_ayz Dump_Freq_Regs(byte param_1, byte channel) {
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

static void NoiseSfxHandler(void);
static void PlayBrickShatter(void);
static void ContinueBrickShatter(void);
static void PlayNoiseSfx(byte vol, byte noise_period);
static void DecrementSfx3Length(void);
static void PlayBowserFlame(void);
static void ContinueBowserFlame(void);

// SMB:f63b, SM2MAIN:d644
// Signature: [] -> []
static void PlayBrickShatter(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 0x20;
  ContinueBrickShatter();
}

// SMB:f640, SM2MAIN:d64b
// Signature: [] -> []
static void ContinueBrickShatter(void) {
  if ((Noise_SfxLenCounter & 1) == 0) {
    DecrementSfx3Length();
  } else {
    PlayNoiseSfx(BrickShatterEnvData[Noise_SfxLenCounter >> 1],
                 BrickShatterFreqData[Noise_SfxLenCounter >> 1]);
  }
}

// SMB:f64d, SM2MAIN:d658
// Signature: [A, X] -> []
static void PlayNoiseSfx(byte vol, byte noise_period) {
  apu_noise_vol(vol);
  apu_noise_lo(noise_period);
  apu_noise_hi(0x18);
  DecrementSfx3Length();
}

// SMB:f658, SM2MAIN:d663
// Signature: [] -> []
static void DecrementSfx3Length(void) {
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
static void PlayBowserFlame(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 0x40;
  ContinueBowserFlame();
}

// SMB:f685, SM2MAIN:d69c
// Signature: [] -> []
static void ContinueBowserFlame(void) {
  byte vol = WaterEventMusEnvData[(Noise_SfxLenCounter >> 1) + 0x27];
  if (SMB1_ONLY && vol == 0) {
    ContinueMusic();
    return;
  }
  PlayNoiseSfx(vol, 0xf);
}

#ifdef SMB2J_MODE

static void PlaySkidSfx(void);
static void ContinueSkidSfx(void);
static void PlayWindSfx(void);
static void ContinueWindSfx(void);

// SM2MAIN:d629
// Signature: [] -> []
static void PlaySkidSfx(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 6;
  ContinueSkidSfx();
}

// SM2MAIN:d630
// Signature: [] -> []
static void ContinueSkidSfx(void) {
  apu_tri_lo(BrickShatterFreqData[Noise_SfxLenCounter + 0xf]);
  apu_tri_linear(0x18);
  apu_tri_hi(0x18);
  DecrementSfx3Length();
}

// SM2MAIN:d6a8
// Signature: [] -> []
static void PlayWindSfx(void) {
  // SMB2J set NoiseSoundBuffer here, but we moved that to the caller
  Noise_SfxLenCounter = 0xc0;
  ContinueWindSfx();
}

// SM2MAIN:d6af
// Signature: [] -> []
static void ContinueWindSfx(void) {
  byte bVar1;

  bVar1 = NoiseSoundQueue & 1;
  NoiseSoundQueue >>= 1;
  if (bVar1 != 0) {
    PlayNoiseSfx(WindFreqEnvData[Noise_SfxLenCounter >> 3] >> 4 | 0x10,
                 WindFreqEnvData[Noise_SfxLenCounter >> 3] & 0xf | 0x10);
  }
}
#endif

#define BIT(v, n) (((v) & (1 << n)) != 0)

#ifdef SMB1_MODE

// SMB:f667
// Signature: [] -> []
static void NoiseSfxHandler(void) {
  byte nsq = NoiseSoundQueue;

  // Bitshifts were originally done to test for bits in 6502.
  // A side-effect is that it modifies the NoiseSoundQueue variable.

  if (nsq != 0) {
    NoiseSoundBuffer = nsq;
    NoiseSoundQueue >>= 1;
    if (BIT(nsq, 0)) { return PlayBrickShatter(); }
    NoiseSoundQueue >>= 1;
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
static void NoiseSfxHandler(void) {
  byte nsb = NoiseSoundBuffer;
  byte nsq = NoiseSoundQueue;

  if (BIT(nsb, 7)) { return ContinueSkidSfx(); }
  if (BIT(nsq, 7)) {
    NoiseSoundBuffer = nsq;
    return PlaySkidSfx();
  }

  // Bitshifts were originally done to test for bits in 6502.
  // A side-effect is that it modifies the NoiseSoundQueue variable.

  NoiseSoundQueue >>= 1;
  if (BIT(nsq, 0)) {
    NoiseSoundBuffer = nsq;
    return PlayBrickShatter();
  }
  if (BIT(nsb, 0)) { return ContinueBrickShatter(); }

  NoiseSoundQueue >>= 1;
  if (BIT(nsq, 1)) {
    NoiseSoundBuffer = nsq;
    return PlayBowserFlame();
  }
  if (BIT(nsb, 1)) { return ContinueBowserFlame(); }

  // yes, these are in the opposite order
  if (BIT(nsb, 2)) { return ContinueWindSfx(); }
  NoiseSoundQueue >>= 1;
  if (BIT(nsq, 2)) {
    NoiseSoundBuffer = nsq;
    return PlayWindSfx();
  }
}

#endif

#undef BIT
