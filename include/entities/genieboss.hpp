#ifndef GENIEBOSS_HPP
#define GENIEBOSS_HPP

class GenieBoss : public Ennemy{
    /*
        Ennemi du boss génie
    */
    private:
        bool direction; // direction du boss
        int proj = 0; // Projectile à balancer
        int state = 0; // État actuel
        int timer = 0; // Temps avant une action
        int fullTimer = 0; // Temps général
        int playerPosX = 0; // Position du joueur
        float initialX; // Position X initiale
        float initialHeight; // Position Y initiale
        float idlePosY; // Position à laquelle rester
    public:
        GenieBoss(int id, int sprite, int palette, int posx, int posy, int hp);
        // Reste à attendre
        void idle();
        // Descend vers le joueur
        void fall();
        // Se déplace vers le joueur
        void moveToPlayer();
        // Remonte en haut
        void rise();
        // Met à jour le boss
        void update();
        // Obtient le projectile à créer
        int getProj();
        // Obtient des infos sur le joueur
        void getPlayer(Player* player);
        ~GenieBoss();
};

#endif