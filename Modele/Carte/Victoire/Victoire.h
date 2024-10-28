#ifndef VICTOIRE_H
#define VICTOIRE_H

#include "Carte.h"

class Victoire : public Carte{
    public:
        // constructeur
        Victoire(int cout) : Carte(cout){}
        
        // destructeur
        ~Victoire(){}
};

#endif