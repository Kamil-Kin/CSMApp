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
  bool KanalWolny();
  void DodajDoKanalu(Pakiet* pakiet);
  void UsunZKanalu(Pakiet* pakiet);
private:
  list<Pakiet*>* lacze_;
};

#endif // !CSMA_PP_KANAL_H
