/*
 * fsm_clock.c
 *
 *  Created on: May 3, 2024
 *      Author: ADMIN
 */

#include "fsm_clock.h"

int status = INIT;

int pos = 0;
int passCheck[3] = {0, 0, 0};
int pass[3] = {0, 0, 0};

int offAlarm = 0;
int alarm = 0;

int tempHour = 0;
int tempMin = 0;
int tempSec = 0;
int tempDate = 0;
int tempMonth = 0;
int tempYear = 0;

int confirm[3] = {0, 0, 0};

void clr_confirm(){
	for (int i = 0; i < 2; i++){
		confirm[i] = 0;
	}
}

void update_change_time_state(){
	tempHour = ds3231_hours;
	tempMin = ds3231_min;
	tempSec = ds3231_sec;
	tempDate = ds3231_date;
	tempMonth = ds3231_month;
	tempYear = ds3231_year;
}

void input_pass_num(int i){
	if (button_count[0] == 1){
		pass[i] = 1;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[1] == 1){
		pass[i] = 2;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[2] == 1){
		pass[i] = 3;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[4] == 1){
		pass[i] = 4;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[5] == 1){
		pass[i] = 5;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[6] == 1){
		pass[i] = 6;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[8] == 1){
		pass[i] = 7;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[9] == 1){
		pass[i] = 8;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[10] == 1){
		pass[i] = 9;
		if (i < 2){
			pos = pos + 1;
		}
	}
	if (button_count[13] == 1){
		pass[i] = 0;
		if (i < 2){
			pos = pos + 1;
		}
	}
}

void input_pass(){
	switch (pos) {
		case 0:
			blinky_displayTime(1, 0);
			input_pass_num(pos);
			if (button_count[3] == 1){
				pos = 1;
			}
			if (button_count[7] == 1){
				pos = 2;
			}
			break;
		case 1:
			blinky_displayTime(2, 0);
			input_pass_num(pos);
			if (button_count[3] == 1){
				pos = 2;
			}
			if (button_count[7] == 1){
				pos = 0;
			}
			break;
		case 2:
			blinky_displayTime(3, 0);
			input_pass_num(pos);
			if (button_count[3] == 1){
				pos = 0;
			}
			if (button_count[7] == 1){
				pos = 1;
			}
			break;
		default:
			break;
	}
}

void check_time(){
	if (tempHour > 24){
		tempHour = 0;
	}
	if (tempMin > 60){
		tempMin = 0;
	}
	if (tempSec > 60){
		tempSec = 0;
	}
	if (tempDate > 31){
		tempDate = 1;
	}
	if (tempMonth > 12){
		tempMonth = 1;
	}
	if (tempDate == 31 && (tempMonth == 2 || tempMonth == 4 || tempMonth == 6 || tempMonth == 9 || tempMonth == 11)){
		tempDate = 1;
		tempMonth = tempMonth + 1;
	}
	if (tempDate == 30 && tempMonth == 2){
		tempDate = 1;
		tempMonth = 3;
	}
	if (tempDate == 29 && tempMonth == 2 && ((tempYear % 4) != 0)){
		tempDate = 1;
		tempMonth = 3;
	}
	if (tempDate > 31){
		tempDate = 1;
		if (tempMonth == 12){
			tempMonth = 1;
			tempYear = tempYear + 1;
		}
		else {
			tempMonth = tempMonth + 1;
		}
	}
	tempYear = tempYear % 100;
}

void update_pass(){
	for (int i = 0; i < 3; i++){
		passCheck[i] = pass[i];
	}
}

void input_process(){
	// quay tro ve trang thai init
	if (button_count[12] >= 20 && button_count[14] >= 20){
		status = INIT;
	}

	// xu ly dau vao trong cac trang thai khac
	switch (status) {
		case INIT:
		case NORMAL:
			if (button_count[3] == 1 || is_touch_third()){
				if (confirm[0] == 1){
					status = ALARM;
					clr_confirm();
					pos = 1;
					update_change_time_state();
					alarm_lcd();
				}
				else{
					clr_confirm();
					confirm[0] = 1;
					home_third_lcd();
				}
			}
			if (button_count[7] == 1 || is_touch_fouth()){
				if (confirm[1] == 1){
					status = CHECK;
					clr_confirm();
					check_pass_lcd();
					for (int i = 0; i < 3; i++){
						pass[i] = 0;
					}
					pos = 0;
				}
				else{
					clr_confirm();
					confirm[1] = 1;
					home_forth_lcd();
				}
			}
			break;
		case ALARM:
			if (bool_key_touch == 0){
				if (button_count[13] == 1 || is_touch_third()){
					if (confirm[0] == 1){
						clr_confirm();
						alarm = 1;
						updateTime_Alarm(tempHour, tempMin, tempSec, tempDate, tempMonth, tempYear);
						status = NORMAL;
						home_lcd();
					}
					else {
						clr_confirm();
						check_time();
						confirm[0] = 1;
						home_third_lcd();
					}
				}
				if (button_count[14] == 1 || is_touch_fouth()){
					if (confirm[1] == 1){
						status = NORMAL;
						clr_confirm();
						home_lcd();
					}
					else{
						clr_confirm();
						confirm[1] = 1;
						home_forth_lcd();
					}
				}
			}
			break;
		case CHECK:
			if (button_count[12] == 1 || is_touch_third()){
				if (confirm[0] == 1){
					status = SETTING;
					clr_confirm();
//					update_change_time_state();
//					alarm_lcd();
					setting_lcd();
				}
				else{
					if (pass[0] != passCheck[0] || pass[1] != passCheck[1] || pass[2] != passCheck[2]){
						error_display();
						clr_confirm();
					}
					else {
						clr_confirm();
						confirm[0] = 1;
						home_third_lcd();
					}
				}
			}
			if (button_count[14] == 1 || is_touch_fouth()){
				if (confirm[1] == 1){
					status = NORMAL;
					clr_confirm();
					home_lcd();
				}
				else{
					clr_confirm();
					confirm[1] = 1;
					home_forth_lcd();
				}
			}
			break;
		case SETTING:
			if (button_count[3] == 1 || is_touch_second()){
				if (confirm[0] == 1){
					status = TIMER;
					clr_confirm();
					pos = 1;
					update_change_time_state();
					setTimer_lcd();
				}
				else{
					clr_confirm();
					confirm[0] = 1;
					home_second_lcd();
				}
			}
			if (button_count[7] == 1 || is_touch_third()){
				if (confirm[1] == 1){
					status = PASS;
					pos = 0;
					clr_confirm();
					check_pass_lcd();
					for (int i = 0; i < 3; i++){
						pass[i] = 0;
					}
					lcd_Fill(POS_X_FORTH, 10, POS_X_FORTH + WIDTH, 10 + HEIGHT, RED);

					lcd_ShowStr(POS_X_FORTH + 10, 10 + 5, "SET PASS", BLACK, BLACK, 24, 1);
				}
				else{
					clr_confirm();
					confirm[1] = 1;
					home_third_lcd();
				}
			}
			if (button_count[11] == 1 || is_touch_fouth()){
				if (confirm[2] == 1){
					status = NORMAL;
					clr_confirm();
					check_pass_lcd();
					for (int i = 0; i < 3; i++){
						pass[i] = 0;
					}
				}
				else{
					clr_confirm();
					confirm[2] = 1;
					home_forth_lcd();
				}
			}
			break;
		case PASS:
			if (button_count[12] == 1 || is_touch_third()){
				if (confirm[0] == 1){
					status = SETTING;
					clr_confirm();
					update_pass();
					setting_lcd();
				}
				else{
					clr_confirm();
					confirm[0] = 1;
					home_third_lcd();
				}
			}
			if (button_count[14] == 1 || is_touch_fouth()){
				if (confirm[1] == 1){
					status = NORMAL;
					clr_confirm();
					home_lcd();
				}
				else{
					clr_confirm();
					confirm[1] = 1;
					home_forth_lcd();
				}
			}
			break;
		case TIMER:
			if (button_count[13] == 1 || is_touch_third()){
				if (confirm[0] == 1){
					status = NORMAL;
					clr_confirm();
					updateTime(tempHour, tempMin, tempSec, tempDate, tempMonth, tempYear);
					home_lcd();
				}
				else{
					clr_confirm();
					check_time();
					confirm[0] = 1;
					home_third_lcd();
				}
			}
			if (button_count[14] == 1 || is_touch_fouth()){
				if (confirm[1] == 1){
					status = NORMAL;
					clr_confirm();
					home_lcd();
				}

				else{
					clr_confirm();
					confirm[1] = 1;
					home_forth_lcd();
				}
			}
			break;
		default:
			break;
	}
}

void check_inc_min(){
	tempMin = ds3231_min_alarm;
	tempHour = ds3231_hours_alarm;
	tempDate = ds3231_date_alarm;
	tempDate = ds3231_date_alarm;
	tempMonth = ds3231_month_alarm;
	tempYear = ds3231_year_alarm;

	tempMin = tempMin + 4;
	if (tempMin >= 60){
		tempMin = tempMin - 60;
		tempHour = tempHour + 1;
		if (tempHour >= 24){
			tempHour = tempHour - 24;
			tempDate = tempDate + 1;
			check_time();
		}
	}
	updateTime_Alarm(tempHour, tempMin, tempSec, tempDate, tempMonth, tempYear);
}

void check_alarm_over(){
	if (offAlarm > 0){
		if (button_count[0] == 1 || is_touch_off_alarm() == 1){
			offAlarm = 0;
			alarm = 0;
			buzzer_SetVolume(0);
			alarm_clear();
		}
		else if (offAlarm < 1000){
			offAlarm++;
			buzzer_SetVolume((5*offAlarm)%100);
			alarm_display();
		}
		else {
			offAlarm = 0;
			buzzer_SetVolume(0);
			alarm_clear();
			check_inc_min();
		}
	}
	if (check_alarm() == 1){
		offAlarm = 1;
		buzzer_SetVolume(5*offAlarm);
		alarm_display();
	}
}

void process_time(){
	touch_change_pos_time();
	if (bool_key_touch != 0){
		touch_key();
	}
	switch (pos) {
		case 1:
			blinky_displayTime(1, 1);
			if (button_count[3] == 1 || button_count[3] > 20){
				tempHour++;
				if (tempHour >= 24){
					tempHour = 0;
				}
			}
			if (button_count[7] == 1 || button_count[7] > 20){
				tempHour--;
				if (tempHour < 0){
					tempHour = 23;
				}
			}
			if (button_count[11] == 1){
				pos = 2;
			}
			if (button_count[15] == 1){
				pos = 6;
			}
			break;
		case 2:
			blinky_displayTime(2, 1);
			if (button_count[3] == 1 || button_count[3] > 20){
				tempMin++;
				if (tempMin >= 60){
					tempMin = 0;
				}
			}
			if (button_count[7] == 1 || button_count[7] > 20){
				tempMin--;
				if (tempMin < 0){
					tempMin = 59;
				}
			}
			if (button_count[11] == 1){
				pos = 3;
			}
			if (button_count[15] == 1){
				pos = 1;
			}
			break;
		case 3:
			blinky_displayTime(3, 1);
			if (button_count[3] == 1 || button_count[3] > 20){
				tempSec++;
				if (tempSec >= 60){
					tempSec = 0;
				}
			}
			if (button_count[7] == 1 || button_count[7] > 20){
				tempSec--;
				if (tempSec < 0){
					tempSec = 59;
				}
			}
			if (button_count[11] == 1){
				pos = 4;
			}
			if (button_count[15] == 1){
				pos = 2;
			}
			break;
		case 4:
			blinky_displayTime(4, 1);
			if (button_count[3] == 1 || button_count[3] > 20){
				tempDate++;
				if (tempDate > 31){
					tempDate = 1;
				}
			}
			if (button_count[7] == 1 || button_count[7] > 20){
				tempDate--;
				if (tempDate <= 0){
					tempDate = 1;
				}
			}
			if (button_count[11] == 1){
				pos = 5;
			}
			if (button_count[15] == 1){
				pos = 3;
			}
			break;
		case 5:
			blinky_displayTime(5, 1);
			if (button_count[3] == 1 || button_count[3] > 20){
				tempMonth++;
				if (tempMonth > 12){
					tempMonth = 1;
				}
			}
			if (button_count[7] == 1 || button_count[7] > 20){
				tempMonth--;
				if (tempMonth < 1){
					tempMonth = 1;
				}
			}
			if (button_count[11] == 1){
				pos = 6;
			}
			if (button_count[15] == 1){
				pos = 4;
			}
			break;
		case 6:
			blinky_displayTime(6, 1);
			if (button_count[3] == 1 || button_count[3] > 20){
				tempYear++;
				if (tempYear > 99){
					tempYear = 0;
				}
			}
			if (button_count[7] == 1 || button_count[7] > 20){
				tempYear--;
				if (tempYear < 0){
					tempYear = 0;
				}
			}
			if (button_count[11] == 1){
				pos = 1;
			}
			if (button_count[15] == 1){
				pos = 5;
			}
			break;
		default:
			break;
	}
}

void fsm_clock(){
	if (alarm == 1) {
		check_alarm_over();
	}
	switch (status) {
		case INIT:
			uart_EspSendBytes("t", 1);
			led7_timer_init();
			status = NORMAL;
		case NORMAL:
			displayTime(ds3231_hours, ds3231_min, ds3231_sec, ds3231_date, ds3231_month, ds3231_year);
			break;
		case ALARM:
			if (bool_key_touch == 1){
				key_num_display();
				bool_key_touch++;
			}
			process_time();
			break;
		case CHECK:
			input_pass();
			break;
		case SETTING:
			break;
		case PASS:
			input_pass();
			break;
		case TIMER:
			if (bool_key_touch == 1){
				key_num_display();
				bool_key_touch++;
			}
			process_time();
			break;
		default:
			break;
	}
}

