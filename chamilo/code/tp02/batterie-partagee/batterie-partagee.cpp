#include <thread>
#include <vector>

#include "Batterie.hpp"
#include "BatteurJazz.hpp"
#include "BatteurRustre.hpp"

using namespace std;

int main(void)
{
  const unsigned long nb_threads = 2;

  // ressource partagée dont les accès doivent être protégés
  Batterie batterie;

  // création des threads
  vector<thread> mes_threads;
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.push_back(thread(BatteurJazz(i,batterie)));

  // attente des threads
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.at(i).join();

  batterie.afficher();

  return EXIT_SUCCESS;
}

