#include "encoder.h"

Encoder::Encoder(int _dir, int _ppr, int _period_ms, float _radius):
	ppr(_ppr),period_ms(_period_ms),radius(_radius){
	if(_dir==1 || _dir==-1)dir=_dir;
}

float Encoder::GetPulse(){
	return 0;
}
float Encoder::GetAngularvelocity(){
	return GetPulse() / (float)ppr * 2.0f * 3.141592f;
}
float Encoder::GetVelocity(){
	return GetAngularvelocity()*radius;
}
