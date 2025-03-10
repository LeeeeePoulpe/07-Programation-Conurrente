#ifndef LECTEUR_HPP_
#define LECTEUR_HPP_

#include <chrono>

#include "Outils.hpp"

class Lecteur
{
public :
  Lecteur(const unsigned long numero_, Outils& outils_);
  void operator()(void);

  // constantes
  static const unsigned long nb_lec = 3;

private :
  const unsigned long numero;
  Outils& outils;

  static std::chrono::duration<double> const start[nb_lec];
  static std::chrono::duration<double> const duree[nb_lec];
};

#endif // LECTEUR_HPP_
