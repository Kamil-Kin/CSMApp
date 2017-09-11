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

  void aktywacja(double czas);
  void aktywacja(double czas, int priorytet);
  void execute(bool logi);

  int id_tx_;
  int faza_;
  bool skonczony_;
  bool ack_;

  double czas_w_buforze_;
  double opoznienie_pakietu_;
  friend bool operator==(const Pakiet& lhs, const Pakiet& rhs);
  __int64 id_;
  static __int64 licznik_;

private:
  const int kMaxLiczbaRetransmisji = 3; //todo
  const double kPrawdopodobienstwo = 0.2;
  const double kCzasPotwierdzenia = 1.0;

  double czas_transmisji_;
  double prawdopodobienstwo;
  int nr_retransmisji_;
  double czas_retransmisji_;
  //statystyki
  double czas_pojawienia_;
  double czas_nadania_;
  double czas_odebrania_;

  Zdarzenie* moje_zdarzenie_;
  Nadajnik* nad_;
  Kanal* kanal_;
  Siec* siec_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PAKIET_H
