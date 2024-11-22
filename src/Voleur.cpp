#include "Voleur.h"
#include "Modele.h"

const int Voleur::COUT_ACHAT = 5;

void Voleur::faireAction(){
    m_modele->actionVoleur();
}