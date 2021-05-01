//GPS Related
#include <TinyGPS++.h>
#include <Ewma.h>
TinyGPSPlus gps;
HardwareSerial GPSSerial(2);
static const int RXPin = 16, TXPin = 17;
static const uint16_t GPSBaud = 9600;
double distanceTo = 10;
double courseTo;


//Paced loop varables
#define SERIAL_DELAY_PERIOD (2000)
unsigned long set_time = 0;
unsigned long set_time_BNO055 = 0;



//Compass Related
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>
/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (50)
#define BNO055_SAMPLERATE_DELAY_MS_STARTUP (500)
float dec_angle = 20.72;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

//Heading Variables
bool startUp = true; 
double gpsHeading = 0;
double gpsHeadingFiltered = 0;
double gpsHeadingFilteredLast = 0;
double gpsHeadingFilteredDelta = 0;
double IMUheadingCalc = 0;
double IMUHeadingSetPoint = 0;
double gpsHeadingSetPoint = 0;
int current_heading = 0;
sensors_event_t event;
int headingMode = 0;

//Heading Filter
Ewma gpsHeadingFilter(0.1);

//IMU Heading Watchdog
bool usingIMU = false;
unsigned long IMUheadingStartTime = 0;
#define IMU_HEADING_USEAGE_TIME (60000)


//SD Card Related
#include "FS.h"
#include "SD.h"
#include "SPI.h"
byte check_val;
uint16_t data_index = 0;
String inputdata;
float lat_data;
float long_data;
bool motor_enable = false;


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

#define OUTPUT_MIN -35
#define OUTPUT_MAX 35
#define KP 0.5
#define KI 0.0005
#define KD 0.1

double currentPoint, setPoint = 0, outputVal;

//PID input error vars
double error;
AutoPID myPID(&currentPoint, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);


//Data input 
int readData;
#define RECEIVE_PERIOD_START (100)
#define RECEIVE_PERIOD_STOP (1900)

//SD Print 
String latSDPrint="";
String lngSDPrint="";
