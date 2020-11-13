void core_1_setup(){
  
}

void core_1_loop(){
  if (millis() > set_time + period){
    display_data();
    set_time = millis();
  }
}
