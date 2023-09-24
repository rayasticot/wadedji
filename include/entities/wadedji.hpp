#ifndef WADEDJI_HPP
#define WADEDJI_HPP

class Wadedji : public Player{
    private:
        int frameAnim;
        int frameTime;

        void updateVertical();
        void updateHorizontal();
        void updateAnimation();
    public:
        Wadedji(int id, int sprite_, int palette_, int posx, int posy);
        void createSprite();
        void deleteSprite();
        void update();
        int getProj();
        ~Wadedji();
};

#endif