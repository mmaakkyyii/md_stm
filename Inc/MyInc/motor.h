#ifndef MOTOR_H_
#define MOTOR_H_

class Motor{
private:
	int dir;
public:
	Motor(int _dir);

	void Drive(float duty);
};

#endif //MOTOR_H_
