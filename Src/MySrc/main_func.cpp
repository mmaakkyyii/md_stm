#include "main_func.h"
#include "my_variable.h"
#include "motor.h"

#include "gpio.h"
#include "tim.h"
#include "usart.h"


void Debug(char* data,int size){
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
	HAL_UART_Transmit_IT(&huart1,(uint8_t *)data,(uint16_t)size);

}


void Init(){
	HAL_TIM_Base_Start_IT(&htim6);

	  char data[20]="Hello rietion\r\n";
	  Debug(data,20);

	  HAL_Delay(100);
}

void Loop(){
}


void TimerInterrupt(){

	static int d=0;
	d++;
	if(d>990){
		d=0;
	}
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	motor.Drive(d);

	int pulse =encoder.GetPulse();
	int v=(int)encoder.GetVelocity();
	char po[20]={};
	sprintf(po,"%d,%d\r\n",pulse,v);
	Debug(po,20);


}
