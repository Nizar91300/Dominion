#include "Joueur.h"

#include "DeckManager.h"
#include "../Carte/Tresor/Cuivre.h"
#include "../Carte/Victoire/Domaine.h"

Joueur::Joueur(Modele* modele){
    m_modele = modele;
    m_deckManager = new DeckManager();

    // initialiser le deck du joueur
    initDeck();
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

    // afficher les cartes de la main
    std::vector<Carte*> main = m_deckManager->getMain();
    for(Carte* carte : main){
        std::cout << typeid((*carte)).name() << std::endl;
    }

    // afficher les cartes de la pioche
    std::vector<Carte*> pioche = m_deckManager->getPioche();
    for(Carte* carte : pioche){
        std::cout << typeid((*carte)).name() << std::endl;
    }
}