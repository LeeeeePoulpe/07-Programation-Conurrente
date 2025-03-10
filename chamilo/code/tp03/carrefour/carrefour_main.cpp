#include <iostream>
#include <thread>
#include <vector>

#include "Commutation.hpp"
#include "Auto.hpp"
#include "Carrefour.hpp"

using namespace std;
using namespace std::chrono; // pour milliseconds et duration

static void usage(const char* nom)
{
  cerr << "Usage : " << nom << " NB_AUTOS_PAR_VOIE {avec_alea | sans_alea}" << endl;
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  unsigned long nb_autos_par_voie = stoul(argv[1]);

  // durées entre deux créations de threads automobilles aléatoires ou non
  bool alea;
  if (string(argv[2])=="avec_alea")
    alea = true;
  else if (string(argv[2])=="sans_alea")
    alea = false;
  else {
    usage(argv[0]); exit(EXIT_FAILURE);
  }

  // création du carrefour
  Carrefour carrefour;

  // création du thread commutation
  bool commutation_active = true;
  thread commutation(Commutation(carrefour, commutation_active));

  // création des threads automobiles
  vector<thread> mes_threads;
  for (unsigned long i=0; i < nb_autos_par_voie; i++)
  {
    // on lance des voitures avec temps de construction aléatoire ou non
    mes_threads.push_back(thread(Auto(i, Carrefour::voie_principale, carrefour, alea)));
    mes_threads.push_back(thread(Auto(i, Carrefour::voie_secondaire, carrefour, alea)));
  }

  // attente des threads automobiles
  for (unsigned long i=0; i < 2*nb_autos_par_voie; i++)
    mes_threads.at(i).join();

  // arrêt et récupération du thread commutation
  commutation_active = false;
  commutation.join();

  // Le programme se termine
  cout << "FIN" << endl;
  return EXIT_SUCCESS;
}
