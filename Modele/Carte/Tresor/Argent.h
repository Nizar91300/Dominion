#ifndef ARGENT_H
#define ARGENT_H

#include "Tresor.h"

class Argent : public Tresor{
    private:
        const int COUT_ACHAT = 3;
        const int VALEUR = 2;

    public:
        Argent(Model* m) : Tresor(m, COUT_ACHAT, VALEUR) {}
        ~Argent();
};

#endif