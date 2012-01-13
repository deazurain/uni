/*
 * MedianFilter.h
 *
 * An object to compute the median of three values 
 *
 * create a struct, initialize it and then you can use
 * add and getMedian
 */

#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

typedef struct MedianFilter MedianFilter;
struct MedianFilter {
  unsigned short v[3];
  unsigned short i;
};

void
MedianFilter_init(MedianFilter * const this);

void 
MedianFilter_add(MedianFilter * const this, unsigned short val);

unsigned short 
MedianFilter_getMedian(MedianFilter * const this);

#endif
