#ifndef SMBCORE_CTX_H
#define SMBCORE_CTX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../mario.h"
#include "../base.h"

#include "interface.h"

#ifdef SMB1_MODE
#include "smb1.h"
#include "smb_romarrays.h"
#endif

#ifdef SMB2J_MODE
#include "smb2j.h"
#include "smb2j_romarrays.h"
#endif

#include "vars.h"
#include "consts.h"
#include "types.h"

#ifdef __cplusplus
}
#endif

#endif
