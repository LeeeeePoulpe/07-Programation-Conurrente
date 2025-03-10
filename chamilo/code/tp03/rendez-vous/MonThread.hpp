#ifndef MONTHREAD_HPP_
#define MONTHREAD_HPP_

#include "RendezVous.hpp"

// Classe avec opérateur parenthèses défini
class MonThread
{
public :
  MonThread(const unsigned long numero_, const unsigned long nb_rendez_vous_, RendezVous& rv_, const bool cascade_);
  void operator()();

private :
  const unsigned long numero;
  RendezVous& rv;
  const unsigned long nb_rendez_vous;
  const bool cascade;
};

#endif // MONTHREAD_HPP_
