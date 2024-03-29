void display_data()
{
    // Code to output to the HC12 - Send in a way so that it can be read by the Python host code
    HC12Serial.print(gps.location.lat(), 6);
    HC12Serial.print(F(","));
    HC12Serial.print(gps.location.lng(), 6);
    HC12Serial.print(F(","));
    HC12Serial.print(gps.speed.kmph(), 2);
    HC12Serial.print(F(","));
    HC12Serial.println(current_heading);
    SerialBT.print("Current Way Point");
    SerialBT.println(data_index);

    SerialBT.print("Distance to Node(m): ");
    SerialBT.println(distanceTo);
    SerialBT.print("Course required: ");
    SerialBT.println(courseTo);
    SerialBT.print("Current Heading: ");
    SerialBT.println(current_heading);

    //Show IMU Status
    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);
    SerialBT.print("Sys:");
    SerialBT.print(system, DEC);
    SerialBT.print(" G:");
    SerialBT.print(gyro, DEC);
    SerialBT.print(" A:");
    SerialBT.print(accel, DEC);
    SerialBT.print(" M:");
    SerialBT.println(mag, DEC);
    SerialBT.println();
}

void receive_commands()
{
    // HC12Serial.flush();
    while (HC12Serial.available() > 0) {
        SerialBT.println("Data Received");
        readData = HC12Serial.read();
        SerialBT.println(readData);
        if (readData == 49) {
            motor_enable = 1;
            SerialBT.println("Motor On");
        }
        if (readData == 48) {
            motor_enable = 0;
            SerialBT.println("Motor Off");
        }
    }
}

//Write the current gps location to SD

void writeToSD()
{
    File fileSDWrite = SD.open("data.txt", FILE_WRITE);
    fileSDWrite.print(gps.location.lat());
    fileSDWrite.print(",");
    fileSDWrite.println(gps.location.lng());
    fileSDWrite.close();
}
