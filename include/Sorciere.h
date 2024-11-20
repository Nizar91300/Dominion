#ifndef SORCIERE_H
#define SORCIERE_H

#include "Action.h"

class Modele;

class Sorciere : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Sorciere(Modele* m) : Action(m, COUT_ACHAT, "witch") {}
        ~Sorciere(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Sorciere(*this); 
        }

        void faireAction()override;
};

#endif