#ifndef MODELE_H
#define MODELE_H

#include <vector>

class Joueur;

class Carte;

class MyFrame;

class Modele{
    private:
        MyFrame* m_view;    // vue

        std::vector<Joueur*> m_joueurs;     // liste des joueurs
        int m_nbJoueurs;    // nb joueurs
        std::vector< std::pair< Carte*, int > > m_reserve;  // liste des carte disposees sur la table avec leurs occurences
        int m_nbActions;  // nombre d'actions restantes
        int m_nbAchats;   // nombre d'achats restants
        int m_nbPieces;   // nombre de pieces restantes
        int m_indexJoueurActif; // index du joueur actif
        Joueur* m_joueurActif;  // joueur actif

        bool m_achatSuiteAction;   // indique si le joueur est en phase d'achat suite a une carte action
        int m_coutMax;              // cout maximal de la carte a recevoir suite a une carte action
    

    public:
        Modele();
        ~Modele();

        void initNewGame(int nbJoueurs); // initialiser une nouvelle partie
        void initJoueurs(); // initialiser les joueurs
        void initReserve(); // initialiser la reserve
        void initNewTour();    // initialise le nouveau tour du joueur
        
        std::vector< std::pair< Carte*, int > >  getReserve();  // retourne la reserve
        std::vector<Carte*> getMain();  // retourne la main du joueur actif
        std::vector<Carte*> getPlayedCards();    // retourne les cartes jouees par le joueur actif

        void setView(MyFrame* mf);

        void ajouterCarte(Carte* carte, int quantite); // ajouter une carte a la reserve
        void ajouterNbActions(int nb);  // ajouter des actions
        void ajouterNbPieces(int nb);   // ajouter des pieces
        void ajouterNbAchats(int nb);   // ajouter des achats

        void piocher(int nb);   // piocher nb cartes
        void defausser(Carte* carte);   // defausser une carte
        void ecarterCarteJouee(Carte* carte);     // ecarter une carte de la liste des cartes jouees
        void recevoirCarteMain(Carte* carte); // recevoir une carte dans la main
        void recevoirCarteDefausse(Carte* carte); // recevoir une carte dans la defausse        

        void jouerCarteAction(Carte* carte);   // jouer une carte action
        void jouerCarteTresor(Carte* carte);   // jouer une carte tresor
        void acheterCarteAvecVerif(Carte* carte);    // acheter une carte en verifiant les conditions pour l'achat
        bool acheterCarte(Carte* carte);    // acheter une carte sans verification
        
        void donnerMalediction();   // donner une malediction a chaque joueur sauf au joueur actif

        void showRecevoirCarte(int coutMax);   // affiche le menu pour recevoir une carte avec un cout inferieur ou egal a coutMax suite a une carte action
        void showEcarterCartes(int nbCartesMax);  // affiche le menu pour ecarter au maximum nbCartes cartes

        bool finPartie();           // verifier si la partie est finie
};

#endif