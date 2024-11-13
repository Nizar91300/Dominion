#ifndef DOMAINE_H
#define DOMAINE_H

#include "Victoire.h"

class Modele;

class Domaine : public Victoire{
    private:
        static const int COUT_ACHAT;
        static const int POINTS;

    public:
        Domaine(Modele* m) : Victoire(m, COUT_ACHAT, POINTS, "estate") {}
        ~Domaine(){}
};

#endif