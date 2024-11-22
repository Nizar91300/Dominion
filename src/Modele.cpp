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
#include "Bot.h"

#include "myframe.hpp"
#include "resources.hpp"


// constructeur
Modele::Modele(){
    // initialiser les attributs
    m_joueurs = std::vector<Joueur*>();
    m_reserve = std::vector< std::pair< Carte*, int > >();

    // initialiser le nombre de joueur avec 2 joueurs par defaut
    m_nbJoueurs = 2;
}

// destructeur
Modele::~Modele(){
    // liberer la memoire des joueurs
    for(size_t i = 0; i < m_joueurs.size(); i++){
        delete m_joueurs[i];
    }

    // liberer la memoire de la reserve
    for(size_t i = 0; i < m_reserve.size(); i++){
        delete m_reserve[i].first;
    }
}

//initialiser une nouvelle partie
void Modele::initNewGame(){
    Resources::getInstance()->getSettings(m_nbJoueurs, m_nbHumans, m_sound, m_chosenCards);

    // initialiser les joueurs
    m_tourAction = true;

    // effacer les anciens joueurs
    if(m_joueurs.size() > 0){
        for(size_t i = 0; i < m_joueurs.size(); i++){
            delete m_joueurs[i];
        }
    }

    if (m_reserve.size() > 0) {
        for(size_t i = 0; i < m_reserve.size(); i++){
            delete m_reserve[i].first;
        }
    }

    m_joueurs.clear();
    m_reserve.clear();



    m_achatSuiteAction = false;
    m_isTrashAction = false;
    m_nbCartesEcarter = 0;

    initJoueurs();

    // initialiser les actions et les achats
    m_nbActions = 1;
    m_nbAchats = 1;

    // initialiser les pieces
    m_nbPieces = 0;

    // initialiser la reserve
    initReserve();
}

// initialiser les joueurs
void Modele::initJoueurs(){
    // creer les joueurs
    for(int i = 0; i < m_nbJoueurs; i++){
        if(i < m_nbHumans){
            m_joueurs.push_back(new Joueur(this));
        }
        else{
            m_joueurs.push_back(new Bot(this));
        }
    }

    // joueur actif
    m_indexJoueurActif = 0;
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
    ajouterCarte(new Domaine(this), 24);
    ajouterCarte(new Duche(this), 12);
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

    // si chaque joueur a jouer son tour
    if( !m_tourAction && m_indexJoueurActif == m_joueurs.size() - 1){
        // on peut maintenant verifier la fin de la partie
        if(finPartie()){
            // afficher la fin de la partie
            endGame();
            return;
        }
    }

    // changer le joueur actif
    m_indexJoueurActif = (m_indexJoueurActif + 1) % m_nbJoueurs;
    m_joueurActif = m_joueurs[m_indexJoueurActif];

    // reinitialiser les actions et les achats
    m_nbActions = 1;
    m_nbAchats = 1;

    // reinitialiser les pieces
    m_nbPieces = 0;

}


bool Modele::getTourAction(){
    return m_tourAction;
}

// retourne le nombre d'actions restantes
int Modele::getNbActions(){
    return m_nbActions;
}

// get le nombres de joueurs
int Modele::getNbJoueurs() const{
    return m_nbJoueurs;
}

// retourne le nombre de pieces restantes
int Modele::getNbPieces(){
    return m_nbPieces;
}

// retourne le nombre d'achats restants
int Modele::getNbAchat(){
    return m_nbAchats;
}

// retourne vrai si le joueur est en phase d'achat suite a une carte action
bool Modele::getAchatSuiteAction(){
    return m_achatSuiteAction;
}

// retourne vrai si le joueur est en train d'utiliser une carte qui permet d'ecarter des cartes
bool Modele::getIsTrashAction(){
    return m_isTrashAction;
}

//retourne le cout maximal de la carte a recevoir suite a une carte action
int Modele::getCoutMax(){
    return m_coutMax;
}

// retourne le nombre maximal de cartes a ecarter
int Modele::getNbMaxEcarter(){
    return m_nbMaxEcarter;
}

// retourne le nombre d'humains
int Modele::getNbHumans(){
    return m_nbHumans;
}

// retourne la reserve
std::vector< std::pair< Carte*, int > > Modele::getReserve(){
    return m_reserve;
}

// retourne la main du joueur actif en tant que vecteur de paires de cartes et de quantites
std::vector< std::pair< Carte*, int > >Modele::getMain(){
    auto main = m_joueurActif->getDeckManager()->getMain();

    return convertVecCarteToVecPair(main);
}

// retourne les cartes jouees par le joueur actif
std::vector< std::pair< Carte*, int > > Modele::getPlayedCards(){
    auto cartesJouees = m_joueurActif->getDeckManager()->getCartesJouees();

    return convertVecCarteToVecPair(cartesJouees);
}

// retourne la defausse
std::vector< Carte* > Modele::getDefausse(){
    return m_joueurActif->getDeckManager()->getDefausse();
}

// convertit un vecteur de cartes en vecteur de paires de cartes et de quantites
std::vector<std::pair<Carte*, int >> Modele::convertVecCarteToVecPair(std::vector<Carte*> vec){
    std::vector<std::pair<Carte*, int >> res = std::vector<std::pair<Carte*, int >>();

    // compter les cartes
    for(Carte* carte : vec){
        auto it = std::find_if(res.begin(), res.end(),
            [&carte](const std::pair<Carte*, int>& element) {
                return element.first->getNom() == carte->getNom();
            });

        if ( it != res.end() ){
            it->second++;
        }
        else{
            res.push_back( std::make_pair(carte, 1) );
        }
    }

    // trier les cartes par type puis par nom
    std::sort(res.begin(), res.end(),
        [](const std::pair<Carte*, int>& a, const std::pair<Carte*, int>& b) {
            if (a.first->getType() != b.first->getType()) {
                return a.first->getType() < b.first->getType(); // Trier par type
            }
            return a.first->getNom() < b.first->getNom(); // Puis par nom
        });

    return res;
}


// setter de la vue
void Modele::setView(MyFrame* mf){
    m_view = mf;
}

// rafrachir l'affichage et mettre en pause le thread
void Modele::refreshAndPauseView(int ms){
    m_view->updateAndPause(ms);
}

// passer a la phase suivante
void Modele::endPhase(){
    // si le joueur est en phase d'action
    if(m_tourAction){
        // passer a la phase d'achat
        m_tourAction = false;

        m_achatSuiteAction = false;
        m_isTrashAction = false;
        m_nbCartesEcarter = 0;
    }
    // si le joueur est en phase d'achat
    else {
        // fin du tour
        initNewTour();

        m_tourAction = true;

        // si c'est un bot on joue son tour
        if(m_joueurActif->isBot()){
            // jouer le tour du bot
            Bot* bot = static_cast<Bot*>(m_joueurActif);
            bot->playActionPhase();
            endPhase();
            bot->playBuyPhase();
            endPhase();
        }
    }
    m_view->updateCurrentPanel();        // refresh l'affichage
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




// jouer une carte action ou tresor
void Modele::jouerCarte(Carte* carte){
    // si le joueur est en phase d'action
    if(m_tourAction){
        // ecarte les cartes si on est en train d'utiliser une carte qui permet d'ecarter des cartes
        if(m_isTrashAction){
            m_nbCartesEcarter--;
            if(m_nbCartesEcarter == 0){
                m_isTrashAction = false;
            }
            m_joueurActif->getDeckManager()->ecarterCarteMain(carte);
            m_view->updateCurrentPanel();        // refresh l'affichage
            return;
        }

        // verifier si le joueur a assez d'actions
        if(m_nbActions == 0)
            return;

        // verifier si la carte est de type action
        if( carte->getType() == TypeCarte::ACTION ){
            Action* action = static_cast<Action*>(carte);

            // ajouter la carte a la liste des cartes jouees
            m_joueurActif->getDeckManager()->addCardMainToJouees(carte);

            // jouer la carte
            action->faireAction();

            // decrementer le nombre d'actions
            m_nbActions--;

            // si la carte est feast on n'update pas la vue
            if(carte->getNom() == "feast")
                return;

            m_view->updateCurrentPanel();        // refresh l'affichage
        }
    }
    // si le joueur est en phase d'achat
    else {
        // verifier si la carte est de type tresor
        if( carte->getType() == TypeCarte::TRESOR ){
            Tresor* tresor = static_cast<Tresor*>(carte);

            // ajoute les pieces
            m_nbPieces += tresor->getValeur();

            // ajouter la carte a la liste des cartes jouees
            m_joueurActif->getDeckManager()->addCardMainToJouees(carte);

            m_view->updateCurrentPanel();        // refresh l'affichage
        }
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

        m_view->updateCurrentPanel(); // mettre a jour l'affichage
        return;
    }

    // si le joueur est en phase d'action on ne peut pas acheter de carte
    if(m_tourAction){
        return;
    }

    // verifier si le joueur a assez d'achats
    if(m_nbAchats == 0){
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

    }

    m_view->updateCurrentPanel();   // mettre a jour l'affichage

}

// acheter une carte sans verification, return vrai si la carte a ete achetee, faux sinon
bool Modele::acheterCarte(Carte* carte){
    // verifier si la carte est disponible
    for(unsigned int i = 0; i < m_reserve.size(); i++){
        if(m_reserve[i].first == carte && m_reserve[i].second > 0){
            // decremente le nombre de cartes disponibles
            m_reserve[i].second--;

            // ajoute une copie de la carte a la defausse du joueur
            m_joueurActif->getDeckManager()->addCardToDefausse( carte->clone() );

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
            // si le joueur a une douve on ne peut pas l'attaquer
            if( m_joueurs[i]->getDeckManager()->mainContientDouve() ){
                return;
            }

            if( malediction.second > 0){
                // decremente le nombre de cartes disponibles
                malediction.second--;

                // ajoute une copie de la carte a la defausse du joueur
                m_joueurs[i]->getDeckManager()->addCardToDefausse( malediction.first->clone() );
            }
        }
    }
}



// recevoir une carte avec un cout inferieur ou egal a coutMax suite a une carte action
void Modele::recevoirCarte(Carte* carte, int coutMax){
    m_coutMax = coutMax;
    m_achatSuiteAction = true;

    m_view->updateCurrentPanel();  
    
    if( carte->getNom() == "feast"){
        if(isBotPlaying()){
            refreshAndPauseView(400);
        }
        m_joueurActif->getDeckManager()->ecarterCarteJouee(carte);  // ecarter la carte feast
    }
}

// ecarter au maximum nbCartes cartes
void Modele::ecarterCartes(int nbCartesMax){
    m_isTrashAction = true;
    m_nbCartesEcarter = nbCartesMax;
    m_nbMaxEcarter = nbCartesMax;
}

void Modele::actionVoleur(){
    // rajouter 1 or a la defausse du joueur actif
    m_joueurActif->getDeckManager()->addCardToDefausse(new Or(this));


    // recuperer les cartes de la main des autres joueurs
    std::vector< std::vector <Carte*>  > cartesAutresJoueurs = std::vector< std::vector <Carte*> >();
    std::vector<int> indJoueurs = std::vector<int>();

    for(unsigned int i = 0; i < m_joueurs.size(); i++){
        if(m_joueurs[i] == m_joueurActif)
            continue;

        // si le joueur a une douve on ne peut pas l'attaquer
        if( m_joueurs[i]->getDeckManager()->mainContientDouve() ){
            return;
        }


        std::vector<Carte*> cartes = std::vector<Carte*>();

        auto c1 = m_joueurs[i]->getDeckManager()->prendreCartePioche();
        auto c2 = m_joueurs[i]->getDeckManager()->prendreCartePioche();

        // on ecarte une carte de type gold ou silver mais on renvoie une copie de la carte pour l'affichage
        if(c1->getNom() == "gold" || c1->getNom() == "silver"){
            auto tmp = c1->clone();
            delete c1;
            c1 = tmp;

            m_joueurs[i]->getDeckManager()->addCardToDefausse(c2);
        }
        else{
            if(c2->getNom() == "gold" || c2->getNom() == "silver"){
                auto tmp = c2->clone();
                delete c2;
                c2 = tmp;

                m_joueurs[i]->getDeckManager()->addCardToDefausse(c1);
            }
            else{
                m_joueurs[i]->getDeckManager()->addCardToDefausse(c1);
                m_joueurs[i]->getDeckManager()->addCardToDefausse(c2);
            }
        }

        cartes.push_back(c1);
        cartes.push_back(c2);

        cartesAutresJoueurs.push_back(cartes);
        indJoueurs.push_back(i);
    }
    m_view->showVoleur(cartesAutresJoueurs, indJoueurs);
}

// true si le joueur actif est un bot, false sinon
bool Modele::isBotPlaying(){
    return m_joueurActif->isBot();
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


// afficher la fin de la partie
void Modele::endGame(){
    // calculer les points de victoire de chaque joueur
    std::vector<int> points = std::vector<int>();
    for(unsigned int i = 0; i < m_joueurs.size(); i++){
        points.push_back( m_joueurs[i]->getDeckManager()->pointsVictoire() );
    }

    // afficher le gagnant
    m_view->showEndGame(points);
}

int Modele::getJoueurActif(){
  return m_indexJoueurActif;
}
