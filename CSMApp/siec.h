#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include <vector>
#include <iostream>
#include "statystyka.h"

class Ziarno;
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

  void Statystyki();
  void StatystykiPakietu(Pakiet* pak);
  void CzyszczenieStatystyk();

private:
  const int kLiczbaNad_ = 2;
  vector<Nadajnik*> nadajniki_;
  Symulacja* sym_;
  Kanal* kanal_;
  Statystyka* stat_;
  //statystyki
  double opoznienie_;
  double czas_oczekiwania_;
};

#endif // !CSMA_PP_SIEC_H
