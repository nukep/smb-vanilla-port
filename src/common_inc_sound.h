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
        default: break;
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







#define BIT(v, n) (((v) & (1<<n)) != 0)

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
    if (BIT(nsq, 7)) { return PlaySkidSfx(nsq); }

    // Bitshifts were originally done to test for bits in 6502.
    // A side-effect is that it modifies the NoiseSoundQueue variable.

    NoiseSoundQueue >>= 1;
    if (BIT(nsq, 0)) { return PlayBrickShatter(nsq); }
    if (BIT(nsb, 0)) { return ContinueBrickShatter(); }

    NoiseSoundQueue >>= 1;
    if (BIT(nsq, 1)) { return PlayBowserFlame(nsq); }
    if (BIT(nsb, 1)) { return ContinueBowserFlame(); }

    // yes, these are in the opposite order
    if (BIT(nsb, 2)) { return ContinueWindSfx(); }
    NoiseSoundQueue >>= 1;
    if (BIT(nsq, 2)) { return PlayWindSfx(nsq); }
}

#endif

#undef BIT