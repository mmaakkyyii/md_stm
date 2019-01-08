#include "controller.h"

ControllerPID::ControllerPID():kp(0),ki(0),kd(0),e(0),sum_e(0),d_e(0){
}

ControllerPID::ControllerPID(float _kp,float _ki,float _kd):kp(_kp),ki(_ki),kd(_kd),e(0),sum_e(0),d_e(0){
}

float ControllerPID::Update(float x){
	return x;
}

void ControllerPID::Reset(){
	sum_e=0;
}

void ControllerBase::SetReference(float _reference){
	reference=_reference;

}

void ControllerPID::SetGain(float _kp,float _ki,float _kd){

}

float ControllerPID::GetReference(){
	return reference;
}


ControllerZPID::ControllerZPID(float _ts,float _fc):ControllerPID(),x_kdm1(0),y_kdm1(0),x_kim1(0),y_kim1(0),ts(_ts),n(_fc*2*3.141592){
}

ControllerZPID::ControllerZPID(float _kp,float _ki,float _kd,float _ts,float _fc):ControllerPID(_kp,_ki,_kd),x_kdm1(0),y_kdm1(0),x_kim1(0),y_kim1(0),ts(_ts),n(_fc*2*3.141592){
}

float ControllerZPID::Update(float x){
	return x;
}

void ControllerZPID::Reset(){
	sum_e=0;
}
