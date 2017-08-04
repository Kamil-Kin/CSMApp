#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H

#include "pakiet.h"
class Pakiet;

class Zdarzenie 
{
public:
  //Zdarzenie(double czas) : czas_zdarzenia_(czas), pakiet_(nullptr) {}
  Zdarzenie(Pakiet* pak) : czas_zdarzenia_(-1.0), pakiet_(pak) {}
  ~Zdarzenie() {}
  void UstawCzasZd(double time) { czas_zdarzenia_ += time; }
  double PobierzCzasZd() const{ return czas_zdarzenia_; }
  Pakiet* PobierzPakiet() { return pakiet_; }
  double czas_zdarzenia_;
  Pakiet* pakiet_;
private:
  
};

#endif // !CSMA_PP_ZDARZENIE_H
