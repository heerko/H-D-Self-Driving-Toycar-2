

// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <ST_HW_HC_SR04.h>#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define TRIGGER_PIN 9
#define ECHO_PIN 10

ST_HW_HC_SR04 ultrasonicSensor(TRIGGER_PIN, ECHO_PIN); // ST_HW_HC_SR04(TRIG, ECHO)

#define LEFT BACKWARD
#define RIGHT FORWARD
#define NEUTRAL RELEASE
#define COLOR_LED A3
#define RED 1
#define GREEN 2
#define BLUE 3

#define SPEED_FAST 255
#define SPEED_SLOW 180

AF_DCMotor steer(1);
AF_DCMotor motor(4);

int LINE_SENSOR = A0;

// First run the SDC_TCRT500 sketch and set the min and max values for the sensor below.
int sMin = 300; // set this to the minimal value you get from the line sensor
int sMax = 1000; // set this to the maximal value you get from the line sensor
int sM = sMin + sMax / 2; // calculate the midpoint.

void setup() {
  Serial.begin( 9600 ); // set up Serial library at 9600 bps for debugging

  // turn on motor
  steer.setSpeed( SPEED_FAST );
  steer.run( NEUTRAL );

  motor.setSpeed( SPEED_FAST );
  motor.run( RELEASE );

  pinMode( COLOR_LED, OUTPUT ); // the led on the color sensor is connected to A3.

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}


void loop() {
  int cm = pulseToCm( ultrasonicSensor.getHitTime() ); // get the ping time and convert to cm.
  if ( cm == 0 || cm > 20 ) { // there doesn't seem to be an obstacle in front of the car. 0 is either too far, or we're right on top of it.
    motor.setSpeed( SPEED_FAST );
    motor.run( FORWARD );
    digitalWrite( COLOR_LED, LOW ); // ineffecient, but convient.
    int sVal = analogRead( LINE_SENSOR );
    int error = sVal - sM;

    if ( error < - 50 ) {
      steer.run(LEFT);
    } else if ( error > 50 ) {
      steer.run(RIGHT);
    } else {
      steer.run(NEUTRAL);
    }
  } else if ( cm > 5 && cm < 20 ) { // we are closer than 15cm = slowly inch closer
    motor.setSpeed( SPEED_SLOW ); // adjust for values that work for your car. We want it to just move.
    motor.run( FORWARD );
  } else  { // We should be right on top of the object now
    motor.run(RELEASE);
    int color = getColor();
    if ( color == RED ) {
      // wait...
      motor.setSpeed( SPEED_FAST ); 
      motor.run( BACKWARD );
      delay( 500 );
    } else if ( color == GREEN ) {
      // drive over the object. gas for 500ms
      motor.setSpeed( SPEED_FAST ); 
      motor.run( FORWARD );
      delay( 500 ); // then continue with normal progam flow.
    }
  }
}

/* The library we are using already divides by 2 */
int pulseToCm( int uS ) {
  return uS / 29.4;
}

int getColor() {
  uint16_t clear, red, green, blue;
  digitalWrite( COLOR_LED, HIGH );
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

  int color = 0;

  if ( r > 160 && g < 80 && b < 60 ) {
    color = RED;
  } else if ( r > 85 && g > 110 && b < 60 ) {
    color = GREEN;
  } else if ( r < 70 && g > 105 && b > 84 ) {
    color = BLUE;
  }
  return color;
}



