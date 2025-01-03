#ifndef CARTE_H
#define CARTE_H

#include <string>

class Modele;

enum TypeCarte{
    ACTION,
    TRESOR,
    VICTOIRE
};

class Carte{
    protected:
        Modele* m_modele;
        int m_cout;       // cout de la carte pour l'acheter
        TypeCarte m_type; // type de la carte
        std::string m_nom; // nom de la carte
        int m_priorite;       // priorite de la carte : pour le bot permet de determiner la carte la plus interessante a jouer


    public:
        // constructeur
        Carte(Modele* modele, int cout, TypeCarte type, std::string nom, int priorite) : m_modele(modele), m_cout(cout), m_type(type), m_nom(nom), m_priorite(priorite){}

        // constructeur de copie
        Carte(const Carte* carte) : m_modele(carte->m_modele), m_cout(carte->m_cout), m_type(carte->m_type), m_nom(carte->m_nom){}

        // destructeur
        virtual ~Carte(){}

        // methode virtuelle pour cloner une carte
        virtual Carte* clone() const {
            return new Carte(*this);
        }


        int getCout() const { return m_cout; }

        TypeCarte getType() const { return m_type; }

        std::string getNom() const { return m_nom; }

        int getPriorite() const { return m_priorite; }
};

#endif