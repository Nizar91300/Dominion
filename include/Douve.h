#ifndef DOUVE_H
#define DOUVE_H

#include "Reaction.h"
#include "Action.h"


class Modele;

class Douve : public Reaction, public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Douve(Modele* m) : Action(m, COUT_ACHAT, "Douve") {}
        ~Douve(){}

        void defendre();
        void faireAction();

};

#endif