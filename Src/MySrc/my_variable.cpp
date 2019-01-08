#include "my_variable.h"

Encoder encoder(1, 4098*4, 1, 1);
Motor motor(1);
ControllerZPID controller(0.10f, 0.0f, 0.0f, 1.0f, 10.0f);



