#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include <vector>
#include <iostream>
#include "pakiet.h"
//#include "siec.h"

class Siec;
class Pakiet;

class Nadajnik 
{
public:
  
  Nadajnik(int idx) : id_(idx) { frame_ = new Pakiet(idx); }
  ~Nadajnik() {}
  void setCGP(double CGP) { CGP_ = CGP; }
  double getCGP() { return CGP_; }
  double losujCGP();//TO DO
  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora();
  Pakiet* CzyPierwszy() { return bufor_.front(); }

  void setId(Siec* siec) { siec_ = siec; } //chyba niepotrzebne?
  Siec* getWebId() { return siec_; }
private:
  int id_;
  std::vector<Pakiet*> bufor_;
  double CGP_;
  Pakiet* frame_;
  Siec* siec_;
};

#endif // !CSMA_PP_NADAJNIK_H
