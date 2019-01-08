#include "motor.h"
#include "tim.h"

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
void Motor::Drive(float duty){
	duty*=dir;
	PWM(duty);

}
