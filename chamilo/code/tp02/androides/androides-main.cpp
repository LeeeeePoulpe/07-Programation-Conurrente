#include <iostream>
#include <chrono>
#include <vector>
#include <thread>

#include "Ecran.hpp"
#include "SequenceEntiere.hpp"
#include "Androide.hpp"

using namespace std;

int main(int argc, char*argv[])
{
  if (argc != 2)
  {
    cerr << "Usage : " << argv[0] << " nb_threads" << endl;
    exit(EXIT_FAILURE);
  }

  const unsigned long nb_threads = stoul(argv[1]);

  Ecran ecran; // sert pour l'affichage de la position des androides

  // initialisateur du distributeur de numero
  SequenceEntiere seq(0);

  // création des threads
  vector<thread> mes_threads;
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.push_back(thread(Androide(seq, ecran)));

  // attente des threads
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.at(i).join();

  // Le programme se termine
  return EXIT_SUCCESS;
}
