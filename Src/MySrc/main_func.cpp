#include "main_func.h"
#include "my_variable.h"
#include "motor.h"

void Init(){

}

void Loop(){
	motor.Drive(1);
}

void TimerInterrupt(){

//	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);

}
