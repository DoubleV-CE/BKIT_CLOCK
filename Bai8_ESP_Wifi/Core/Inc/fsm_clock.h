/*
 * fsm_clock.h
 *
 *  Created on: May 3, 2024
 *      Author: ADMIN
 */

#ifndef INC_FSM_CLOCK_H_
#define INC_FSM_CLOCK_H_

#include "button.h"
#include "interface.h"
#include "ds3231.h"
#include "buzzer.h"
#include "extra_function.h"
#include "touch_screen.h"
#include "uart.h"
#include "led7.h"

#define INIT	0
#define NORMAL 	1
#define ALARM	2
#define CHECK	3
#define SETTING 4
#define TIMER	41
#define PASS	42


extern int status;

extern int pos;

extern int offAlarm;
extern int alarm;

extern int tempHour;
extern int tempMin;
extern int tempSec;
extern int tempDate;
extern int tempMonth;
extern int tempYear;

extern int pass[];
extern int passCheck[];


void input_process();
void fsm_clock();

#endif /* INC_FSM_CLOCK_H_ */
