#ifndef LABORATOIRE_H
#define LABORATOIRE_H

#include "Action.h"

class Modele;

class Laboratoire : public Action{
    private:
        const COUT_ACHAT = 5;

    public:
        Laboratoire(Model* m) : Carte(m, COUT_ACHAT) {}
        ~Laboratoire();

        void faireAction();

};

#endif