#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern "C" {
#endif

int time_run_at_frequency(double fps, void *userdata, int (*cb)(void *userdata));

#ifdef __cplusplus
}
#endif

#endif