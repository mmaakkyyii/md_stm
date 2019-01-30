#include "my_variable.h"

Encoder encoder(1, 1024*4, 10, 30);
Motor motor(1);
ControllerZPID controller(5.313f, 25.62f, 0.0f, 0.01f, 10.0f);



