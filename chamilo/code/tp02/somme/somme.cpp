#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>

#include "RessourceProtegee.hpp"
#include "MonThread.hpp"

/*-------------------------------------------------------------------------------
 * Macro pour éviter les warnings "unused ..." dans une version intermédiaire.
 * A enlever lorsqu'elle n'est plus utilisée.
 * -----------------------------------------------------------------------------*/
#define UNUSED(x) (void)(x)

using namespace std;

static void usage(const char* nom)
{
  cerr << "Usage : " << nom << " {une | pls} nb_threads nb_itérations" << endl;
}

int main(int argc, char*argv[])
{
  if (argc != 4)
  {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  // ressource partagée dont les accès doivent être protégés
  RessourceProtegee ressource;

  // option d'exécution
  bool une_sc_par_thread;
  if (string(argv[1])=="une")
  {
    une_sc_par_thread = true;
  }
  else if (string(argv[1])=="pls")
  {
    une_sc_par_thread = false;
  }
  else {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  unsigned long nb_threads = stoul(argv[2]);
  unsigned long nb_iterations = stoul(argv[3]);

  // création des threads
  vector<thread> mes_threads;
  //--TODO-- à remplacer --TODO--/
  UNUSED(nb_threads); UNUSED(nb_iterations); UNUSED(une_sc_par_thread);
  //-----------------------------/

  // attente des threads
  //--TODO-- à compléter --TODO--/
  //-----------------------------/

  cout << "À la fin,            total = " << setw(9) << ressource.acces_non_protege() << endl;

  return EXIT_SUCCESS;
}

