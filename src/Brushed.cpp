// #include <Arduino.h>
// #include "Brushed.h"
// #include <stdint.h>

// Brushed::Brushed(int _FWDPin, int _RVSPin, int _ENPin)
// {
//     FWDPin = _FWDPin;
//     RVSPin = _RVSPin;
//     ENPin = _ENPin;
//     pinMode(FWDPin, OUTPUT);
//     pinMode(RVSPin, OUTPUT);
//     // analogWriteFrequency(FWDPin, 600);
//     // analogWriteFrequency(RVSPin, 600);
//     digitalWrite(RVSPin, LOW);
//     digitalWrite(FWDPin, LOW);
// }

// Brushed::~Brushed()
// {
// }

// void Brushed::rotate(int speed) {
//     if(speed > 128) {
//         speed = 128;
//     }
//     if(speed < -128) {
//         speed = -128;
//     }
//     if(speed > 0) {
//         digitalWrite(RVSPin, LOW);
//         digitalWrite(FWDPin, HIGH);
//     }
//     else {
//         digitalWrite(FWDPin, LOW);
//         digitalWrite(RVSPin, HIGH);
//     }
//     analogWrite(ENPin, abs(speed));
//     // if(speed > 0) {
//     //     analogWrite(RVSPin, 0);
//     //     //Serial.println(map(speed, 0, 100, 0, 256));
//     //     analogWrite(FWDPin, speed*2);
//     // }
//     // else
//     // {
//     //     analogWrite(FWDPin, 0);
//     //     //Serial.println("reverse");
//     //     analogWrite(RVSPin, abs(speed)*2);
//     // }
// }
#include <Arduino.h>
#include "Brushed.h"
#include <stdint.h>

Brushed::Brushed(int _FWDPin, int _RVSPin, int _enPin)
{
    FWDPin = _FWDPin;
    RVSPin = _RVSPin;
    enPin = _enPin;
    enPinMode = (_enPin >= 0);
    pinMode(FWDPin, OUTPUT);
    pinMode(RVSPin, OUTPUT);
    if(!enPinMode) {
    }
    else {
        pinMode(enPin, OUTPUT);
    }
}

void Brushed::rotate(int speed) {
    if(speed > 128) {
        speed = 128;
    }
    if(speed < -128) {
        speed = -128;
    }
    if(speed > 0) {
        if(enPinMode) {
            digitalWrite(RVSPin, LOW);
            digitalWrite(FWDPin, HIGH);
            analogWrite(enPin, speed*2);
        }
        else {
            analogWrite(RVSPin, 0);
            analogWrite(FWDPin, speed*2);
        }
    }
    else {
        if(enPinMode) {
            digitalWrite(FWDPin, LOW);
            digitalWrite(RVSPin, HIGH);
            analogWrite(enPin, abs(speed*2));
        }
        else {
            analogWrite(FWDPin, 0);
            analogWrite(RVSPin, abs(speed)*2);
        }
    }
}

void Brushed::ramp() {
    
}