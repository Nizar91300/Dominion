#ifndef JARDIN_H
#define JARDIN_H

#include "Victoire.h"

class Modele;

class Jardin : public Victoire{
    private:
        static const int COUT_ACHAT;
        static const int POINTS;

    public:
        Jardin(Modele* m) : Victoire(m, COUT_ACHAT, POINTS) {}
        ~Jardin(){}
};
#endif