#ifndef DOUVE_H
#define DOUVE_H

#include "Reaction.h"

class Modele;

class Douve : public Reaction, public Carte{
    private:
        const COUT_ACHAT = 2;

    public:
        Douve(Modele* m, int cout) : Carte(m, COUT_ACHAT) {}
        ~Douve();

        void defendre();

};

#endif