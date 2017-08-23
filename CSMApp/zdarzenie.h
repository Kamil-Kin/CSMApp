#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H

class Pakiet;

class Zdarzenie 
{
public:
  //Zdarzenie(double czas) : czas_zdarzenia_(czas), pakiet_(nullptr) {}
  Zdarzenie(Pakiet* pak) : czas_zdarzenia_(-1.0), pakiet_(pak) {}
  ~Zdarzenie() {}

  double czas_zdarzenia_;
  Pakiet* pakiet_;
};

#endif // !CSMA_PP_ZDARZENIE_H
