

void core_0_setup(){
  GPSSerial.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin);
  compass_setup();
  core_0_setup_done = 1;
}


//Loop Function (Must be last)

void core_0_loop()
{
  while(core_1_setup_done){
    get_gps_data();
    if (millis() > set_time_BNO055 + BNO055_SAMPLERATE_DELAY_MS){
      update_compass();
    set_time_BNO055 = millis();
    }
  }
}
