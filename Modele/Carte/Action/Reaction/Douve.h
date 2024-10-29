#ifndef DOUVE_H
#define DOUVE_H

#include "Reaction.h"
#include "../../Carte.h"

class Modele;

class Douve : public Reaction, public Carte{
    private:
        static const int COUT_ACHAT;

    public:
        Douve(Modele* m) : Carte(m, COUT_ACHAT) {}
        ~Douve(){}

        void defendre();

};

#endif