#include <iostream>
#include <mutex>
#include <sys/syscall.h>

#include "ThreadClient.hpp"
#include "Serveur.hpp"
#include "EnvoiReception.hpp"

using namespace std;

ThreadClient::ThreadClient(ClientConnecte& client_, unsigned long numero_client_) :
  client(client_),
  serveur(client_.serveur),
  numero_client(numero_client_)
{ }

void ThreadClient::dialogue_avec_client(void)
{
  cout<<"Démarrage d'un thread de TID "<<syscall(SYS_gettid)<<" pour le client n°"<<numero_client<<endl;
  try
  {
    while(true)
    {
      // TODO: à compléter: réception d'une chaîne
      string chaine_recue="";
	cout<<"Client "<<numero_client<<" : "<<client.sock.remote_endpoint()<<" Chaîne reçue : "<<chaine_recue<<endl;
      serveur.envoyer_message_vers_tous_clients(numero_client,chaine_recue);
    }
  }
  catch(exception& e)
  {
    cerr<<"Exception dans un thread: "<<e.what()<<endl;
  }
    cout<<"Client déconnecté : "<<client.sock.remote_endpoint()<<endl;
    cout<<"Suppression du client "<<numero_client<<endl;

  // TODO: à compléter: enlever le client de la map, en exclusion mutuelle
  serveur.envoyer_message_vers_tous_clients(0,"Déconnexion du client n°"+to_string(numero_client)); // 0 = n° spécial représentant le serveur
    cout<<"Nombre de clients restants : "<<serveur.nb_clients()<<endl;

    cout<<"Fin du thread de TID "<<syscall(SYS_gettid)<<" associé au client n°"<<numero_client<<endl;
}

void ThreadClient::operator()(void)
{
  dialogue_avec_client();
}
