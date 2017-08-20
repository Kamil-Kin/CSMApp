#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include <vector>

class Ziarno;
class Symulacja;
class Nadajnik;
class Kanal;
class Pakiet;

using std::vector;

class Siec 
{
public:
  Siec(Symulacja* sym, Ziarno ziarno);
  ~Siec();
  int LiczbaNad() { return kLiczbaNad_; }
  //Symulacja* getSim() { return sym_; }
  //Kanal* getKanal() { return kanal_; }
  //Nadajnik* getNad(int id) { return nadajniki_.at(id); }

private:
  const int kLiczbaNad_ = 1;
  vector<Nadajnik*> nadajniki_;
  Symulacja* sym_;
  Kanal* kanal_;
};

#endif // !CSMA_PP_SIEC_H
