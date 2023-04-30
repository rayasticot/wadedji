#ifndef PLAYER_HPP
#define PLAYER_HPP
class Player : public Object{
    private:
        float accelerationX;
        float accelerationY;
        float speedX;
        float speedY;
        bool run = false;

        void updateVertical();
        void updateHorizontal();
    
    public:
        Player();
        void updatePlayer();
};
#endif