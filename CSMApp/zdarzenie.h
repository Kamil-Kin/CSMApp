#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H
#include <iostream>
class Pakiet;
using std::cout;

class Zdarzenie 
{
public:
  Zdarzenie(Pakiet* pak) : czas_zdarzenia_(-1.0), pakiet_(pak), priorytet_(0) {}
  ~Zdarzenie() { 
    //cout << "Destruktor klasy Zdarzenie\n";
  }

  double czas_zdarzenia_;
  Pakiet* pakiet_;
  int priorytet_;
};

#endif // !CSMA_PP_ZDARZENIE_H
