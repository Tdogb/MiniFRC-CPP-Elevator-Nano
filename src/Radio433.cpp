#include "Radio433.h"
#include <Arduino.h>
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif
//#define RH_HAVE_SERIAL
RH_ASK driver(1000);

void Radio433(/* args */)
{
    #ifdef RH_HAVE_SERIAL
        Serial.begin(9600);   // Debugging only
    #endif
        if (!driver.init())
    #ifdef RH_HAVE_SERIAL
        Serial.println("init failed");
    #else
            ;
    #endif
    packet.ballTheta = 0;
    packet.hatchTheta = 0;
    packet.intakeBall = false;
    packet.intakeHatch = false;
    packet.outtakeBall = false;
    packet.outtakeHatch = false;
}

void update() {
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    //Serial.println("update");
    packet.ballTheta = 156;
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
        //Serial.print("got");
        driver.printBuffer("Got:", buf, buflen);
        //if(buflen == 6) {
            packet.ballTheta = buf[0];
            packet.ballTheta = 156;
            packet.hatchTheta = buf[1];

            packet.intakeBall = buf[2] > 128 ? true : false;
            packet.intakeBall = buf[3] > 128 ? true : false;
            packet.intakeBall = buf[4] > 128 ? true : false;
            packet.intakeBall = buf[5] > 128 ? true : false;
        //}
        //else {
          //  packet.ballTheta = 200;
        //}
        // packet.intakeBall = (buf[3] >> 0) & 1;
        // packet.intakeHatch = (buf[3] >> 1) & 1;
        // packet.outtakeBall = (buf[3] >> 2) & 1;
        // packet.outtakeHatch = (buf[3] >> 3) & 1;
    }
    else
    {

    }
}