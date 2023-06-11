#include <stdio.h>
#include <SDL.h>
#include "audio.h"

#include "nes_apu/Nes_Apu.h"

#define SAMPLE_RATE 44100
#define MAX_SAMPLES_TO_BE_QUEUED 4096

struct SMB_audio {
	Blip_Buffer *buf;
	Nes_Apu *apu;
	blip_time_t clock;
	int frame;
	SDL_AudioDeviceID audio_device_id;
};

static int null_dmc_reader(int) {
	return 0x55;
}

bool SMB_audio_init(struct SMB_audio* audio) {
	audio->buf = new Blip_Buffer();
	audio->buf->clock_rate(1789773);
	audio->buf->set_sample_rate(SAMPLE_RATE);

	audio->apu = new Nes_Apu();
	audio->apu->dmc_reader = null_dmc_reader;
	audio->apu->set_output(audio->buf);

	audio->clock = 0;
	audio->frame = 0;

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
		printf("ERROR: %s\n", SDL_GetError());
		return false;
	}

	SDL_AudioSpec spec;
	spec.freq = SAMPLE_RATE;
	spec.format = AUDIO_S16SYS;
	spec.channels = 1;
	spec.silence = 0;
	spec.samples = 2048;	// doesn't seem to matter with SDL_QueueAudio
	spec.size = 0;
	spec.callback = 0;	// queueing audio with SDL_QueueAudio

	SDL_AudioDeviceID audio_device_id = SDL_OpenAudioDevice(0, 0, &spec, 0, 0);
	bool success = audio_device_id > 0;
	if (success) {
		audio->audio_device_id = audio_device_id;
		SDL_PauseAudioDevice(audio_device_id, false);
	} else {
		printf("ERROR: %s\n", SDL_GetError());
		delete audio->apu;
		delete audio->buf;
	}
	return success;
}
void SMB_audio_fini(struct SMB_audio* audio) {
	SDL_CloseAudioDevice(audio->audio_device_id);
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
	blip_sample_t buf[2048];
	audio->clock = 0;

	// Toggle between 29780 and 29701 clocks per frame on NTSC
	// An average of 29780.5 clocks per frame
	audio->frame = (audio->frame+1)%2;
	blip_time_t frame_length = audio->frame==0 ? 29780 : 29781;

	audio->apu->end_frame(frame_length);
	audio->buf->end_frame(frame_length);
	int count = audio->buf->read_samples(buf, sizeof(buf) / sizeof(blip_sample_t));

	// Only queue audio if too much isn't queued already.
	// If too much audio is queued, we have an audio overrun. Or informally: "audio lag".

	uint32_t queued_bytes = SDL_GetQueuedAudioSize(audio->audio_device_id);
	bool too_much_queued = queued_bytes > (MAX_SAMPLES_TO_BE_QUEUED * sizeof(buf[0]));

	if (!too_much_queued) {
		if (SDL_QueueAudio(audio->audio_device_id, buf, count*sizeof(buf[0])) != 0) {
			printf("ERROR: %s\n", SDL_GetError());
		}
	}
}
