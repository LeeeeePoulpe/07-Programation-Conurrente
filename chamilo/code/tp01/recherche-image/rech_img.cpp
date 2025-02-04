#include <iostream>
#include <sstream>
#include "ImagePPM.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 3) {
          cerr << "Usage : " << argv[0] << " image_source image_requete" << endl;
          exit(EXIT_FAILURE);
	}

	t_image source = read_image(argv[1]);
	t_image query = read_image(argv[2]);

	cout << "Recherche l'image ...." << endl;
	int x = 0;
	int y = 0;
	int match = 0;
	search_image(source,query,x,y,match);
	cout << endl << "Meilleure correspondance : " << match << " en (" << x << "," << y << ")." << endl;

	// Dessine un rectangle rouge à l'emplacement trouvé
	t_pixel red = {255,0,0};
	draw_rect(source,red,x,y,query.width,query.height);

        // Création du fichier résultat contenant votre login dans son nom
        ostringstream oss;
        oss << "/tmp/resultat-" << getenv("LOGNAME") << ".ppm";
	cout << "Résultat dans le fichier '"<< oss.str() << "'." << endl;
	write_image(source, oss.str().c_str());

	delete_image(source);
	delete_image(query);
	return EXIT_SUCCESS;
}
