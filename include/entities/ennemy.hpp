#ifndef ENNEMY_HPP
#define ENNEMY_HPP

/*
class PoolItem{
    public:
        int itemId;
        int dropRate;
        PoolItem(int id, int rate);
};

class DropPool{
    private:
        std::vector<PoolItem> items;
        bool loaded = false;
    public:
        void loadPoolFile(std::string fileName);
        int giveItem();
};
*/

class Ennemy : public Entity{
    protected:
        int frameAnim = 0;
        int frameTime = 0;

        int health = 4;
        int hurtTime = 0;
        int meleeDamage = 1;
        int type = -1;
    public:
        bool alive = true;
        //DropPool itemPool;
        int getType(){ return type; };
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };
        int getMeleeDamage(){ return meleeDamage; };
        virtual void update() = 0;
        int checkHit(Player* player);
        void hurt(int damage, float direction);
        int dropItem();
        virtual int getProj();
        virtual ~Ennemy(){};
};

#endif