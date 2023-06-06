void Reset();
void NMI();

void UpdateScreen(const byte*);
void WriteNTAddr(byte);
byte InitializeMemory(byte);
void ReadJoypads();
void ReadPortBits(byte joynum);

// SMB only
#ifndef SMB2J_MODE

void DrawTitleScreen();
bool TransposePlayers();

#else

void ScrollScreen(byte);
struct_ayz LoadFiles();
void UpdateGamesBeaten();

#endif
