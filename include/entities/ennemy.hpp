#ifndef ENNEMY_HPP
#define ENNEMY_HPP

/*
class PoolItem{
    public:
        int itemId;
        int dropRate;
        PoolItem(int id, int rate);
};

class DropPool{
    private:
        std::vector<PoolItem> items;
        bool loaded = false;
    public:
        void loadPoolFile(std::string fileName);
        int giveItem();
};
*/

class Ennemy : public Entity{
    /*
        Classe pour les différents ennemis du jeu
    */
    protected:
        int frameAnim = 0; // Frame actuelle de l'animation
        int frameTime = 0; // Temps entre les frames

        int health = 4; // Vie
        int hurtTime = 0; // Cooldown de prise de dégats
        int meleeDamage = 1; // Dégats corps à corps
        int type = -1; // Type d'ennemi
    public:
        bool alive = true; // Si l'ennemi est en vie
        //DropPool itemPool;
        int getType(){ return type; };
        int getHurtTime(){ return hurtTime; };
        int getHealth(){ return health; };
        int getMeleeDamage(){ return meleeDamage; };
        virtual void update() = 0;
        // Vérifie si l'ennemi touche le joueur
        int checkHit(Player* player);
        // Applique des dégats à l'ennemi
        void hurt(int damage, float direction);
        // Fait tomber un objet au sol
        int dropItem();
        // Obtiens des infos sur le joueur
        virtual void getPlayer(Player* player) = 0;
        virtual int getProj();
        virtual ~Ennemy(){};
};

#endif