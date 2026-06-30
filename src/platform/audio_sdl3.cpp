#include "audio.h"
#include <SDL3/SDL.h>
#include <stdio.h>

#include "nes_apu/Nes_Apu.h"

struct SMB_audio {
  Blip_Buffer *buf;
  Nes_Apu *apu;
  blip_time_t clock;
  int frame;
  SDL_AudioStream *audio_stream;
  uint64_t max_samples_to_be_queued;
  blip_sample_t *readsamples_tmpbuf;
  size_t readsamples_tmpbuf_count;
};

static int null_dmc_reader(int) {
  return 0x55;
}

bool SMB_audio_init(struct SMB_audio *audio, int32_t samplerate, int32_t maxlatency_ms) {
  audio->buf = new Blip_Buffer();
  audio->buf->clock_rate(1789773);
  audio->buf->set_sample_rate(samplerate);

  audio->apu = new Nes_Apu();
  audio->apu->dmc_reader = null_dmc_reader;
  audio->apu->set_output(audio->buf);

  audio->clock = 0;
  audio->frame = 0;
  audio->max_samples_to_be_queued = ((uint64_t)samplerate * (uint64_t)maxlatency_ms / 1000);
  // should be enough for 60fps, but adding more for contingency
  audio->readsamples_tmpbuf_count = (samplerate / 30);
  audio->readsamples_tmpbuf = (blip_sample_t*)malloc(audio->readsamples_tmpbuf_count * sizeof(blip_sample_t));

  if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
    printf("ERROR: %s\n", SDL_GetError());
    return false;
  }

  SDL_AudioSpec spec;
  SDL_zero(spec);
  spec.freq = samplerate;
  spec.format = SDL_AUDIO_S16;
  spec.channels = 1;

  audio->audio_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
  if (!audio->audio_stream) {
    printf("ERROR: %s\n", SDL_GetError());
    delete audio->apu;
    delete audio->buf;
    return false;
  }
  SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(audio->audio_stream));
  return true;
}
void SMB_audio_fini(struct SMB_audio *audio) {
  free(audio->readsamples_tmpbuf);
  SDL_DestroyAudioStream(audio->audio_stream);
  delete audio->apu;
  delete audio->buf;
}

size_t SMB_audio_size() {
  return sizeof(struct SMB_audio);
}

void SMB_audio_write_register(struct SMB_audio *audio, uint16_t addr, uint8_t data) {
  audio->apu->write_register(audio->clock, addr, data);

  // In the NES game, the clocks at which APU registers are written are more spread apart
  // and are sensitive to the logic of the sound engine.
  // But we're not too concerned about accurate sound emulation
  audio->clock += 4;
}
void SMB_audio_end_frame(struct SMB_audio *audio) {
  blip_sample_t *buf = audio->readsamples_tmpbuf;
  size_t buf_count = audio->readsamples_tmpbuf_count;
  audio->clock = 0;

  // Toggle between 29780 and 29701 clocks per frame on NTSC
  // An average of 29780.5 clocks per frame
  audio->frame = (audio->frame + 1) % 2;
  blip_time_t frame_length = audio->frame == 0 ? 29780 : 29781;

  audio->apu->end_frame(frame_length);
  audio->buf->end_frame(frame_length);
  int count = audio->buf->read_samples(buf, buf_count);

  // Only queue audio if too much isn't queued already.
  // If too much audio is queued, we have an audio overrun. Or informally: "audio lag".

  int queued_bytes = SDL_GetAudioStreamQueued(audio->audio_stream);
  bool too_much_queued = queued_bytes > (int)(audio->max_samples_to_be_queued * sizeof(buf[0]));

  if (!too_much_queued) {
    if (!SDL_PutAudioStreamData(audio->audio_stream, buf, count * sizeof(buf[0]))) {
      printf("ERROR: %s\n", SDL_GetError());
    }
  }
}
