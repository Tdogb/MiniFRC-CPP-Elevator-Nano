// #include "Radio433.h"
// #include <Arduino.h>
// #include <RH_ASK.h>
// #ifdef RH_HAVE_HARDWARE_SPI
// #include <SPI.h> // Not actually used but needed to compile
// #endif
// //#define RH_HAVE_SERIAL
// RH_ASK driver(1000);

// void initRadio(/* args */)
// {
//     #ifdef RH_HAVE_SERIAL
//         Serial.begin(9600);   // Debugging only
//     #endif
//         if (!driver.init())
//     #ifdef RH_HAVE_SERIAL
//         Serial.println("init failed");
//     #else
//             ;
//     #endif
//     packetRadio.ballTheta = 0;
//     packetRadio.hatchTheta = 0;
//     packetRadio.intakeBall = false;
//     packetRadio.intakeHatch = false;
//     packetRadio.outtakeBall = false;
//     packetRadio.outtakeHatch = false;
// }

// void updateRadio() {
//     uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
//     uint8_t buflen = sizeof(buf);
//     //Serial.println("update");
//     packetRadio.ballTheta = 156;
//     if (driver.recv(buf, &buflen)) // Non-blocking
//     {
//         //Serial.print("got");
//         driver.printBuffer("Got:", buf, buflen);
//         //if(buflen == 6) {
//             packetRadio.ballTheta = buf[0];
//             packetRadio.ballTheta = 156;
//             packetRadio.hatchTheta = buf[1];

//             packetRadio.intakeBall = buf[2] > 128 ? true : false;
//             packetRadio.intakeBall = buf[3] > 128 ? true : false;
//             packetRadio.intakeBall = buf[4] > 128 ? true : false;
//             packetRadio.intakeBall = buf[5] > 128 ? true : false;
//         //}
//         //else {
//           //  packetRadio.ballTheta = 200;
//         //}
//         // packetRadio.intakeBall = (buf[3] >> 0) & 1;
//         // packetRadio.intakeHatch = (buf[3] >> 1) & 1;
//         // packetRadio.outtakeBall = (buf[3] >> 2) & 1;
//         // packetRadio.outtakeHatch = (buf[3] >> 3) & 1;
//     }
//     else
//     {

//     }
// }