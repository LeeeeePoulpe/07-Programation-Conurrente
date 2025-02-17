#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <limits.h>
#include "ImagePPM.hpp"
#include "Chercheur.hpp"
#include "SearchImageData.hpp"

using namespace std;

int main(int argc, char *argv[])
{

        if (argc != 4)
        {
                cerr << "Usage : " << argv[0] << " image_source image_requete nb_threads" << endl;
                exit(EXIT_FAILURE);
        }

        unsigned long const nb_threads = stoul(argv[3]);
        if (nb_threads != 2 && nb_threads != 4 && nb_threads != 8)
        {
                cerr << "nb_threads doit être égal à 2, 4 ou 8" << endl;
                exit(EXIT_FAILURE);
        }

        t_image source = read_image(argv[1]);
        t_image query = read_image(argv[2]);

        t_image *subImg = new t_image[nb_threads];

        // Découpage de l'image en deux ou en quatre
        split_image(source, subImg[0], subImg[1], query.height);

        if (nb_threads >= 4)
        {
                split_image(subImg[0], subImg[0], subImg[2], query.height);
                split_image(subImg[1], subImg[1], subImg[3], query.height);
        }
        if (nb_threads == 8)
        {
                split_image(subImg[0], subImg[0], subImg[4], query.height);
                split_image(subImg[1], subImg[1], subImg[5], query.height);
                split_image(subImg[2], subImg[2], subImg[6], query.height);
                split_image(subImg[3], subImg[3], subImg[7], query.height);
        }

        // Création des objets contenant les résultats des recherches
        vector<SearchImageData> data(nb_threads);

        // Création des threads
        vector<thread> threads;
        for (unsigned long i = 0; i < nb_threads; i++)
        {
                threads.push_back(thread(Chercheur(subImg[i], query, data[i])));
        }

        cout << "Recherche de l'image ..." << endl;
        cout << "Attente des threads ..." << endl;

        // Wait for all threads to complete
        for (auto &t : threads) {
            t.join();
        }

        // Recherche du thread qui a trouvé la meilleure solution
        unsigned long bestThread = nb_threads + 1;
        int bestMatch = INT_MAX;
        for (unsigned long i = 0; i < nb_threads; i++)
        {
                if (data[i].match < bestMatch)
                {
                        bestMatch = data[i].match;
                        bestThread = i;
                }
        }

        if (bestThread == nb_threads + 1)
        {
                cerr << "Erreur : la meilleure correspondance n'a pas été trouvée" << endl;
                delete_image(source);
                delete_image(query);
                delete[] subImg;
                exit(EXIT_FAILURE);
        }

        cout << endl
             << "Meilleure correspondance " << bestMatch << " trouvée par le thread " << bestThread;
        cout << " en (" << data[bestThread].x << "," << data[bestThread].y << ")." << endl;

        // Dessine un rectangle rouge à l'emplacement trouvé relativement à la sous image
        // où la meilleure solution est trouvée
        t_pixel red = {255, 0, 0};
        draw_rect(subImg[bestThread], red, data[bestThread].x, data[bestThread].y, query.width, query.height);

        // Création du fichier résultat contenant votre login dans son nom
        ostringstream oss;
        oss << "/tmp/resultat-" << getenv("LOGNAME") << ".ppm";
        cout << "Résultat dans le fichier '" << oss.str() << "'." << endl;
        write_image(source, oss.str().c_str());

        delete_image(source);
        delete_image(query);
        delete[] subImg;
        return EXIT_SUCCESS;
}
