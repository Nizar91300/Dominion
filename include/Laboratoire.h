#ifndef LABORATOIRE_H
#define LABORATOIRE_H

#include "Action.h"

class Modele;

class Laboratoire : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Laboratoire(Modele* m) : Action(m, COUT_ACHAT, "laboratory", 8) {
            setNbPioche(2);
            setNbActions(1);
        }
        ~Laboratoire(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Laboratoire(*this); 
        }

        void faireAction()override;

};

#endif