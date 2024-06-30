/*
 * touch_creen.c
 *
 *  Created on: Jun 3, 2024
 *      Author: ADMIN
 */

#include "touch_screen.h"

int bool_key_touch = 0;

int is_touch_fisrt(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > POS_X_FIRST
			&& touch_GetX() < POS_X_FIRST + WIDTH
			&& touch_GetY() > POS_Y_FIRST
			&& touch_GetY() < POS_Y_FIRST + HEIGHT);
}

int is_touch_second(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > POS_X_SECOND
			&& touch_GetX() < POS_X_SECOND + WIDTH
			&& touch_GetY() > POS_Y_SECOND
			&& touch_GetY() < POS_Y_SECOND + HEIGHT);
}

int is_touch_third(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > POS_X_THIRD
			&& touch_GetX() < POS_X_THIRD + WIDTH
			&& touch_GetY() > POS_Y_THIRD
			&& touch_GetY() < POS_Y_THIRD + HEIGHT);
}

int is_touch_fouth(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > POS_X_FORTH
			&& touch_GetX() < POS_X_FORTH + WIDTH
			&& touch_GetY() > POS_Y_FORTH
			&& touch_GetY() < POS_Y_FORTH + HEIGHT);
}

int is_touch_time_1(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 75
			&& touch_GetX() < 75 + 25
			&& touch_GetY() > 70
			&& touch_GetY() < 70 + 25);
}

int is_touch_time_2(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 110
			&& touch_GetX() < 110 + 25
			&& touch_GetY() > 70
			&& touch_GetY() < 70 + 25);
}

int is_touch_time_3(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 150
			&& touch_GetX() < 150 + 25
			&& touch_GetY() > 70
			&& touch_GetY() < 70 + 25);
}

int is_touch_time_4(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 75
			&& touch_GetX() < 75 + 25
			&& touch_GetY() > 100
			&& touch_GetY() < 100 + 25);
}

int is_touch_time_5(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 110
			&& touch_GetX() < 110 + 25
			&& touch_GetY() > 100
			&& touch_GetY() < 100 + 25);
}

int is_touch_time_6(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 150
			&& touch_GetX() < 150 + 25
			&& touch_GetY() > 100
			&& touch_GetY() < 100 + 25);
}
void touch_change_pos_time(){
	if (is_touch_time_1() == 1){
		pos = 1;
		check_time();
		bool_key_touch++;
	}
	if (is_touch_time_2() == 1){
		pos = 2;
		check_time();
		bool_key_touch++;
	}
	if (is_touch_time_3() == 1){
		pos = 3;
		check_time();
		bool_key_touch++;
	}
	if (is_touch_time_4() == 1){
		pos = 4;
		check_time();
		bool_key_touch++;
	}
	if (is_touch_time_5() == 1){
		pos = 5;
		check_time();
		bool_key_touch++;
	}
	if (is_touch_time_6() == 1){
		pos = 6;
		check_time();
		bool_key_touch++;
	}
}

int is_touch_off_alarm(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 10
			&& touch_GetX() < 60
			&& touch_GetY() > 10
			&& touch_GetY() < 60);
}

int is_touch_key_1(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 0
			&& touch_GetX() < 60
			&& touch_GetY() > 170
			&& touch_GetY() < 220);
}

int is_touch_key_2(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 60
			&& touch_GetX() < 120
			&& touch_GetY() > 170
			&& touch_GetY() < 220);
}

int is_touch_key_3(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 120
			&& touch_GetX() < 180
			&& touch_GetY() > 170
			&& touch_GetY() < 220);
}

int is_touch_key_X(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 180
			&& touch_GetX() < 240
			&& touch_GetY() > 170
			&& touch_GetY() < 220);
}

int is_touch_key_4(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 0
			&& touch_GetX() < 60
			&& touch_GetY() > 220
			&& touch_GetY() < 270);
}

int is_touch_key_5(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 60
			&& touch_GetX() < 120
			&& touch_GetY() > 220
			&& touch_GetY() < 270);
}

int is_touch_key_6(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 120
			&& touch_GetX() < 180
			&& touch_GetY() > 220
			&& touch_GetY() < 270);
}

int is_touch_key_0(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 180
			&& touch_GetX() < 240
			&& touch_GetY() > 220
			&& touch_GetY() < 270);
}

int is_touch_key_7(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 0
			&& touch_GetX() < 60
			&& touch_GetY() > 270
			&& touch_GetY() < 320);
}

int is_touch_key_8(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 60
			&& touch_GetX() < 120
			&& touch_GetY() > 270
			&& touch_GetY() < 320);
}

int is_touch_key_9(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 120
			&& touch_GetX() < 180
			&& touch_GetY() > 270
			&& touch_GetY() < 320);
}

int is_touch_key_E(){
	if (!touch_IsTouched()) return 0;
	return (touch_GetX() > 180
			&& touch_GetX() < 240
			&& touch_GetY() > 270
			&& touch_GetY() < 320);
}

void update_key(int key){
	switch (pos) {
		case 1:
			tempHour = tempHour * 10;
			tempHour += key;
			tempHour = tempHour % 100;
			break;
		case 2:
			tempMin = tempMin * 10;
			tempMin += key;
			tempMin = tempMin % 100;
			break;
		case 3:
			tempSec = tempSec * 10;
			tempSec += key;
			tempSec = tempSec % 100;
			break;
		case 4:
			tempDate = tempDate * 10;
			tempDate += key;
			tempDate = tempDate % 100;
			break;
		case 5:
			tempMonth = tempMonth * 10;
			tempMonth += key;
			tempMonth = tempMonth % 100;
			break;
		case 6:
			tempYear = tempYear * 10;
			tempYear += key;
			tempYear = tempYear % 100;
			break;
		default:
			break;
	}
}

void touch_key(){
	if (is_touch_key_0() == 1){
		update_key(0);
		while (touch_IsTouched());
	}
	if (is_touch_key_1() == 1){
		update_key(1);
		while (touch_IsTouched());
	}
	if (is_touch_key_2() == 1){
		update_key(2);
		while (touch_IsTouched());
	}
	if (is_touch_key_3() == 1){
		update_key(3);
		while (touch_IsTouched());
	}
	if (is_touch_key_4() == 1){
		update_key(4);
		while (touch_IsTouched());
	}
	if (is_touch_key_5() == 1){
		update_key(5);
		while (touch_IsTouched());
	}
	if (is_touch_key_6() == 1){
		update_key(6);
		while (touch_IsTouched());
	}
	if (is_touch_key_7() == 1){
		update_key(7);
		while (touch_IsTouched());
	}
	if (is_touch_key_8() == 1){
		update_key(8);
		while (touch_IsTouched());
	}
	if (is_touch_key_9() == 1){
		update_key(9);
		while (touch_IsTouched());
	}
	if (is_touch_key_X() == 1){
		return_button_off_key();
		bool_key_touch = 0;
		check_time();
		while (touch_IsTouched());
	}
	if (is_touch_key_E() == 1){
		if (pos == 6){
			return_button_off_key();
			bool_key_touch = 0;
			check_time();
		}
		else {
			pos++;
			check_time();
		}
		while (touch_IsTouched());
	}
}
