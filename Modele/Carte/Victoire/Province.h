#ifndef PROVINCE_H
#define PROVINCE_H

#include "Victoire.h"

class Modele;

class Province : public Victoire{
    private:
        const int COUT_ACHAT = 8;
        const int POINTS = 6;

    public:
        Province(Model* m) : Victoire(m, COUT_ACHAT, POINTS) {}
        ~Province();
};

#endif