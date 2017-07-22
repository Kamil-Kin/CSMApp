#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H

class Pakiet;

class Zdarzenie 
{
public:
  //Zdarzenie(double czas) : czas_zdarzenia_(czas), pakiet_(nullptr) {}
  Zdarzenie(Pakiet* pak) : czas_zdarzenia_(0.0), pakiet_(pak) {}
  ~Zdarzenie() {}
  void ustaw_czas_zd(double time) { czas_zdarzenia_ = time; }
  double pobierz_czas_zd() const{ return czas_zdarzenia_; }
private:
  double czas_zdarzenia_;
  Pakiet* pakiet_;
};

#endif // !CSMA_PP_ZDARZENIE_H
