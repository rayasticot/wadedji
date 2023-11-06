#ifndef PIG_HPP
#define PIG_HPP

class Pig : public Ennemy{
    /*
        Classe pour les ennemis cochons
    */
    private:
        bool dirRight = false; // Direction du cochon
        // Met à jour l'animation du cochon
        void updateAnimation();
    public:
        Pig(int id, int sprite, int palette, int posx, int posy, int hp);
        // Met à jour le cochon
        void update();
        int getProj();
        void getPlayer(Player* player){};
        ~Pig();
};

#endif