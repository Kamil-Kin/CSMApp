#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include <vector>

class Ziarno;
class GenRownomierny;
class Symulacja;
class Nadajnik;
class Kanal;
class Pakiet;

using std::vector;

class Siec 
{
public:
  Siec(Symulacja* sym, int nr_sym);
  ~Siec();
  int LiczbaNad() { return kLiczbaNad_; }

  Symulacja* getSim() { return sym_; }
  Kanal* getKanal() { return kanal_; }
  Nadajnik* getNad(int id) { return nadajniki_.at(id); }
  Ziarno* getZiarno() { return ziarno_; }

  double LosCTP();
  double LosPT();
  double LosR(int l_ret);
private:
  const int kLiczbaNad_ = 2;
  vector<Nadajnik*> nadajniki_;

  Symulacja* sym_;
  Kanal* kanal_;
  Ziarno* ziarno_;
  GenRownomierny* losCTP_;
  GenRownomierny* losPT_;
  GenRownomierny* losR_;
};

#endif // !CSMA_PP_SIEC_H
