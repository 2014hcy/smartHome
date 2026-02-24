#ifndef ULTRALIB_H
#define ULTRALIB_H

#include "Arduino.h"

class Ultra {
private:
    int _trigPin;
    int _echoPin;

public:
    Ultra(int trigPin, int echoPin);
    float read();
};

#endif