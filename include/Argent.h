#ifndef ARGENT_H
#define ARGENT_H

#include "Tresor.h"

class Modele;

class Argent : public Tresor{
    private:
        static const int COUT_ACHAT;
        static const int VALEUR;

    public:
        Argent(Modele* m) : Tresor(m, COUT_ACHAT, VALEUR, "Argent") {}
        ~Argent(){}
};
#endif