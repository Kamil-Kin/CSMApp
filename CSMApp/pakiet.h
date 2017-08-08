#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H


#include <string>
class Symulacja;
class Kanal;
class Nadajnik;
class Zdarzenie;

using std::string;

class Pakiet 
{
public:
  Pakiet(int idx, Symulacja* sym, Kanal* kanal, Nadajnik* nad);
  ~Pakiet();
  int losujCTP();
  double losujPT();
  double losujR();
  void aktywacja(double czas);
  void execute(double zegar);
  double CzasZdarzenia() const;
  bool CzySkonczony() { return skonczony_; }
  void UstawKolor(string numer);
private:
  const int kLR = 5;
  const double kPT = 0.2;
  int faza_;
  bool skonczony_;
  int id_tx_;
  int czas_CTP_;
  int licznik_ret_;
  double czas_CRP_;
  bool ack_;
  double czas_zdarzenia;

  Zdarzenie* moje_zd_;
  Nadajnik* nad_;
  Kanal* kanal_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PAKIET_H
