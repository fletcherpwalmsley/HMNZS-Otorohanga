/*
 * HMNZS Controller Code for an ESP32 running Ardinuo
 * Created by Fletcher Walmsley
 * Project Started Jan, 2020
 * File Created 13/
 
    o
o      ______/~/~/~/__           /((
  o  // __            ====__    /_((
 o  //  @))       ))))      ===/__((
    ))           )))))))        __((
    \\     \)     ))))    __===\ _((
     \\_______________====      \_((
                                 \((
 */



//////////////////////////////////////////////////
// Global Variables (Mainly Communication)
//////////////////////////////////////////////////



//////////////////////////////////////////////////
// Includes for the other code headers
//////////////////////////////////////////////////
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#include "setup_decs.h"
#include "gps.h"
#include "compass.h"
#include "sd_code.h"
#include "servo_and_motor.h"
#include "communication.h"
#include "core_0.h"
#include "core_1.h"


void setup() {
  SerialBT.begin("ESP32test"); 
  HC12Serial.begin(HC12Baud, SERIAL_8N1, HC12TXPin, HC12RXPin);
  delay(1000);      
  core_0_setup();
  delay(1000);
  core_1_setup();
}

void loop() {
  core_0_loop();
  core_1_loop(); 
}
