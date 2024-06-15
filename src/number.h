#ifndef NUMBER_H
#define NUMBER_H

#if (CPP)
#include <limits>

int imin = std::numeric_limits<int>::min();
int imax = std::numeric_limits<int>::max();

float fmin = std::numeric_limits<float>::min();
float fmax = std::numeric_limits<float>::max();

cout.setf(ios::fixed);
cout.precision(5);
#else
#include <float.h>
#include <limits.h>

int imin = INT_MIN;
int imax = INT_MAX;

float fmin = FLT_MIN;
float fmax = FLT_MAX;

double dmin = DBL_MIN;
double dmax = DBL_MAX;
#endif

#if (CPP)
#include <algorithm>

int maxValue = *max_element(nums.begin(), nums.end());
int minValue = *min_element(nums.begin(), nums.end());
#endif

#endif  // NUMBER_H
