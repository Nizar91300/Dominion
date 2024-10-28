#ifndef VOLEUR_H
#define VOLEUR_H

#include "Attaque.h"

class Modele;

class Voleur : public Attaque, public Carte{
    private:
        const COUT_ACHAT = 4;

    public:
        Voleur(Model* m) : Carte(m, COUT_ACHAT) {}
        ~Voleur();

        void attaquer();

};

#endif