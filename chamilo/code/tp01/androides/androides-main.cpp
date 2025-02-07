#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <thread>

#include "Ecran.hpp"
#include "Androide.hpp"

/*-------------------------------------------------------------------------------
 * Macro pour éviter les warnings "unused ..." dans une version intermédiaire.
 * A enlever lorsqu'elle n'est plus utilisée.
 * -----------------------------------------------------------------------------*/
#define UNUSED(x) (void)(x)

using namespace std;

int main(int argc, char *argv[])
{
    const unsigned long nb_latences = 2;

    if (argc != 2)
    {
        cerr << "Usage : " << argv[0] << " nb_threads" << endl;
        exit(EXIT_FAILURE);
    }

    const unsigned long nb_threads = stoul(argv[1]);

    Ecran ecran;

    // initialisation des latences
    unsigned long latences[nb_latences];
    default_random_engine gen;
    uniform_int_distribution<unsigned long> dis(1, 5);
    latences[0] = dis(gen);
    for (unsigned long i = 1; i < nb_latences; i++)
        latences[i] = 3 + latences[i - 1];

    // création des threads
    vector<thread> mes_threads;

    for (unsigned long i = 0; i < nb_threads; i++)
    {
        mes_threads.push_back(thread(Androide(i, latences[i % nb_latences], ecran)));
    }
    UNUSED(nb_threads);

    // accélération des explorations après un moment
    this_thread::sleep_for(chrono::seconds(2));
    ecran.affiche_chaine("Accélération!!", 10, Androide::COTE_ESPACE + 10);
    for (unsigned long i = 0; i < nb_latences; i++)
        latences[i] /= 3;

    // attente des threads
    for (unsigned long i = 0; i < nb_threads; i++)
    {
        mes_threads[i].join();
    }

    // Le programme se termine
    return EXIT_SUCCESS;
}
