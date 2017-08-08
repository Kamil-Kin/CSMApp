#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H

#include "proces.h"

class Symulacja;
class Kanal;
class Nadajnik;
class Zdarzenie;

class Pakiet :public Proces
{
public:
  Pakiet(int idx, Symulacja* sym, Kanal* kanal, Nadajnik* nad);
  ~Pakiet();
  int losujCTP();
  double losujPT();
  double losujR();
  //void aktywacja(double czas);
  void execute();
  //double CzasZdarzenia() const;
private:
  const int kLR = 5;
  const double kPT = 0.2;

  int id_tx_;
  int czas_CTP_;
  int licznik_ret_;
  double czas_CRP_;
  bool ack_;

  Zdarzenie* moje_zdarzenie_;
  Nadajnik* nad_;
  Kanal* kanal_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PAKIET_H
