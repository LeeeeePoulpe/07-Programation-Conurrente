#ifndef REDACTEUR_HPP_
#define REDACTEUR_HPP_

#include <chrono>

#include "Outils.hpp"

class Redacteur
{
public :
  Redacteur(const unsigned long numero_, Outils& outils_);
  void operator()(void);

  // constantes
  static const unsigned long nb_red = 3;

private :
  const unsigned long numero;
  Outils& outils;

  static std::chrono::duration<double> const start[nb_red];
  static std::chrono::duration<double> const duree[nb_red];
};

#endif // REDACTEUR_HPP_
