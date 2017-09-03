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
  list<Pakiet*> lacze_;
private:
  bool wolny_;
    
};

#endif // !CSMA_PP_KANAL_H
