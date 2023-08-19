/* config.h
  LED quilt project configuration settings.
  
  Assumes a uniform grid of strips of LEDs, one strip per grid cell, all
  LED strips positioned the same relative to their grid cells.

*/
#ifndef CONFIG_H
#define CONFIG_H

/* LED Grid Settings */



// Number of rows of LED strips in the grid.
constexpr int N_ROWS = 6;
// Number of columns of LED strips in the grid.
constexpr int N_COLS = 6;
// Number of LEDs on each individual LED strip in the grid.
constexpr int N_LEDS_PER_STRIP = 27;

// Data pins used by the LED strips. Should be organized from top row first to
// bottom row last
constexpr byte LED_DATA_PINS[N_ROWS] = {11, 12, 13, 14, 15, 16};

// LED Y and X relative positions within a grid cell. Assumes grid cell top-left
// is (0,0) and grid cell bottom-right is (1,1).
constexpr float LED_REL_POS_Y[N_LEDS_PER_STRIP] = {
    0,1./9,2./9, 3./9,4./9,5./9, 6./9,7./9,8./9,
    1,1,1, 1,1,1, 1,1,1,
    8./9,7./9,6./9, 5./9,4./9,3./9, 2./9,1./9,0};
constexpr float LED_REL_POS_X[N_LEDS_PER_STRIP] = {
    0,0,0, 0,0,0, 0,0,0,  
    0,1./8,2./8, 3./8,4./8,5./8, 6./8,7./8,1,
    1,1,1, 1,1,1, 1,1,1};

// Interior width of each grid cell, in inches.
constexpr float GRID_CELL_WIDTH = 6;
// Width of border between rows of grid cells, in inches.
constexpr float ROW_BORDER_WIDTH = 0.5;
// Width of border between columns of grid cells, in inches.
constexpr float COL_BORDER_WIDTH = 0.5;

// Border size, relative to grid cell size.
constexpr float REL_ROW_BORDER_WIDTH = ROW_BORDER_WIDTH / GRID_CELL_WIDTH;
constexpr float REL_COL_BORDER_WIDTH = COL_BORDER_WIDTH / GRID_CELL_WIDTH;

// Maintain a history of LED colors for this number of past steps.
constexpr int HISTORY_BUFFER_DEPTH = 2;

/* Ultrasonic Sensor Settings */

// Number of ultrasonic sensors.
constexpr int N_SENSORS = 5;

// Ultrasonic sensor trig pin (always just one).
constexpr byte SENSOR_TRIG_PIN = 6;
// Ultrasonic sensor echo pins (one per sensor).
constexpr byte SENSOR_ECHO_PINS[N_SENSORS] = {17, 18, 19, 20, 21};

// All coordinates assume (0,0) is the quilt top-left and (1,1) is the 
// quilt top-right.
// Sensor Y positions, from leftmost sensor to rightmost sensor.
constexpr float SENSOR_POS_Y[N_SENSORS] = {1, 1, 1, 1, 1};
// Sensor X positions, from leftmost sensor to rightmost sensor.
constexpr float SENSOR_POS_X[N_SENSORS] = {0, 1./4, 2./4, 3./4, 1};




#endif // CONFIG_H
