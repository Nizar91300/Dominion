#ifndef MODELE_H
#define MODELE_H

#include <vector>
#include <set>
#include <string>

class Joueur;

class Carte;

class MyFrame;

class Modele{
    private:
        MyFrame* m_view;    // vue

        std::vector<Joueur*> m_joueurs;     // liste des joueurs
        int m_nbJoueurs;    // nb joueurs
        int m_nbHumans;       // nb bots
        std::vector< std::pair< Carte*, int > > m_reserve;  // liste des carte disposees sur la table avec leurs occurences
        int m_nbActions;  // nombre d'actions restantes
        int m_nbAchats;   // nombre d'achats restants
        int m_nbPieces;   // nombre de pieces restantes
        int m_indexJoueurActif; // index du joueur actif
        Joueur* m_joueurActif;  // joueur actif

        bool m_tourAction;  // vrai si le joueur est en phase d'action faux sinon c'est-a-dire en phase d'achat

        bool m_achatSuiteAction;   // indique si le joueur est en phase d'achat suite a une carte action
        int m_coutMax;              // cout maximal de la carte a recevoir suite a une carte action

        bool m_isTrashAction; // indique si le joueur est en train d'utiliser une carte qui permet d'ecarter des cartes
        int m_nbMaxEcarter;    // nombre maximal de cartes a ecarter
        int m_nbCartesEcarter;    // nombre de cartes a ecarter

        int m_sound;   // indique si le son est active ou non
        std::set< std::string > m_chosenCards; // liste des cartes choisies pour la partie


    public:
        Modele();
        ~Modele();

        void initNewGame(); // initialiser une nouvelle partie
        void initJoueurs(); // initialiser les joueurs
        void initReserve(); // initialiser la reserve
        void initNewTour();    // initialise le nouveau tour du joueur

        int getJoueurActif();
        bool getTourAction();    // retourne vrai si le joueur est en phase d'action faux sinon
        int getNbJoueurs() const; // retourne le nombre de joueurs
        int getNbActions(); // retourne le nombre d'actions restantes
        int getNbAchat();   // retourne le nombre d'achats restants
        int getNbPieces();  // retourne le nombre de pieces restantes
        bool getAchatSuiteAction(); // retourne vrai si le joueur est en phase d'achat suite a une carte action
        bool getIsTrashAction();    // retourne vrai si le joueur est en train d'utiliser une carte qui permet d'ecarter des cartes
        int getCoutMax();   // retourne le cout maximal de la carte a recevoir suite a une carte action
        int getNbMaxEcarter();  // retourne le nombre maximal de cartes a ecarter
        int getNbHumans();  // retourne le nombre de joueurs humains
        std::vector< std::pair< Carte*, int > >  getReserve();  // retourne la reserve
        std::vector< std::pair< Carte*, int > > getMain();  // retourne la main du joueur actif
        std::vector<std::pair<Carte*, int >> getPlayedCards();    // retourne les cartes jouees par le joueur actif
        std::vector<std::pair<Carte*, int >> convertVecCarteToVecPair(std::vector<Carte*> vec); // convertir un vecteur de cartes en vecteur de paires de cartes et de quantites
        std::vector< Carte* > getDefausse();    // retourne la defausse

        void setView(MyFrame* mf);
        void refreshAndPauseView(int ms); // rafraichir l'affichage et mettre en pause le thread

        void endPhase();    // passer a la phase suivante

        void ajouterCarte(Carte* carte, int quantite); // ajouter une carte a la reserve
        void ajouterNbActions(int nb);  // ajouter des actions
        void ajouterNbPieces(int nb);   // ajouter des pieces
        void ajouterNbAchats(int nb);   // ajouter des achats

        void piocher(int nb);   // piocher nb cartes
        void defausser(Carte* carte);   // defausser une carte
        void ecarterCarteJouee(Carte* carte);     // ecarter une carte de la liste des cartes jouees
        void recevoirCarteMain(Carte* carte); // recevoir une carte dans la main
        void recevoirCarteDefausse(Carte* carte); // recevoir une carte dans la defausse

        void jouerCarte(Carte* carte);   // jouer une carte action ou tresor
        void acheterCarteAvecVerif(Carte* carte);    // acheter une carte en verifiant les conditions pour l'achat
        bool acheterCarte(Carte* carte);    // acheter une carte sans verification

        void donnerMalediction();   // donner une malediction a chaque joueur sauf au joueur actif

        void showRecevoirCarte(int coutMax);   // affiche le menu pour recevoir une carte avec un cout inferieur ou egal a coutMax suite a une carte action
        void showEcarterCartes(int nbCartesMax);  // affiche le menu pour ecarter au maximum nbCartes cartes
        void actionVoleur();    // action du voleur

        bool isBotPlaying();    // verifier si le joueur actif est un bot

        bool finPartie();           // verifier si la partie est finie
        void endGame();             // affiche fin de la partie
};

#endif
