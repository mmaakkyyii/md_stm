#ifndef _ENCODER_H_
#define _ENCODER_H_

class Encoder{
private:
	int dir;
	int ppr;
	int period_ms;
	float radius;
public:
	Encoder(int _dir, int _ppr, int _period_ms, float _radius);
	float GetPulse();
	float GetAngularvelocity();
	float GetVelocity();
};

#endif //_ENCODER_H_
