

void core_0_setup(){
  GPSSerial.begin(GPSBaud, SERIAL_8N1, TXPin, RXPin);
}


//Loop Function (Must be last)

void core_0_loop()
{
  get_gps_data();
}
