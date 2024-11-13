#ifndef ATELIER_H
#define ATELIER_H

#include "Action.h"

class Modele;

class Atelier : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Atelier(Modele* m) : Action(m, COUT_ACHAT, "workshop") {}
        ~Atelier(){}

        void faireAction();
};

#endif