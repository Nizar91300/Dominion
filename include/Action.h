#ifndef ACTION_H
#define ACTION_H

#include "Carte.h"

class Modele;

class Action : public Carte{
    public:
        Action(Modele* m, int cout, std::string nom) : Carte(m, cout, TypeCarte::ACTION, nom) {}
        virtual ~Action(){}

        virtual void faireAction() = 0;
};

#endif