# Self Driving Toy Car - version 2

## Preparation
- Open SDC_5_car_with_distance.ino.
- Solder extra headers on the motorshield analog pins
- Solder the header to the TCS34725
- Install the Adafruit TCS34725 library
- Install ST_HW_ST_HCRS04 library


## description of the sketches
**SDC_5_car_with_distance**
Instead of writing the code for the ultrasonic sensor ourselves we use a bit more robust library.
Connect the sensor, install the library and test if everything works.

**SDC_5_car_with_distance_2**
We add some complexity. Slow the car down it we're closer than 20cm. Then slowly inch closer until we're right up to the obstacle.

**SDC_6_color_sensor**
Solder and connect the TCS34725 RGB sensor. Search for and read the datasheet.
Analyse the code. The sketch prints RGB values to the serial port.
Scan different colored papers and write down the values read.

**SDC_6_color_sensor2**
Adjust the RGB values so you get solid color readings.

**SDC_7_car_with_distance_color**
All the previous sketches combined. Make sure you adjust the values.
The car stops and backs up when it encounters a red obstacle.
When it confronts a green object it will continue 'through' the object.

Good luck!