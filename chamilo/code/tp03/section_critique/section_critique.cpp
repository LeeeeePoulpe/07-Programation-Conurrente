#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

#include "SectionCritique.hpp"
#include "MonThread.hpp"

using namespace std;

unsigned long MonThread::en_cours=0;
std::mutex MonThread::mutex_cout;

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    cerr << "Usage : " << argv[0] << " nb_threads nb_libre" << endl;
    exit(EXIT_FAILURE);
  }

  const unsigned long nb_threads = stoul(argv[1]);
  const unsigned long nb_libre = stoul(argv[2]);

  SectionCritique ma_sc(nb_libre);
  
  // création des threads se donnant nb_rendez_vous
  vector<thread> mes_threads;
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.push_back(thread(MonThread(i,ma_sc)));

  // attente des threads
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.at(i).join();

  return EXIT_SUCCESS;
}
