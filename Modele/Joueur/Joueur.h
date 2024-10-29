#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>

class Modele;
class DeckManager;

class Joueur{
    private:
        Modele* m_modele;
        DeckManager* m_deckManager;

    public:
        Joueur(Modele*);
        ~Joueur();

        void initDeck();    // initialiser le deck du joueur

};

#endif