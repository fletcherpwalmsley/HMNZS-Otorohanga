void display_data(){


// Code to output to the HC12 - Send in a way so that it can be read by the Python host code 
  HC12Serial.print(gps.location.lat(), 6);
  HC12Serial.print(F(","));
  HC12Serial.print(gps.location.lng(), 6);
  HC12Serial.print(F(","));
  HC12Serial.print(gps.speed.kmph(), 2);
  HC12Serial.print(F(","));
  HC12Serial.println(current_heading);
  SerialBT.print("Distance to Node(m): ");
  SerialBT.println(distanceTo);
  SerialBT.print("Course required: ");
  SerialBT.println(courseTo);
  SerialBT.print("Current Heading: ");
  SerialBT.println(current_heading);
  SerialBT.print("\n\n");
}
