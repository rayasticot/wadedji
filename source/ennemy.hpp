#ifndef ENNEMY_HPP
#define ENNEMY_HPP

class Ennemy : public Object{
    protected:
        float accelerationX;
        float accelerationY;
        float speedX;
        float speedY;
        int health = 20;
        int defense = 10;
        int hurtTime = 0;
    public:
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };
        virtual void update() = 0;
        int checkHit(Player* player);
        void hurt(float damage, float direction);
};

#endif