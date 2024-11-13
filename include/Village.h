#ifndef VILLAGE_H
#define VILLAGE_H

#include "Action.h"

class Modele;

class Village : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Village(Modele* m) : Action(m, COUT_ACHAT, "village") {}
        ~Village(){}

        void faireAction();

};

#endif