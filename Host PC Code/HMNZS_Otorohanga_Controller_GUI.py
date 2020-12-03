import PySimpleGUI as sg
import serial
import time


heading = 0
cycle_count = 0
sail_start = False


serialcomm = serial.Serial('COM6', 1200)
serialcomm.timeout = 1

print("Connection Successful!")
layout = [[sg.Text("Hello from PySimpleGUI")], [sg.Button("OK")]]
window = sg.Window("HMNZS Otorohanga Controller GUI", layout)




while True:
    raw = serialcomm.readline().decode('ascii')
    data = raw.split(",")
    print(raw)
    
    #GUI Stuff
    event, values = window.read()
    if event == sg.WIN_CLOSED:
        break
       
      
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

        
                        
                        
serialcomm.close()