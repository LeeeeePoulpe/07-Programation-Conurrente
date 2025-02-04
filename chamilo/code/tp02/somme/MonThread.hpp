#ifndef MONTHREAD_HPP_
#define MONTHREAD_HPP_

#include "RessourceProtegee.hpp"

// Classe avec opérateur parenthèses défini
class MonThread
{
public :
  MonThread(const unsigned long numero_, RessourceProtegee& ressource_, const bool une_sc_par_thread_, const unsigned long nb_iterations_);
  void operator()(void);

private :
  const unsigned long numero;
  RessourceProtegee& ressource;
  const bool une_sc_par_thread;
  const unsigned long nb_iterations;
};

#endif // MONTHREAD_HPP_
