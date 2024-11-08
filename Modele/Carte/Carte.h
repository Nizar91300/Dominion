#ifndef CARTE_H
#define CARTE_H

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


    public:
        // constructeur
        Carte(Modele* modele, int cout, TypeCarte type) : m_modele(modele), m_cout(cout), m_type(type){}

        // constructeur de copie
        Carte(const Carte* carte) : m_modele(carte->m_modele), m_cout(carte->m_cout){}

        // destructeur
        virtual ~Carte(){}

        int getCout() const { return m_cout; }

        TypeCarte getType() const { return m_type; }
};

#endif