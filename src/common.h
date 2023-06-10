#ifdef __cplusplus
extern "C" {
#endif

void UpdateScreen(const byte*);
void WriteNTAddr(byte);
byte InitializeMemory(byte);
void ReadJoypads();
void ReadPortBits(byte joynum);

void dectimers();

#ifdef __cplusplus
}
#endif