#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayerParameters{
    public:
        float hSpeedLimit;
        float hAcc;
        float hDeceleration;
        float vSpeedLimit;
        float vGravityAcc;
        float vJumpStartSpeed;
        float hRunAcc;
        float hRunSpeedLimit;

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
};

class Player : public Object{
    protected:
        float accelerationX;
        float accelerationY;
        float speedX;
        float speedY;
        bool run = false;
    
    public:
        //Player(int id, int sprite, int palette, int posx, int posy);
        virtual void update() = 0;
};
#endif