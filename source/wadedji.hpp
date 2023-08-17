#ifndef WADEDJI_HPP
#define WADEDJI_HPP

class Wadedji : public Player{
    private:
        PlayerParameters parameters = PlayerParameters(2, 0.5, 0.25, 5, 0.15, -4.5, 0.3, 6);
        int frameAnim;
        int frameTime;

        void updateVertical();
        void updateHorizontal();
        void updateAnimation();
    public:
        Wadedji(int id, int sprite, int palette, int posx, int posy);
        void createSprite();
        void deleteSprite();
        int update();
};

#endif