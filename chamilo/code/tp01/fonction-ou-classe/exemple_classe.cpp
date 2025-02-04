#include <iostream>
#include <thread>
#include <vector>
#include "MonThread.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "Usage : " << argv[0] << " nb_threads" << endl;
    exit(EXIT_FAILURE);
  }

  const unsigned long nb_threads = stoul(argv[1]);

  // création des threads...
  vector<thread> mes_threads;

  // ...avec une fonction
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.push_back(thread(MonThread(i)));

  // attente des threads
  for (unsigned long i=0; i < nb_threads; i++)
    mes_threads.at(i).join();

  cout << endl;

  return EXIT_SUCCESS;
}
