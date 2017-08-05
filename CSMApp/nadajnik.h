#ifndef CSMA_PP_NADAJNIK_H
#define CSMA_PP_NADAJNIK_H

#include <vector>
#include <iostream>
//class Symulacja;
class Siec;
class Kanal;
class Pakiet;

class Nadajnik 
{
public:
  Nadajnik(int idx, Siec* siec, Kanal* kanal);
  ~Nadajnik();

  //void setCGP(double CGP) { CGP_ = CGP; }
  //double getCGP() { return CGP_; }
  double losujCGP();
  void DodajDoBufora(Pakiet* pak);
  void UsunZBufora();
  Pakiet* PierwszyPakiet();

private:
  int id_;
  std::vector<Pakiet*> bufor_;
  double CGP_;
  //Symulacja* sym_;
  Siec* siec_;
  Kanal* kanal_;
  Pakiet* pak_;
};

#endif // !CSMA_PP_NADAJNIK_H
