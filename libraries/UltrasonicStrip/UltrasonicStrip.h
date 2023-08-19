/* UltrasonicStrip.h
  Header for the UltrasonicStrip class, which abstracts the detection of activity in front
  of a 1D strip of HC-SR04 ultrasonic sensors.
  
  Users specify the number of ultrasonic sensors and their positioning upon the quilt
  backing, in config.h in the project root folder. Sensor position coordinates assume
  the top-left of the quilt backing is (0,0), and the bottom-right of the quilt backing 
  is (1,1).
*/
#ifndef ULTRASONICSTRIP_H
#define ULTRASONICSTRIP_H

#include <HCSR04.h>
// TODO: Write this, add relevant info to config, add data pin info to config.
