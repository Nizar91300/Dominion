#ifndef DECKMANAGER_H
#define DECKMANAGER_H

#include <vector>
#include <algorithm> 
#include <random> 
#include <iostream>

class Carte;

class Modele;

class DeckManager {
    private:
        std::vector<Carte*> m_pioche;
        std::vector<Carte*> m_defausse;
        std::vector<Carte*> m_main;

    public:
        DeckManager();

        ~DeckManager();

        // getters
        const std::vector<Carte*> getPioche();
        const std::vector<Carte*> getDefausse();
        const std::vector<Carte*> getMain();

        void addCardToPioche(Carte* carte);

        // melanger la pioche
        void melangerPioche();

        // piocher n cartes
        void piocher(int n);
};

#endif