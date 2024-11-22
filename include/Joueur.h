#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>

class Modele;
class DeckManager;

class Joueur{
    protected:
        Modele* m_modele;
        DeckManager* m_deckManager;

    public:
        Joueur(Modele*);
        virtual ~Joueur();

        void initDeck();    // initialiser le deck du joueur
        DeckManager* getDeckManager() { return m_deckManager; }
        virtual bool isBot() { return false; }

};

#endif