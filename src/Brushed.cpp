#include <Arduino.h>
#include "Brushed.h"
#include <stdint.h>

Brushed::Brushed(int _FWDPin, int _RVSPin, int _ENPin)
{
    FWDPin = _FWDPin;
    RVSPin = _RVSPin;
    ENPin = _ENPin;
    pinMode(FWDPin, OUTPUT);
    pinMode(RVSPin, OUTPUT);
    // analogWriteFrequency(FWDPin, 600);
    // analogWriteFrequency(RVSPin, 600);
    digitalWrite(RVSPin, LOW);
    digitalWrite(FWDPin, LOW);
}

Brushed::~Brushed()
{
}

void Brushed::rotate(int speed) {
    if(speed > 128) {
        speed = 128;
    }
    if(speed < -128) {
        speed = -128;
    }
    if(speed > 0) {
        digitalWrite(RVSPin, LOW);
        digitalWrite(FWDPin, HIGH);
    }
    else {
        digitalWrite(FWDPin, LOW);
        digitalWrite(RVSPin, HIGH);
    }
    analogWrite(ENPin, abs(speed));
    // if(speed > 0) {
    //     analogWrite(RVSPin, 0);
    //     //Serial.println(map(speed, 0, 100, 0, 256));
    //     analogWrite(FWDPin, speed*2);
    // }
    // else
    // {
    //     analogWrite(FWDPin, 0);
    //     //Serial.println("reverse");
    //     analogWrite(RVSPin, abs(speed)*2);
    // }
}