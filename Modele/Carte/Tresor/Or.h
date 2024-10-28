#ifndef OR_H
#define OR_H

#include "Tresor.h"

class Modele;

class Or : public Tresor{
    private:
        const int COUT_ACHAT = 6;
        const int VALEUR = 3;

    public:
        Or(Model* m) : Tresor(m, COUT_ACHAT, VALEUR) {}
        ~Or();
};

#endif