#include <DFRobot_TCS34725.h>

// init color sensor
DFRobot_TCS34725 tcs = 
  DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// global color values, initialized during calibration
int YELLOW_MIN = 20000;
int WHITE_MIN = 20000;

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

  char* COLORS[] = {"WHITE", "RED", "GREEN", "YELLOW", "BLUE"};

  WHITE_MIN = get_clear_min("WHITE", WHITE_MIN);
}

String currentColor = "WHITE";
String newColor;
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

  // get the highest color
  int minClear = 20000;
  unsigned long int currentTime = millis();
  while (millis() < currentTime + 50) {
    tcs.getRGBC(&red, &green, &blue, &clr);
    tcs.lock();
    minClear = clr < minClear ? clr : minClear;
  }

  if (minClear > WHITE_MIN) {
    newColor = "WHITE";
  }
  else {
    newColor = "RED";
  }

  if (! currentColor.equals(newColor)) {
    Serial.println(newColor);
    currentColor = newColor;
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}




// UTILS
int get_clear_min(String color, int colorMin) {
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
    if (clr < colorMin) {
      colorMin = clr;
    }
  }
  Serial.println("Done.");
  Serial.print("Found new minimum: "); Serial.println(colorMin);
  Serial.println();
  return colorMin;
}
