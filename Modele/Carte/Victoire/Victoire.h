#ifndef VICTOIRE_H
#define VICTOIRE_H

#include "Carte.h"

class Modele;

class Victoire : public Carte{
    protected:
        int m_points;       // point de victoire que la carte rapporte

    public:
        Victoire(Model* m, int cout, int points) : Carte(m, cout), m_points(points) {}
        ~Victoire();
};

#endif