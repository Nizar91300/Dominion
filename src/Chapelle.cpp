#include "Chapelle.h"
#include "Modele.h"

const int Chapelle::COUT_ACHAT = 2;

void Chapelle::faireAction(){
    m_modele->showEcarterCartes(4);
}