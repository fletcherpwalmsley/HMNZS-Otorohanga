void displaySensorOffsets(const adafruit_bno055_offsets_t &calibData)
{
    SerialBT.print("Accelerometer: ");
    SerialBT.print(calibData.accel_offset_x); Serial.print(" ");
    SerialBT.print(calibData.accel_offset_y); Serial.print(" ");
    SerialBT.print(calibData.accel_offset_z); Serial.print(" ");

    SerialBT.print("\nGyro: ");
    SerialBT.print(calibData.gyro_offset_x); Serial.print(" ");
    SerialBT.print(calibData.gyro_offset_y); Serial.print(" ");
    SerialBT.print(calibData.gyro_offset_z); Serial.print(" ");

    SerialBT.print("\nMag: ");
    SerialBT.print(calibData.mag_offset_x); Serial.print(" ");
    SerialBT.print(calibData.mag_offset_y); Serial.print(" ");
    SerialBT.print(calibData.mag_offset_z); Serial.print(" ");

    SerialBT.print("\nAccel Radius: ");
    SerialBT.print(calibData.accel_radius);

    SerialBT.print("\nMag Radius: ");
    SerialBT.print(calibData.mag_radius);
}


void displayCalStatus(void)
{
    /* Get the four calibration values (0..3) */
    /* Any sensor data reporting 0 should be ignored, */
    /* 3 means 'fully calibrated" */
    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);

    /* The data should be ignored until the system calibration is > 0 */
    SerialBT.print("\t");
    if (!system)
    {
        SerialBT.print("! ");
    }

    /* Display the individual values */
    SerialBT.print("Sys:");
    SerialBT.print(system, DEC);
    SerialBT.print(" G:");
    SerialBT.print(gyro, DEC);
    SerialBT.print(" A:");
    SerialBT.print(accel, DEC);
    SerialBT.print(" M:");
    SerialBT.println(mag, DEC);
}

void compass_setup(){
  
    SerialBT.println("Orientation Sensor Test"); SerialBT.println("");
    EEPROM.begin(64);
    /* Initialise the sensor */
    if (!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        SerialBT.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1);
    }

    int eeAddress = 0;
    long bnoID;
    bool foundCalib = false;
    
    bnoID = EEPROM.read(eeAddress);

    adafruit_bno055_offsets_t calibrationData;
    sensor_t sensor;

    /*
    *  Look for the sensor's unique ID at the beginning oF EEPROM.
    *  This isn't foolproof, but it's better than nothing.
    */


    bno.getSensor(&sensor);
    SerialBT.println("Connected Sensors ID: ");
    SerialBT.println(sensor.sensor_id);
    SerialBT.println("Data Found in EEPROM: ");
    SerialBT.println(bnoID);
    delay(2000);
    /*
    if (bnoID != sensor.sensor_id)
    {
        SerialBT.println("\nNo Calibration Data for this sensor exists in EEPROM");
        delay(500);
    }
    else
    {
        SerialBT.println("\nFound Calibration for this sensor in EEPROM.");
        eeAddress += sizeof(long);
        EEPROM.get(eeAddress, calibrationData);
        displaySensorOffsets(calibrationData);

        SerialBT.println("\n\nRestoring Calibration data to the BNO055...");
        bno.setSensorOffsets(calibrationData);

        SerialBT.println("\n\nCalibration data loaded into BNO055");
        foundCalib = false;
        
    }
  */
  delay(10);

   /* Crystal must be configured AFTER loading calibration data into BNO055. */
    bno.setExtCrystalUse(true);

    sensors_event_t event;
    bno.getEvent(&event);
    /* always recal the mag as It goes out of calibration very often */
    if (foundCalib){
        SerialBT.println("Move sensor slightly to calibrate magnetometers");
        while (!bno.isFullyCalibrated())
        {
            bno.getEvent(&event);
            displayCalStatus();
            delay(1000);
        }
    }
    else
    {
        SerialBT.println("Please Calibrate Sensor: ");
        while (!bno.isFullyCalibrated())
        {
            bno.getEvent(&event);

            SerialBT.print("X: ");
            SerialBT.print(event.orientation.x, 4);
            SerialBT.print("\tY: ");
            SerialBT.print(event.orientation.y, 4);
            SerialBT.print("\tZ: ");
            SerialBT.print(event.orientation.z, 4);

            /* Optional: Display calibration status */
            displayCalStatus();

            /* New line for the next sample */
            SerialBT.println("");

            /* Wait the specified delay before requesting new data */
            delay(BNO055_SAMPLERATE_DELAY_MS_STARTUP);
        }
    }

    SerialBT.println("\nFully calibrated!");
    SerialBT.println("--------------------------------");
    SerialBT.println("Calibration Results: ");
    adafruit_bno055_offsets_t newCalib;
    bno.getSensorOffsets(newCalib);

    SerialBT.println("\n\nStoring calibration data to EEPROM...");

    eeAddress = 1;
    bno.getSensor(&sensor);
    bnoID = sensor.sensor_id;

    //EEPROM.put(eeAddress, bnoID);

    //eeAddress += sizeof(long);
   // EEPROM.put(eeAddress, newCalib);
    //EEPROM.commit();
    Serial.println("Data stored to EEPROM.");

    SerialBT.println("\n--------------------------------\n");
    delay(500);
}

bool isGPSHeadingValid(){
  gpsHeadingFilteredDelta = gpsHeadingFiltered - gpsHeadingFilteredLast;
  if(gpsHeadingFilteredDelta < -180)
    gpsHeadingFilteredDelta += 360;
  else if(gpsHeadingFilteredDelta > 180)
    gpsHeadingFilteredDelta -= 360;

    if ((gpsHeadingFilteredDelta > 4) || (gpsHeadingFiltered == 0))
      return(false);
    else
      return(true);
}

double IMUHeading(){
  bno.getEvent(&event);
  IMUheadingCalc = event.orientation.x - IMUHeadingSetPoint;
  if(IMUheadingCalc < -180)
    IMUheadingCalc += 360;
  else if(IMUheadingCalc > 180)
    IMUheadingCalc -= 360;  
  return(IMUheadingCalc);
}


void update_compass(){
    /* Get a new sensor event */
    /*

    SerialBT.println(event.orientation.x);
      
    if (event.orientation.x < (360 - dec_angle)){
      event.orientation.x = (event.orientation.x + dec_angle);
    }else{
      event.orientation.x = (event.orientation.x + dec_angle - 360);
    }
    */

    bno.getEvent(&event);

    //Get first heading from GPS after starting motors
    if((motor_enable) && (startUp)) {
      current_heading = round(courseTo);
      headingMode = 1;
      IMUHeading();
      if (isGPSHeadingValid()){
         startUp = false;
         usingIMU = false;
         gpsHeadingSetPoint = gpsHeadingFiltered;
         SerialBT.println("Setup Ended");
      }
      
      //Main Code that is to be used while underway
    }else if ((!startUp) && (gps.speed.kmph() > 2) && (isGPSHeadingValid()) && (distanceTo > 7.0)){  
      current_heading = gpsHeadingFiltered;
      gpsHeadingSetPoint = gpsHeadingFiltered;
      IMUHeadingSetPoint = event.orientation.x; 
      usingIMU = false; 
      headingMode = 2;
    }else{
      headingMode = 3;
      current_heading = gpsHeadingSetPoint + IMUHeading();
      //if IMU heading has been used for too long, set startUp flag back to true to get another datum
      if (!usingIMU){
        IMUheadingStartTime = millis();
        usingIMU = true; 
      }
      if (millis() > IMUheadingStartTime + IMU_HEADING_USEAGE_TIME){
        startUp = true;
    }
     
    } 
}
