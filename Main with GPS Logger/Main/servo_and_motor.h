void calc_error(){
  //Calculate error, and compensate for discontinuit at north 
  error = courseTo - current_heading;
  if(error < -180)
  error += 360;
  else if(error > 180)
  error -= 360;  
  currentPoint = error;
}


void move_servo(){
  currentServoPos = (90 + outputVal);
//Add a deband to the servo movement
  if (abs(outputVal) > 3){
    myservo.write(currentServoPos);
  }
}

void controls_setup(){
  //Motor Output Setup
    //Servo Setup      
  myservo.attach(
        servoPin, 
        Servo::CHANNEL_NOT_ATTACHED, 
        0,
        180
    );

  myservo.write(90);
  delay(5000);
  pinMode(26, OUTPUT);
  myPID.setBangBang(100);
  //set PID update interval to 30ms
  myPID.setTimeStep(10);
  

}


//Motor
void set_speed(){
  //if ((motor_enable==0 ) || (distanceTo > 100000)){
  if (motor_enable==0 ){
    digitalWrite(26, LOW);
  }else{
    digitalWrite(26, HIGH); 
  }
}
