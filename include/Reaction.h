#ifndef REACTION_H
#define REACTION_H

class Reaction{
    public:
        Reaction(){}

        virtual ~Reaction(){}

        virtual void defendre() = 0;
};

#endif