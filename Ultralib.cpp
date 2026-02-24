#include "Arduino.h"
#include "Ultralib.h"

Ultra::Ultra(int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;

  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);

  digitalWrite(_trigPin, LOW);
  delay(100);
}

float Ultra::read() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH, 30000);

    if (duration == 0) {
        return 0;
    }
    
    float distance = duration * 0.034 / 2;
    
    return distance;
}