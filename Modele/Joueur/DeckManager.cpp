#include "DeckManager.h"
#include "../Carte/Carte.h"

DeckManager::DeckManager(){
    m_pioche = std::vector<Carte*>(); 
    m_defausse = std::vector<Carte*>(); 
    m_main = std::vector<Carte*>();
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
}

// getters
const std::vector<Carte*> DeckManager::getPioche() {
    return m_pioche;
}
const std::vector<Carte*> DeckManager::getDefausse() {
    return m_defausse;
}
const std::vector<Carte*> DeckManager::getMain() {
    return m_main;
}

void DeckManager::addCardToPioche(Carte* carte){
    m_pioche.push_back(carte);
}

// melanger la pioche
void DeckManager::melangerPioche() {
    std::shuffle(m_pioche.begin(), m_pioche.end(),  std::random_device());
}

// piocher n cartes
void DeckManager::piocher(int n) {
    for (int i = 0; i < n; i++) {
        if (m_pioche.size() == 0) {
            // remettre la defausse dans la pioche
            m_pioche = m_defausse;

            m_defausse.clear();

            melangerPioche();
        }
        m_main.push_back(m_pioche.back());  // on pioche
        m_pioche.pop_back();    // on retire la carte qui a ete piochee
    }
}