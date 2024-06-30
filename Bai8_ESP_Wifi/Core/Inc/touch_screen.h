/*
 * touch_screen.h
 *
 *  Created on: Jun 3, 2024
 *      Author: ADMIN
 */

#ifndef INC_TOUCH_SCREEN_H_
#define INC_TOUCH_SCREEN_H_

#include "touch.h"
#include "interface.h"
#include "fsm_clock.h"

extern int bool_key_touch;

int is_touch_fisrt();
int is_touch_second();
int is_touch_third();
int is_touch_fouth();

void touch_change_pos_time();

int is_touch_off_alarm();

int is_touch_key_0();
int is_touch_key_1();
int is_touch_key_2();
int is_touch_key_3();
int is_touch_key_4();
int is_touch_key_5();
int is_touch_key_6();
int is_touch_key_7();
int is_touch_key_8();
int is_touch_key_9();
int is_touch_key_X();
int is_touch_key_E();
void touch_key();

#endif /* INC_TOUCH_SCREEN_H_ */
