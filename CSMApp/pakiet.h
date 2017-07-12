#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H

#include "zdarzenie.h"
#include "nadajnik.h"

//class Nadajnik;

using namespace std;

class Pakiet 
{
public:
  Pakiet(int idx): faza_(0), skonczony_(false), id_tx_(idx) 
  { 
    moje_zd_ = new Zdarzenie(this); 
  }
  ~Pakiet() {}

  void aktywacja(double czas);
  void execute();

  Nadajnik* getTxId() { return nad_; }

private: 
  int faza_;
  bool skonczony_;
  int id_tx_;
  Zdarzenie* moje_zd_;
  Nadajnik* nad_;
};

#endif // !CSMA_PP_PAKIET_H
