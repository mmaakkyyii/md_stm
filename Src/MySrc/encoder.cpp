#include "encoder.h"
#include "tim.h"

Encoder::Encoder(int _dir, int _ppr, int _period_ms, float _radius):
	ppr(_ppr),period_ms(_period_ms),radius(_radius){
	if(_dir==1 || _dir==-1)dir=_dir;
}

static const int16_t ENC_ZERO=0x7FFF;

int Encoder::GetPulse(){
	int pulse=TIM1->CNT;
	TIM1->CNT=ENC_ZERO;
	return pulse-ENC_ZERO;
}
float Encoder::GetAngularvelocity(){
	return (float)GetPulse() / (float)ppr * 2.0f * 3.141592f;
}
float Encoder::GetVelocity(){
	return GetAngularvelocity()*radius;
}
