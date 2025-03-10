#include <thread>
#include <chrono>

#include "Outils.hpp"
#include "Lecteur.hpp"
#include "Redacteur.hpp"

using namespace std;
using namespace std::chrono;

duration<double> const Redacteur::start[nb_red] = {seconds(1), seconds(2), seconds(6)};
duration<double> const Redacteur::duree[nb_red] = {seconds(4), seconds(3), seconds(1)};

Redacteur::Redacteur(const unsigned long numero_, Outils& outils_) :
  numero(numero_),
  outils(outils_)
{}

void Redacteur::operator()(void)
{
  this_thread::sleep_for(start[numero]);

  outils.afficher_message(Lecteur::nb_lec+numero," demande ");
  outils.debut_ecriture();
  outils.afficher_message(Lecteur::nb_lec+numero,"  écrit  ");

  this_thread::sleep_for(duree[numero]);

  outils.afficher_message(Lecteur::nb_lec+numero,"  fini   ");
  outils.fin_ecriture();
}
