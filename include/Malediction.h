#ifndef MALEDICTION_H
#define MALEDICTION_H

#include "Victoire.h"

class Modele;

class Malediction : public Victoire{
    private:
        static const int COUT_ACHAT;
        static const int POINTS;

    public:
        Malediction(Modele* m) : Victoire(m, COUT_ACHAT, POINTS, "curse") {}
        ~Malediction(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Malediction(*this); 
        }
};

#endif