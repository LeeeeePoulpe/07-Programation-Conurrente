#include <iostream>
#include <thread>
#include <chrono>
#include "Chercheur.hpp"
#include "ImagePPM.hpp"
#include <limits.h>

using namespace std;

// Constructeur: Initialise le chercheur avec une sous-image, une image de référence et une structure pour stocker les résultats
Chercheur::Chercheur(t_image &subImg, t_image &queryImg, SearchImageData &data)
    : subImage(subImg), query(queryImg), result(data) {}

void Chercheur::operator()()
{
  // Variables pour stocker la meilleure position trouvée et la différence minimale
  int best_x = 0, best_y = 0;
  int best_match = INT_MAX;

  // Parcours de chaque position possible dans la sous-image
  for (int y = 0; y <= subImage.height - query.height; y++) {
    for (int x = 0; x <= subImage.width - query.width; x++) {
      // Compteur pour la différence totale à la position actuelle
      int current_match = 0;

      // Compare chaque pixel de l'image de référence avec les pixels correspondants dans la sous-image
      for (int qy = 0; qy < query.height; qy++) {
        for (int qx = 0; qx < query.width; qx++) {
          // Calcule la différence entre les pixels pour chaque canal de couleur
          t_pixel subPixel = pixel_at(subImage, x + qx, y + qy);
          t_pixel queryPixel = pixel_at(query, qx, qy);
          current_match += diff_pixel(subPixel, queryPixel);
        }
      }

      // Met à jour la meilleure correspondance si la position actuelle a une différence plus faible
      if (current_match < best_match) {
        best_match = current_match;
        best_x = x;
        best_y = y;
      }
    }
  }

  // Stocke les résultats de la recherche
  result.match = best_match;
  result.x = best_x;
  result.y = best_y;
}
