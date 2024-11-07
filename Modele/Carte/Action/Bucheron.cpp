#include "Bucheron.h"
#include "../../Modele.h"

const int Bucheron::COUT_ACHAT = 3;

void Bucheron::faireAction(){
    m_modele->ajouterNbAchats(1);
    m_modele->ajouterNbPieces(2);
}