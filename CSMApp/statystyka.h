#ifndef CSMA_PP_STATYSTYKA_H
#define CSMA_PP_STATYSTYKA_H

struct Statystyka
{
public:
  Statystyka()
  {
    pakiety_wygenerowane_ = 0;
    pakiety_nadane_ = 0;
    pakiety_stracone_ = 0;
    pakiety_odebrane_ = 0;
    licznik_retransmisji_ = 0;
    sr_stopa_bledow_ = 0.0;
    max_stopa_bledow_ = 0.0;
    sr_l_ret_ = 0.0;
    przeplywnosc_ = 0.0;
    sr_opoznienie_ = 0.0;
    sr_czas_oczekiwania_ = 0.0;
  }
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
