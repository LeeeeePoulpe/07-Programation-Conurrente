#include <iostream>
#include "RessourceProtegee.hpp"

using namespace std;

RessourceProtegee::RessourceProtegee() :
  total(0)
{}

void RessourceProtegee::incrementer_avec_une_sc(unsigned long numero, unsigned long nb_iterations)
{
  //--TODO-- à compléter --TODO--/
  for (unsigned long i=0; i<nb_iterations; i++)
  {
    cout << " " << numero << ",";
    total++;
  }
  cout << endl;
  //-----------------------------/
}

void RessourceProtegee::incrementer_avec_pls_sc(unsigned long numero, unsigned long nb_iterations)
{
  //--TODO-- à compléter --TODO--/
  for (unsigned long i=0; i<nb_iterations; i++)
  {
    cout << " " << numero << ",";
    total++;
  }
  cout << endl;
  //-----------------------------/
}

// méthode donnant un accès non protégé à la ressource :
// le thread appelant cette méthode doit être seul à s'exécuter
unsigned long RessourceProtegee::acces_non_protege(void)
{
  return total;
}
