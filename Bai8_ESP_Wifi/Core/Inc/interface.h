/*
 * interface.h
 *
 *  Created on: May 3, 2024
 *      Author: ADMIN
 */

#ifndef INC_INTERFACE_H_
#define INC_INTERFACE_H_

#include "lcd.h"
#include "ds3231.h"
#include "fsm_clock.h"
#include "stdio.h"
#include "picture.h"

#define POS_X_FIRST 65		// Toa do x goc tren ben trai CLASSIC
#define POS_Y_FIRST 100		// Toa do y goc tren ben trai CLASSIC
#define POS_X_SECOND 65		// Toa do x goc tren ben trai NEWGAME/SPEED
#define POS_Y_SECOND 150	// Toa do y goc tren ben trai NEWGAME/SPEED
#define POS_X_THIRD 65		// Toa do x goc tren ben trai CONTINUE/TIME
#define POS_Y_THIRD 200		// Toa do y goc tren ben trai CONTINUE/TIME
#define POS_X_FORTH	65		// Toa do x goc tren ben trai HIGHSCORE/QUIT
#define POS_Y_FORTH	250		// Toa do y goc tren ben trai HIGHSCORE/QUIT
#define WIDTH 120			// Chieu rong o
#define HEIGHT 35			// Chieu dai o

extern int counter_blink;

void displayPass(int id1, int id2, int id3);
void check_pass_lcd();
void displayTime(uint8_t t_hour, uint8_t t_min, uint8_t t_sec, uint8_t t_date, uint8_t t_month, uint8_t t_year);
void blinky_displayTime(int id, int check);
void home_lcd();
void setting_lcd();
void alarm_lcd();
void alarm_clear();
void home_second_lcd();
void home_third_lcd();
void home_forth_lcd();
void error_display();
void alarm_display();
void alarm_display_current();
void setTimer_lcd();

void time_fix_zero(uint8_t fix);

void key_num_display();
void return_button_off_key();


#endif /* INC_INTERFACE_H_ */
