#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include "ziarno.h"
#include <queue>
#include <iostream>

class Ziarno;
class GenWykladniczy;
class Symulacja;
class Siec;
class Kanal;
class Pakiet;

using std::queue;

class Nadajnik 
{
public:
  Nadajnik(int idx, Ziarno ziarno, Symulacja* sym, Siec* siec, Kanal* kanal);
  ~Nadajnik();

  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora();
  bool CzyBuforPusty();
  Pakiet* PierwszyPakiet();
  double LosCGP();
  //statystyki
  double stopa_bledow_;
  int licznik_pakietow_;
  int licznik_nadanych_;
  int licznik_straconych_;
  int licznik_odebranych_;
  int licznik_ret_;
  double StopaBledow();
  void CzyszczenieStatystykNad();

private:
  int id_;
  queue<Pakiet*> bufor_;
  double CGP_;

  Symulacja* sym_;
  Siec* siec_;
  Kanal* kanal_;
  Pakiet* pak_;
  Ziarno ziarno_;
  GenWykladniczy* losCGP_;
};

#endif // !CSMA_PP_NADAJNIK_H
