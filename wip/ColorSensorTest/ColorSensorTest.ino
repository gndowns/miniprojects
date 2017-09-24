#include <DFRobot_TCS34725.h>

byte gammatable[256];

DFRobot_TCS34725 tcs = 
  DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
  
void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No sensor found :(");
    while (1); // halt
  }

  // gamma table
  // converts RBG colors to "human" colors
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    gammatable[i] = x;
  }
}

void loop() {
  uint16_t clear, red, green, blue;
  tcs.getRGBC(&red, &green, &blue, &clear);
  tcs.lock(); // turn off sensor LED

  // grab hex code from color
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum; r *= 256;
  g = green; g /= sum;  g *= 256;
  b = blue; b /= sum; b *= 256;
  
  Serial.print("C: "); Serial.println(clear);
  Serial.print("R: "); Serial.print(red);
  Serial.print("\t\t"); Serial.println(int(r), HEX);
  
  Serial.print("G: "); Serial.print(green);
  Serial.print("\t\t"); Serial.println(int(g), HEX);
  
  Serial.print("B: "); Serial.print(blue);
  Serial.print("\t\t"); Serial.println(int(b), HEX);

  Serial.println();
  Serial.println();

  delay(5000);
}
