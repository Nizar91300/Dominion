#ifndef CARTE_H
#define CARTE_H

class Modele;

class Carte{
    protected:
        Modele* m_modele;
        int m_cout;       // cout de la carte pour l'acheter

    public:
        // constructeur
        Carte(Modele* modele, int cout) : m_modele(modele), m_cout(cout){}

        // destructeur
        virtual ~Carte(){}
};

#endif