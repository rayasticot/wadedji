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
    /*
        Divers paramètres au niveau du mouvement du joueur
    */
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
    /*
        Objet pour les différentes armes
    */
    public:
        int itemId = 0; // Identifiant de l'objet
        int type = 0; // Type d'arme
        int damage = 0; // Dégats
        int cost = 0; // Cout en mana
        int coolDown = 0; // Temps d'attente

        // Charge un fichier d'arme
        void loadWeapon(std::string fileName);
};

class Player : public Entity{
    /*
        Classe du joueur, descendante de l'entité
    */
    protected:
        ItemInfo itemInfo; // Constantes sur les objets
        //std::vector<std::unique_ptr<ActiveItem>> items;
        std::vector<int> activeIndex; // Vecteur des objets actifs
        std::array<bool, 5> itemIndex = {0, 0, 0, 0, 0}; // Indique les objets collectés
        std::array<int, 5> inventory = {0, 0, -1, -2, 0}; // Indique l'inventaire
        Interface inter; // Objet de l'interface
        std::array<Weapon, 2> weapons; // Indique les armes
        // Différents paramètres au niveau du mouvement du joueur
        PlayerParameters parameters = PlayerParameters(2, 0.5, 0.25, 5, 0.15, -4.5, 0.3, 6, 0.3, 1);
        bool run = false; // Indique si le joueur est en train de courir
        bool crouch = false; // Indique si le joueur est baissé
        bool pound = false; // Indique si le joueur fait une attaque depuis la hauteur

        int proj = 0; // Projectile lancé par le joueur (0 = aucun)
        int projDamage = 0; // Dégats du projectile

        int attackTime = 0; // Temps de cooldown entre les coup de poings
        int exit = 0; // Si le joueur a interragi avec une porte
        int side = 0; // Indique le côté du joueur
        int hurtTime = 0; // Temps de cooldown des dégats reçus

        int* difficulty; // Pointeur vers la difficulté actuelle
        int* currentLevel; // Pointeur vers le niveau actuel
        int* profile; // Pointeur vers le profil actuel

        u32 hurtTimer = 0; // Temps à faire clignoter le joueur
        u32 timer = 0; // Timer général du jeu
        u32 coolDown = 0; // Cooldown entre les attaques à distances

        int health = 8; // petit h // Indique la vie
        int mana = 100; // petit m // Indique la mana
        int fcfa = 100; // petit f // L'argent du joueur

        int maxHealth = 8; // grand H // Vie maximale
        int maxMana = 100; // grand M // Mana maximale
        int meleeDamage = 2; // petit d // Dégats corps à corps
        int magicDamage = 2; // grand D // Dégats magiques

        friend class ActiveEffect;

    public:
        //Player(int id, int sprite, int palette, int posx, int posy);
        bool getPound(){ return pound; };
        int getAttack(){ return attackTime; };
        int getSide(){ return side; };
        int getExit(){ return exit; };
        int getMeleeDamage(){ return meleeDamage; };
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };
        int getCrouchPosY();
        // Donne de la mana au joueur
        void giveMana(int ammount);
        // Donne de l'argent au joueur
        void giveMoney(int ammount);

        // Sauvegarde une partie
        virtual void loadSave() = 0;
        // Charge une partie
        virtual void saveGame() = 0;

        //void newItem(int id, bool type);
        // Met à jour la position selon le nouveau niveau
        void updateLevel(int x, int y);
        // Fais des dégats au joueur
        void hurt(int damage, float direction);
        // Lorsque collision avec le joueur et un objet
        bool setupItem(int item);
        // Donne un objet au joueur
        void obtainItem(int item);
        // Applique un effet au joueur
        void applyItemEffect(int item);
        virtual void createSprite() = 0;
        virtual void deleteSprite() = 0;
        virtual void update() = 0;
        virtual int getProj() = 0;
        virtual int getProjDamage() = 0;
        virtual ~Player(){};
};

class ActiveEffect{
    /*
        Classe pour gérer les effets actifs
    */
    private:
        // Fonction pour le portefeuille magique
        void portefeuilleMagique(Player& player);
        // Fonction pour les poings anti-gravité
        void attackGravity(Player& player);
        const std::unordered_map<int, std::function<void(ActiveEffect&, Player&)>> activeEffectList = {
            {2, std::mem_fn(&ActiveEffect::portefeuilleMagique)},
            {3, std::mem_fn(&ActiveEffect::attackGravity)}
        }; // Association des différents objets aux fonctions correspondantes
    public:
        // Applique les effets actifs au joueur
        void applyActive(Player& player);
};

#endif