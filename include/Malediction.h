#ifndef MALEDICTION_H
#define MALEDICTION_H

#include "Victoire.h"

class Modele;

class Malediction : public Victoire{
    private:
        static const int COUT_ACHAT;
        static const int POINTS;

    public:
        Malediction(Modele* m) : Victoire(m, COUT_ACHAT, POINTS, "Malediction") {}
        ~Malediction(){}
};

#endif