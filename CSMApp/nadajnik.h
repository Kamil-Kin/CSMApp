#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include <vector>
#include <iostream>

class Pakiet;

class Nadajnik 
{
public:
  Nadajnik(int idx);
  ~Nadajnik();

  void setCGP(double CGP) { CGP_ = CGP; }
  double getCGP() { return CGP_; }
  double losujCGP();
  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora();
  Pakiet* CzyPierwszy();

private:
  int id_;
  std::vector<Pakiet*> bufor_;
  double CGP_;
  Siec* siec_;
  Pakiet* pak_;
};

#endif // !CSMA_PP_NADAJNIK_H
