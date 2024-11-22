#ifndef VILLAGE_H
#define VILLAGE_H

#include "Action.h"

class Modele;

class Village : public Action{
    private:
        static const int COUT_ACHAT;

    public:
        Village(Modele* m) : Action(m, COUT_ACHAT, "village", 10) {
            setNbPioche(1);
            setNbActions(2);
        }
        ~Village(){}

        // Implementation de la methode clone
        Carte* clone() const override {
            return new Village(*this); 
        }

        void faireAction()override;

};

#endif