#include <thread>
#include <chrono>

#include "Auto.hpp"
#include "Carrefour.hpp"

using namespace std;
using namespace std::chrono;

duration<double> const Auto::dureeAvantArrivee(milliseconds(900));
duration<double> const Auto::dureeAvantFeu(milliseconds(100));
duration<double> const Auto::dureeTraversee(milliseconds(100)); // 100 ou 2000 selon la question

default_random_engine Auto::gen;
uniform_int_distribution<int> Auto::dis(1,3);

Auto::Auto(const unsigned long numero_, const unsigned int voie_, Carrefour& carrefour_, const bool alea) :
  numero(numero_),
  voie(voie_),
  carrefour(carrefour_)
{
  if(alea) {
    this_thread::sleep_for(dis(gen)*dureeAvantArrivee);
  }
  else {
    this_thread::sleep_for(dureeAvantArrivee);
  }
}

void Auto::operator()(void)
{
  carrefour.afficherMessageAuto(voie, numero, " ARRIVE");
  this_thread::sleep_for(dureeAvantFeu); // le temps d'arriver au feu

  carrefour.entrer_dans_carrefour(voie);

  carrefour.afficherMessageAuto(voie, numero, " TRAVERSE");
  this_thread::sleep_for(dureeTraversee); // le temps de traverser
  carrefour.afficherMessageAuto(voie, numero, " QUITTE");

  carrefour.sortir_du_carrefour(voie);
}
