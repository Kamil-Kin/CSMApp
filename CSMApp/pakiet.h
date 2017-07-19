#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H

class Symulacja;
class Kanal;
class Nadajnik;
class Zdarzenie;

class Pakiet 
{
public:
  Pakiet(int idx, Symulacja* sym, Kanal* kanal, Nadajnik* nad);
  ~Pakiet();
  int losujCTP();
  double losujPT();
  void aktywacja(double czas);
  void execute();

private:
  const double kPT = 0.2;
  int faza_;
  bool skonczony_;
  int id_tx_;
  int CTP_;

  Zdarzenie* moje_zd_;
  Nadajnik* nad_;
  Kanal* kanal_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PAKIET_H
