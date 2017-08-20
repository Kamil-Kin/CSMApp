#ifndef CSMA_PP_STATYSTYKA_H
#define CSMA_PP_STATYSTYKA_H

struct Statystyka
{
  int pakiety_wygenerowane_;
  int pakiety_nadane_;
  int pakiety_stracone_;
  int pakiety_odebrane_;
  int licznik_retransmisji_;

};

#endif // !CSMA_PP_STATYSTYKA_H
