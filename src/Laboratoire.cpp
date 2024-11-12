#include "Laboratoire.h"
#include "Modele.h"

const int Laboratoire::COUT_ACHAT = 5;

void Laboratoire::faireAction(){
    m_modele->piocher(2);
    m_modele->ajouterNbActions(1);
}