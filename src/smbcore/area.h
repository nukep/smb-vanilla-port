#ifndef SMBCORE_AREA_H
#define SMBCORE_AREA_H

// TODO: make these non-static once games are compiled standalone

static void LoadAreaPointer(void);
static void GetAreaDataAddrs(void);

#ifdef SMB2J_MODE
static void AltHard_GetAreaDataAddrs(void);
#endif

static void AreaParserTaskControl(void);
static void AreaParserTaskHandler(void);

#endif
