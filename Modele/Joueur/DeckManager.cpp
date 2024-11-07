#include "DeckManager.h"

#include "../Carte/Carte.h"
#include "../Carte/Tresor/Tresor.h"

DeckManager::DeckManager(){
    m_pioche = std::vector<Carte*>(); 
    m_defausse = std::vector<Carte*>(); 
    m_main = std::vector<Carte*>();
    m_cartesEnAttente = std::vector<Carte*>();
    m_cartesjouees = std::vector<Carte*>();
}

DeckManager::~DeckManager(){
    // Supprime toutes les cartes
    for (Carte* carte : m_pioche) {
        delete carte;
    }
    for (Carte* carte : m_defausse) {
        delete carte;
    }
    for (Carte* carte : m_main) {
        delete carte;
    }
    for (Carte* carte : m_cartesEnAttente) {
        delete carte;
    }
    for (Carte* carte : m_cartesjouees) {
        delete carte;
    }
}

// GETTERS
const std::vector<Carte*> DeckManager::getPioche() {
    return m_pioche;
}
const std::vector<Carte*> DeckManager::getDefausse() {
    return m_defausse;
}
const std::vector<Carte*> DeckManager::getMain() {
    return m_main;
}
const std::vector<Carte*> DeckManager::getCartesEnAttente() {
    return m_cartesEnAttente;
}
const std::vector<Carte*> DeckManager::getCartesJouees() {
    return m_cartesjouees;
}

// ajouter une carte a la pioche
void DeckManager::addCardToPioche(Carte* carte){
    m_pioche.push_back(carte);
}

// ajouter une carte a la main
void DeckManager::addCardToMain(Carte* carte){
    m_main.push_back(carte);
}

// ajouter une carte a la defausse
void DeckManager::addCardToDefausse(Carte* carte){
    m_defausse.push_back(carte);
}

// ajouter une carte aux cartes en attente
void DeckManager::addCardPiocheToEnAttente(){
    Carte* carte = prendreCartePioche();  // on recupere la carte
    m_cartesEnAttente.push_back(carte);    // on ajoute la carte aux cartes en attente
}

// ajouter la carte de la main aux cartes jouees
void DeckManager::addCardMainToJouees(Carte* carte){
    m_cartesjouees.push_back(carte);    // on ajoute la carte aux cartes jouees

    // on retire la carte de la main
    m_main.erase(std::remove(m_main.begin(), m_main.end(), carte), m_main.end());
}

// melanger la pioche
void DeckManager::melangerPioche() {
    std::shuffle(m_pioche.begin(), m_pioche.end(),  std::random_device());
}

// piocher n cartes, les met dans la main
void DeckManager::piocher(int n) {
    for (int i = 0; i < n; i++) {
        Carte* carte = prendreCartePioche();  // on recupere la carte
        m_main.push_back(carte);    // on ajoute la carte a la main
    }
}

// retourne la carte du haut de la pioche en la retirant de la pioche
Carte* DeckManager::prendreCartePioche() {
    if (m_pioche.size() == 0) {
        // remettre la defausse dans la pioche
        m_pioche = m_defausse;

        m_defausse.clear();

        melangerPioche();
    }
    Carte* carte = m_pioche.back();     // on recupere la carte
    m_pioche.pop_back();    // on retire la carte qui a ete piochee
    return carte;
}

// defausser une carte
void DeckManager::defausser(Carte* carte) {
    m_defausse.push_back(carte);    // on defausse la carte

    // on retire la carte de la main
    m_main.erase(std::remove(m_main.begin(), m_main.end(), carte), m_main.end());
}

// ecarter une carte de la liste des cartes jouees
void DeckManager::ecarterCarteJouee(Carte* carte) {
    // on supprime la carte des cartes jouees
    m_cartesjouees.erase(std::remove(m_cartesjouees.begin(), m_cartesjouees.end(), carte), m_cartesjouees.end());

    // on ecrase la carte en memoire
    delete carte;
}

// retirer la carte de sa pile actuelle
void DeckManager::retirerCartePile(Carte* carte) {
    // on trouve ou est la carte et on la retire dans la bonne pile
    std::vector<std::vector<Carte*>*> piles = {&m_main, &m_defausse, &m_pioche, &m_cartesEnAttente};

    for (auto& pile : piles) {
        auto it = std::find(pile->begin(), pile->end(), carte);
        if (it != pile->end()) {
            pile->erase(it);
            return;
        }
    }
}

// ajuster le deck du joueur apres son tour
void DeckManager::ajusterDeck() {
    // on remet les cartes jouees dans la defausse
    for (Carte* carte : m_cartesjouees) {
        m_defausse.push_back(carte);
    }
    m_cartesjouees.clear(); // on vide les cartes jouees

    // on remet les cartes en attente dans la pioche
    for (Carte* carte : m_cartesEnAttente) {
        m_pioche.push_back(carte);
    }
    m_cartesEnAttente.clear(); // on vide les cartes en attente

    // on pioche 5 cartes
    piocher(5);
}