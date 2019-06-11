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


uint8_t spi_buff[3]={0,0,0xf3};
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


void TimerInterrupt(){//10msおきに呼ばれる
	static int pre_data=0;

	uint8_t spi[3];
	spi[0]=spi_buff[0];
	spi[1]=spi_buff[1];
	spi[2]=spi_buff[2];
	if(spi[0]==0 && spi[1]==0 && spi[2]==0)spi[2]=1;//配列がすべて0のときがあるけどこれをそのまま通すと回ってる最中に目標値0が入ってガタっとするので目標値0を送るときだけ特殊な値を送るようにしている
	if(spi[0]==0 && spi[1]==0 && spi[2]==0xf0)spi[2]=0;//意図的に目標値0をｋ送るとき最後のビットは0xf0にすることにしているのでこんな感じ

	int vel=(int16_t)((((uint16_t)spi[0])<<8) |((uint16_t)spi[1]));
	int rx_state=spi[2];

	if((pre_data-vel>100)||(pre_data-vel<-100))vel=pre_data; //目標値の変化量が大きすぎるときは通信が怪しいのでそのままの値にする

	if(spi[2]==spi[0]^spi[1]){
		pre_data=vel;
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		spi[2]=0xaa;
	}else if(spi[2]==0xf3){
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	}else{
		vel=pre_data;
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
		spi[2]=0xaa;
	}



	controller.SetReference(vel);

	encoder.Update();
	float v=encoder.GetVelocity();
	float output = 0;
	if(rx_state==spi[0]^spi[1]){
		output=controller.Update(v);
		motor.Drive(output);
	}

	char po[20]={};
	int num = sprintf(po,"%d,%d,%d\r\n",(int)vel,(int)v,(int)rx_state);

	Debug(po,num);

}
