/*
 * MedianFilter.c
 *
 * An object to compute the median of three values 
 *
 * create a struct, initialize it and then you can use
 * add and getMedian
 */

#include "MedianFilter.h"

void
MedianFilter_init(MedianFilter * const this) {
  this->v[0] = 1;
  this->v[1] = 1;
  this->v[2] = 1;
  this->i = 0;
}

void 
MedianFilter_add(MedianFilter * const this, unsigned short val) {
  this->v[this->i++] = val;
  if(this->i > 2) { this->i = 0; }
}

unsigned short 
MedianFilter_getMedian(MedianFilter * const this) {
  unsigned short * v = this->v;
  if(v[0] > v[1]) {
    // 0 > 1
    if(v[1] > v[2]) {
      // 0 > 1, 1 > 2
      return v[1];
    }
    else {
      // 0 > 1, 1 < 2
      if(v[0] > v[2]) {
        // 0 > 1, 1 < 2, 0 > 2
        return v[2];
      }
      else {
        // 0 > 1, 1 < 2, 0 < 2
        return v[0];
      }
    }
  }
  else {
    // 0 < 1
    if(v[1] > v[2]) {
      // 0 < 1, 1 > 2
      if(v[0] > v[2]) {
        // 0 < 1, 1 > 2, 0 > 2
        return v[0];
      }
      else {
        // 0 < 1, 1 > 2, 0 < 2
        return v[2];
      }
    }
    else {
      // 0 < 1, 1 < 2
      return v[1];
    }
  }

  return ~0;
}

