void core_1_setup(){
  delay(3000);
   if(!SD.begin()){
        Serial.println("Card Mount Failed");
       return;
    }
  readFile(SD, "/map.txt");

}

void core_1_loop(){
    if (millis() > set_time + SERIAL_DELAY_PERIOD){
      display_data();
      set_time = millis();
    }
    if (at_destination()){
      readFile(SD, "/map.txt");
    } 

    if((millis() > (set_time + RECEIVE_PERIOD_START)) && (millis() > (set_time + RECEIVE_PERIOD_START))){
      receive_commands();
    }
}
