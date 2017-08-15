#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include "ziarno.h"
#include <vector>
#include <iostream>

class GenWykladniczy;
class Symulacja;
class Siec;
class Kanal;
class Pakiet;

class Nadajnik 
{
public:
  Nadajnik(int idx, Symulacja* sym, Siec* siec, Kanal* kanal);
  ~Nadajnik();

  double losujCGP();
  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora();
  bool CzyBuforPusty();
  Pakiet* PierwszyPakiet();

private:
  int id_;
  std::vector<Pakiet*> bufor_;
  double CGP_;
  Symulacja* sym_;
  Siec* siec_;
  Kanal* kanal_;
  Pakiet* pak_;
  GenWykladniczy* losCGP_;
};

#endif // !CSMA_PP_NADAJNIK_H
