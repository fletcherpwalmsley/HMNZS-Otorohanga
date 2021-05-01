

void core_0_setup(){
  GPSSerial.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin);
  controls_setup();
  compass_setup();

}


//Loop Function (Must be last)

void core_0_loop()
{
    get_gps_data();
    if (millis() > set_time_BNO055 + BNO055_SAMPLERATE_DELAY_MS){
      update_compass();
    set_time_BNO055 = millis();
    }
    
    calc_error();
    myPID.run();
    move_servo();
    set_speed();
}
