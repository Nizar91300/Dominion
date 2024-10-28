#ifndef TRESOR_H
#define TRESOR_H

#include "Carte.h"

class Modele;

class Tresor : public Carte{
    protected:
        int m_valeur;       // valeur que la carte rapporte

    public:
        Tresor(Model* m, int cout, int valeur) : Carte(m, cout), m_valeur(valeur) {}
        ~Tresor();
};

#endif