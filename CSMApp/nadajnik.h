#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include <vector>
#include <iostream>

class Siec;
class Pakiet;

class Nadajnik 
{
public:
  Nadajnik(int idx);
  ~Nadajnik();

  void NowyPakiet(int idx);

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

  Pakiet* pak_;
  Siec* siec_;
};

#endif // !CSMA_PP_NADAJNIK_H
