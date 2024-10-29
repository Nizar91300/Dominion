#ifndef PROVINCE_H
#define PROVINCE_H

#include "Victoire.h"

class Modele;

class Province : public Victoire{
    private:
        static const int COUT_ACHAT;
        static const int POINTS;

    public:
        Province(Modele* m) : Victoire(m, COUT_ACHAT, POINTS) {}
        ~Province(){}
};
#endif