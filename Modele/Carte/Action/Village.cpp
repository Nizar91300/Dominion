#include "Village.h"

const int Village::COUT_ACHAT = 3;

void Village::faireAction(){
    m_modele->piocher(1);
    m_modele->ajouterNbActions(2);
}