#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include <vector>

class Symulacja;
class Nadajnik;
class Kanal;

class Siec 
{
public:
  Siec(Symulacja* sym);
  ~Siec();

  Symulacja* getSim() { return sym_; }

private:
  const int kLiczbaNad_ = 4;
  std::vector<Nadajnik*> nadajniki_;

  Symulacja* sym_;
  Kanal* kanal_;
};

#endif // !CSMA_PP_SIEC_H
