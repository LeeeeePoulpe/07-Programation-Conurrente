#include <iostream>
#include <thread>
#include <chrono>
#include "Chercheur.hpp"
#include "ImagePPM.hpp"
#include <limits.h>

using namespace std;

Chercheur::Chercheur(t_image &subImg, t_image &queryImg, SearchImageData &data)
    : subImage(subImg), query(queryImg), result(data) {}

void Chercheur::operator()()
{
  int best_x = 0, best_y = 0;
  int best_match = INT_MAX;

  // Loop through each possible position in the sub-image
  for (int y = 0; y <= subImage.height - query.height; y++) {
    for (int x = 0; x <= subImage.width - query.width; x++) {
      int current_match = 0;

      // Compare each pixel of the query image with the corresponding pixels in the sub-image
      for (int qy = 0; qy < query.height; qy++) {
        for (int qx = 0; qx < query.width; qx++) {
          // Calculate pixel differences for each color channel
          t_pixel subPixel = pixel_at(subImage, x + qx, y + qy);
          t_pixel queryPixel = pixel_at(query, qx, qy);
          current_match += diff_pixel(subPixel, queryPixel);
        }
      }

      // Update best match if current position has a better match
      if (current_match < best_match) {
        best_match = current_match;
        best_x = x;
        best_y = y;
      }
    }
  }

  result.match = best_match;
  result.x = best_x;
  result.y = best_y;
}
