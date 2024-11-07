#include "Douve.h"
#include "../../../Modele.h"

const int Douve::COUT_ACHAT = 2;

void Douve::defendre(){
    return;
}

void Douve::faireAction(){
    m_modele->piocher(2);
}