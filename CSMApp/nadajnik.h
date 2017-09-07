#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include "ziarno.h"
#include <list>
#include <iostream>

class Ziarno;
class GenWykladniczy;
class Symulacja;
class Siec;
class Kanal;
class Pakiet;

using std::list;

class Nadajnik
{
public:
  Nadajnik(int idx, Ziarno ziarno, Symulacja* sym, Siec* siec, Kanal* kanal);
  ~Nadajnik();

  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora(Pakiet* pak);
  bool CzyBuforPusty();
  Pakiet* PierwszyPakiet();
  double LosCzasGeneracji();
  //statystyki
  double stopa_bledow_;
  int licznik_pakietow_;
  int licznik_nadanych_;
  int licznik_straconych_;
  int licznik_odebranych_;
  int licznik_retransmisji_;
  double StopaBledow();
  void CzyszczenieStatystykNadajnika();

private:
  int id_;
  list<Pakiet*> bufor_;
  double czas_generacji_;

  Symulacja* sym_;
  Siec* siec_;
  Kanal* kanal_;
  Pakiet* pak_;
  Ziarno ziarno_;
  GenWykladniczy* los_czas_generacji_;
};

#endif // !CSMA_PP_NADAJNIK_H
