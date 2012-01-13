/*
 * Control.h
 *
 * Control will be used by the main method to start controlling the tank.
 * It could contain an extra debug mode to test the sensors of a tank so
 * that we don't have to use different programs. If main accepts a 'mode'
 * parameter to choose the control function. 
 * 
 */

#ifndef CONTROL_H 
#define CONTROL_H

// standard
int Control_init();
int Control_cleanup();

// public constants

// methodsz
int Control_doPledge();
int Control_doTests();

#endif
