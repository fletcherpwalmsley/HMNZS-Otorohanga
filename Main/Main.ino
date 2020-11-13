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



TaskHandle_t Task1;
TaskHandle_t Task2;

//////////////////////////////////////////////////
// Global Variables (Mainly Communication)
//////////////////////////////////////////////////



//////////////////////////////////////////////////
// Inculdes for the other code headers
//////////////////////////////////////////////////

#include "setup_decs.h"
#include "gps.h"
#include "compass.h"
#include "sd_code.h"
#include "communication.h"
#include "core_0.h"
#include "core_1.h"


void setup() {
  Serial.begin(115200); 
  HC12Serial.begin(HC12Baud, SERIAL_8N1, HC12TXPin, HC12RXPin);
  delay(2000);
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    50000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(1000); 
    
    core_0_setup();
    core_1_setup();
    //Always last


}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
  core_0_loop();
  delay(1);
  } 
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
  core_1_loop();
  delay(1);
  }
}

void loop() {
  
}
