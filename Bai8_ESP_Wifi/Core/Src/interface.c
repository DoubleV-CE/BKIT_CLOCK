/*
 * interface.c
 *
 *  Created on: May 3, 2024
 *      Author: ADMIN
 */

#include "interface.h"

void displayPass(int id1, int id2, int id3){
	lcd_ShowIntNum(70 + 5, 100 - 30, id1, 1, CHGREEN, WHITE, 24);
	lcd_ShowIntNum(110 + 5, 100 - 30, id2, 1, CHGREEN, WHITE, 24);
	lcd_ShowIntNum(150 + 5, 100 - 30, id3, 1, CHGREEN, WHITE, 24);
//	lcd_ShowIntNum(20, 130, ds3231_day, 2, YELLOW, BLACK, 24);
//	lcd_ShowIntNum(70, 130, ds3231_date, 2, YELLOW, BLACK, 24);
//	lcd_ShowIntNum(110, 130, ds3231_month, 2, YELLOW, BLACK, 24);
//	lcd_ShowIntNum(150, 130, ds3231_year, 2, YELLOW, BLACK, 24);
}

char str[3] = "";

void time_fix_zero(uint8_t fix){
	str[0] = '0';
	char temp = (int)fix + 48;
	str[1] = temp;
	str[2] = '\0';
}

void displayTime(uint8_t t_hours, uint8_t t_min, uint8_t t_sec, uint8_t t_date, uint8_t t_month, uint8_t t_year){
	//hour
	if (t_hours > 9){
		lcd_ShowIntNum(70, 100 - 30, t_hours, 2, BRRED, WHITE, 24);
	}
	else {
		time_fix_zero(t_hours);
		lcd_ShowStr(70, 100 - 30, str , BRRED, WHITE, 24, 0);
	}
	//min
	if (t_min > 9){
		lcd_ShowIntNum(110, 100 - 30, t_min, 2, BRRED, WHITE, 24);
	}
	else {
		time_fix_zero(t_min);
		lcd_ShowStr(110, 100 - 30, str , BRRED, WHITE, 24, 0);
	}
	//sec
	if (t_sec > 9){
		lcd_ShowIntNum(150, 100 - 30, t_sec, 2, BRRED, WHITE, 24);
	}
	else {
		time_fix_zero(t_sec);
		lcd_ShowStr(150, 100 - 30, str , BRRED, WHITE, 24, 0);
	}
	//date
	if (t_date > 9){
		lcd_ShowIntNum(70, 130 - 30, t_date, 2, DARKBLUE, WHITE, 24);
	}
	else {
		time_fix_zero(t_date);
		lcd_ShowStr(70, 130 - 30, str , DARKBLUE, WHITE, 24, 0);
	}
	//month
	if (t_month > 9){
		lcd_ShowIntNum(110, 130 - 30, t_month, 2, DARKBLUE, WHITE, 24);
	}
	else {
		time_fix_zero(t_month);
		lcd_ShowStr(110, 130 - 30, str , DARKBLUE, WHITE, 24, 0);
	}
	//year
	if (t_year > 9){
		lcd_ShowIntNum(150, 130 - 30, t_year, 2, DARKBLUE, WHITE, 24);
	}
	else {
		time_fix_zero(t_year);
		lcd_ShowStr(150, 130 - 30, str , DARKBLUE, WHITE, 24, 0);
	}
	//ky tu dac biet
	lcd_ShowChar(70 + 25, 100 - 30, ':', ORANGE, WHITE, 24, 1);
	lcd_ShowChar(110 + 25, 100 - 30, ':', ORANGE, WHITE, 24, 1);
	lcd_ShowChar(70 + 25, 130 - 30, '-', ORANGE, WHITE, 24, 1);
	lcd_ShowChar(110 + 25, 130 - 30, '-', ORANGE, WHITE, 24, 1);
}

int counter_blink = 0;

void blinky_displayTime(int id, int check){
	counter_blink++;
	if (counter_blink <= 20){
		switch (id) {
			case 0:
				lcd_Fill(70, 100 - 30, 95, 125 - 30, WHITE);
				lcd_Fill(110, 100 - 30, 135, 125 - 30, WHITE);
				lcd_Fill(150, 100 - 30, 175, 125 - 30, WHITE);
				lcd_Fill(70, 130 - 30, 95, 155 - 30, WHITE);
				lcd_Fill(110, 130 - 30, 135, 155 - 30, WHITE);
				lcd_Fill(150, 130 - 30, 175, 155 - 30, WHITE);
			break;
			case 1:
				lcd_Fill(70, 100 - 30, 95, 125 - 30, WHITE);
				break;
			case 2:
				lcd_Fill(110, 100 - 30, 135, 125 - 30, WHITE);
				break;
			case 3:
				lcd_Fill(150, 100 - 30, 175, 125 - 30, WHITE);
				break;
			case 4:
				lcd_Fill(70, 130 - 30, 95, 155 - 30, WHITE);
				break;
			case 5:
				lcd_Fill(110, 130 - 30, 135, 155 - 30, WHITE);
				break;
			case 6:
				lcd_Fill(150, 130 - 30, 175, 155 - 30, WHITE);
				break;
			default:
				break;
		}
	}
	else if (counter_blink <= 40){
		if (check == 1)
			displayTime(tempHour, tempMin, tempSec, tempDate, tempMonth, tempYear);
		else
			displayPass(pass[0], pass[1], pass[2]);
	}
	if (counter_blink >= 40){
		counter_blink = 0;
	}
}

void alarm_clear(){
	lcd_Fill(10, 10, 60, 60, WHITE);
}

void error_display(){
	lcd_Fill(POS_X_FORTH, 10, POS_X_FORTH + WIDTH, 10 + HEIGHT, RED);

	lcd_ShowStr(POS_X_FORTH + 30, 10 + 5, "ERROR", BLACK, BLACK, 24, 1);
}

void alarm_display(){
	if (counter_blink <= 20){
//		lcd_Fill(POS_X_FORTH, 10, POS_X_FORTH + WIDTH, 10 + HEIGHT, RED);
//
//		lcd_ShowStr(POS_X_FORTH + 30, 10 + 5, "ALARM", BLACK, BLACK, 24, 1);
		lcd_ShowPicture(10, 10, 50, 50, gImage_bell);
	}
	else if (counter_blink <= 40){
		alarm_clear();
	}
	else {
		counter_blink = 0;
	}
	counter_blink++;
}

void alarm_display_current(){
	lcd_ShowStr(POS_X_FORTH + 30, 50 + 5, "ALARM", BLACK, BLACK, 24, 1);
}

void home_lcd(){
	lcd_Clear(WHITE);
	displayTime(ds3231_hours, ds3231_min, ds3231_sec, ds3231_date, ds3231_month, ds3231_year);
	lcd_Fill(POS_X_THIRD, POS_Y_THIRD, POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, BROWN);
	lcd_Fill(POS_X_FORTH, POS_Y_FORTH, POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, BROWN);

	lcd_ShowStr(POS_X_THIRD + 30, POS_Y_THIRD + 5, "ALARM", BLACK, BLACK, 24, 1);
	lcd_ShowStr(POS_X_FORTH + 17, POS_Y_FORTH + 5, "SETTING", BLACK, BLACK, 24, 1);
}

void setting_lcd(){
	lcd_Clear(WHITE);
	displayTime(ds3231_hours, ds3231_min, ds3231_sec, ds3231_date, ds3231_month, ds3231_year);
	lcd_Fill(POS_X_SECOND, POS_Y_SECOND, POS_X_SECOND + WIDTH, POS_Y_SECOND + HEIGHT, BROWN);
	lcd_Fill(POS_X_THIRD, POS_Y_THIRD, POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, BROWN);
	lcd_Fill(POS_X_FORTH, POS_Y_FORTH, POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, BROWN);

	lcd_ShowStr(POS_X_SECOND + 40, POS_Y_SECOND + 5, "TIME", BLACK, BLACK, 24, 1);
	lcd_ShowStr(POS_X_THIRD + 40, POS_Y_THIRD + 5, "PASS", BLACK, BLACK, 24, 1);
	lcd_ShowStr(POS_X_FORTH + 30, POS_Y_FORTH + 5, "CANCEL", BLACK, BLACK, 24, 1);
}

void alarm_lcd(){
	lcd_Clear(WHITE);
	lcd_Fill(POS_X_FORTH, 10, POS_X_FORTH + WIDTH, 10 + HEIGHT, LIGHTBLUE);
	lcd_ShowStr(POS_X_FORTH + 5, 10 + 5, "SET ALARM", BLACK, BLACK, 24, 1);
	displayTime(tempHour, tempMin, tempSec, tempDate, tempMonth, tempYear);

	lcd_Fill(POS_X_THIRD, POS_Y_THIRD, POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, BROWN);
	lcd_Fill(POS_X_FORTH, POS_Y_FORTH, POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, BROWN);
	lcd_ShowStr(POS_X_THIRD + 45, POS_Y_THIRD + 5, "OK", BLACK, BLACK, 24, 1);
	lcd_ShowStr(POS_X_FORTH + 30, POS_Y_FORTH + 5, "CANCEL", BLACK, BLACK, 24, 1);
}

void setTimer_lcd(){
	lcd_Clear(WHITE);
	lcd_Fill(POS_X_FORTH, 10, POS_X_FORTH + WIDTH, 10 + HEIGHT, LIGHTBLUE);
	lcd_ShowStr(POS_X_FORTH + 5, 10 + 5, "SET TIMER", BLACK, BLACK, 24, 1);
	displayTime(tempHour, tempMin, tempSec, tempDate, tempMonth, tempYear);
	lcd_Fill(POS_X_THIRD, POS_Y_THIRD, POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, BROWN);
	lcd_Fill(POS_X_FORTH, POS_Y_FORTH, POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, BROWN);

	lcd_ShowStr(POS_X_THIRD + 45, POS_Y_THIRD + 5, "OK", BLACK, BLACK, 24, 1);
	lcd_ShowStr(POS_X_FORTH + 30, POS_Y_FORTH + 5, "CANCEL", BLACK, BLACK, 24, 1);
}

void check_pass_lcd(){
	lcd_Clear(WHITE);
	displayPass(0, 0, 0);
	lcd_Fill(POS_X_THIRD, POS_Y_THIRD, POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, BROWN);
	lcd_Fill(POS_X_FORTH, POS_Y_FORTH, POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, BROWN);

	lcd_ShowStr(POS_X_THIRD + 45, POS_Y_THIRD + 5, "OK", BLACK, BLACK, 24, 1);
	lcd_ShowStr(POS_X_FORTH + 30, POS_Y_FORTH + 5, "CANCEL", BLACK, BLACK, 24, 1);
}

void home_not_select(){
	lcd_DrawRectangle(POS_X_THIRD, POS_Y_THIRD,
			POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, GRAY);
	lcd_DrawRectangle(POS_X_THIRD + 1, POS_Y_THIRD + 1,
			POS_X_THIRD + WIDTH - 1, POS_Y_THIRD + HEIGHT - 1, GRAY);

	lcd_DrawRectangle(POS_X_FORTH, POS_Y_FORTH,
			POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, GRAY);
	lcd_DrawRectangle(POS_X_FORTH + 1, POS_Y_FORTH + 1,
			POS_X_FORTH + WIDTH - 1, POS_Y_FORTH + HEIGHT - 1, GRAY);
}

void home_second_lcd(){
	home_not_select();
	lcd_DrawRectangle(POS_X_SECOND, POS_Y_SECOND,
			POS_X_SECOND + WIDTH, POS_Y_SECOND + HEIGHT, BLACK);
	lcd_DrawRectangle(POS_X_SECOND + 1, POS_Y_SECOND + 1,
			POS_X_SECOND + WIDTH - 1, POS_Y_SECOND + HEIGHT - 1, BLACK);
}

void home_third_lcd(){
	home_not_select();
	lcd_DrawRectangle(POS_X_THIRD, POS_Y_THIRD,
			POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, BLACK);
	lcd_DrawRectangle(POS_X_THIRD + 1, POS_Y_THIRD + 1,
			POS_X_THIRD + WIDTH - 1, POS_Y_THIRD + HEIGHT - 1, BLACK);
}

void home_forth_lcd(){
	home_not_select();
	lcd_DrawRectangle(POS_X_FORTH, POS_Y_FORTH,
			POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, BLACK);
	lcd_DrawRectangle(POS_X_FORTH + 1, POS_Y_FORTH + 1,
			POS_X_FORTH + WIDTH - 1, POS_Y_FORTH + HEIGHT - 1, BLACK);
}

void key_num_display(){
	lcd_Fill(0, 170, 240, 320, LIGHTGREEN);
	lcd_DrawLine(0, 170, 240, 170, BLACK);
	lcd_DrawLine(0, 220, 240, 220, BLACK);
	lcd_DrawLine(0, 270, 240, 270, BLACK);
	lcd_DrawLine(0, 320, 240, 320, BLACK);

	lcd_DrawLine(60, 170, 60, 320, BLACK);
	lcd_DrawLine(120, 170, 120, 320, BLACK);
	lcd_DrawLine(180, 170, 180, 320, BLACK);

	lcd_ShowIntNum(22, 180, 1, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowIntNum(85, 180, 2, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowIntNum(145, 180, 3, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowChar(205, 180, 'X', WHITE, LIGHTGREEN, 24, 0);

	lcd_ShowIntNum(22, 230, 4, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowIntNum(85, 230, 5, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowIntNum(145, 230, 6, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowIntNum(205, 230, 0, 1, WHITE, LIGHTGREEN, 24);

	lcd_ShowIntNum(22, 280, 7, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowIntNum(85, 280, 8, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowIntNum(145, 280, 9, 1, WHITE, LIGHTGREEN, 24);
	lcd_ShowChar(205, 280, 'E', WHITE, LIGHTGREEN, 24, 0);
}

void return_button_off_key(){
	lcd_Fill(0, 170, 240, 320, WHITE);

	lcd_Fill(POS_X_THIRD, POS_Y_THIRD, POS_X_THIRD + WIDTH, POS_Y_THIRD + HEIGHT, BROWN);
	lcd_Fill(POS_X_FORTH, POS_Y_FORTH, POS_X_FORTH + WIDTH, POS_Y_FORTH + HEIGHT, BROWN);
	lcd_ShowStr(POS_X_THIRD + 45, POS_Y_THIRD + 5, "OK", BLACK, BLACK, 24, 1);
	lcd_ShowStr(POS_X_FORTH + 30, POS_Y_FORTH + 5, "CANCEL", BLACK, BLACK, 24, 1);
}
