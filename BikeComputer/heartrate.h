#ifndef HEARTRATE_H
#define HEARTRATE_H

#define HEART_RATE_HISTORY 60

void init_heartrate();
void check_heartrate();

unsigned int heart_rate_history[HEART_RATE_HISTORY];

unsigned int heart_rate_state = 0; // Line flip-flops when beat detected. This is previous state.

#endif
