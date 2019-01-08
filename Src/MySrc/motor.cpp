#include "motor.h"

Motor::Motor(int _dir){
	if(_dir == 1 || _dir == -1)dir=_dir;
	else dir=1;
}

void Motor::Drive(float duty){
	duty*=dir;

}
