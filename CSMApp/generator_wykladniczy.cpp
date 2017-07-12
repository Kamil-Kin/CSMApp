#include "generator_wykladniczy.h"

int GenWykladniczy::GeneracjaW() 
{
  double k = uniform_->Generacja01();
  return -(1.0 / lambda_) * log(k);
}