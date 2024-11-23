#ifndef DECKMANAGER_H
#define DECKMANAGER_H

#include <vector>
#include <string>
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
        std::vector<Carte*> m_cartesEnAttente ; // cartes mises de cote, jusqu’à ce que les instructions indiquent ou les mettre
        std::vector<Carte*> m_cartesjouees; // cartes jouees pendant le tour

    public:
        DeckManager();
        DeckManager(std::vector<Carte*> m_pioche,std::vector<Carte*> m_defausse,std::vector<Carte*> m_main,std::vector<Carte*> m_cartesEnAttente, std::vector<Carte*> m_cartesjouees)
          :m_pioche(m_pioche),m_defausse(m_defausse),m_main(m_main),m_cartesEnAttente(m_cartesEnAttente),m_cartesjouees(m_cartesjouees) {}

        ~DeckManager();

        // getters
        const std::vector<Carte*> getPioche();
        const std::vector<Carte*> getDefausse();
        const std::vector<Carte*> getMain();
        const std::vector<Carte*> getCartesJouees();

        bool mainContientDouve(); // verifie si la main contient une douve

        void addCardToPioche(Carte* carte);
        void addCardToMain(Carte* carte);   // ajouter une carte a la main
        void addCardToDefausse(Carte* carte);   // ajouter une carte a la defausse
        void addCardPiocheToEnAttente();   // pioche une carte et la met dans les cartes en attente
        void addCardMainToJouees(Carte* carte);   // met la carte de la main en parametre dans les cartes jouees
        std::vector<Carte*> getAllCards();   // retourne toutes les cartes du deck


        void melangerPioche();          // melanger la pioche
        void piocher(int n);            // piocher n cartes, les met dans la main
        Carte* prendreCartePioche();    // retourne la carte du haut de la pioche en la retirant de la pioche
        void defausser(Carte* carte);   // defausser une carte
        void ecarterCarteJouee(Carte* carte);     // ecarter une carte de la liste des cartes jouees
        void ecarterCarteMain(Carte* carte);      // ecarter une carte de la main

        void ajusterDeck(); // ajuster le deck du joueur apres son tour
        int pointsVictoire(); // calculer les points de victoire du joueur

        std::string toString();
};

#endif
