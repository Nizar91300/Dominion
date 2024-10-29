#include "Modele.h"

#include <iostream>
#include "Joueur/Joueur.h"

#include "Carte/Tresor/Cuivre.h"
#include "Carte/Tresor/Argent.h"
#include "Carte/Tresor/Or.h"
#include "Carte/Victoire/Domaine.h"
#include "Carte/Victoire/Duche.h"
#include "Carte/Victoire/Province.h"
#include "Carte/Victoire/Jardin.h"
#include "Carte/Action/Atelier.h"
#include "Carte/Action/Bucheron.h"
#include "Carte/Action/Reaction/Douve.h"
#include "Carte/Action/Chapelle.h"
#include "Carte/Action/Laboratoire.h"
#include "Carte/Action/Attaque/Sorciere.h"
#include "Carte/Action/Village.h"
#include "Carte/Action/Attaque/Voleur.h"
#include "Carte/Action/Festin.h"


// constructeur
Modele::Modele(int nbJoueurs){
    m_nbJoueurs = nbJoueurs;

    // initialiser les joueurs
    initJoueurs();

    // initialiser la reserve
    initReserve();
}

// destructeur
Modele::~Modele(){
    // liberer la memoire des joueurs
    for(unsigned int i = 0; i < m_joueurs.size(); i++){
        delete m_joueurs[i];
    }

    // liberer la memoire de la reserve
    for(unsigned int i = 0; i < m_reserve.size(); i++){
        delete m_reserve[i].first;
    }
}

// initialiser les joueurs
void Modele::initJoueurs(){
    // creer les joueurs
    for(int i = 0; i < m_nbJoueurs; i++){
        m_joueurs.push_back(new Joueur(this));
    }
}

// initialiser la reserve
void Modele::initReserve(){

    // CARTES TRESOR
    const int NB_CARTES_CUIVRE = 60 - 7 * m_nbJoueurs;      // depend du nombre de joueurs
    ajouterCarte(new Cuivre(this), NB_CARTES_CUIVRE);
    ajouterCarte(new Argent(this), 40);
    ajouterCarte(new Or(this), 30);

    // CARTES VICTOIRE
    int nbCartesVictoire = (m_nbJoueurs > 2) ? 12 : 8;
    ajouterCarte(new Domaine(this), nbCartesVictoire);
    ajouterCarte(new Duche(this), nbCartesVictoire);
    ajouterCarte(new Province(this), nbCartesVictoire);

    // CARTES ROYAUME
    struct CarteInfo {
        Carte* carte;
        int quantite;
    };

    std::vector<CarteInfo> cartesRoyaume = {
        {new Jardin(this), 12},
        {new Atelier(this), 10},
        {new Bucheron(this), 10},
        {new Douve(this), 10},
        {new Chapelle(this), 10},
        {new Laboratoire(this), 10},
        {new Sorciere(this), 10},
        {new Village(this), 10},
        {new Voleur(this), 10},
        {new Festin(this), 10}
    };

    for (const auto& carteInfo : cartesRoyaume) {
        ajouterCarte(carteInfo.carte, carteInfo.quantite);
    }


    // afficher la reserve
    for (const auto& carteInfo : m_reserve) {
        std::cout << typeid(*(carteInfo.first)).name() << " : " << carteInfo.second << std::endl;
    }
}

// ajouter une carte a la reserve
void Modele::ajouterCarte(Carte* carte, int nbCartes){
    m_reserve.push_back( std::make_pair(carte, nbCartes) );
}