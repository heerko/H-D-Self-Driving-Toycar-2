#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Serial.println("Color View Test!");

  pinMode( A3, OUTPUT );
  digitalWrite(A3, HIGH );
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}


void loop() {
  uint16_t clear, red, green, blue;

  delay(60);  // Sensor takes 50ms to read
  tcs.getRawData(&red, &green, &blue, &clear);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256;
  g *= 256;
  b *= 256;
  
  Serial.print("\tR:\t"); Serial.print(r);
  Serial.print("\tG:\t"); Serial.print(g);
  Serial.print("\tB:\t"); Serial.print(b);

  r = r > 128 ? 255 : 0;
  g = g > 110 ? 255 : 0;
  b = b > 128 ? 255 : 0;

  Serial.print("\t");
  Serial.print((int)r); Serial.print((int)g); Serial.print((int)b);
  Serial.println();
 
  delay(100);
}

