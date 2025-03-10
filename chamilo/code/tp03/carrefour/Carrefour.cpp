#include <iostream>

#include "Carrefour.hpp"


using namespace std;

Carrefour::Carrefour()
{
  //--TODO-- à remplacer --TODO--/
  (void)voie_verte;
  (void)automobile_engagee;
  //-----------------------------/
}

void Carrefour::entrer_dans_carrefour(unsigned int voie)
{
  //--TODO-- à remplacer --TODO--/
  (void)voie;
  //-----------------------------/
}

void Carrefour::sortir_du_carrefour(unsigned int) // on n'utilise pas le paramètre dans cette version
{
  //--TODO-- à compléter --TODO--/
  //-----------------------------/
}

void Carrefour::basculer_sur(unsigned int nouvelle_voie_verte)
{
  //--TODO-- à compléter --TODO--/
  afficherMessageCommutation(voie_verte, " FEU ORANGE");
  afficherMessageCommutation(voie_verte, " FEU ROUGE");
  afficherMessageCommutation(voie_verte, " FEU VERT");
  //-----------------------------/
  //--TODO-- à supprimer --TODO--/
  (void)nouvelle_voie_verte;
  //-----------------------------/
}

const string nom_voie[Carrefour::nb_voies]={"PRINCIPALE","SECONDAIRE"};

void Carrefour::afficherMessageCommutation(unsigned int voie, string message)
{
  lock_guard<mutex> verrou(mutex_affichage);
  cout << nom_voie[voie] << message << endl;
}

void Carrefour::afficherMessageAuto(unsigned int voie, unsigned long numero, string message)
{
  lock_guard<mutex> verrou(mutex_affichage);
  cout << nom_voie[voie] << " " << numero << message << endl;
}
