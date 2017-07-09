#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include <vector>
#include "pakiet.h"

class Pakiet;

class Nadajnik 
{
public:
  Nadajnik(int id);
  ~Nadajnik();
  void setCGP(double CGP);
  double getCGP();
private:
  int id_;
  std::vector<Pakiet*> bufor_;
  double CGP_;
  Pakiet* frame_;
};

#endif // !CSMA_PP_NADAJNIK_H
