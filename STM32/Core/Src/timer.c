/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2024
 *      Author: admin
 */
#include"timer.h"

#define MAX_COUNTER 10
int timer_counter[MAX_COUNTER];
int timer_flag[MAX_COUNTER];

void setTimer(int index, int value) {
	timer_counter[index] = value;
	timer_flag[index] = 0;
}
int isTimerExpired(int index) {
	if (timer_flag[index] == 1) {
		timer_flag[index] = 0;
		return 1;
	}
	return 0;
}
void timerRun() {
	for (int i = 0; i < MAX_COUNTER; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
			if (timer_counter[i] <= 0) {
				timer_flag[i] = 1;
			}
		}
	}

}
