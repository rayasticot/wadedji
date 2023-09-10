#ifndef ENNEMY_HPP
#define ENNEMY_HPP

class Ennemy : public Object{
    protected:
        float accelerationX;
        float accelerationY;
        float speedX;
        float speedY;
        int health = 4;
        int hurtTime = 0;
        int meleeDamage = 1;
    public:
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };
        int getMeleeDamage(){ return meleeDamage; };
        virtual void update() = 0;
        int checkHit(Player* player);
        void hurt(int damage, float direction);
        virtual int getProj();
        virtual ~Ennemy(){};
};

#endif