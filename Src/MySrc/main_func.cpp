#include "main_func.h"
#include "my_variable.h"
#include "motor.h"

#include "gpio.h"
#include "tim.h"
void Init(){
	HAL_TIM_Base_Start_IT(&htim6);

}

void Loop(){
	motor.Drive(1);
}

void TimerInterrupt(){

	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);

}
