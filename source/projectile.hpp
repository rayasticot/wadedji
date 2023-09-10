#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile : public Object{
    protected:
        float speed;
        float dirX;
        float dirY;
        int damage;
        int touch = 0;
        void normalizeDir();
    public:
        void kill();
        int getDamage(){ return damage; };
        int checkHit(Player* player);
        virtual int update();
        virtual ~Projectile(){};
};

#endif