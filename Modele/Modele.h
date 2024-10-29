#ifndef MODELE_H
#define MODELE_H

#include <vector>

class Joueur;

class Carte;

class Modele{
    private:
        // liste des joueurs
        std::vector<Joueur*> m_joueurs;

        // nb joueurs
        int m_nbJoueurs;

        // liste des carte disposees sur la table avec leurs occurences
        std::vector< std::pair< Carte*, int > > m_reserve;

    public:
        Modele(int nbJoueurs);
        ~Modele();

        void initJoueurs(); // initialiser les joueurs
        void initReserve(); // initialiser la reserve
        void ajouterCarte(Carte* carte, int quantite); // ajouter une carte a la reserve
};

#endif