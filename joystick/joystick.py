import math
import time
import serial
from inputs import get_gamepad

# Windows
arduino = serial.Serial('COM5', 115200, timeout=.1)

# Linux
#  arduino = serial.Serial('COM5', 115200, timeout=.1)

time.sleep(.1) #give the connection a second to settle

while 1:
     events = get_gamepad()

     for event in events:

        #event.ev_type, event.code, and event.state are all important variables. i am only using event.code and event.state
        #print(event.ev_type, event.code, event.state)

        #checking input type. this should be the Y axix of the right joystick
        if event.code == "ABS_Y":

            state = event.state
            data = arduino.readline()#[:-2] #the last bit gets rid of the new-line chars
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
                #sets linear movement of the joystick to an exponential (x^3) increase in value. Used to create a more fluid movement for motor movement
                state_pow = math.floor(math.pow(state,3))
                state_powf = math.floor(state_pow/64263) #resetting it to max = 255
                stateFinal = math.floor(state_powf)

                #s = str(stateFinal).encode() #****ignore this****
                #stateFinalBytes = bytes(stateFinal,"ascii") #****ignore this****

                #sends data encoded in bytes to the arduino
                if stateFinal < 255 and stateFinal > -1:
                    stateFinalString = str( + stateFinal) #stateFinal to string for encoding. must be string
                    stateFinalEncoded = bytes(stateFinalString,encoding="ascii") #encoded in bytes for the arduino transmission

                    arduino.write(stateFinalEncoded)

                    print('sending:', stateFinalEncoded)
                    print(data)

            else:
                #send the value of 0 when nothing is going on
                print("sending: 0````")
                arduino.write(b'0')
        #while True:
	     #      data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
	           #if data:
		                 #print(data)
