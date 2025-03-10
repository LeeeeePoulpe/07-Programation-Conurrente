#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

#include "RendezVous.hpp"
#include "MonThread.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 3 && argc != 4)
  {
    cerr << "Usage : " << argv[0] << " nb_threads nb_rendez_vous [cascade]" << endl;
    exit(EXIT_FAILURE);
  }

  const unsigned long nb_threads = stoul(argv[1]);
  const unsigned long nb_rendez_vous = stoul(argv[2]);
  const bool cascade = (argc==4 && string(argv[3])=="cascade");

  RendezVous mon_rv(nb_threads);

  // affichage de l'en-tête
  string titre;
  if (cascade)
    titre="Version : Cascade";
  else
    titre="Version : Le dernier réveille les autres";
  cout << endl << setw(static_cast<int>((nb_threads*16-titre.length())/2+titre.length())) << titre << endl;
  cout << setfill('-') << setw(static_cast<int>(nb_threads)*16) << "-" << setfill(' ')<< endl;
  for (unsigned long i=0; i < nb_threads; i++)
    cout << "   Thread "<< i << "    |";
  cout << endl;

  // création des threads se donnant nb_rendez_vous
  vector<thread> mes_threads;
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.push_back(thread(MonThread(i,nb_rendez_vous,mon_rv,cascade)));

  // attente des threads
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.at(i).join();

  return EXIT_SUCCESS;
}
