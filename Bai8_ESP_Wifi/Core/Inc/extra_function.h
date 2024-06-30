/*
 * extra_function.h
 *
 *  Created on: May 27, 2024
 *      Author: ADMIN
 */

#ifndef INC_EXTRA_FUNCTION_H_
#define INC_EXTRA_FUNCTION_H_

#include "ds3231.h"

void updateTime(int hour, int min, int sec, int date, int month, int year);
void updateTime_Alarm(int hour, int min, int sec, int date, int month, int year);
uint8_t check_alarm();

#endif /* INC_EXTRA_FUNCTION_H_ */
