#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile : public Entity{
    /*
        Entité projectile
    */
    protected:
        float speedMul; // Intensité de la direction
        int damage; // Dégats du projectile
        int touch = 0; // Si le projectile touch quelque chose
        // Normalise la vitesse du projectile
        void normalizeSpeed();
    public:
        // Tue le projectile
        void kill();
        int getDamage(){ return damage; };
        // Vérifie qu'il touche le joueur
        int checkHit(Player* player);
        // Vérifie qu'il touche un ennemi
        int checkHit(Ennemy* ennemy);
        virtual int update();
        virtual ~Projectile(){};
};

#endif