/*
 * Median5Filter.c
 *
 * An object to compute the median of five values 
 *
 * create a struct, initialize it and then you can use
 * addValue and getMedian
 */

#ifndef MEDIAN_5_FILTER_H
#define MEDIAN_5_FILTER_H

typedef struct Median5Filter Median5Filter;
struct Median5Filter {
  unsigned short v[5]; // value
  int vi;
};

void
Median5Filter_init(Median5Filter * this);

void 
Median5Filter_addValue(Median5Filter * this, int value);

unsigned short
Median5Filter_getMedian(Median5Filter * this);

#endif
