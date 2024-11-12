#ifndef CUIVRE_H
#define CUIVRE_H

#include "Tresor.h"

class Modele;

class Cuivre : public Tresor{
    private:
        static const int COUT_ACHAT;
        static const int VALEUR;

    public:
        Cuivre(Modele* m) : Tresor(m, COUT_ACHAT, VALEUR, "Cuivre") {}
        ~Cuivre(){}
};
#endif