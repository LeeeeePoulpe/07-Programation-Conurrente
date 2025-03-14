#ifndef CLIENT_CONNECTE_HPP_
#define CLIENT_CONNECTE_HPP_

#include <boost/asio.hpp>

class Serveur; // déclaration "forward" pour couper le cycle de dépendances entre classes

// Classe qui sert à stocker les informations relatives à un client, en particulier son socket.

class ClientConnecte
{
public :
  ClientConnecte(unsigned long numero_client_, Serveur& serveur_);

private :
  unsigned long numero_client;
  Serveur& serveur;

  // attention: sock non copiable => ClientConnecte non copiable
  boost::asio::ip::tcp::socket sock; // attribut non copiable !

  // pas de mutex pour sock
  // pour simplifier, on utilise le mutex de "clients"
  // attention en cas d'extension du programme !

  // pour faciliter les accès depuis ces autres classes
  // il n'est donc pas nécessaire d'écrire des "getters"
  friend class Serveur;
  friend class ThreadClient;
};

#endif // CLIENT_CONNECTE_HPP_
