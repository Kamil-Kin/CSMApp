#ifndef CSMA_PP_SYMULACJA_H
#define CSMA_PP_SYMULACJA_H

#include <vector>
#include <queue>
#include <string>
class Siec;
class Zdarzenie;
//class Pakiet;

using std::vector;
using std::priority_queue;
using std::binary_function;
using std::string;

//const auto comparer = [](Zdarzenie* z1, Zdarzenie* z2)->bool
//{return z1->pobierz_czas_zd() > z2->pobierz_czas_zd(); };

struct comparer : public binary_function<Zdarzenie*, Zdarzenie*, bool>
{ bool operator()(const Zdarzenie* zd1, const Zdarzenie* zd2) const; };

class Symulacja 
{
public:
  Symulacja();
  ~Symulacja();

  void run();

  void DodajDoKalendarza(Zdarzenie* zd);
  void UsunZKalendarza();
  Zdarzenie* PobierzPierwszyElement();

  void UstawKolor(string numer);

  double zegar_;
  int liczba_symulacji_;
  double czas_symulacji_;
  char tryb_symulacji_;

private:

  Siec* siec_;
  Zdarzenie* zd_;

  priority_queue<Zdarzenie*, vector<Zdarzenie*>, comparer> kalendarz_;
  //priority_queue<Zdarzenie*, vector<Zdarzenie*>, decltype(comparer)> kalendarz_;
  //priority_queue<Zdarzenie*> kalendarz_;
};

#endif // !CSMA_PP_SYMULACJA_H
