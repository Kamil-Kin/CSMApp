#ifndef CSMA_PP_ZDARZENIE_H
#define CSMA_PP_ZDARZENIE_H

class Proces;

class Zdarzenie 
{
public:
  //Zdarzenie(double czas) : czas_zdarzenia_(czas), pakiet_(nullptr) {}
  Zdarzenie(Proces* proc) : czas_zdarzenia_(-1.0), proces_(proc) {}
  ~Zdarzenie() {}
  //void UstawCzasZd(double time) { czas_zdarzenia_ += time; }
  //double PobierzCzasZd() const { return czas_zdarzenia_; }
  //Proces* PobierzProces() { return proces_; }
  double czas_zdarzenia_;
  Proces* proces_;
//private:
};

#endif // !CSMA_PP_ZDARZENIE_H
