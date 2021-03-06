/*
 * header with pin definitions
 *
 */

#ifndef TANK_USER_H
#define TANK_USER_H

// sensor I2C addresses
#define SENSOR_CMDREG   0x00 // command register
#define SENSOR_FL       0xE0 // front left sensor
#define SENSOR_FR       0xE2 // front right sensor
#define SENSOR_RL       0xE4 // rear left sensor
#define SENSOR_RR       0xE6 // rear right sensor
#define SENSOR_COMPASS  0xC0 // compas ?

//GPIO pins
#define LEFT_REVERSE        2
#define LEFT_FORWARD        3
#define LEFT_ENABLE         4
#define RIGHT_REVERSE       5
#define RIGHT_FORWARD       6
#define RIGHT_ENABLE        7
#define LEFT_BUTTON_INPUT   8
#define LEFT_LED_OUTPUT     8
#define RIGHT_BUTTON_INPUT  9
#define RIGHT_LED_OUTPUT    9

//
#define MAX_BYTE  255
int STATE;

// motor wrapper functions
void InitMotor();
void Forward();
void Backward();
void TurnLeft();
void TurnRight();
void RightInPlace();
void LeftInPlace();
void Halt();
void Off();

// led wrapper functions
void initLEDS();
void enableOLED();
void enableGLED();
void disableOLED();
void disableGLED();










#endif
