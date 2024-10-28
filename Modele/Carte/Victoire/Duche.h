#ifndef DUCHE_H
#define DUCHE_H

#include "Victoire.h"

class Modele;

class Duches : public Victoire{
    private:
        const int COUT_ACHAT = 5;
        const int POINTS = 3;

    public:
        Duches(Model* m) : Victoire(m, COUT_ACHAT, POINTS) {}
        ~Duches();
};

#endif