#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H

class Pakiet;

class Zdarzenie 
{
public:
  Zdarzenie(Pakiet *pak) : czas_zdarzenia_(0.0), pakiet_(pak) {}
  void ustaw_czas_zd(double time) { czas_zdarzenia_ = time; }
  double pobierz_czas_zd() { return czas_zdarzenia_; }
private:
  double czas_zdarzenia_;
  Pakiet* pakiet_;
};

#endif // !CSMA_PP_ZDARZENIE_H
