#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include "ziarno.h"
#include <vector>
#include <iostream>

class GenRownomierny;
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

  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora();
  bool CzyBuforPusty();
  Pakiet* PierwszyPakiet();

  double LosCGP();
  double LosCTP();
  double LosPT();
  double LosR(int l_ret);
private:
  int id_;
  std::vector<Pakiet*> bufor_;
  double CGP_;
  Symulacja* sym_;
  Siec* siec_;
  Kanal* kanal_;
  Pakiet* pak_;
  Ziarno* ziarno_;
  GenWykladniczy* losCGP_;
  GenRownomierny* losCTP_;
  GenRownomierny* losPT_;
  GenRownomierny* losR_;
};

#endif // !CSMA_PP_NADAJNIK_H
