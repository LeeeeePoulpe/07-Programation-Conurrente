#include <iostream>
#include <vector>
#include <thread>

#include "Lecteur.hpp"
#include "Redacteur.hpp"
#include "Outils.hpp"
#include "OutilsShared.hpp"
#include "OutilsCond.hpp"
#include "OutilsCondPrio.hpp"
#include "OutilsCondFifo.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "Usage : " << argv[0] << " {cond|condPrio|condFifo|shared}" << endl;
    exit(EXIT_FAILURE);
  }

  // outils partagés pour la synchronisation
  Outils* outils_synchro;

  // affichage de l'en-tête
  for (unsigned long i=0; i < Lecteur::nb_lec; i++)
    cout << "  Lec." << i+1 << "  ";
  for (unsigned long i=0; i < Redacteur::nb_red; i++)
    cout << "  Red." << i+1 << "  ";
  cout << endl;

  int mon_hash = static_cast<int>(argv[1][4]); //switch ne fonctionne pas sur les string,
  // on prend ici le code ASCII d'un caractère unique dans les options possibles

  switch(mon_hash) {
  case 101: // 'd'
    outils_synchro=new OutilsShared();
    break;
  case 0:  // ''
    outils_synchro=new OutilsCond();
    break;
  case 80: // 'P'
    outils_synchro=new OutilsCondPrio();
    break;
  case 70: // 'F'
    outils_synchro=new OutilsCondFifo();
    break;
  default:
    cerr << "Usage : " << argv[0] << " {cond|condPrio|condFifo|shared}" << endl;
    exit(EXIT_FAILURE);
  }

  // création des threads
  vector<thread> mes_threads;

  for (unsigned long i=0; i < Lecteur::nb_lec; i++)
    mes_threads.push_back(thread(Lecteur(i,*outils_synchro)));

  for (unsigned long i=0; i < Redacteur::nb_red; i++)
    mes_threads.push_back(thread(Redacteur(i,*outils_synchro)));

  // attente des threads
  for (unsigned long i=0; i < Lecteur::nb_lec+Redacteur::nb_red; i++)
    mes_threads.at(i).join();

  delete outils_synchro;

  return EXIT_SUCCESS;
}
