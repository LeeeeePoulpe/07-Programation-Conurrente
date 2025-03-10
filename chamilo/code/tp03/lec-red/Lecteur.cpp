#include <thread>
#include <chrono>

#include "Outils.hpp"
#include "Lecteur.hpp"

using namespace std;
using namespace std::chrono;

duration<double> const Lecteur::start[nb_lec] = {seconds(3), seconds(4), seconds(7)}; //12
duration<double> const Lecteur::duree[nb_lec] = {seconds(3), seconds(1), seconds(2)};

Lecteur::Lecteur(const unsigned long numero_, Outils& outils_) :
  numero(numero_),
  outils(outils_)
{}

void Lecteur::operator()(void)
{
  this_thread::sleep_for(start[numero]);

  outils.afficher_message(numero," demande ");
  outils.debut_lecture();
  outils.afficher_message(numero,"   lit   ");

  this_thread::sleep_for(duree[numero]);

  outils.afficher_message(numero,"  fini   ");
  outils.fin_lecture();
}
