#include <DFRobot_TCS34725.h>

// init color sensor
DFRobot_TCS34725 tcs = 
  DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// global color values, initialized during calibration
int WHITE_MIN = 5000;
int YELLOW_MIN = 5000;

uint16_t clr, red, green, blue;

void setup() {
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
  YELLOW_MIN = get_clear_min("YELLOW", YELLOW_MIN);
}

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
    tcs.getRGBC(&red, &green, &blue, &clr);
    if (clr < colorMin) {
      colorMin = clr;
    }
  }
  Serial.println("Done.");
  Serial.print("Found new minimum: "); Serial.println(colorMin);
  Serial.println();
  return colorMin;
}

void loop() {
  // check if color changes from white to yellow
  tcs.getRGBC(&red, &green, &blue, &clr);
  if (clr > (YELLOW_MIN - 100)) {
    Serial.println("YELLOW!");
    Serial.println(clr);
  }
  delay(100);
}
