#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H

#include <iostream>

class Symulacja;
class Nadajnik;
class Zdarzenie;

using namespace std;

class Pakiet 
{
public:
  Pakiet(int idx);
  ~Pakiet();
  int losujCTP();//TO DO
  double losujPT();//TO DO
  void aktywacja(double czas);
  void execute();

private:
  int faza_;
  bool skonczony_;
  int id_tx_;
  int CTP_;
  Zdarzenie* moje_zd_;
  Nadajnik* nad_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PAKIET_H
