//GPS Related
#include <TinyGPS++.h>
TinyGPSPlus gps;
HardwareSerial GPSSerial(2);
static const int RXPin = 16, TXPin = 17;
static const uint16_t GPSBaud = 9600;
double distanceTo = 10;
double courseTo;


//Paced loop varables
#define SERIAL_DELAY_PERIOD (1500)
unsigned long set_time = 0;
unsigned long set_time_BNO055 = 0;


//Compass Related
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>
/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
float dec_angle = 20.72;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
int current_heading = 0;



//SD Card Related
#include "FS.h"
#include "SD.h"
#include "SPI.h"
byte check_val;
uint16_t data_index = 0;
String inputdata;
float lat_data;
float long_data;
bool file_end = false;


//HC-12 Setup
HardwareSerial HC12Serial(1);
static const uint16_t HC12Baud = 1200;
static const int HC12RXPin = 2, HC12TXPin = 15;


//PID and Servo setup
#include <AutoPID.h>
#include <Servo.h>
Servo myservo;
static const int servoPin = 4;
int currentServoPos = 90;

#define OUTPUT_MIN -55
#define OUTPUT_MAX 55
#define KP 0.5
#define KI 0.0005
#define KD 0.1

double currentPoint, setPoint = 0, outputVal;

//PID input error vars
double error;
AutoPID myPID(&currentPoint, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
