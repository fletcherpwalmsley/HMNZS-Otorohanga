void core_1_setup(){
  delay(3000);
   if(!SD.begin()){
        Serial.println("Card Mount Failed");
       return;
    }
  readFile(SD, "/map.txt");
  core_1_setup_done = 1;
}

void core_1_loop(){
  while(core_0_setup_done){
    if (millis() > set_time + SERIAL_DELAY_PERIOD){
      display_data();
      set_time = millis();
    }
    if (at_destination()){
      readFile(SD, "/map.txt");
  } 
  } 
}
