#ifndef CSMA_PP_KANAL_H
#define CSMA_PP_KANAL_H

class Kanal 
{
public:
  Kanal();
  ~Kanal();
  void UstawLacze(bool stan_lacza);   //set
  bool StanLacza();                   //get
private:
  bool czy_wolny_;
};

#endif // !CSMA_PP_KANAL_H
