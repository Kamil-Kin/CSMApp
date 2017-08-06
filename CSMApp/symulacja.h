#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include <vector>
#include <queue>

class Siec;
class Zdarzenie;
class Pakiet;

using std::vector;
using std::priority_queue;
using std::binary_function;

//const auto comparer = [](Zdarzenie* z1, Zdarzenie* z2)->bool
//{return z1->pobierz_czas_zd() > z2->pobierz_czas_zd(); };

struct comparer : public binary_function<Pakiet*, Pakiet*, bool> 
{ bool operator()(const Pakiet* pak1, const Pakiet* pak2) const; };

class Symulacja 
{
public:
  Symulacja();
  ~Symulacja();

  void run();
  double StanZegara() { return zegar_; }

  void DodajDoKalendarza(Pakiet* pak);
  void UsunZKalendarza();
  Pakiet* PobierzPierwszyElement();

  double zegar_;
private:

  Siec* siec_;
  Zdarzenie* zd_;

  priority_queue<Pakiet*, vector<Pakiet*>, comparer> kalendarz_;
  //priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)> kalendarz_;
  //priority_queue<Zdarzenie*> kalendarz_;
};

#endif // !CSMA_PP_SYMULACJA_H
