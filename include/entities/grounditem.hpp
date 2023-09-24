#ifndef GROUND_ITEM_HPP
#define GROUND_ITEM_HPP

class GroundItem : public Entity{
    private:
        int itemId;
        int spawnWait = 60;
    public:
        int getWait(){ return spawnWait; };
        int getItemId(){ return itemId; };
        int checkHit(Player* player);
        void update();
        GroundItem(int id, int sprite_, int palette_, int posx, int posy, int itemid);
        ~GroundItem();
};

#endif