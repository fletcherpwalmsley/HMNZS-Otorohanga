const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
bool state = 1;
bool load_method = 0;
int heading_mode = 0;
int sys = 0;
int gyro = 0;
int accl = 0;
int mago = 0;
boolean newData = false;

#define RXD2 16
#define TXD2 17

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(1200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}


void loop() {
    request_data();
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
    delay(100);
}

//============

void request_data(){
  // This is the only that the esp32 sends to the nano
  // It will simply trigger a response
  Serial2.print(1);
}


void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    
    delay(1); // Give the poor Nano sometime to respond
    while (Serial2.available() > 0 && newData == false) {
        rc = Serial2.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;         
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // Get index of the first comma
    state = atoi(strtokIndx);  // Copy every before the index

    strtokIndx = strtok(NULL, ","); 
    heading_mode = atoi(strtokIndx);     

    strtokIndx = strtok(NULL, ","); 
    sys = atoi(strtokIndx);   

    strtokIndx = strtok(NULL, ","); 
    gyro = atoi(strtokIndx);     

    strtokIndx = strtok(NULL, ","); 
    accl = atoi(strtokIndx);   

    strtokIndx = strtok(NULL, ","); 
    mago = atoi(strtokIndx);   
}

//============

void showParsedData() {
//    Serial.print("state ");
//    Serial.println(state);
    Serial.print("heading_mode ");
    Serial.print(heading_mode);
    Serial.print(" sys ");
    Serial.print(sys);
    Serial.print(" gyro ");
    Serial.print(gyro);
    Serial.print(" accl ");
    Serial.print(accl);
    Serial.print(" mago ");
    Serial.println(mago);
}
