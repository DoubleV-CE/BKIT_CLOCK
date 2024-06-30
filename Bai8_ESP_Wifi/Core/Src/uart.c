/*
 * uart.c
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */
#include "uart.h"

uint8_t msg[100];
uint8_t bool_start_time = 0;
uint8_t bool_start_alarm = 0;
uint8_t i = 0;
char receive_msg[100];

uint8_t receive_buffer1 = 0, receive_buffer2 = 0;
uint8_t check_esp = 0;

void uart_init_rs232(){
	HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
}

void uart_Rs232SendString(uint8_t* str){
	HAL_UART_Transmit(&huart1, (void*)msg, sprintf((void*)msg,"%s",str), 10);
}

void uart_Rs232SendBytes(uint8_t* bytes, uint16_t size){
	HAL_UART_Transmit(&huart1, bytes, size, 10);
}

void uart_Rs232SendNum(uint32_t num){
	if(num == 0){
		uart_Rs232SendString("0");
		return;
	}
    uint8_t num_flag = 0;
    int i;
	if(num < 0) uart_Rs232SendString("-");
    for(i = 10; i > 0; i--)
    {
        if((num / mypow(10, i-1)) != 0)
        {
            num_flag = 1;
            sprintf((void*)msg,"%d",num/mypow(10, i-1));
            uart_Rs232SendString(msg);
        }
        else
        {
            if(num_flag != 0)
            	uart_Rs232SendString("0");
        }
        num %= mypow(10, i-1);
    }
}

void uart_Rs232SendNumPercent(uint32_t num)
{
	sprintf((void*)msg,"%ld",num/100);
    uart_Rs232SendString(msg);
    uart_Rs232SendString(".");
    sprintf((void*)msg,"%ld",num%100);
    uart_Rs232SendString(msg);
}

void uart_init_esp(){
	HAL_UART_Receive_IT(&huart2, &receive_buffer2, 1);
	HAL_GPIO_WritePin(ESP12_PWR_GPIO_Port, ESP12_PWR_Pin, 1);
}

void uart_EspSendBytes(uint8_t* bytes, uint16_t size){
	HAL_UART_Transmit(&huart2, bytes, size, 10);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1){
		// rs232 isr
		// can be modified
		HAL_UART_Transmit(&huart1, &receive_buffer1, 1, 10);

		// turn on the receive interrupt
		HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
	}

	if(huart->Instance == USART2){
		if (bool_start_time == 1){
			if (receive_buffer2 == 'E'){
				bool_start_time = 0;
				//xu ly chuoi o day
//				lcd_ShowStr(30, 30, receive_msg, GREEN, GREEN, 24, 1);
//				lcd_ShowChar(10, 10, receive_msg[8], GREEN, GREEN, 24, 1);
		           int year = (receive_msg[2+2] - '0')*10 + (receive_msg[3+2] - '0');
		           int month = (receive_msg[5+2] - '0')*10 + (receive_msg[6+2] - '0');
		           int date = (receive_msg[8+2] - '0')*10 + (receive_msg[9+2] - '0');
		           int hour = (receive_msg[11+2] - '0')*10 + (receive_msg[12+2] - '0');
		           int min = (receive_msg[14+2] - '0')*10 + (receive_msg[15+2] - '0');
		           int sec = (receive_msg[17+2] - '0')*10 + (receive_msg[18+2] - '0');
		           updateTime(hour, min, sec, date, month, year);
			}
			else {
				receive_msg[i] = receive_buffer2;
				i++;
			}
		}
		if (bool_start_alarm == 1){
			if (receive_buffer2 == 'Z'){
				bool_start_alarm = 0;
				//xu ly
				i = 0;
				lcd_ShowStr(30, 30, receive_msg, GREEN, GREEN, 24, 0);
				while (receive_msg[i] != 'D'){
					i++;
				}
				i++;
		        int year = (receive_msg[2] - '0')*10 + (receive_msg[3] - '0');
		        int month = (receive_msg[5] - '0')*10 + (receive_msg[6] - '0');
		        int date = (receive_msg[8] - '0')*10 + (receive_msg[9] - '0');
		        int hour = (receive_msg[11] - '0')*10 + (receive_msg[12] - '0');
		        int min = (receive_msg[14] - '0')*10 + (receive_msg[15] - '0');
		        int sec = (receive_msg[17] - '0')*10 + (receive_msg[18] - '0');
		        updateTime_Alarm(hour, min, sec, date, month, year);
			}
			else {
				receive_msg[i] = receive_buffer2;
				i++;
			}
		}

		if (receive_buffer2 == 'O') check_esp = 1;
		else if (receive_buffer2 == 'B'){
//			light_status = 1;
			HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, 1);
		}
		else if (receive_buffer2  == 'b'){
//			light_status = 0;
			HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, 0);
		}
//		else if (receive_buffer2 == 'A'){
////			light_status = 1;
//			HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 1);
//		}
//		else if (receive_buffer2  == 'a'){
////			light_status = 0;
//			HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, 0);
//		}
		else if (receive_buffer2 == 'S'){
			bool_start_time = 1;
			i = 0;
		}
		else if (receive_buffer2 == 'A') {
//			uart_EspSendBytes("a", 1);
			bool_start_alarm = 1;
			i = 0;
		}
		HAL_UART_Receive_IT(&huart2, &receive_buffer2, 1);
	}
}

uint8_t uart_EspCheck(){
	if(check_esp == 1) return 1;
	return 0;
}



