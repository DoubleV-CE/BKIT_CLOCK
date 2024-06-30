/*
 * extra_function.c
 *
 *  Created on: May 27, 2024
 *      Author: ADMIN
 */
#include "extra_function.h"

void updateTime(int hour, int min, int sec, int date, int month, int year){
	ds3231_Write(ADDRESS_YEAR, year);
	ds3231_Write(ADDRESS_MONTH, month);
	ds3231_Write(ADDRESS_DATE, date);
	ds3231_Write(ADDRESS_HOUR, hour);
	ds3231_Write(ADDRESS_MIN, min);
	ds3231_Write(ADDRESS_SEC, sec);
}

void updateTime_Alarm(int hour, int min, int sec, int date, int month, int year){
	ds3231_Write(ADDRESS_YEAR_ALARM, year);
	ds3231_Write(ADDRESS_MONTH_ALARM, month);
	ds3231_Write(ADDRESS_DATE_ALARM, date);
	ds3231_Write(ADDRESS_HOUR_ALARM, hour);
	ds3231_Write(ADDRESS_MIN_ALARM, min);
	ds3231_Write(ADDRESS_SEC_ALARM, sec);
}

uint8_t check_alarm(){
	ds3231_ReadTime_Alarm();
	if (ds3231_year == ds3231_year_alarm && ds3231_month == ds3231_month_alarm && ds3231_date == ds3231_date_alarm &&
		ds3231_hours == ds3231_hours_alarm && ds3231_min == ds3231_min_alarm && ds3231_sec == ds3231_sec_alarm) {
		return 1;
	}
	return 0;
}


