#ifndef SORCIERE_H
#define SORCIERE_H

#include "Action.h"

class Modele;

class Sorciere : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Sorciere(Modele* m) : Action(m, COUT_ACHAT) {}
        ~Sorciere(){}

        void faireAction();
};

#endif