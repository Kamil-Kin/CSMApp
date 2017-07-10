#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H

#include "zdarzenie.h"

class Pakiet 
{
public:
  Pakiet(int idx) :faza_(0), skonczony_(false) { moje_zd_ = new Zdarzenie(this); }
  ~Pakiet();
  void execute();
  void aktywacja(double czas);
  int faza_;
  bool skonczony_;
  int getId();
private:
  int id_tx_;
  Zdarzenie* moje_zd_;
};

#endif // !CSMA_PP_PAKIET_H
