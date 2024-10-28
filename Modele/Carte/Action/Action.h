#ifndef ACTION_H
#define ACTION_H

#include "Carte.h"

class Modele;

class Action : public Carte{
    public:
        Action(Model* m, int cout) : Carte(m, cout) {}
        ~Action();

        virtual void faireAction() = 0;
};

#endif