#ifndef VOLEUR_H
#define VOLEUR_H

#include "Action.h"

class Modele;

class Voleur : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Voleur(Modele* m) : Action(m, COUT_ACHAT, "bandit", 7) {}
        ~Voleur(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Voleur(*this); 
        }

        void faireAction() override;

};

#endif