#include "generator_rownomierny.h"

double GenRownomierny::Generacja01() 
{
  int h = kernel_ / Q;
  kernel_ = A*(kernel_ - Q*h) - R*h;
  if (kernel_ < 0)
    kernel_ = kernel_ + static_cast<int>(M);
  return kernel_ / M;
}

double GenRownomierny::GeneracjaR(double dol, double gora) 
{
  return Generacja01() * (gora - dol) + gora;
}