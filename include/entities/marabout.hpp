#ifndef MARABOUT_HPP
#define MARABOUT_HPP

class Marabout : public Ennemy{
    /*
        Classe pour les ennemis marabouts
    */
    private:
        int timeSinceProj = 90; // Temps depuis le projectile
        int proj = 0; // projectile à faire apparaitre (0 = aucun)
        int projFind = 0; // projectile qui sera éventuellement créé
        int lastHealth = 0; // Vie à la frame précedente

        void updateAnimation();
    public:
        Marabout(int id, int sprite, int palette, int posx, int posy, int hp, int projfind);
        // Met à jour l'ennemi
        void update();
        int getProj();
        void getPlayer(Player* player){};
        ~Marabout();
};

#endif