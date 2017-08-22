#ifndef CSMA_PP_STATYSTYKA_H
#define CSMA_PP_STATYSTYKA_H

struct Statystyka
{
  int pakiety_wygenerowane_;
  int pakiety_nadane_;
  int pakiety_stracone_;
  int pakiety_odebrane_;
  int licznik_retransmisji_;
  double sr_stopa_bledow_;
  double max_stopa_bledow_;
  double sr_l_ret_;
  double przeplywnosc_;   //  [pakiety/sek]
  double sr_opoznienie_;  //  [ms]
  double sr_czas_oczekiwania_;  //  [ms]
};

#endif // !CSMA_PP_STATYSTYKA_H
