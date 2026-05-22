#ifdef __cplusplus
extern "C" {
#endif

void sync_pointers(void);

void set_world_and_level(byte world, byte level);

void update_screen(const byte *buf, const u16 length);
void WriteNTAddr(byte);
byte InitializeMemory(byte);
void ReadJoypads();
void ReadPortBits(byte joynum);

void dectimers();
void update_prng(byte *prng);

#ifdef __cplusplus
}
#endif
