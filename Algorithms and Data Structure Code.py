
#!/usr/bin/env python
#
# GrovePi Example for using the Grove Temperature & Humidity Sensor Pro 
# (http://www.seeedstudio.com/wiki/Grove_-_Temperature_and_Humidity_Sensor_Pro)
#
# The GrovePi connects the Raspberry Pi and Grove sensors.  
# You can learn more about GrovePi here:  http://www.dexterindustries.com/GrovePi


import grovepi
from time import sleep
from math import isnan
import json
import math
import time

#import sys

# Connect the Grove Temperature & Humidity Sensor Pro to digital port D4
# This example uses the blue colored sensor.

sensor = 4  # The Sensor goes on digital port 4.
   
# Connect the Grove Light Sensor to analog port A0
# SIG,NC,VCC,GND
light_sensor = 0

    # temp_humidity_sensor_type
    # Grove Base Kit comes with the blue sensor.
blue = 0    # The Blue colored sensor.
white = 1   # The White colored sensor.

# Connect the Green LED to digital port D6
ledGreen = 6

# Connect the Red LED to digital port D7
ledRed = 7

# Connect the Blue LED to digital port D8
ledBlue = 8
     
outputData = {}
outputData['weather'] = []

while True:
    try:
    # This example uses the blue colored sensor. 
    # The first parameter is the port, the second parameter is the type of sensor.
        [temp,humidity] = grovepi.dht(sensor,blue) 
    # Check to see if the reading is a not a valid number display  
        if math.isnan(temp) == False and math.isnan(humidity) == False:
    # Convert Reading from Celsius to Fahrenheit
            temp = (temp * 1.8) + 32
            print("temps = %.02f F humidity =%.02f%%"%(temp, humidity))
            
                
            #Output data to file
            outputData['weather'].append({
                'temperature':temp,
                'humidity':humidity
                })
            #Green LED lights up when temperature is between 60 and 85 and humidity is < 80
            if (60 < temp < 85 , humidity < 80):
                grovepi.digitalWrite(ledGreen,1)
            else:
                grovepi.digitalWrite(ledGreen,0)
                
            #Blue LED lights up when temperature is between 60 and 85 and humidity is < 80
            if (85 < temp < 95, humidity < 80):
                grovepi.digitalWrite(ledBlue,1)
            else:
                grovepi.digitalWrite(ledBlue,0)
                
            #Red LED lights up when temperature is greater than 95
            if (temp > 95):
                grovepi.digitalWrite(ledRed,1)
            else:
                grovepi.digitalWrite(ledRed,0)
                
            #Green and Blue LED light up when humidity > 80
            if (humidity > 80):
                grovepi.digitalWrite(ledGreen,1)
                grovepi.digitalWrite(ledBlue,1)
            else:
                grovepi.digitalWrite(ledGreen,0)
                grovepi.digitalWrite(ledBlue,0)  
  
  
        #print(temp)

        with open("data.json", "w") as s:
            #sleep(5)
            #s = json.dump(outputData, s)
            
            e = json.dumps(outputData, indent = len(outputData))         
            s.write(e)
            s.close()
            sleep(60)
            
    except IOError:
        print ("Error")
        
    except KeyboardInturrupt:
        print("\nProgram manually terminated .\n") #Detects loop
        grovepi.digitalWrite(ledRed, o) #Turns Light sensor off
        grovepi.digitalWrite(ledGreen, o) #Turns Light sensor off
        grovepi.digitalWrite(ledBlue, o) #Turns Light sensor off
        break
    


        

                            
    

               

