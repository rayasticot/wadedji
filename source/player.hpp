#ifndef PLAYER_HPP
#define PLAYER_HPP
class Player : public Object{
    private:
        float accelerationX;
        float accelerationY;
        float speedX;
        float speedY;
        int frameAnim;
        int frameTime;
        bool run = false;

        void updateVertical();
        void updateHorizontal();
        void updateAnimation();
    
    public:
        Player();
        void updatePlayer();
};
#endif