#include <SoftwareSerial.h>

SoftwareSerial btSerial(10, 11); //RX, TX

const int motorPin = 9;

char data;

void setup() {
  pinMode(motorPin, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial);

  btSerial.begin(9600);
  btSerial.println("Hello from arduino!");
}

void loop() {
  if (btSerial.available()) {
    data = btSerial.read();
  }
  if (data == '1') {
    digitalWrite(motorPin, HIGH);
  }
  else {
    digitalWrite(motorPin, LOW);
  }
  delay(1000);
}
