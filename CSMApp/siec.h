#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include <vector>
#include <iostream>
#include "statystyka.h"

class GenRownomierny;
class Symulacja;
class Nadajnik;
class Kanal;
class Pakiet;

using std::vector;
using std::cout;
using std::endl;

class Siec
{
public:
  Siec(Symulacja* sym, Ziarno ziarno, Statystyka* stat);
  ~Siec();
  int LiczbaNad() { return kLiczbaNad_; }
  double LosCTP();
  double LosPT();
  double LosR(int l_ret);

  void Statystyki();
  void StatystykiPakietu(Pakiet* pak);
  void CzyszczenieStatystyk();
  Nadajnik* Nad(int index);
  Kanal* Kan();
private:
  const int kLiczbaNad_ = 10;
  vector<Nadajnik*> nadajniki_;
  Symulacja* sym_;
  Kanal* kanal_;
  Statystyka* stat_;
  //statystyki
  double opoznienie_;
  double czas_oczekiwania_;

  GenRownomierny* losCTP_;
  GenRownomierny* losPT_;
  GenRownomierny* losR_;
};

#endif // !CSMA_PP_SIEC_H
