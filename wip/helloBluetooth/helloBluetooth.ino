#include <SoftwareSerial.h>

SoftwareSerial btSerial(11, 12); //RX, TX

char data;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial);

  btSerial.begin(115200);
  btSerial.println("Hello from arduino!");
}

void loop() {
  if (btSerial.available()) {
    data = btSerial.read();
    Serial.println(data);
  }
  if (data == '1') {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (data == '0') {
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(100);
}
