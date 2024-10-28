#ifndef VILLAGE_H
#define VILLAGE_H

#include "Action.h"

class Modele;

class Village : public Action{
    private:
        const COUT_ACHAT = 3;

    public:
        Village(Model* m) : Carte(m, COUT_ACHAT) {}
        ~Village();

        void faireAction();

};

#endif