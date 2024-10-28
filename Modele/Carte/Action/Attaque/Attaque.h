#ifndef ATTAQUE_H
#define ATTAQUE_H

class Attaque{
    public:
        Attaque();
        ~Attaque();

        virtual void attaquer() = 0;    // methode virtuelle pure
};

#endif