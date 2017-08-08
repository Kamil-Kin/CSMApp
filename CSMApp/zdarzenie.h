#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H

class Proces;

class Zdarzenie 
{
public:
  //Zdarzenie(double czas) : czas_zdarzenia_(czas), pakiet_(nullptr) {}
  Zdarzenie(Proces* proc) : czas_zdarzenia_(-1.0), proces_(proc) {}
  ~Zdarzenie() {}

  double czas_zdarzenia_;
  Proces* proces_;
};

#endif // !CSMA_PP_ZDARZENIE_H
