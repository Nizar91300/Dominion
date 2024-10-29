#ifndef VOLEUR_H
#define VOLEUR_H

#include "Attaque.h"
#include "../../Carte.h"

class Modele;

class Voleur : public Attaque, public Carte{
    private:
        static const int COUT_ACHAT;

    public:
        Voleur(Modele* m) : Carte(m, COUT_ACHAT) {}
        ~Voleur(){}

        void attaquer();

};

#endif