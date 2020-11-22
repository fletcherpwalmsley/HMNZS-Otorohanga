"""Created by Fletcher Walmsley, 18/04/20"""

import os
import sys

def createfile(input_filename):
    """Do stuff"""
    
    infile = open(input_filename)
    try:
        outfile = open('map.txt', 'x')
    except:
        print("An output file already exists in the current directory, do you want to override it? (y/n)")
        if (input() == ("y" or "Y")):
            os.remove("map.txt")
            outfile = open('map.txt', 'x')
        else:
            sys.exit()
        

    lines = (infile.readlines())
    
    for i in range(0, len(lines)):
        if lines[i].strip() == "<coordinates>":
            coord_line = lines[i+1].strip()
            break
        
    coord_array = coord_line.split(" ")
    for ii in range(0, len(coord_array)):
        coord_data = coord_array[ii].split(",")
        outfile.write("[{}]{:.6f},{:.6f};".format(ii,float(coord_data[1]), float(coord_data[0])))
   

print("Input the name of the KML file to convert (include the .kml extension)")
input_file = input()
#input_file = "test.kml"
createfile(input_file)



"""old code from orginal COSC121 file, might be usedfull"""

#for i in range(0, len(lines)):
    #inv = -1*(i+1)
    #reverise.append(lines[inv])

#for lin in range(0, len(reverise)):
    #strip.append(reverise[lin].rstrip("\n"))

#for output in strip:
    #finaloutput = (output + '\n')
    #outfile.write(finaloutput)     