#include <iostream>
#include "RessourceProtegee.hpp"
#include <mutex>

using namespace std;

RessourceProtegee::RessourceProtegee() :
  total(0)
{}

void RessourceProtegee::incrementer_avec_une_sc(unsigned long numero, unsigned long nb_iterations)
{
  mon_mutex.lock();
  for (unsigned long i=0; i<nb_iterations; i++)
  {
    cout << " " << numero << ",";
    total++;
  }
  cout << endl;
  mon_mutex.unlock();
}

void RessourceProtegee::incrementer_avec_pls_sc(unsigned long numero, unsigned long nb_iterations)
{
  for (unsigned long i=0; i<nb_iterations; i++)
  {
    mon_mutex.lock();
    cout << " " << numero << ",";
    total++;
    mon_mutex.unlock();
  }
  cout << endl;
}

// méthode donnant un accès non protégé à la ressource :
// le thread appelant cette méthode doit être seul à s'exécuter
unsigned long RessourceProtegee::acces_non_protege(void)
{
  return total.load();
}
