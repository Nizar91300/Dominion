#ifndef ACTION_H
#define ACTION_H

#include "Carte.h"

class Modele;

class Action : public Carte{
    private:
        int m_nbPioche;     // nombre de cartes supplementaires qu'on peut piocher grace a la carte
        int m_nbActions;    // nombre d'actions supplementaires qu'on peut jouer grace a la carte
    public:
        Action(Modele* m, int cout, std::string nom, int priorite) : Carte(m, cout, TypeCarte::ACTION, nom, priorite) {
            m_nbPioche = 0;
            m_nbActions = 0;
        }
        virtual ~Action(){}

        virtual void faireAction() = 0;

        int getNbPioche() const { return m_nbPioche; }
        int getNbActions() const { return m_nbActions; }

        void setNbPioche(int nb) { m_nbPioche = nb; }
        void setNbActions(int nb) { m_nbActions = nb; }
};

#endif