#include "main_func.h"
#include "my_variable.h"
#include "motor.h"

#include "gpio.h"
#include "tim.h"
void Init(){
	HAL_TIM_Base_Start_IT(&htim6);

}

void Loop(){
}

void TimerInterrupt(){

	static int d=0;
	d++;
	if(d>990)d=0;
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	motor.Drive(d);

}
