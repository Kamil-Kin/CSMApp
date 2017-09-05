#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H

class Symulacja;
class Siec;
class Kanal;
class Nadajnik;
class Zdarzenie;

class Pakiet
{
public:
  Pakiet(int idx, Symulacja* sym, Siec* siec, Kanal* kanal, Nadajnik* nad);
  ~Pakiet();
  //int losujCTP();
  //double losujPT();
  //double losujR();
  void aktywacja(double czas);
  void aktywacja(double czas, int priorytet);
  void execute(bool logi);
  
  int id_tx_;
  int faza_;
  bool skonczony_;

  double czas_w_buforze_;
  double opoznienie_pakietu_;

private:
  const int kLR = 5;
  const double kPT = 0.2;
  const double kCTIZ = 1.0;
  bool kolizja_;
  double czas_CTP_;
  double p;
  int nr_ret_;
  double czas_CRP_;
  bool ack_;
  //statystyki
  double czas_narodzin_;
  double czas_nadania_;
  double czas_odebrania_;

  Zdarzenie* moje_zdarzenie_;
  Nadajnik* nad_;
  Kanal* kanal_;
  Siec* siec_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PAKIET_H
