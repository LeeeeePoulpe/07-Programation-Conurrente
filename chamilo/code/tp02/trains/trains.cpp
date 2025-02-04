#include <vector>
#include <thread>

#include "VoieVille.hpp"
#include "Positions.hpp"
#include "Temps.hpp"
#include "Train.hpp"

using namespace std;

int main(void)
{
  const unsigned long nb_threads = 15;
  const unsigned long nb_villes = 3;

  // création des voies reliées aux villes.
  // chacune est une ressource critique protégée par son mutex
  vector<VoieVille> voies_villes(nb_villes);

  // vecteur des positions des différents trains (ressource critique)
  Positions positions(nb_threads,voies_villes);

  // thread affichant à intervalles de temps réguliers
  // la position des différents trains en circulation
  bool tempsActif = true;
  thread temps(Temps(tempsActif,positions));

  // création des threads simulant les trains
  vector<thread> mes_threads;
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.push_back(thread(Train(i,positions)));

  // attente des threads simulant les trains
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.at(i).join();

  // arrêt et récupération du thread temps
  tempsActif = false;
  temps.join();

  return EXIT_SUCCESS;
}
