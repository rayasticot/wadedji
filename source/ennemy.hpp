#ifndef ENNEMY_HPP
#define ENNEMY_HPP

class Ennemy : public Object{
    protected:
        int health;
    public:
        virtual int update() = 0;
};

#endif