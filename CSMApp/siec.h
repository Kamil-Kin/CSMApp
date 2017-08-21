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
  //Symulacja* getSim() { return sym_; }
  //Kanal* getKanal() { return kanal_; }
  //Nadajnik* getNad(int id) { return nadajniki_.at(id); }
  void Statystyki();

private:
  const int kLiczbaNad_ = 1;
  vector<Nadajnik*> nadajniki_;
  Symulacja* sym_;
  Kanal* kanal_;
  Statystyka* stat_;
};

#endif // !CSMA_PP_SIEC_H
