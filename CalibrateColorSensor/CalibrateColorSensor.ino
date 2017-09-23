#include <DFRobot_TCS34725.h>

// init color sensor
DFRobot_TCS34725 tcs = 
  DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Color Sensor Calibration");

  if (tcs.begin()) {
    Serial.println("Found Sensor");
  }
  else {
    Serial.println("No sensor found :(");
    while (1);
  }
}

void loop() {
  Serial.println();
  
  uint16_t clear, red, green, blue;
  tcs.getRGBC(&red, &green, &blue, &clear);
  tcs.lock(); // turn off sensor LED

  char* COLORS[] = {"WHITE", "GREEN", "YELLOW", "BLUE", "BLACK"};

  for (int i=0; i < 4; i++) {
    Serial.print("Callibrating "); Serial.println(COLORS[i]);
    Serial.println("Place the Sensor over said color. you have 5 seconds");
    delay(5000);

    tcs.getRGBC(&red, &green, &blue, &clear);
    tcs.lock();

    Serial.print("C: "); Serial.println(clear);
    Serial.print("R: "); Serial.println(red);
    Serial.print("G: "); Serial.println(green);
    Serial.print("B: "); Serial.println(blue);

    Serial.println();
  }
}
