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


uint8_t spi_buff[3]={0,0,0xf0};
int spi_data_size=3;

void Init(){

    HAL_SPI_Receive_IT(&hspi1, spi_buff, spi_data_size);//Start the receiving process?
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
	encoder.Update();

	HAL_TIM_Base_Start_IT(&htim6);
	HAL_SPI_Receive_IT(&hspi1,spi_buff,spi_data_size);


}

void Loop(){
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	HAL_SPI_Receive_IT(&hspi1,spi_buff,spi_data_size);

	//	HAL_SPI_Receive(&hspi1,spi_buff,spi_data_size,10);
//	HAL_SPI_Receive_IT(&hspi1,spi_buff,spi_data_size);
	//SetSPIData(spi_buff,spi_data_size);
}


void TimerInterrupt(){//10ms‚¨‚«‚ÉŒÄ‚Î‚ê‚é
	static int pre_data=0;

	int vel=(int16_t)((((uint16_t)spi_buff[0])<<8) |((uint16_t)spi_buff[1]));


	if(spi_buff[2]==0xff){
		pre_data=vel;
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		spi_buff[2]=0;
	}else if(spi_buff[2]==0xf0){
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	}else{
		vel=pre_data;
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
		spi_buff[2]=0;
	}


	controller.SetReference(vel);

	encoder.Update();
	float v=encoder.GetVelocity();
	float output = 0;
	if(spi_buff[2]!=0xff){
		output=controller.Update(v);
		motor.Drive(output);
	}

	char po[20]={};
	int num = sprintf(po,"%d,%d\r\n",(int)vel,(int)v);

	Debug(po,num);

}
