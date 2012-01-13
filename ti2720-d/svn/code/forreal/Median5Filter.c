/*
 * Median5Filter.c
 *
 * An object to compute the median of five values 
 *
 * create a struct, initialize it and then you can use
 * addValue and getMedian
 */

#include "Median5Filter.h"

void
Median5Filter_init(Median5Filter * this) {
  int i;
  for(i = 0; i < 5; i++) {
    this->v[i] = 0;
  }
  this->vi = 0;
}

void 
Median5Filter_addValue(Median5Filter * this, int value) {
  this->v[this->vi] = value;
  if(this->vi > 3) { this->vi = 0; }
  else{ this->vi++; }
}

/*
 * The idea is to filter the min and max out of the measured values twice. This 
 * way the only remaining value is the median. 
 */

unsigned short
Median5Filter_getMedian(Median5Filter * this) {
  unsigned short r[5] = {0,0,0,0,0}; // removed values
  unsigned short * v = this->v;
  int i;
  unsigned short mini = 0;
  unsigned short maxi = 0;
  for(i = 1; i < 5; i++) {
    if(v[i] < v[mini]) { mini = i; }
    if(v[i] > v[maxi]) { maxi = i; }
  }
  r[mini] = 1;
  r[maxi] = 1;
  for(i = 0; i < 5; i++) { // go to the first unremoved value
    if(r[i] == 0) break;
  }
  mini = i;
  maxi = i;
  for(; i < 5; i++) {
    if(r[i]) continue;
    if(v[i] < v[mini]) { mini = i; }
    if(v[i] > v[maxi]) { maxi = i; }
  }
  r[mini] = 1;
  r[maxi] = 1;
  for(i = 0; i < 5; i++) {
    if(r[i] == 0) break;
  }

  return v[i];
}

