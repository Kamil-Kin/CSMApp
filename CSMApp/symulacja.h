#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include "siec.h"

class Symulacja 
{
public:
  Symulacja() {};
  ~Symulacja() {};
  void run();
private:
  Siec* siec_;
};

#endif // !CSMA_PP_SYMULACJA_H
