#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include <vector>
#include <iostream>

class Siec;
class Pakiet;

using std::vector;

class Nadajnik 
{
public:
  
  Nadajnik(int idx);
  ~Nadajnik();
  void setCGP(double CGP) { CGP_ = CGP; }
  double getCGP() { return CGP_; }
  double losujCGP();//TO DO
  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora();
  Siec* getWebId();
  Pakiet* CzyPierwszy();
private:
  int id_;
  vector<Pakiet*> bufor_;
  double CGP_;
  Pakiet* frame_;
  Siec* siec_;
};

#endif // !CSMA_PP_NADAJNIK_H
