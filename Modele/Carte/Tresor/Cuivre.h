#ifndef CUIVRE_H
#define CUIVRE_H

#include "Tresor.h"

class Modele;

class Cuivre : public Tresor{
    private:
        const int COUT_ACHAT = 0;
        const int VALEUR = 1;

    public:
        Cuivre(Model* m) : Tresor(m, COUT_ACHAT, VALEUR) {}
        ~Cuivre();
};

#endif