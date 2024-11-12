#ifndef CHAPELLE_H
#define CHAPELLE_H

#include "Action.h"

class Modele;

class Chapelle : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Chapelle(Modele* m) : Action(m, COUT_ACHAT, "Chapelle") {}
        ~Chapelle(){}

        void faireAction();

};

#endif

