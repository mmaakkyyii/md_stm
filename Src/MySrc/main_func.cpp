#include "main_func.h"
#include "my_variable.h"
#include "motor.h"
#include "math.h"

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

	HAL_SPI_Receive_IT(&hspi1,spi_buff,spi_data_size);

	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	while(spi_buff[2]==0xf3){}
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);

	HAL_TIM_Base_Start_IT(&htim6);



}

void Loop(){
}

int v_ref=0;

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	HAL_SPI_Receive_IT(&hspi1,spi_buff,spi_data_size);
	if(spi_buff[0]==0 && spi_buff[1]==0 && spi_buff[2]==0)spi_buff[2]=1;//配列がすべて0のときがあるけどこれをそのまま通すと回ってる最中に目標値0が入ってガタっとするので目標値0を送るときだけ特殊な値を送るようにしている
	if(spi_buff[0]==0 && spi_buff[1]==0 && spi_buff[2]==0xf0)spi_buff[2]=0;//意図的に目標値0をｋ送るとき最後のビットは0xf0にすることにしているのでこんな感じ

	if(spi_buff[2]==spi_buff[0]^spi_buff[1]){
		v_ref=(int16_t)((((uint16_t)spi_buff[0])<<8) |((uint16_t)spi_buff[1]));
	}

}


void TimerInterrupt(){//10msおきに呼ばれる
	static int pre_data=0;

//	if((pre_data-vel>200)||(pre_data-vel<-200))vel=pre_data; //目標値の変化量が大きすぎるときは通信が怪しいのでそのままの値にする

//	if(spi[2]==spi[0]^spi[1]){
//		pre_data=vel;
//		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
//		spi[2]=0xaa;
//	}else if(spi[2]==0xf3){
//		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//	}else{
//		vel=pre_data;
//		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//		spi[2]=0xaa;
//	}

	controller.SetReference(v_ref);

	encoder.Update();
	float v=encoder.GetVelocity();
	float output=controller.Update(v);

	const int lim=120;
	if(0<output && output<lim){
		output=lim*(-std::pow((output/lim-1),2)+1);
	}else if(-lim<output && output<0){
		output=lim*(std::pow((output/lim+1),2)-1);
	}
	motor.Drive(output);

	char po[15]={};
	int num = sprintf(po,"%d,%d\r\n",(int)v_ref,(int)v);

	Debug(po,num);

}
