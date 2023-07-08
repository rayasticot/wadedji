#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayerParameters{
    public:
        float hSpeedLimit = 2;
        float hAcc = 0.5;
        float hDeceleration = 0.25;
        float vSpeedLimit = 5;
        float vGravityAcc = 0.15;
        float vJumpStartSpeed = -4.5;
        float hRunAcc = 0.3;
        float hRunSpeedLimit = 6;

        /*
        PlayerParameters(
            float hspeedlimit,
            float hacc,
            float hdeceleration,
            float vspeedlimit,
            float vgravityacc,
            float vjumpstartspeed,
            float hrunacc,
            float hrunspeedlimit
        );
        */
};

class Player : public Object{
    private:
        PlayerParameters parameters;
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
        Player(int id, int sprite, int palette, int posx, int posy);
        void update();
};
#endif