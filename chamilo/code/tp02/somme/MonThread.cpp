#include <iostream>

#include "MonThread.hpp"

using namespace std;

MonThread::MonThread(const unsigned long numero_, RessourceProtegee& ressource_, bool une_sc_par_thread_, const unsigned long nb_iterations_) :
  numero(numero_),
  ressource(ressource_),
  une_sc_par_thread(une_sc_par_thread_),
  nb_iterations(nb_iterations_)
{}

void MonThread::operator()(void)
{
  if (une_sc_par_thread)
  {
    ressource.incrementer_avec_une_sc(numero,nb_iterations);
  }
  else
  {
    ressource.incrementer_avec_pls_sc(numero,nb_iterations);
  }
}
