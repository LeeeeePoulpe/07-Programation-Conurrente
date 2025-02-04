#include <iostream>
#include <iomanip>

#include "Trajet.hpp"
#include "Positions.hpp"

using namespace std;

Positions::Positions(const unsigned long nb_threads, vector<VoieVille>& voies_villes) :
  position(vector<char>(nb_threads,' '))
{
  // Entête de la simulation : affichage des trajets des différents trains
  for (unsigned long i=0; i < nb_threads; i++)
    cout << setw(3) << i << " |";
  cout << endl;

  // création et affichage des trajets
  for (unsigned long i=0; i < nb_threads; i++)
    trajets.push_back(Trajet(i,voies_villes));

  cout << endl;
}

/*-----------------------------------------------------------------------------*
 *            Pour la création des threads trains                              *
 *-----------------------------------------------------------------------------*/
Trajet& Positions::getTrajet(const unsigned long numero)
{
  return trajets.at(numero);
}

/*-----------------------------------------------------------------------------*
 *            Pour affichage des positions par le thread Temps                 *
 *-----------------------------------------------------------------------------*/
void Positions::afficherPositions(void)
{
  lock_guard<mutex> verrou(mutex_position);
  for (unsigned long i=0; i<position.size(); i++)
    cout << "   " << position.at(i) << "|";
  cout << endl;
}

/*-----------------------------------------------------------------------------*
 *        Changements de position du train numero                              *
 *-----------------------------------------------------------------------------*/
void Positions::sePreparer(const unsigned long numero)
{
  lock_guard<mutex> verrou(mutex_position);
  afficherNouvellesPositions(numero,"PRE");
  testerCollisions();
}

void Positions::partir(const unsigned long numero)
{
  lock_guard<mutex> verrou(mutex_position);
  position.at(numero)=trajets.at(numero).getDepart();
  afficherNouvellesPositions(numero,"DEP");
  testerCollisions();
}

void Positions::arriverJonction(const unsigned long numero)
{
  lock_guard<mutex> verrou(mutex_position);
  position.at(numero)='J';
  afficherNouvellesPositions(numero,"ARR");
  testerCollisions();
}

void Positions::partirJonction(const unsigned long numero)
{
  lock_guard<mutex> verrou(mutex_position);
  afficherNouvellesPositions(numero,"DEP");
  position.at(numero)=trajets.at(numero).getArrivee();
  testerCollisions();
}

void Positions::arriver(const unsigned long numero)
{
  lock_guard<mutex> verrou(mutex_position);
  afficherNouvellesPositions(numero,"ARR");
  position.at(numero)=' ';
  testerCollisions();
}

/*-----------------------------------------------------------------------------*
 *    Pour test de collision et affichage des nouvelles positions              *
 *-----------------------------------------------------------------------------*/
// Test de collision avec les autres trains
// à exécuter à chaque changement de position/état
void Positions::testerCollisions(void)
{
  bool collision = false;
  char pos = ' ';
  for (unsigned long i=0; i < position.size(); i++)
    for (unsigned long j=i+1; j < position.size(); j++)
    {
      // pour qu'il y ait collision, les trains doivent circuler sur la même voie
      if (position.at(i)==position.at(j))
      {
        pos = position.at(i);
        // et donc en particulier ne pas être en gare
        if (pos == ' ')
          collision = false;
        // si les deux trains sont à la jonction,
        // il faut regarder leurs trajets (depart/arrivée)
        else if (pos != 'J')
          collision = true;
        else if ( (trajets.at(i).getDepart()==trajets.at(j).getDepart()
                    &&
                   trajets.at(i).getArrivee()==trajets.at(j).getArrivee())
                 ||
                  (trajets.at(i).getDepart()==trajets.at(j).getArrivee()
                    &&
                   trajets.at(i).getArrivee()==trajets.at(j).getDepart())
                )
          collision = true;
        if (collision)
        {
          cerr << "###COLLISION en " << pos;
          cerr << " entre le train " << i << " et " << j << endl;
          throw;
        }
      }
    }
}

void Positions::afficherNouvellesPositions(const unsigned long numero, const string& message)
{
  for (unsigned long i=0; i < position.size(); i++)
  {
    if (i==numero)
    {
      cout << message;
      if (message=="PRE")
        cout << trajets.at(i).getDepart();
      else
        cout << position.at(i);
    }
    else
      cout << "   " << position.at(i);
    cout << "|";
  }
  cout << endl;
}
