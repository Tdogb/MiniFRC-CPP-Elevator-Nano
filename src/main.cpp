#include <Arduino.h>
#include "Brushed.h"
#include <Servo.h>
#include <Chrono.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

//#define RH_HAVE_SERIAL
//RH_ASK driver(1000);

#define UPDATE_INTERVAL 100

int mapRangeToServo();
void ballIntakeUpdate();
void hatchUpdate();
void setBallMotors(bool intake, int speed);
void debug();
void updateBT();
struct packet_t {
    uint8_t ballTheta; //from -128 to 128
    uint8_t hatchTheta;
    bool intakeBall;
    bool intakeHatch;
    bool outtakeBall;
    bool outtakeHatch;
};
packet_t packet = {0,0,false, false, false, false};
int tempbt = 0;
//Radio433 *radio = new Radio433();
// Radio433 radio;
Chrono timer;

SoftwareSerial neoSerial(2, 3);

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
  //neoSerial.setTimeout(15);
  Serial.begin(9600);
  Serial.println("Serial started");
  neoSerial.begin(9600); 
  Serial.println("Neoserial started"); 
}

bool alternate = false;

void loop() {
  updateBT();
  if(timer.hasPassed(UPDATE_INTERVAL)) {
    timer.restart();
    ballIntakeUpdate();
    hatchUpdate();
  }
}

// void updateBT() {
//   uint8_t buffer[4];
//   int8_t** bufferConvert[4];
//   if(neoSerial.available() > 0) {
//     neoSerial.readBytesUntil('~', buffer, sizeof(buffer));
//   }
// }

bool updateData = false;
int iterator = 0;
int8_t garbage = 0;
bool startFound = false;
int8_t tempPacket[4];
void updateBT() {
    if(neoSerial.available() > 0) {
        if(!startFound) {
            int8_t in = neoSerial.read();
            //Serial.println(in);
            if(in == '~') {
                startFound = true;
                //Serial.println("Found");
            }
        }
        else {
          //Serial.println(neoSerial.peek());
            if(iterator == 3) {
                garbage = neoSerial.read();
                if(garbage != '~') {startFound = false;}
                updateData = true;
                iterator = 0;
                //Serial.println("");
            }
            else {
                tempPacket[iterator] = neoSerial.read();
                //Serial.print(packet[iterator]);
                //Serial.print(" ");
                iterator++;
            }
        }
        if(updateData) {
            packet.ballTheta = tempPacket[0];
            packet.hatchTheta = tempPacket[1];
            //Serial.println(tempPacket[2]);
            // switch (tempPacket[2])
            // {
            // case 1:
            //   packet.intakeBall = true;
            //   packet.outtakeBall = false;
            //   packet.intakeHatch = false;
            //   packet.outtakeHatch = false;
            //   break;
            // case 5: //both on
            //   packet.intakeBall = true;
            //   packet.intakeHatch = true;
            //   break;
            // case 6: //Right on, left off
            //   packet.intakeBall = false;
            //   packet.intakeHatch = true;
            //   break;
            // case 9: //Right off, left on
            //   packet.intakeHatch = false;
            //   packet.intakeBall = true;
            //   break;

            // case 10: //both off
            //   packet.intakeHatch = false;
            //   packet.intakeBall = false;
            //   break;
            // default:
            //   break;
            // }
            packet.intakeBall = bitRead(tempPacket[2], 0);
            packet.outtakeBall = bitRead(tempPacket[2], 1);
            packet.intakeHatch = bitRead(tempPacket[2], 2);
            packet.outtakeHatch = bitRead(tempPacket[2], 3);
        }
    }
    // Serial.println("");
    // Serial.print(packet.ballTheta);
    // Serial.print(" ");
    // Serial.print(packet.hatchTheta);
    // Serial.print(" ");
    // Serial.print(packet.intakeBall);
    // Serial.print(" ");
    // Serial.print(packet.intakeHatch);
    // Serial.print(" ");
    // Serial.print(packet.outtakeBall);
    // Serial.print(" ");
    // Serial.print(packet.outtakeHatch);
}

/*
One press: raise ball intake rocket, 2 press: raise ball intake cargoship
Start: 2250
Rocket Ball: 1600?

Intake: 750
*/
void ballIntakeUpdate() {
  ballServo.writeMicroseconds(map(packet.ballTheta, 0, 90, 750, 2250)); //1300 is horizontal 
  //Serial.println(map(packet.ballTheta, 0, 90, 1000,2000));
  //ballServo.writeMicroseconds(tempbt*10);

  if(packet.intakeBall){
    setBallMotors(true, 127);
    //Serial.println("Intake ball");
  }
  else if(packet.outtakeBall) {
    setBallMotors(false, 127);
  }
  else {
    //ballServo.writeMicroseconds(map(packet.ballTheta, 0, 90, 800,1600));
    setBallMotors(true, 0);
  }
}

void hatchUpdate() {
  //hatchServo.writeMicroseconds(map(packet.hatchTheta, 0, 90, 1087,2100)); //1846
  if(packet.intakeHatch){
    hatchServo.writeMicroseconds(1846);
    bladeServo.writeMicroseconds(1700);
  }
  else if(packet.outtakeHatch) {
    hatchServo.writeMicroseconds(1846); //2100
    bladeServo.writeMicroseconds(1300);
  }
  else {
    hatchServo.writeMicroseconds(1846); //2100
    bladeServo.writeMicroseconds(1566);
  }
}

int mapRangeToServo() {
  return 0;
}

void setBallMotors(bool intake, int speed) {
  lBallMotor.rotate((intake ? 1 : -1) * speed);
  rBallMotor.rotate((intake ? -1 : 1) * speed);
}

// void debug() {
//     if(alternate) {
//       packet.ballTheta = 110;
//       packet.outtakeBall = false;
//       packet.intakeBall = true;
//       packet.outtakeHatch = false;
//       packet.intakeHatch = true;
//     }
//     else {
//       packet.ballTheta = 160;
//       packet.intakeBall = false;
//       packet.outtakeBall = true;
//       packet.intakeHatch = false;
//       packet.outtakeHatch = true;
//     }
//     alternate = !alternate;
// }