#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SMB_audio;

bool SMB_audio_init(struct SMB_audio *audio, int32_t samplerate, int32_t maxlatency_ms);
void SMB_audio_fini(struct SMB_audio *audio);
size_t SMB_audio_size();
void SMB_audio_write_register(struct SMB_audio *audio, uint16_t addr, uint8_t data);
void SMB_audio_end_frame(struct SMB_audio *audio);

#ifdef __cplusplus
}
#endif

#endif
