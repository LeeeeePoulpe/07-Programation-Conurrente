#include <iostream>
#include <string>

#include "ThreadReception.hpp"
#include "EnvoiReception.hpp"
#include "Client.hpp"

using namespace std;

ThreadReception::ThreadReception(boost::asio::ip::tcp::socket& sock_) :
  sock(sock_)
{ }

[[noreturn]] void ThreadReception::recevoir_et_afficher_messages(void)
{
  try
  {
    while(true)
    {
      // Réception d'un message (émetteur,texte)
      // TODO: à compléter/remplacer
      (void)sock;
      unsigned long numero=0;
      string chaine_recue="";

      // Affichage de l'émetteur et du texte
      cout<<endl; // fin de ligne pour afficher en dessous du prompt
      if(numero==0)
	cout<<"Le serveur dit : "<<chaine_recue<<endl;
      else
	cout<<"Le client n°"+to_string(numero)+" dit : "+chaine_recue<<endl;
      cout<<prompt<<flush; // on ré-affiche le "prompt"
    }
  }
  catch(exception& e)
  {
    cerr<<"Exception dans le thread de réception : "<<e.what()<<endl;
  }
  cout<<"Connexion au serveur perdue.  Fin du programme."<<endl;
  exit(0); // évite un vilain message d'erreur du thread principal
}

[[noreturn]] void ThreadReception::operator()(void)
{
  recevoir_et_afficher_messages();
}
