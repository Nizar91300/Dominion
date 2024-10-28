#ifndef CARTE_H
#define CARTE_H

class Carte{
    protected:
        int m_cout;       // cout de la carte pour l'acheter

    public:
        // constructeur
        Carte(int cout) : m_cout(cout){}

        // destructeur
        ~Carte(){}

};

#endif