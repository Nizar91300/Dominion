#ifndef ATELIER_H
#define ATELIER_H

#include "Action.h"

class Modele;

class Atelier : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Atelier(Modele* m) : Action(m, COUT_ACHAT, "workshop", 4) {}
        ~Atelier(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Atelier(*this); 
        }

        void faireAction()override;
};

#endif