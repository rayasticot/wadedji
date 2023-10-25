#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile : public Entity{
    protected:
        float speedMul;
        int damage;
        int touch = 0;
        void normalizeSpeed();
    public:
        void kill();
        int getDamage(){ return damage; };
        int checkHit(Player* player);
        int checkHit(Ennemy* ennemy);
        virtual int update();
        virtual ~Projectile(){};
};

#endif