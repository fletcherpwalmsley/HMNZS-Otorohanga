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
     /*
      if (motor_enable){
        writeToSD();
      }
      */
      set_time = millis();
    }
    if (at_destination()){
      //motor_enable =0;
      //set_speed();
      readFile(SD, "/map.txt");
      delay(2000);
      motor_enable =1;
     // set_speed();
    } 

    if((millis() > (set_time + RECEIVE_PERIOD_START)) && (millis() < (set_time + RECEIVE_PERIOD_STOP))){
      receive_commands();
    }
}
