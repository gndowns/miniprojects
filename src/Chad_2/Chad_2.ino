// Second Arduino on Robot
// Controls Servo

#include <Servo.h>
Servo servo;

// input from other arduino
#define Chad_1_in 4
// servo pin
#define servoPin 3


bool upDown = true;

void setup() {
  // init pin input
  pinMode(Chad_1_in, INPUT);
  
  // init servo
  servo.attach(servoPin);

  // set to 'default' off
  servo.write(5);
}

void loop() {
  if (digitalRead(Chad_1_in) == HIGH) {
    upDown = !upDown;
    upDown ? servo.write(5) : servo.write(35);
  }
}
