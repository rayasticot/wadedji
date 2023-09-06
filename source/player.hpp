#ifndef PLAYER_HPP
#define PLAYER_HPP

/*
health
mana
FCFA
----
max health
max mana
phys attack
genie attack
speed
jump
scam
*/

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
        Interface inter;
        float accelerationX;
        float accelerationY;
        float speedX;
        float speedY;
        bool run = false;
        int attackTime = 0;
        int exit = 0;
        int side = 0;
        int health = 8;
        int hurtTime = 0;
        int meleeDamage = 2;
        //virtual void attack() = 0;
    
    public:
        //Player(int id, int sprite, int palette, int posx, int posy);
        int getAttack(){ return attackTime; };
        int getSide(){ return side; };
        int getExit(){ return exit; };
        int getMeleeDamage(){ return meleeDamage; };
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };
        void updateLevel(int x, int y);
        void hurt(int damage, float direction);
        virtual void createSprite();
        virtual void deleteSprite();
        virtual void update() = 0;
};
#endif