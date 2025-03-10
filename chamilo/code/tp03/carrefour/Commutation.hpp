#ifndef COMMUTATION_HPP_
#define COMMUTATION_HPP_
#include <mutex>

#include "Carrefour.hpp"

// Classe avec opérateur parenthèses défini
class Commutation
{
public :
  Commutation(Carrefour& carrefour_, bool& actif_);
  void operator()(void);

private :
  Carrefour& carrefour;
  bool& actif;

  // durée du feu vert sur chaque voie
  static std::chrono::duration<double> const duree_principale;
  static std::chrono::duration<double> const duree_secondaire;
};

#endif // COMMUTATION_HPP_
