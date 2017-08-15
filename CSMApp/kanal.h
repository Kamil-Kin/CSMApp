#ifndef CSMA_PP_KANAL_H
#define CSMA_PP_KANAL_H

#include <list>

class Pakiet;

using std::list;

class Kanal 
{
public:
  Kanal();
  ~Kanal();
  void KanalWolny(bool stan_lacza);
  bool StanLacza();
  bool CzyKolizja();
  void DodajDoKanalu(Pakiet*);
  void UsunZKanalu();
private:
  bool czy_wolny_;
  list<Pakiet*> lacze_;
};

#endif // !CSMA_PP_KANAL_H
