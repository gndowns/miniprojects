
char data = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  if(Serial.available() > 0) {
    data = Serial.read();
    Serial.print(data);
    Serial.print("\n");
    if(data == '1') {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(data == '0') {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
