#include <iostream>
#include <thread>
#include <chrono>

#include "Commutation.hpp"
#include "Carrefour.hpp"

using namespace std;
using namespace std::chrono;

duration<double> const Commutation::duree_principale(seconds(5));
duration<double> const Commutation::duree_secondaire(seconds(3));

Commutation::Commutation(Carrefour& carrefour_, bool& actif_) :
  carrefour(carrefour_),
  actif(actif_)
{}

void Commutation::operator()(void)
{
  while (actif)
  {
    this_thread::sleep_for(duree_principale);
    carrefour.basculer_sur(Carrefour::voie_secondaire);
    this_thread::sleep_for(duree_secondaire);
    carrefour.basculer_sur(Carrefour::voie_principale);
  }
}
