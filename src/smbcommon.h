#ifdef __cplusplus
extern "C" {
#endif

void sync_data(void);

void set_world_and_level(u8 world, u8 level);

void update_screen(const u8 *buf, const u16 length);
void WriteNTAddr(u8);
u8 InitializeMemory(u8);
void ReadJoypads();
void ReadPortBits(u8 joynum);

void dectimers();
void update_prng(u8 *prng);

#ifdef __cplusplus
}
#endif
