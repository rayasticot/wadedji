#ifndef GENIEBOSS_HPP
#define GENIEBOSS_HPP

class GenieBoss : public Ennemy{
    private:
        bool direction;
        int proj = 0;
        int state = 0;
        int timer = 0;
        int fullTimer = 0;
        int playerPosX = 0;
        float initialX;
        float initialHeight;
        float idlePosY;
    public:
        GenieBoss(int id, int sprite, int palette, int posx, int posy, int hp);
        void idle();
        void fall();
        void moveToPlayer();
        void rise();
        void update();
        int getProj();
        void getPlayer(Player* player);
        ~GenieBoss();
};

#endif