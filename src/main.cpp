#include <Arduino.h>
#include "Radio433.h"
#include "Brushed.h"
#include <Servo.h>
#include <Chrono.h>

#define UPDATE_INTERVAL 2000

int mapRangeToServo();
void ballIntakeUpdate();
void hatchUpdate();
void setBallMotors(bool intake, int speed);
void debug();

//Radio433 *radio = new Radio433();
Radio433 radio;
Chrono timer;

Servo hatchServo;
Servo ballServo;
Servo bladeServo;
Brushed lBallMotor(7,8,A3);
Brushed rBallMotor(9,10,A4);

void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  bladeServo.attach(5);
  hatchServo.attach(4);
  ballServo.attach(3);
  //Serial.begin(9600);
}

bool alternate = false;

void loop() {
  radio.update();
  if(timer.hasPassed(UPDATE_INTERVAL)) {
    timer.restart();
    //debug();
  }
  ballIntakeUpdate();
  hatchUpdate();
}

void debug() {
    if(alternate) {
      radio.packet.ballTheta = 110;
      radio.packet.outtakeBall = false;
      radio.packet.intakeBall = true;
      radio.packet.outtakeHatch = false;
      radio.packet.intakeHatch = true;
    }
    else {
      radio.packet.ballTheta = 160;
      radio.packet.intakeBall = false;
      radio.packet.outtakeBall = true;
      radio.packet.intakeHatch = false;
      radio.packet.outtakeHatch = true;
    }
    alternate = !alternate;
}

void ballIntakeUpdate() {
  ballServo.writeMicroseconds((radio.packet.ballTheta)*10);
  if(radio.packet.intakeBall){
    setBallMotors(true, 200);
  }
  else if(radio.packet.outtakeBall) {
    setBallMotors(false, 50);
  }
  else {
    setBallMotors(true, 0);
  }
}

void hatchUpdate() {
  hatchServo.writeMicroseconds((radio.packet.hatchTheta)*10);
  if(radio.packet.intakeHatch){
    bladeServo.writeMicroseconds(2000);
  }
  else if(radio.packet.outtakeHatch) {
    bladeServo.writeMicroseconds(1000);
  }
  else {
    bladeServo.writeMicroseconds(1500);
  }
}

int mapRangeToServo() {
  return 0;
}

void setBallMotors(bool intake, int speed) {
  lBallMotor.rotate((intake ? -1 : 1) * speed);
  rBallMotor.rotate((intake ? 1 : -1) * speed);
}