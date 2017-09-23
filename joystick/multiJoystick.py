import math
import time
import serial
from inputs import get_gamepad
arduino = serial.Serial('COM7', 115200, timeout=.1)
time.sleep(.1) #give the connection a second to settle

while 1:
     events = get_gamepad()
     rightStickValue = 0
     leftStickValue = 0
     for event in events:

        #event.ev_type, event.code, and event.state are all important variables. i am only using event.code and event.state
        #print(event.ev_type, event.code, event.state)

        #checking input type. this should be the Y axix of the right joystick
        if event.code == "ABS_Y" or event.code == "ABS_RY":
            state = event.state


            #data = arduino.readline()#[:-2] #the last bit gets rid of the new-line chars
            #this is for limiting the sensativity of the joystick. if not included, joystick input is too sensative and will send too much information.
            #joystick can move between -5000 <= y <= 5000 and not send any data
            if state > 5000 or state < -5000:
                #ignore this value - 32780
                #adjusting input by moving it closer to 0. will be needed for later.
                if state < 0:
                    state = state + 5000
                elif state > 0:
                    state = state - 5000

                #the start to setting the max value at 255
                state = math.floor(state / 109.5)
                #s = str(stateFinal).encode() #****ignore this****
                #stateFinalBytes = bytes(stateFinal,"ascii") #****ignore this****
                print(state)
                #sends data encoded in bytes to the arduino
                if event.code == "ABS_Y":
                    if state < 256 and state > -256:
                        leftStickValue = state
                        ##stateFinalString ="L"+ str(state) #stateFinal to string for encoding. must be string
                        stateFinalString = "L" + str(leftStickValue)
                        stateFinalEncoded = bytes(stateFinalString,encoding="ascii") #encoded in bytes for the arduino transmission

                        arduino.write(stateFinalEncoded)
                        #arduino.write(stateFinalEncoded)
                        #arduino.write(b'1')

                        print('sending: L  ', stateFinalEncoded)
                        #print("\treceived:",data)
                if event.code == "ABS_RY":
                    if state < 255 and state > -256:
                        rightStickValue = state
                        stateFinalString = "R" + str(rightStickValue) #stateFinal to string for encoding. must be string
                        stateFinalEncoded = bytes(stateFinalString,encoding="ascii") #encoded in bytes for the arduino transmission

                        arduino.write(stateFinalEncoded)
                        #arduino.write(stateFinalEncoded)
                        #arduino.write(b'1')

                        print('sending: R  ', stateFinalEncoded)
                    #    print("\treceived:",data)

            else:
                #send the value of 0 when nothing is going on
                print("sending~~: 0")
                #arduino.write(b'R0')
                #arduino.write(b'L0')
        elif event.code == "BTN_EAST" and event.state == 1:
            arduino.write(b'B_B')
            print("sending: B_B")
        #while True:
	     #      data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
	           #if data:
		                 #print(data)
