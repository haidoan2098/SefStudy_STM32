#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "main.h"

typedef struct button {
	uint8_t btn_current;
	uint8_t btn_filter;
	uint8_t btn_last;
	uint8_t is_press;
	uint16_t Pin;
	GPIO_TypeDef *Port;
	uint32_t t_deboune;
	uint32_t time_start_press;
} Button_t;


void Button_Init(Button_t *btn, GPIO_TypeDef *Port, uint16_t Pin);
	

void button_handle(Button_t *btn);

#endif
