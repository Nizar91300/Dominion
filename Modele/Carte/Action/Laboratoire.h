#ifndef LABORATOIRE_H
#define LABORATOIRE_H

#include "Action.h"

class Modele;

class Laboratoire : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Laboratoire(Modele* m) : Action(m, COUT_ACHAT) {}
        ~Laboratoire(){}

        void faireAction();

};

#endif