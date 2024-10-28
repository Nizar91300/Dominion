#ifndef SORCIERE_H
#define SORCIERE_H

#include "Attaque.h"

class Modele;

class Sorciere : public Attaque, public Carte{
    private:
        const COUT_ACHAT = 5;

    public:
        Sorciere(Model* m) : Carte(m, COUT_ACHAT) {}
        ~Sorciere();

        void attaquer();
};

#endif