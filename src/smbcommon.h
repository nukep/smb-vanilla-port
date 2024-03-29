#ifdef __cplusplus
extern "C" {
#endif

void set_world_and_level(byte world, byte level);

void UpdateScreen(const byte *);
void WriteNTAddr(byte);
byte InitializeMemory(byte);
void ReadJoypads();
void ReadPortBits(byte joynum);

void dectimers();
void update_prng(byte *prng);

#ifdef __cplusplus
}
#endif
