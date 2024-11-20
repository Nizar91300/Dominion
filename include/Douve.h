#ifndef DOUVE_H
#define DOUVE_H

#include "Reaction.h"
#include "Action.h"


class Modele;

class Douve : public Reaction, public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Douve(Modele* m) : Action(m, COUT_ACHAT, "moat") {}
        ~Douve(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Douve(*this); 
        }

        void defendre()override;
        void faireAction()override;

};

#endif