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

  bool Skonczony() { return skonczony_; }

  //Czas oczekiwania oraz opóŸnienie pakietu
  double CzasWBuforze() { return czas_w_buforze_; }
  double Opoznienie() { return opoznienie_pakietu_; }

  //Potwierdzenie odbioru
  bool PobierzACK() { return ack_; }
  void UstawACK(bool ack) { ack_ = ack; }

  //Unikatowe id pakietu
  long IdPakietu() { return id_pakietu_; }
  
  //Porównywanie pakietów, nie adresów pamiêci
  friend bool operator==(const Pakiet& lhs, const Pakiet& rhs);

private:
  const int kMaxLiczbaRetransmisji = 3;   //zmiana
  const double kPrawdopodobienstwo = 0.4;   //zmiana
  const double kCzasPotwierdzenia = 1.0;
  long id_pakietu_;
  int id_tx_;
  int faza_;
  bool ack_;
  bool skonczony_;
  double czas_transmisji_;
  double prawdopodobienstwo;
  int nr_retransmisji_;
  double czas_retransmisji_;
  //statystyki
  double czas_pojawienia_;
  double czas_nadania_;
  double czas_odebrania_;
  double czas_w_buforze_;
  double opoznienie_pakietu_;
  Zdarzenie* moje_zdarzenie_;
  Nadajnik* nad_;
  Kanal* kanal_;
  Siec* siec_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PAKIET_H
