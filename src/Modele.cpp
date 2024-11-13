#include "Modele.h"

#include <iostream>
#include "Joueur.h"
#include "DeckManager.h"

#include "Cuivre.h"
#include "Argent.h"
#include "Or.h"
#include "Malediction.h"
#include "Domaine.h"
#include "Duche.h"
#include "Province.h"
#include "Jardin.h"
#include "Atelier.h"
#include "Bucheron.h"
#include "Douve.h"
#include "Chapelle.h"
#include "Laboratoire.h"
#include "Sorciere.h"
#include "Village.h"
#include "Voleur.h"
#include "Festin.h"


// constructeur
Modele::Modele(){
    // initialiser les attributs
    m_joueurs = std::vector<Joueur*>();
    m_reserve = std::vector< std::pair< Carte*, int > >();

    // initialiser la partie avec 2 joueurs par defaut
    initNewGame(2);
}

// destructeur
Modele::~Modele(){
    // liberer la memoire des joueurs
    for(unsigned int i = 0; i < m_joueurs.size(); i++){
        delete m_joueurs[i];
    }

    // liberer la memoire de la reserve
    for(unsigned int i = 0; i < m_reserve.size(); i++){
        delete m_reserve[i].first;
    }
}

//initialiser une nouvelle partie
void Modele::initNewGame(int nbJoueurs){
    // initialiser les joueurs
    m_nbJoueurs = nbJoueurs;
    initJoueurs();

    // initialiser le tour
    initNewTour();

    // initialiser la reserve
    initReserve();
}

// initialiser les joueurs
void Modele::initJoueurs(){
    // creer les joueurs
    for(int i = 0; i < m_nbJoueurs; i++){
        m_joueurs.push_back(new Joueur(this));
    }

    // joueur actif
    m_indexJoueurActif = 1;
    m_joueurActif = m_joueurs[m_indexJoueurActif];
}

// initialiser la reserve
void Modele::initReserve(){

    // CARTES TRESOR
    const int NB_CARTES_CUIVRE = 60 - 7 * m_nbJoueurs;      // depend du nombre de joueurs
    ajouterCarte(new Cuivre(this), NB_CARTES_CUIVRE);
    ajouterCarte(new Argent(this), 40);
    ajouterCarte(new Or(this), 30);
    ajouterCarte(new Malediction(this), 30);

    // CARTES VICTOIRE
    int nbCartesVictoire = (m_nbJoueurs > 2) ? 12 : 8;
    ajouterCarte(new Domaine(this), nbCartesVictoire);
    ajouterCarte(new Duche(this), nbCartesVictoire);
    ajouterCarte(new Province(this), nbCartesVictoire);

    // CARTES ROYAUME
    struct CarteInfo {
        Carte* carte;
        int quantite;
    };

    std::vector<CarteInfo> cartesRoyaume = {
        {new Jardin(this), 12},
        {new Atelier(this), 10},
        {new Bucheron(this), 10},
        {new Douve(this), 10},
        {new Chapelle(this), 10},
        {new Laboratoire(this), 10},
        {new Sorciere(this), 10},
        {new Village(this), 10},
        {new Voleur(this), 10},
        {new Festin(this), 10}
    };

    for (const auto& carteInfo : cartesRoyaume) {
        ajouterCarte(carteInfo.carte, carteInfo.quantite);
    }
}

// initialise le nouveau tour du joueur
void Modele::initNewTour(){
    // ajuste le deck de l'ancien joueur actif
    m_joueurActif->getDeckManager()->ajusterDeck();

    // changer le joueur actif
    m_indexJoueurActif = (m_indexJoueurActif + 1) % m_nbJoueurs;
    m_joueurActif = m_joueurs[m_indexJoueurActif];

    // reinitialiser les actions et les achats
    m_nbActions = 1;
    m_nbAchats = 1;

    // reinitialiser les pieces
    m_nbPieces = 0;
}



// retourne la reserve
std::vector< std::pair< Carte*, int > > Modele::getReserve(){
    return m_reserve;
}

// retourne la main du joueur actif
std::vector<Carte*> Modele::getMain(){
    return m_joueurActif->getDeckManager()->getMain();
}

// setter de la vue
void Modele::setView(MyFrame* mf){
    m_view = mf;
}



// ajouter une carte a la reserve
void Modele::ajouterCarte(Carte* carte, int nbCartes){
    m_reserve.push_back( std::make_pair(carte, nbCartes) );
}

// ajouter des actions
void Modele::ajouterNbActions(int nb){
    m_nbActions += nb;
}

// ajouter des pieces
void Modele::ajouterNbPieces(int nb){
    m_nbPieces += nb;
}

// ajouter des achats
void Modele::ajouterNbAchats(int nb){
    m_nbAchats += nb;
}

// piocher nb cartes
void Modele::piocher(int nb){
    m_joueurActif->getDeckManager()->piocher(nb);
}

// defausser une carte
void Modele::defausser(Carte* carte){
    m_joueurActif->getDeckManager()->defausser(carte);
}

// ecarter une carte de la main ou de la defausse ou de la pioche
void Modele::ecarterCarteJouee(Carte* carte){
    m_joueurActif->getDeckManager()->ecarterCarteJouee(carte);
}

// recevoir une carte dans la main
void Modele::recevoirCarteMain(Carte* carte){
    m_joueurActif->getDeckManager()->addCardToMain(carte);
}

// recevoir une carte dans la defausse
void Modele::recevoirCarteDefausse(Carte* carte){
    m_joueurActif->getDeckManager()->addCardToDefausse(carte);
}

// jouer une carte action
void Modele::jouerCarteAction(Carte* carte){
    // verifier si le joueur a assez d'actions
    if(m_nbActions == 0)
        return;

    // verifier si la carte est de type action
    if( carte->getType() == TypeCarte::ACTION ){
        Action* action = static_cast<Action*>(carte);

        // jouer la carte
        action->faireAction();  
        
        // decrementer le nombre d'actions
        m_nbActions--;

        // ajouter la carte a la liste des cartes jouees
        m_joueurActif->getDeckManager()->addCardMainToJouees(carte);
    }
}

// jouer une carte tresor
void Modele::jouerCarteTresor(Carte* carte){
    // verifier si la carte est de type tresor
    if( carte->getType() == TypeCarte::TRESOR ){
        Tresor* tresor = static_cast<Tresor*>(carte);

        // ajoute les pieces
        m_nbPieces += tresor->getValeur();

        // ajouter la carte a la liste des cartes jouees
        m_joueurActif->getDeckManager()->addCardMainToJouees(carte);
    }
}

// acheter une carte
void Modele::acheterCarteAvecVerif(Carte* carte){

    // si on a achete une carte grace a une carte action on ne s'occupe pas de toucher aux attributs du joueur
    if(m_achatSuiteAction){
        if(carte->getCout() > m_coutMax){
            return;
        }
        m_achatSuiteAction = false;     // sinon on peut acheter la carte
        acheterCarte(carte);            // achat
        return;
    }

    // verifier si le joueur a assez de pieces
    if(m_nbPieces < carte->getCout())
        return;

    // verifier si le joueur a assez d'achats et acheter la carte
    bool achetee = acheterCarte(carte);

    if(achetee){
        // decremente le nombre d'achats
        m_nbAchats--;

        // decremente le nombre de pieces
        m_nbPieces -= carte->getCout();

        // si le nombre d'achats est nul, fin du tour
        if(m_nbAchats == 0){
            initNewTour();
        }
    }
    
}

// acheter une carte sans verification, return vrai si la carte a ete achetee, faux sinon
bool Modele::acheterCarte(Carte* carte){
    // verifier si la carte est disponible
    for(unsigned int i = 0; i < m_reserve.size(); i++){
        if(m_reserve[i].first == carte && m_reserve[i].second > 0){
            // decremente le nombre de cartes disponibles
            m_reserve[i].second--;

            // ajoute une copie de la carte a la defausse du joueur
            m_joueurActif->getDeckManager()->addCardToDefausse( new Carte(carte) );

            return true;
        }
    }
    return false;
}

// donner une malediction a chaque joueur sauf au joueur actif
void Modele::donnerMalediction(){
    std::pair<Carte*, int> malediction = {nullptr, 0};
    // chercher le pointeur de la carte malediction
    for(unsigned int i = 0; i < m_reserve.size(); i++){
        if( (m_reserve[i].first)->getNom() == "curse" ){
            malediction = m_reserve[i];
            break;
        }
    }

    // si on ne trouve pas la carte on arrete
    if(malediction.first == nullptr){
        return;
    }

    // donner une malediction a chaque joueur sauf au joueur actif
    for(unsigned int i = 0; i < m_joueurs.size(); i++){
        if(m_joueurs[i] != m_joueurActif){
            if( malediction.second > 0){
                // decremente le nombre de cartes disponibles
                malediction.second--;

                // ajoute une copie de la carte a la defausse du joueur
                m_joueurs[i]->getDeckManager()->addCardToDefausse( new Carte(malediction.first) );
            }
        }
    }
}



// recevoir une carte avec un cout inferieur ou egal a coutMax suite a une carte action
void Modele::showRecevoirCarte(int coutMax){
    m_coutMax = coutMax;
    // view.showAchatSuiteAction(coutMax);
    m_achatSuiteAction = true;
}

// ecarter au maximum nbCartes cartes
void Modele::showEcarterCartes(int nbCartesMax){
    // view.showEcarterCartes(nbCartesMax);
    nbCartesMax += 0;
}



// verifier la fin de la partie, vrai si la partie est finie, faux sinon
bool Modele::finPartie(){
    // fin de partie si 3 piles de cartes royaume sont vides ou si la pile de province est vide
    int nbPilesVides = 0;
    for(unsigned int i = 0; i < m_reserve.size(); i++){
        if(m_reserve[i].second == 0){
            if( (m_reserve[i].first)->getNom() == "province" ){
                return true;
            }
            nbPilesVides++;
        }
    }

    return nbPilesVides >= 3;
}
