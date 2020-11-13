void display_data(){


// Code to output to the HC12 - Send in a way so that ir can be read by the Python host code 
//  HC12Serial.print(gps.location.lat(), 6);
//  HC12Serial.print(F(","));
//  HC12Serial.print(gps.location.lng(), 6);
//  HC12Serial.print(F(","));
//  HC12Serial.print(gps.speed.kmph(), 2);
//  HC12Serial.print(F(","));
//  HC12Serial.println(compass.getAzimuth());
  Serial.println(distanceTo);
  Serial.println(courseTo);
    
}
