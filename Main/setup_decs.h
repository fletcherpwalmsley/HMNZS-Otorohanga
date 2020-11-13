//GPS Related

#include <TinyGPS++.h>
TinyGPSPlus gps;
HardwareSerial GPSSerial(2);
static const int RXPin = 16, TXPin = 17;
static const uint16_t GPSBaud = 9600;
double distanceTo = 10;
double courseTo;



//Paced loop varables
int period = 1500;
unsigned long set_time = 0;



//Compass Related
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>
