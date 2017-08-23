#ifndef CSMA_PP_HISTOGRAM_H
#define CSMA_PP_HISTOGRAM_H

#include "generator_rownomierny.h"
#include "generator_wykladniczy.h"
#include <fstream>
#include <iostream>

using std::fstream;
using std::ios;

class Histogram 
{
public:
  Histogram() {}
  ~Histogram() {}

  void Rownomierny();
  void Wykladniczy();
};

#endif // !CSMA_PP_HISTOGRAM_H
