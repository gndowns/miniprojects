#!/usr/bin/env python

import math
import time
import serial
from inputs import get_gamepad
arduino = serial.Serial('COM3', 115200, timeout=.1)#establish connection to bluetooth though proper COM port
time.sleep(1) #give the connection a second to settle

while 1:
     events = get_gamepad()
     rightStickValue = 0
     leftStickValue = 0
     for event in events:

        #Will execute when controller there is a change in the positioning of the right and left joystick
        if event.code == "ABS_Y" or event.code == "ABS_RY":
            state = event.state

            #joystick can move between -5000 <= y <= 5000 and not send any data. Limits sensativity
            if state > 5000 or state < -5000:

                #changing input value by readjusting it relative to 0. will be needed for later.
                if state < 0:
                    state = state + 5000
                elif state > 0:
                    state = state - 5000

                #the start to setting the max value at 255
                stateScale = math.floor(state / 109.5)

                #sends left joystick data to arduino
                if event.code == "ABS_Y":
                    if stateScale < 256 and stateScale > -256:
                        leftStickValue = stateScale
                        stateFinalString = "L" + str(leftStickValue)#converts stateFinal to string
                        stateFinalEncoded = bytes(stateFinalString,encoding="ascii") #encoded in bytes for the arduino transmission

                        arduino.write(stateFinalEncoded)
                        print('sending: L  ', stateFinalEncoded)

                #sends right joystick data to arduino
                if event.code == "ABS_RY":
                    if stateScale < 255 and stateScale > -256:
                        rightStickValue = stateScale
                        stateFinalString = "R" + str(rightStickValue) #stateFinal to string for encoding. must be string
                        stateFinalEncoded = bytes(stateFinalString,encoding="ascii") #encoded in bytes for the arduino transmission

                        arduino.write(stateFinalEncoded)
                        print('sending: R  ', stateFinalEncoded)

        #Button B moves the servo mortor
        elif event.code == "BTN_EAST" and event.state == 1:
            arduino.write(b'B_B')
            print("sending: B_B")
