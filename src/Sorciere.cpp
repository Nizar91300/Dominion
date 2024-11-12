#include "Sorciere.h"
#include "Modele.h"

const int Sorciere::COUT_ACHAT = 5;

void Sorciere::faireAction(){
    m_modele->piocher(2);

    m_modele->donnerMalediction();
}