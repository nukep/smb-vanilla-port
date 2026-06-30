#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

int timer_run_at_frequency(double fps, void *userdata, int (*cb)(void *userdata));

#ifdef __cplusplus
}
#endif

#endif
