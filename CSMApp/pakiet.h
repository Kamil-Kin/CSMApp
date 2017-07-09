#ifndef CSMA_PP_PAKIET_H
#define CSMA_PP_PAKIET_H

class Pakiet 
{
public:
  Pakiet(int idx);
  ~Pakiet();
  int getId();
private:
  int id_tx_;
};

#endif // !CSMA_PP_PAKIET_H
