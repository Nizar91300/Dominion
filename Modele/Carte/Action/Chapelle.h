#ifndef CHAPELLE_H
#define CHAPELLE_H

#include "Action.h"

class Modele;

class Chapelle : public Action{
    private:
        const COUT_ACHAT = 2;

    public:
        Chapelle(Model* m) : Carte(m, COUT_ACHAT) {}
        ~Chapelle();

        void faireAction();

};

#endif

