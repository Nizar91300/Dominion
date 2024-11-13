#ifndef BUCHERON_H
#define BUCHERON_H

#include "Action.h"

class Modele;

class Bucheron : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Bucheron(Modele* m) : Action(m, COUT_ACHAT, "woodcutter") {}
        ~Bucheron(){}

        void faireAction();
};

#endif