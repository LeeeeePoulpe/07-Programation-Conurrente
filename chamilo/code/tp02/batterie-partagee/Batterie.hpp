#ifndef BATTERIE_HPP_
#define BATTERIE_HPP_

#include <mutex>

class Batterie
{
public :
  Batterie();

  void frapper_decale(const unsigned long cote);
  void frapper_ensemble(const unsigned long cote);
  void afficher(void);

private :
  unsigned long toms[2];
  std::mutex mutex_toms[2];
};

#endif // BATTERIE_HPP_
