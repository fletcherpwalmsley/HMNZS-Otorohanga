//Inculde Related
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h> 

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (200)
#define BNO055_SAMPLERATE_DELAY_MS_STARTUP (500)
float dec_angle = 0; //20.72 <<-- Correct Det (might need to revisit this number, as zero seems to give better results)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);


int update_compass(){
  
    sensors_event_t event;
    bno.getEvent(&event);

    if (event.orientation.x < (360 - dec_angle)){
      event.orientation.x = (event.orientation.x + dec_angle);
    }else{
      event.orientation.x = (event.orientation.x + dec_angle - 360);
    }
    return round(event.orientation.x);
}


void data_send(bool state, bool setup_method){

  //Get BNO055 Status
   uint8_t system, gyro, accel, mag;
   system = gyro = accel = mag = 0;
   bno.getCalibration(&system, &gyro, &accel, &mag);

  if (state == 1){
    Serial.print(state);
    Serial.print(',');
    Serial.print(setup_method);
    Serial.print(',');
    Serial.print(system);
    Serial.print(',');
    Serial.print(gyro);
    Serial.print(',');
    Serial.print(accel);
    Serial.print(',');
    Serial.print(mag);
    Serial.println();
  }else{
    Serial.print(state);
    Serial.print(',');
    Serial.print(update_compass());
    Serial.print(',');
    Serial.print(system);
    Serial.print(',');
    Serial.print(gyro);
    Serial.print(',');
    Serial.print(accel);
    Serial.print(',');
    Serial.print(mag);
    Serial.println();
  }  
}


void compass_setup(){
  
    if (!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1);
    }

    int eeAddress = 0;
    long bnoID;
    bool foundCalib = false;

    EEPROM.get(eeAddress, bnoID);
    adafruit_bno055_offsets_t calibrationData;
    sensor_t sensor;
    bno.getSensor(&sensor);
    EEPROM.write(eeAddress, bnoID);
    delay(1000);
    
    if (bnoID == sensor.sensor_id){
        eeAddress += sizeof(long);
        EEPROM.get(eeAddress, calibrationData);
        bno.setSensorOffsets(calibrationData);
        foundCalib = true;
    }
    delay(1000);

   /* Crystal must be configured AFTER loading calibration data into BNO055. */
    bno.setExtCrystalUse(true);
    sensors_event_t event;
    bno.getEvent(&event);
    
    while (!bno.isFullyCalibrated()){
        data_send(1, foundCalib);
        delay(BNO055_SAMPLERATE_DELAY_MS_STARTUP);
    }
    adafruit_bno055_offsets_t newCalib;
    bno.getSensorOffsets(newCalib);
    eeAddress = 0;
    bno.getSensor(&sensor);
    bnoID = sensor.sensor_id;

    EEPROM.put(eeAddress, bnoID);
    eeAddress += sizeof(long);
    EEPROM.put(eeAddress, newCalib);
    delay(500);
}


void setup() {
  Serial.begin(9600);
  compass_setup();
}


void loop() {
  data_send(0, 2);
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
