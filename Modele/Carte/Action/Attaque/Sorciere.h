#ifndef SORCIERE_H
#define SORCIERE_H

#include "Attaque.h"
#include "../../Carte.h"

class Modele;

class Sorciere : public Attaque, public Carte{
    private:
        static const int COUT_ACHAT;

    public:
        Sorciere(Modele* m) : Carte(m, COUT_ACHAT) {}
        ~Sorciere(){}

        void attaquer();
};

#endif