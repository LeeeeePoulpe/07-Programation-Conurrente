#include "VoieVille.hpp"

using namespace std;

unsigned long VoieVille::compteur = 0;

// Le nom des villes est défini par un caractère ASCII à partir de 'A'
VoieVille::VoieVille():
  nom(static_cast<char>('A'+compteur++))
{}
