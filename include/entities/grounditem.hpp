#ifndef GROUND_ITEM_HPP
#define GROUND_ITEM_HPP

class GroundItem : public Entity{
    /*
        Classe pour les objets au sol
    */
    private:
        int itemId; // Identifiant de l'objet
        int spawnWait = 60; // Attente avant que l'objet puisse être ramassé
    public:
        int getWait(){ return spawnWait; };
        int getItemId(){ return itemId; };
        // Vérifie si l'objet est touché
        int checkHit(Player* player);
        // Met à jour l'objet
        void update();
        GroundItem(int id, int sprite_, int palette_, int posx, int posy, int itemid);
        ~GroundItem();
};

#endif