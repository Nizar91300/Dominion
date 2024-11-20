#ifndef DUCHE_H
#define DUCHE_H

#include "Victoire.h"

class Modele;

class Duche : public Victoire{
    private:
        static const int COUT_ACHAT;
        static const int POINTS;

    public:
        Duche(Modele* m) : Victoire(m, COUT_ACHAT, POINTS, "duchy") {}
        ~Duche(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Duche(*this); 
        }
};
#endif