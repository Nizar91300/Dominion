#ifndef BUCHERON_H
#define BUCHERON_H

#include "Action.h"

class Modele;

class Bucheron : public Action{
    private:
        const COUT_ACHAT = 3;

    public:
        Bucheron(Model* m) : Carte(m, COUT_ACHAT) {}
        ~Bucheron();

        void faireAction();
};

#endif