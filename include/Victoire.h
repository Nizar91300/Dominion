#ifndef VICTOIRE_H
#define VICTOIRE_H

#include "Carte.h"

class Modele;

class Victoire : public Carte{
    protected:
        int m_points;       // point de victoire que la carte rapporte

    public:
        Victoire(Modele* m, int cout, int points, std::string nom, int priorite) : Carte(m, cout, TypeCarte::VICTOIRE, nom, priorite), m_points(points) {}
        virtual ~Victoire(){}

        int getPoints() const { return m_points; }
};

#endif