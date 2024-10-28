#ifndef DOMAINE_H
#define DOMAINE_H

#include "Victoire.h"

class Modele;

class Domaine : public Victoire{
    private:
        const int COUT_ACHAT = 2;
        const int POINTS = 1;

    public:
        Domaine(Model* m) : Victoire(m, COUT_ACHAT, POINTS) {}
        ~Domaine();
};

#endif