// Most of this file is C-style code.
// This is intentional, as to make this easier to port to pure C implemntations.
// Nes_Snd_Emu is a C++ library, so that's accessed the C++ way.


#include "audio.h"
#ifdef USE_SDL2
#  include <SDL.h>
#else
#  include <SDL3/SDL.h>
#endif
#include <stdio.h>

#include "nes_apu/Nes_Apu.h"


// The caller for NesAudioImpl assumes signed 16-bit samples,
// so let's assert that Nes_Snd_Emu indeed uses this.
static_assert(std::is_same_v<blip_sample_t, std::int16_t>,
              "blip_sample_t should be int16_t");

class NesAudioImpl {
private:
  Blip_Buffer _buf;

  // Note: apu references buf
  Nes_Apu _apu;

  blip_time_t _clock;
  int _frame;

  bool _valid;

  static int null_dmc_reader(int unused) {
    (void)unused;
    return 0x55;
  }

public:

  NesAudioImpl(int32_t samplerate) : _buf(), _apu(), _clock(0), _frame(0), _valid(false) {
    _buf.clock_rate(1789773);
    std::error_condition error = _buf.set_sample_rate(samplerate);

    if (error) {
      printf("ERROR: %s\n", error.message().c_str());
      return;
    }

    _apu.dmc_reader = NesAudioImpl::null_dmc_reader;
    _apu.set_output(&_buf);

    _valid = true;
  }

  bool valid() const {
    return this->_valid;
  }

  void write_register(uint16_t addr, uint8_t data) {
    this->_apu.write_register(this->_clock, addr, data);

    // In the NES game, the clocks at which APU registers are written are more spread apart
    // and are sensitive to the logic of the sound engine.
    // But we're not too concerned about accurate sound emulation
    this->_clock += 4;
  }

  int end_frame_then_read_i16(int16_t *out, size_t count) {
    this->_clock = 0;

    // Toggle between 29780 and 29701 clocks per frame on NTSC
    // An average of 29780.5 clocks per frame
    this->_frame = (this->_frame + 1) % 2;
    blip_time_t frame_length = this->_frame == 0 ? 29780 : 29781;

    this->_apu.end_frame(frame_length);
    this->_buf.end_frame(frame_length);

    return this->_buf.read_samples(out, count);
  }
};


struct SMB_audio {
  NesAudioImpl *nesaudio;

#ifdef USE_SDL2
  SDL_AudioDeviceID audio_device_id;
#else
  SDL_AudioStream *audio_stream;
#endif

  uint64_t max_samples_to_be_queued;
  int16_t *readsamples_tmpbuf;
  size_t readsamples_tmpbuf_count;
};


bool SMB_audio_init(struct SMB_audio *audio, int32_t samplerate, int32_t maxlatency_ms) {
  audio->nesaudio = new NesAudioImpl(samplerate);

  if (!audio->nesaudio->valid()) {
    // There was an error initializing
    delete audio->nesaudio;
    return false;
  }

  audio->max_samples_to_be_queued = ((uint64_t)samplerate * maxlatency_ms / 1000);

  // should be enough for 60fps, but adding more for contingency
  audio->readsamples_tmpbuf_count = (samplerate * 2 / 60);
  audio->readsamples_tmpbuf = (int16_t*)malloc(audio->readsamples_tmpbuf_count * sizeof(int16_t));

#ifdef USE_SDL2
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    printf("ERROR: %s\n", SDL_GetError());
    return false;
  }

  SDL_AudioSpec spec;
  spec.freq = samplerate;
  spec.format = AUDIO_S16SYS;
  spec.channels = 1;
  spec.silence = 0;
  spec.samples = 2048; // doesn't seem to matter with SDL_QueueAudio
  spec.size = 0;
  spec.callback = 0; // queueing audio with SDL_QueueAudio

  SDL_AudioDeviceID audio_device_id = SDL_OpenAudioDevice(0, 0, &spec, 0, 0);
  bool success = audio_device_id > 0;
  if (success) {
    audio->audio_device_id = audio_device_id;
    SDL_PauseAudioDevice(audio_device_id, false);
  } else {
    printf("ERROR: %s\n", SDL_GetError());
    delete audio->nesaudio;
  }
  return success;
#else
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
    delete audio->nesaudio;
    return false;
  }
  SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(audio->audio_stream));
  return true;
#endif
}

void SMB_audio_fini(struct SMB_audio *audio) {
  free(audio->readsamples_tmpbuf);

#ifdef USE_SDL2
  SDL_CloseAudioDevice(audio->audio_device_id);
#else
  SDL_DestroyAudioStream(audio->audio_stream);
#endif

  delete audio->nesaudio;
}

size_t SMB_audio_size() {
  return sizeof(struct SMB_audio);
}

void SMB_audio_write_register(struct SMB_audio *audio, uint16_t addr, uint8_t data) {
  audio->nesaudio->write_register(addr, data);
}

void SMB_audio_end_frame(struct SMB_audio *audio) {
  int16_t *buf = audio->readsamples_tmpbuf;
  size_t buf_count = audio->readsamples_tmpbuf_count;

  int count = audio->nesaudio->end_frame_then_read_i16(buf, buf_count);

  // Only queue audio if too much isn't queued already.
  // If too much audio is queued, we have an audio overrun. Or informally: "audio lag".

#ifdef USE_SDL2
  uint32_t queued_bytes = SDL_GetQueuedAudioSize(audio->audio_device_id);
  bool too_much_queued = queued_bytes > (audio->max_samples_to_be_queued * sizeof(buf[0]));

  if (!too_much_queued) {
    if (SDL_QueueAudio(audio->audio_device_id, buf, count * sizeof(buf[0])) != 0) {
      printf("ERROR: %s\n", SDL_GetError());
    }
  }
#else
  int queued_bytes = SDL_GetAudioStreamQueued(audio->audio_stream);
  bool too_much_queued = queued_bytes > (int)(audio->max_samples_to_be_queued * sizeof(buf[0]));

  if (!too_much_queued) {
    if (!SDL_PutAudioStreamData(audio->audio_stream, buf, count * sizeof(buf[0]))) {
      printf("ERROR: %s\n", SDL_GetError());
    }
  }
#endif
}
