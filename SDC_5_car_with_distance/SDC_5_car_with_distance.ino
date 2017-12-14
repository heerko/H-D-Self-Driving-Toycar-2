

// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <ST_HW_HC_SR04.h>

#define TRIGGER_PIN 9
#define ECHO_PIN 10
ST_HW_HC_SR04 ultrasonicSensor(TRIGGER_PIN, ECHO_PIN); // ST_HW_HC_SR04(TRIG, ECHO)

#define LEFT BACKWARD
#define RIGHT FORWARD
#define NEUTRAL RELEASE

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
  steer.setSpeed( 255 );
  steer.run( NEUTRAL );

  motor.setSpeed( 255 );
  motor.run( RELEASE );
}

void loop() {
  int cm = pulseToCm( ultrasonicSensor.getHitTime() ); // get the ping time and convert to cm.
  if ( cm == 0 || cm > 15 ) { // there doesn't seem to be an obstacle in front of the car. 0 is either too far, or we're right on top of it. 
    motor.setSpeed( 180 );
    motor.run( FORWARD );

    int sVal = analogRead( LINE_SENSOR );
    int error = sVal - sM;

    if ( error < - 50 ) {
      steer.run(LEFT);
    } else if ( error > 50 ) {
      steer.run(RIGHT);
    } else {
      steer.run(NEUTRAL);
    }
  } else { // less then 15cm = stop the car
    motor.run(RELEASE);
  }
}

/* The library we are using already divides by 2 */
int pulseToCm( int uS ) {
  return uS / 29.4;
}
