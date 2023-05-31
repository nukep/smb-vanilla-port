void Start();
void NonMaskableInterrupt();

void UpdateScreen(const byte*);
void WriteNTAddr(byte);
void DrawTitleScreen();
byte InitializeMemory(byte);
bool TransposePlayers();
