#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include "siec.h"

class Symulacja 
{
public:
  Symulacja() 
  {
    siec_ = new Siec();
  }
  ~Symulacja() {}
private:
  Siec* siec_;
};

#endif // !CSMA_PP_SYMULACJA_H
