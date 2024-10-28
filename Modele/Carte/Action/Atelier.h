#ifndef ATELIER_H
#define ATELIER_H

#include "Action.h"

class Modele;

class Atelier : public Action{
    private:
        const COUT_ACHAT = 3;

    public:
        Atelier(Model* m) : Carte(m, COUT_ACHAT) {}
        ~Atelier();

        void faireAction();
};

#endif