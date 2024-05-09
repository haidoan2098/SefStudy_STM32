#include "Button.h"


//-------------------------FUNCTION BUTTON----------------------------
__weak void btn_press_callback(Button_t *btn){
	//nhan nut
}

__weak void btn_realese_callback(Button_t *btn){
	//nha nut
}

__weak void btn_press_short_callback(Button_t *btn){
	//nhan roi nha ngay
}

__weak void btn_press_long_callback(Button_t *btn){
	//nhan giu roi moi nha ra
}

//-------------------Khoi tao doi tuong nut nhan-----------------------
void Button_Init(Button_t *btn, GPIO_TypeDef *Port, uint16_t Pin){
	btn->Port = Port;
	btn->Pin = Pin;
	
	btn->btn_filter = 1;
	btn->t_deboune = 0;
	btn->time_start_press = 0;
	btn->btn_last = 1;
	btn->is_press = 0;
}


//---------------XU LI LOC NHIEU & SU KIEN-------------------
void button_handle(Button_t *btn){
	uint8_t status = HAL_GPIO_ReadPin(btn->Port, btn->Pin);
	if(status != btn->btn_filter){
		btn->btn_filter = status;
		btn->t_deboune = HAL_GetTick();
	}
	if(HAL_GetTick() - btn->t_deboune >= 15){
		btn->btn_current = btn->btn_filter;
		if(btn->btn_current != btn->btn_last){
			if(btn->btn_current == 0){ 
				btn->time_start_press = HAL_GetTick();
				btn_press_callback(btn);
				btn->is_press = 1;
		}
		else { 
			if(HAL_GetTick() - btn->time_start_press <= 1000){
				btn_press_short_callback(btn);
			}
			btn_realese_callback(btn);
			btn->is_press = 0;
		}
		btn->btn_last = btn->btn_current;
		}
		if(btn->is_press && (HAL_GetTick() - btn->time_start_press >= 3000)){
			btn_press_long_callback(btn);
			btn->is_press = 0;
		}
	}
}

