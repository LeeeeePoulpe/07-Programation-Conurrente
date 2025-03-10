#include <iostream>
#include <thread>
#include <vector>

#include "EcranManchots.hpp"
#include "Tampon.hpp"
#include "TamponCond.hpp"
#include "TamponSBQ.hpp"
#include "Producteur.hpp"
#include "Consommateur.hpp"

using namespace std;

static void usage(const char* nom)
{
  cerr << "Usage : " << nom << " {cond|sbq} nb_producteurs nb_elem_prod nb_consommateurs nb_elem_cons nb_cases_tampon" << endl;
}

int main(int argc, char* argv[])
{
  if (argc-1 != 6)
  {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  unsigned long nb_prod = stoul(argv[2]);
  unsigned long nb_elem_prod = stoul(argv[3]);
  unsigned long nb_cons = stoul(argv[4]);
  unsigned long nb_elem_cons = stoul(argv[5]);
  unsigned long taille = stoul(argv[6]);

  EcranManchots ecran(nb_prod,taille,nb_cons,nb_elem_cons);

  Tampon* tampon;
  if(string(argv[1])=="cond")
    tampon = new TamponCond(taille,ecran);
  else  if(string(argv[1])=="sbq")
    tampon = new TamponSBQ(taille,ecran);
  else
  {
    ecran.~EcranManchots();
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  // création des threads
  vector<thread> mes_threads;
  for (unsigned long i=0; i < nb_cons; i++)
    mes_threads.push_back(thread(Consommateur(i+1, nb_elem_cons, *tampon)));

  for (unsigned long i=0; i < nb_prod; i++)
    mes_threads.push_back(thread(Producteur(i+1, nb_elem_prod, *tampon)));

  // attente de la terminaison des threads
  for (unsigned long i=0; i < nb_cons+nb_prod; i++)
    mes_threads.at(i).join();

  delete tampon;

  getchar();

  return EXIT_SUCCESS;
}
