/*
 * alarm_queue.h
 *
 *  Created on: Jun 4, 2024
 *      Author: ADMIN
 */

#ifndef INC_ALARM_QUEUE_H_
#define INC_ALARM_QUEUE_H_

struct timeStruct{
	int time_hour;
	int time_min;
	int time_sec;
	int time_date;
	int time_month;
	int time_year;
};

extern int alarm_queue;



#endif /* INC_ALARM_QUEUE_H_ */
