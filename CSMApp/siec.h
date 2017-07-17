#ifndef CSMA_PP_SIEC_H
#define CSMA_PP_SIEC_H

#include <vector>

class Nadajnik;
class Kanal;

class Siec 
{
public:
  Siec();
  ~Siec();
private:
  const int kLiczbaNad_ = 4;
  std::vector<Nadajnik*> nadajniki_;
  Kanal* kanal_;
};

#endif // !CSMA_PP_SIEC_H
