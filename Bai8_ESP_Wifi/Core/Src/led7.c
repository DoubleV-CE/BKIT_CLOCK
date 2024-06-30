/*
 * led7.c
 *
 *  Created on: May 31, 2024
 *      Author: ADMIN
 */

#include "led7.h"

int hours_1 = 0;
int hours_2 = 0;
int min_1 = 0;
int min_2 = 0;

void led7_timer_init(){
	led7_SetDigit(ds3231_hours / 10, 0, 0);
	led7_SetDigit(ds3231_hours % 10, 1, 0);
	led7_SetDigit(ds3231_min / 10, 2, 0);
	led7_SetDigit(ds3231_min % 10, 3, 0);
}

void led7_timer(){
	if (min_2 != ds3231_min % 10){
		led7_timer_init();
	}
	else if (ds3231_min % 10 == 0){
		led7_timer_init();
	}
}
