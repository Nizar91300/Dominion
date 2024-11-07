#ifndef VOLEUR_H
#define VOLEUR_H

#include "Action.h"

class Modele;

class Voleur : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Voleur(Modele* m) : Action(m, COUT_ACHAT) {}
        ~Voleur(){}

        void faireAction();

};

#endif