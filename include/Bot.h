#ifndef BOT_H
#define BOT_H

#include "Joueur.h"

class Modele;
class Carte;

class Bot : public Joueur {

public:
    Bot(Modele* modele) : Joueur(modele){}

    void playActionPhase(); // Gere la phase d'action
    void playBuyPhase(); // Gere la phase d'achat

    Carte* findBestActionCard(); // Trouve la meilleure carte d'action a jouer
    Carte* findBestBuyCard(int coutMax); // Trouve la carte avec le cout le + eleve a acheter selon coutMax

    bool isBot() override{ return true; }

    void playAllTreasures(); // Joue tous les tresors possibles
};

#endif // BOT_H
