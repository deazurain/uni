#ifndef CONSTANTS_H
#define MOTOR_H
/*
 * HardwareConstants.h
 *
 * Defines all the pins, addresses/registers and commands used
 * by most components' init methods
 */

// ======
//  PINS
// ======

// engines
#define PIN_ENGINE_LEFT_BACKWARD  2
#define PIN_ENGINE_LEFT_FORWARD   3
#define PIN_ENGINE_LEFT_ENABLE    4

#define PIN_ENGINE_RIGHT_BACKWARD 5
#define PIN_ENGINE_RIGHT_FORWARD  6
#define PIN_ENGINE_RIGHT_ENABLE   7

// LEDs
#define PIN_LED_LEFT             8
#define PIN_LED_RIGHT            9
#define PIN_LED_ORANGE	PIN_LED_LEFT
#define PIN_LED_GREEN	PIN_LED_RIGHT

// Buttons
#define PIN_BUTTON_LEFT	 PIN_LED_LEFT
#define PIN_BUTTON_RIGHT PIN_LED_RIGHT
#define PIN_BUTTON_GREEN          PIN_LED_GREEN
#define PIN_BUTTON_ORANGE         PIN_LED_ORANGE

// ===========
//  ADDRESSES COMMANDS REGISTERS
// ===========

#define REG_SENSOR_COMMAND        0x00        // command register
#define REG_SENSOR_FL             (0xE0 >> 1) // front left
#define REG_SENSOR_FR             (0xE2 >> 1) // front right
#define REG_SENSOR_SL             (0xE4 >> 1) // side left
#define REG_SENSOR_SR             (0xE6 >> 1) // side right

#define REG_COMPASS               (0xC0 >> 1) // compass?!

// ============
//  I/O
// ============
#define INPUT	0
#define	OUTPUT	1
#define OFF	0
#define	ON	1

#endif

