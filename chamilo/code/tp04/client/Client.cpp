#include <iostream>
#include <thread>
#include <boost/asio.hpp>

#include "Client.hpp"
#include "EnvoiReception.hpp"
#include "ThreadReception.hpp"
#include "ThreadLecture.hpp"

using namespace std;

Client::Client(std::string nom, unsigned short n_port) :
  sock(service_es)
{
  // résolution DNS
  boost::asio::ip::tcp::resolver requeteur(service_es);
  auto endpoints = requeteur.resolve(nom, to_string(n_port));
  boost::asio::ip::tcp::endpoint point_distant = *endpoints.begin(); // on prend la 1ère adresse IP (dans le cas où le DNS en donne plusieurs)

  cout<<"Tentative de connexion au serveur "<<point_distant<<"..."<<endl;
  // connexion au serveur
  sock.connect(point_distant);
  cout<<"Connexion OK"<<endl;

  cout<<"Adresse IP et n° de port côté client : "<<sock.local_endpoint()<<endl;
}

void Client::dialogue_avec_serveur(void)
{
  // initialisation du n° de client avec le numéro envoyé par le serveur
  cout<<"Réception du numéro de client..."<<endl;
  unsigned long entier_recu; // TODO : mettre à jour !

  cout<<"Bonjour, le serveur à répondu que nous sommes le client n°"+to_string(entier_recu)<<endl;

  // TODO: à compléter V1: appel de la méthode ThreadLecture::lire_clavier_et_envoyer_messages()
  //                   V2: lancer les 2 threads du client

  // TODO: à compléter V2: attendre la fin du thread de lecture
  // on fait un join() pour occuper le thread principal
  // mais le programme sera arrêté par un exit() dans l'un des 2 threads secondaires
}
