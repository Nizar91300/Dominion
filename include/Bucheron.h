#ifndef BUCHERON_H
#define BUCHERON_H

#include "Action.h"

class Modele;

class Bucheron : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Bucheron(Modele* m) : Action(m, COUT_ACHAT, "woodcutter", 6) {}
        ~Bucheron(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Bucheron(*this); 
        }

        void faireAction()override;
};

#endif