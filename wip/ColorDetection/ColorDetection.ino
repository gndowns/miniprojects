#include <DFRobot_TCS34725.h>

// init color sensor
DFRobot_TCS34725 tcs = 
  DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// global color values, initialized during calibration
int WHITE_MIN_CLEAR = 0;

uint16_t clr, red, green, blue;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.println("Calibrating Color Sensor");

  // get sensor
  if (tcs.begin()) {
    Serial.println("Found Sensor");
  }
  else {
    Serial.println("No sensor found :(");
    while (1);
  }

  // calibrate
  Serial.println();

  WHITE_MIN_CLEAR = get_color_min("WHITE", WHITE_MIN_CLEAR);
}

String currentColor = "WHITE";
String newColor;
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

  // get the highest color
  int minClear = 0;
  unsigned long int currentTime = millis();
  while (millis() < currentTime + 50) {
    tcs.getRGBC(&red, &green, &blue, &clr);
    tcs.lock();
    minClear = !minClear ? clr : min(clr, minClear);
  }

  newColor = minClear > WHITE_MIN_CLEAR ? "WHITE" : "RED";

  if (! currentColor.equals(newColor)) {
    Serial.println(newColor);
    currentColor = newColor;
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}




// UTILS
int get_color_min(String color, int minClear) {
  Serial.println("Calibrating " + color);
  Serial.print("Place Sensor over said color. ");
  Serial.println("Calibration will begin in 5 seconds");
  
  int t = millis();
  while (millis() < t + 5000);

  Serial.print("Calibrating now. ");
  Serial.println("Hold sensor over color for another 5 seconds");

  // find the lower bound of clear value
  t = millis();
  while (millis() < t + 5000) {
    tcs.getRGBC( &red, &green, &blue, &clr);
    minClear = !minClear ? clr : min(clr, minClear);
  }
  Serial.println("Done.");
  Serial.print("Found new minimum: "); Serial.println(minClear);
  Serial.println();
  return minClear;
}
