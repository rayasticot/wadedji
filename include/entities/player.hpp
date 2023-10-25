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
        float crouchAcc;
        float crouchSpeedLimit;

        float default_hSpeedLimit;
        float default_hAcc;
        float default_hDeceleration;
        float default_vSpeedLimit;
        float default_vGravityAcc;
        float default_vJumpStartSpeed;
        float default_hRunAcc;
        float default_hRunSpeedLimit;
        float default_crouchAcc;
        float default_crouchSpeedLimit;

        PlayerParameters(
            float hspeedlimit,
            float hacc,
            float hdeceleration,
            float vspeedlimit,
            float vgravityacc,
            float vjumpstartspeed,
            float hrunacc,
            float hrunspeedlimit,
            float crouchacc,
            float crouchspeedlimit
        );
};

class Weapon{
    public:
        int itemId = 0;
        int type = 0;
        int damage = 0;
        int cost = 0;
        int coolDown = 0;

        void loadWeapon(std::string fileName);
};

class Player : public Entity{
    protected:
        static constexpr std::array<int, 5> effectIndex = {0, 0, 2, 2, 3};
        //std::vector<std::unique_ptr<ActiveItem>> items;
        std::vector<int> activeIndex;
        std::array<bool, 5> itemIndex = {0, 0, 0, 0, 0};
        std::array<int, 5> inventory = {0, 0, -1, -2, 0};
        Interface inter;
        std::array<Weapon, 2> weapons;
        PlayerParameters parameters = PlayerParameters(2, 0.5, 0.25, 5, 0.15, -4.5, 0.3, 6, 0.3, 1);
        bool run = false;
        bool crouch = false;

        int proj = 0;
        int projDamage = 0;        

        int attackTime = 0;
        int exit = 0;
        int side = 0;
        int hurtTime = 0;

        u32 hurtTimer = 0;
        u32 timer = 0;
        u32 coolDown = 0;

        int health = 8; // petit h
        int mana = 100; // petit m
        int fcfa = 100; // petit f

        int maxHealth = 8; // grand H
        int maxMana = 100; // grand M
        int meleeDamage = 2; // petit d
        int magicDamage = 2; // grand D

        friend class ActiveEffect;

    public:
        //Player(int id, int sprite, int palette, int posx, int posy);
        int getAttack(){ return attackTime; };
        int getSide(){ return side; };
        int getExit(){ return exit; };
        int getMeleeDamage(){ return meleeDamage; };
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };
        int getCrouchPosY();

        //void newItem(int id, bool type);
        void updateLevel(int x, int y);
        void hurt(int damage, float direction);
        bool setupItem(int item);
        void obtainItem(int item);
        void applyItemEffect(int item);
        virtual void createSprite() = 0;
        virtual void deleteSprite() = 0;
        virtual void update() = 0;
        virtual int getProj() = 0;
        virtual int getProjDamage() = 0;
        virtual ~Player(){};
};

class ActiveEffect{
    private:
        void portefeuilleMagique(Player& player);
        void attackGravity(Player& player);
        const std::unordered_map<int, std::function<void(ActiveEffect&, Player&)>> activeEffectList = {
            {2, std::mem_fn(&ActiveEffect::portefeuilleMagique)},
            {3, std::mem_fn(&ActiveEffect::attackGravity)}
        };
    public:
        void applyActive(Player& player);
};

#endif