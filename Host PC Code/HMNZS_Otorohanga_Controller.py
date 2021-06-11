import serial
import time
import msvcrt

heading = 0
cycle_count = 0
sail_start = False


print("\n\nWelcome to the HMNZS Control Pannel\n")
time.sleep(1)
print("This python script controls communication between the PC and the craft,\nalong with displaying the incoming GPS data in Google maps,\nmake sure that the 'auto_update_boat.kml' in the same directory as this program has been loaded into Google earth\n")
time.sleep(1)
print("To upload at map file to the craft, press 'u'\n")
time.sleep(1)
print("To start the crafts voyage, press 'g'\n")
time.sleep(1)
print("To to force the craft to return home, press 'h'\n")
time.sleep(1)
print("Connection to the HMNZS Otorohanga will now be made\n")

serialcomm = serial.Serial('COM9', 1200)
serialcomm.timeout = 1

print("Connection Successful!")

while True:
    raw = serialcomm.readline().decode('ascii')
    data = raw.split(",")
    print(raw)
    if len(data) == 4:
        cycle_count = cycle_count + 1
        with open ("position.kml", "w") as pos:
            pos.write("""
            <kml xmlns="http://www.opengis.net/kml/2.2" xmlns:gx="http://www.google.com/kml/ext/2.2">
            <Placemark>
                <name>kph = {2}</name>
                <description>Current Location of the HMNZS Otorohanga, Update #{4}</description>
                    <LookAt>
                        <longitude>{0}</longitude>
                        <latitude>{1}</latitude>
                        <range>200</range>
                        <tilt>0</tilt>
                        <heading>0</heading>
                    </LookAt>
                    <Style id="track_n">
                        <IconStyle>
                            <scale>1</scale>
                            <heading>{3}</heading>
                            <Icon>
                                <href>http://maps.google.com/mapfiles/kml/shapes/track.png</href>
                            </Icon>
                        </IconStyle>
                        <LabelStyle>
                            <scale>0.65</scale>
                        </LabelStyle>
                        <Orientation>
                            <heading>90</heading>
                        </Orientation> 
                    </Style>
                    <Point>
                        <coordinates>{0},{1},0</coordinates>
                    </Point>
            </Placemark>
            </kml>""".format(data[1], data[0], data[2], data[3], cycle_count ))

        print("KML Updated, Update #{}".format(cycle_count))
    
    if msvcrt.kbhit():
        keyval = msvcrt.getch().decode("utf-8")
        print(keyval)

        if keyval == "g":
            tempinput = input("Are you sure you want to set sail? Y/N?")
            if (tempinput == "Y" or tempinput == "y"):
                print("Anchors Away!")
                sail_start = True

        if (keyval == "h" and sail_start):
            tempinput = input("Are you sure you want to return home? Y/N?")
            if (tempinput == "Y" or tempinput == "y"):
                print("Ship Returning Home!")
                sail_start = False

        if (keyval == "u" and not sail_start):
            tempinput = input("Are you sure you want to upload the map.txt file from the current directory ? Y/N?")
            if (tempinput == "Y" or tempinput == "y"):
                print("Uploading File!")
                
serialcomm.close()
