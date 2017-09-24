// Central Arduino On Robot

// Time up LED 
#define TIME_LED_PIN 13
unsigned long duration = 60000;

// DC Motors
#define MOT_A1_PIN 5
#define MOT_A2_PIN 6
#define MOT_B1_PIN 9
#define MOT_B2_PIN 10

// sends signal to Chad_2 to control servo
#define Chad_2_servo 3

// Bluetooth Serial
#include <SoftwareSerial.h>
SoftwareSerial btSerial(11, 12); // RX, TX

void setup() {
  // init stepper driver control pins to output drive mode
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  pinMode(MOT_B1_PIN, OUTPUT);
  pinMode(MOT_B2_PIN, OUTPUT);

  // signal to Chad 2
  pinMode(Chad_2_servo, OUTPUT);

  // init with drivers off, motors coasting
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, LOW);

  // init servo off
  digitalWrite(Chad_2_servo, LOW);

  // init serial
  Serial.begin(115200);
  while (!Serial);
  // bluetooth serial
  btSerial.begin(115200);
  btSerial.print("hello from chad 1");

  //Timer LED
  pinMode(TIME_LED_PIN , OUTPUT);
}

void loop() {
  if (btSerial.available()) {
    String data = "";
    // read 1 char at a time
    while (btSerial.available()) {
      char j = btSerial.read();
      data += j;
    }

    String subDataFront = data.substring(0,1);
    String subDataBack = data.substring(1);
    int data2 = subDataBack.toInt();

    if ( abs(data2) < 256 ) {
      // check left or right wheel
      if (subDataFront == "R") {
        set_motor_pwm(data2, MOT_B1_PIN, MOT_B2_PIN);
      }
      else if (subDataFront == "L") {
        set_motor_pwm(data2, MOT_A1_PIN, MOT_A2_PIN);
      }

      // if button, send to Chad 2 to toggle servo
      else if (subDataFront == "B") {
        digitalWrite(Chad_2_servo, HIGH);
        digitalWrite(Chad_2_servo, LOW);
      }

      // LOG
      Serial.print(subDataFront + " ON ");
      Serial.println(data2);
      btSerial.print(subDataFront + " ON ");
      btSerial.println(data2);

      // flush
      btSerial.flush();
    }
    // flush?
    btSerial.flush();
  }
  if(millis() > duration){
    digitalWrite(TIME_LED_PIN, HIGH);
  }
}

// UTILS ==========================
void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN) {
  if (pwm >= 0) {
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
  // reverse
  else {
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);
  }
}

