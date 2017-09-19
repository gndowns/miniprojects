import math
from inputs import get_gamepad
while 1:
     events = get_gamepad()
     for event in events:
        #print(event.ev_type, event.code, event.state)
        #print(event.code)
        if event.code == "ABS_Y":
            #print(event.state)
            state = event.state
            if state > 15000 or state < -15000:
                if state < 0:
                    state = state + 15000
                elif state > 0:
                    state = state - 15000

                state = math.floor(state / 70)

                state_pow = math.floor(math.pow(state,3))
                #print(state_pow)
                state_powf = math.floor(state_pow/64263)
                print(state_powf)
