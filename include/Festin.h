#ifndef FESTIN_H
#define FESTIN_H

#include "Action.h"

class Modele;

class Festin : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Festin(Modele* m) : Action(m, COUT_ACHAT, "feast") {}
        ~Festin(){}

        void faireAction();

};

#endif