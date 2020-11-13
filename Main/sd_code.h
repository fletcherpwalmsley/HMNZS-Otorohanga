void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }
    
    while(file.available()){
        check_val = file.read();
          if (check_val == '['){
           check_val = file.parseInt();
            if (check_val == data_index){
              file.seek(file.position()+1);  //move the read pointer past the close square bracket
              inputdata = file.readStringUntil(';');
              data_index++;
              
              //Create Temp char aray to store the string in 
              char inputdata_array[inputdata.length()+1];
              inputdata.toCharArray(inputdata_array, inputdata.length()+1);

              char * strtokIndex;
              strtokIndex = strtok(inputdata_array, ",");
              lat_data = atof(strtokIndex);
              strtokIndex = strtok(NULL, ",");
              long_data = atof(strtokIndex);
              return;
            }
               
          }
    }
    SerialBT.println("The file is at its end");
    file_end = true;
    file.close();
}
