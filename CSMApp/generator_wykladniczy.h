#ifndef CSMA_PP_GENERATOR_WYKLADNICZY_H
#define CSMA_PP_GENERATOR_WYKLADNICZY_H

#include "generator_rownomierny.h"
#include <cmath>

class Symulacja;

class GenWykladniczy
{
public:
  GenWykladniczy(double lam, int kernel) :lambda_(lam)
  {
    uniform_ = new GenRownomierny(kernel);
  }
  ~GenWykladniczy() {}
  
  double GeneracjaW();

private:
  double lambda_;
  GenRownomierny *uniform_;
};

#endif // !CSMA_PP_GENERATOR_WYKLADNICZY_H
