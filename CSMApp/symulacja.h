#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include "siec.h"
#include <cstdlib>
#include <ctime>

class Symulacja 
{
public:
  Symulacja() 
  {
    siec_ = new Siec();
  }
  ~Symulacja() {}

  void run();

private:
  Siec* siec_;
};

#endif // !CSMA_PP_SYMULACJA_H
