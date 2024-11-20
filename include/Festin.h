#ifndef FESTIN_H
#define FESTIN_H

#include "Action.h"

class Modele;

class Festin : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Festin(Modele* m) : Action(m, COUT_ACHAT, "feast") {}
        ~Festin(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Festin(*this); 
        }

        void faireAction() override;

};

#endif