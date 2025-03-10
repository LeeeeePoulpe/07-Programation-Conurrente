#include <iostream>
#include <thread>

#include "MonThread.hpp"
#include "RendezVous.hpp"

using namespace std;
using namespace std::chrono;

MonThread::MonThread(const unsigned long numero_, const unsigned long nb_rendez_vous_, RendezVous& rv_, const bool cascade_) :
  numero(numero_),
  rv(rv_),
  nb_rendez_vous(nb_rendez_vous_),
  cascade(cascade_)
{}

void MonThread::operator()(void)
{
  for (unsigned long r=1; r <= nb_rendez_vous; ++r)
  {
    this_thread::sleep_for(milliseconds(500)*(numero+1));
    rv.afficher(numero, " demande rv", r);
    if (cascade)
      rv.rvCascade();
    else
      rv.rvReveilleurUnique();
    rv.afficher(numero, " sort du rv", r);
  }
}
