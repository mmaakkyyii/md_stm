#include "main_func.h"
#include "my_variable.h"
#include "motor.h"

#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "spi.h"



void Debug(char* data,int size){
	HAL_UART_Transmit_IT(&huart1,(uint8_t *)data,(uint16_t)size);

}


uint8_t spi_buff[2];
int spi_data_size=2;

void Init(){


    HAL_SPI_Receive_IT(&hspi1, spi_buff, spi_data_size);//Start the receiving process?
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
	encoder.Update();

	HAL_TIM_Base_Start_IT(&htim6);

	char data[20]="Hello rietion\r\n";
	Debug(data,20);

	HAL_Delay(100);
}

void Loop(){
	HAL_SPI_Receive(&hspi1,spi_buff,spi_data_size,10);
}


//void SetSPIData(uint8_t *pData, int Size){
//	for(int i=0;i<Size;i++){
//		spi_buff[i]=pData[i];
//	}
//}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
//	HAL_SPI_Receive(&hspi1,spi_buff,spi_data_size,10);
//	HAL_SPI_Receive_IT(&hspi1,spi_buff,spi_data_size);
	//SetSPIData(spi_buff,spi_data_size);
}


void TimerInterrupt(){//10ms‚¨‚«‚ÉŒÄ‚Î‚ê‚é

	static float ref_v=100;
	static int d=0;
	static int dir=1;
	d+=dir;
	if(d>1990){
		dir=-10;
	}
	if(d<-1990){
		dir=10;
	}

	static int neko=0;
	neko++;
	if(neko>500){
		neko=0;
		ref_v+=100;
		if(ref_v>600)ref_v=0;
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
	}
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);

	controller.SetReference(ref_v);

	encoder.Update();
	float v=encoder.GetVelocity();
	float output = controller.Update(v);

	motor.Drive(output);


	char po[20]={};
	int num = sprintf(po,"%d,%d\r\n",(int)ref_v,(int)v);

	Debug(po,num);


}
