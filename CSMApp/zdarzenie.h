#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H

class Pakiet;

class Zdarzenie 
{
public:
  Zdarzenie(Pakiet* pak) : czas_zdarzenia_(-1.0), pakiet_(pak), priorytet_(0) {}
  ~Zdarzenie() {}

  double czas_zdarzenia_;
  Pakiet* pakiet_;
  int priorytet_;
};

#endif // !CSMA_PP_ZDARZENIE_H
