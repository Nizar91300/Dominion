#ifndef JARDIN_H
#define JARDIN_H

#include "Victoire.h"

class Modele;

class Jardin : public Victoire{
    private:
        static const int COUT_ACHAT;
        static const int POINTS;

    public:
        Jardin(Modele* m) : Victoire(m, COUT_ACHAT, POINTS, "gardens", 4) {}
        ~Jardin(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Jardin(*this); 
        }
};
#endif