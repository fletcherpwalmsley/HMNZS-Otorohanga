
bool at_destination(){
  if(distanceTo < 4.0){
    HC12Serial.println("Destination Reached, Reading Next Location");
    return true;
}return false;
  
}

void update_delta(){
        distanceTo =
        TinyGPSPlus::distanceBetween(
          gps.location.lat(),
          gps.location.lng(),
          lat_data, 
          long_data);
       courseTo =
        TinyGPSPlus::courseTo(
          gps.location.lat(),
          gps.location.lng(),
          lat_data, 
          long_data);
}


void get_gps_data(){
    // This sketch displays information every time a new sentence is correctly encoded.
  while (GPSSerial.available() > 0){
    if (gps.encode(GPSSerial.read()))
    {
      update_delta();
      if (gps.course.isUpdated()){
        gpsHeading = gps.course.deg();
        gpsHeadingFilteredLast = gpsHeadingFiltered;
        gpsHeadingFiltered = gpsHeadingFilter.filter(gpsHeading);
      }
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    SerialBT.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
