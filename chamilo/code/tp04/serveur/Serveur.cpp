#include <iostream>
#include <utility> // pour std::move()

#include "Serveur.hpp"
#include "EnvoiReception.hpp"

using namespace std;
using boost::asio::ip::tcp;

// TODO Bonus : déclarer une constante N pour le nombre maximal de clients connectés

Serveur::Serveur(unsigned short n_port) :
  socket_ecoute(service_es,
		tcp::endpoint(tcp::v4(), n_port))
{
  numero_nouveau_client=1; // le n° 0 est réservé pour le serveur
}


[[noreturn]] void Serveur::attend_clients(void)
{
  cout<<"Adresse IP et n° de port côté serveur : "<<socket_ecoute.local_endpoint()<<endl;
  cout<<"En attente d'un client..."<<endl;

  // boucle infinie pour attendre les nouveaux clients
  while(true) {

    // créer un objet ClientConnecte
    ClientConnecte client(numero_nouveau_client,*this);

    // attendre une connexion TCP
    socket_ecoute.accept(client.sock);

    // stocker l'objet ClientConnecte dans la map
    // TODO : (attention à l'exclusion mutuelle)
    
    clients.emplace(numero_nouveau_client, move(client));
    ClientConnecte& client_ref=clients.at(numero_nouveau_client); // référence de l'objet déplacé qu'on aura le droit d'utiliser en dehors de cette section critique


    // afficher les paramètres IP du client
    // TODO: protéger l'affichage (question 6 de la partie 2.1)
      cout<<"Connexion d'un client : "<<client_ref.sock.remote_endpoint()<<endl;
 
    // TODO: envoyer au client son numéro


    // TODO V2: à compléter: annoncer à tous les clients l'arrivée d'un nouveau client

    // TODO: à compléter: lancer le thread ThreadClient
      cout<<"Nombre de clients : "<<nb_clients()<<endl;

    // incrementer le nouveau numero du client
    numero_nouveau_client++;
  }
}

// pas const car on modifie un mutex
unsigned long Serveur::nb_clients(void)
{
  // TODO: à compléter en pensant à l'exclusion mutuelle
  return 0;
}

void Serveur::envoyer_message_vers_tous_clients(unsigned long numero_client, const std::string& chaine)
{
  // TODO V2: à compléter: exclusion mutuelle

  // TODO V2: à remplacer: parcourir la map et envoyer la chaîne à tous les *autres* clients
  (void)numero_client; (void)chaine;
}
