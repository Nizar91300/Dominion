#include "Festin.h"
#include "../../Modele.h"

const int Festin::COUT_ACHAT = 4;

void Festin::faireAction(){
    m_modele->showRecevoirCarte(5);
    m_modele->ecarterCarteJouee(this);
}