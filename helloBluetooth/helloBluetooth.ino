char data;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("hello from arduino!");
}

void loop() {
  if (Serial.available()) {
    data = Serial.read();
  }
  if (data == '1') {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (data == '0') {
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(100);
}
