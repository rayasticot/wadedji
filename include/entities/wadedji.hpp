#ifndef WADEDJI_HPP
#define WADEDJI_HPP

class Wadedji : public Player{
    private:
        int frameAnim;
        int frameTime;
        int heightModif = 0;

        void updateVertical();
        void updateHorizontal();
        void updateCrouch();
        void updateWalkAnimation();
        void updateCrouchAnimation();
        void updateWeapons();
    public:
        Wadedji(int id, int sprite_, int palette_, int posx, int posy);
        void createSprite();
        void deleteSprite();
        void update();
        int getProj();
        int getProjDamage();
        ~Wadedji();
};

#endif