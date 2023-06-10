
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
