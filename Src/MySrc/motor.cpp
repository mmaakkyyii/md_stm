#include "motor.h"
#include "tim.h"
#include "gpio.h"

Motor::Motor(int _dir){
	if(_dir == 1 || _dir == -1)dir=_dir;
	else dir=1;

}

void Motor::PWM(int duty){
	if(duty<0)duty*=-1;
	TIM_OC_InitTypeDef sConfigOC;

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = duty;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	HAL_TIM_PWM_ConfigChannel(&htim3,&sConfigOC,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);

}
void Motor::Drive(float duty){//0~2400
	duty*=dir;
	PWM(duty);
	HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port, MOTOR_EN_Pin,GPIO_PIN_SET);

	if(duty<0){
		HAL_GPIO_WritePin(MOTOR_IN_A_GPIO_Port, MOTOR_IN_A_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_IN_B_GPIO_Port, MOTOR_IN_B_Pin,GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(MOTOR_IN_A_GPIO_Port, MOTOR_IN_A_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_IN_B_GPIO_Port, MOTOR_IN_B_Pin,GPIO_PIN_SET);
	}

}
