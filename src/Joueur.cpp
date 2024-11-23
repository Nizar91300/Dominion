#include "Joueur.h"

#include "DeckManager.h"
#include "Cuivre.h"
#include "Domaine.h"

Joueur::Joueur(Modele* modele){
    m_modele = modele;
    m_deckManager = new DeckManager();

    // initialiser le deck du joueur
    initDeck();
}


Joueur::Joueur(Modele* modele,DeckManager* deckManager){
    m_modele = modele;
    m_deckManager = deckManager;
}

Joueur::~Joueur(){
    delete m_deckManager;
}

// initialiser le deck du joueur
void Joueur::initDeck(){
    // nb cartes initiales
    const int NB_CARTES_CUIVRE = 7;
    const int NB_CARTES_DOMAINE = 3;

    // ajout des 7 cartes cuivre
    for(int i = 0; i < NB_CARTES_CUIVRE; i++){
        Cuivre* cuivre = new Cuivre(m_modele);

        m_deckManager->addCardToPioche( cuivre );
    }

    // ajout des 3 cartes domaine
    for(int i = 0; i <NB_CARTES_DOMAINE; i++ ){
        Domaine* domaine = new Domaine(m_modele);

        m_deckManager->addCardToPioche( domaine );
    }

    // melanger la pioche
    m_deckManager->melangerPioche();

    // piocher 5 cartes
    m_deckManager->piocher(5);
}
