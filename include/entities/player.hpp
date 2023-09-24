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

class Player : public Entity{
    protected:
        static constexpr std::array<bool, 2> effectIndex = {0, 0};
        //std::vector<std::unique_ptr<ActiveItem>> items;
        std::array<bool, 2> itemIndex;
        //std::array<int, 4> = {0, 1, 0, 2};

        Interface inter;
        PlayerParameters parameters = PlayerParameters(2, 0.5, 0.25, 5, 0.15, -4.5, 0.3, 6);
        bool run = false;
        int attackTime = 0;
        int exit = 0;
        int side = 0;
        int hurtTime = 0;

        int health = 8; // petit h
        int mana = 50; // petit m
        int fcfa = 100; // petit f

        int maxHealth = 8; // grand H
        int maxMana = 50; // grand M
        int meleeDamage = 2; // petit d
        int magicDamage = 2; // grand D

    public:
        //Player(int id, int sprite, int palette, int posx, int posy);
        int getAttack(){ return attackTime; };
        int getSide(){ return side; };
        int getExit(){ return exit; };
        int getMeleeDamage(){ return meleeDamage; };
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };

        //void newItem(int id, bool type);
        void updateLevel(int x, int y);
        void hurt(int damage, float direction);
        void obtainItem(int item);
        void applyItemEffect(int item);
        virtual void createSprite() = 0;
        virtual void deleteSprite() = 0;
        virtual void update() = 0;
        virtual int getProj() = 0;
        virtual ~Player(){};
};

#endif