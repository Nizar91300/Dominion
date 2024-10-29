#ifndef OR_H
#define OR_H

#include "Tresor.h"

class Modele;

class Or : public Tresor{
    private:
        static const int COUT_ACHAT;
        static const int VALEUR ;

    public:
        Or(Modele* m) : Tresor(m, COUT_ACHAT, VALEUR) {}
        ~Or(){}
};
#endif