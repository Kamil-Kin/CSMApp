#ifndef CSMA_PP_PROCES_H
#define CSMA_PP_PROCES_H

class Zdarzenie;
class Symulacja;

class Proces
{
public:
  Proces(Symulacja* sym);
  ~Proces();

  void virtual execute() = 0;
  void aktywacja(double czas);

  int faza_;
  bool skonczony_;

private:
  Zdarzenie* moje_zdarzenie_;
  Symulacja* sym_;
};

#endif // !CSMA_PP_PROCES_H
