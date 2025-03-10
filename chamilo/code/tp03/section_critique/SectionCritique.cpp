#include <iostream>
#include <iomanip>

#include "SectionCritique.hpp"

/*-------------------------------------------------------------------------------
 * Macro pour éviter les warnings "unused ..." dans une version intermédiaire.
 * A enlever lorsqu'elle n'est plus utilisée.
 * -----------------------------------------------------------------------------*/
#define UNUSED(x) (void)(x)

using namespace std;

SectionCritique::SectionCritique(const unsigned long nb_libre_) :
  nb_libre(nb_libre_)
{}

SectionCritique::~SectionCritique()
{}

//--TODO-- à compléter --TODO--/
void SectionCritique::entrer(void)
{
  UNUSED(nb_libre);
}

void SectionCritique::sortir(void)
{}

//-----------------------------/
