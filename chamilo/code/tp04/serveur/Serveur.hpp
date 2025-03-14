#ifndef SERVEUR_HPP_
#define SERVEUR_HPP_

#include <mutex>
#include <map>
#include <boost/asio.hpp>

#include "ThreadClient.hpp"
#include "ClientConnecte.hpp"

class Serveur
{
public :
  Serveur(unsigned short n_port);


  [[noreturn]] void attend_clients(void);
  unsigned long nb_clients(void);
  void envoyer_message_vers_tous_clients(unsigned long numero_client, const std::string& chaine_recue);

private :
  boost::asio::io_service service_es;
  boost::asio::ip::tcp::acceptor socket_ecoute;

  // attribut numero_nouveau_client
  unsigned long numero_nouveau_client;


  // TODO: à compléter: mutex pour cout

  // std::map 
  std::map<unsigned long, ClientConnecte> clients;
  // TODO: Outil de synchro à définir
  

  // pour faciliter les accès depuis ces autres classes
  // il n'est donc pas nécessaire d'écrire des "getters"
  friend class ThreadClient;
  friend class ClientConnecte;
};

#endif // SERVEUR_HPP_
