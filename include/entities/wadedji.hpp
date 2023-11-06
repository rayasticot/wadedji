#ifndef WADEDJI_HPP
#define WADEDJI_HPP

class Wadedji : public Player{
    /*
        Classe du personnage jouable Wadedji
    */
    private:
        int frameAnim; // Frame actuelle de l'animation
        int frameTime; // Temps depuis la dernière frame
        int heightModif = 0; // Taille modifiée du joueur

        // Met à jour sa position verticale
        void updateVertical();
        // Met à jour sa position horizontale
        void updateHorizontal();
        // Met à jour si il est baissé
        void updateCrouch();
        // Met à jour son animation normale
        void updateWalkAnimation();
        // Met à jour son animation si il est baissé
        void updateCrouchAnimation();
        // Met à jour ses armes
        void updateWeapons();
    public:
        Wadedji(int id, int sprite_, int palette_, int posx, int posy, int* diff, int* level, int* profil);
        // Charge une partie
        void loadSave();
        // Sauvegarde une partie
        void saveGame();
        void createSprite();
        void deleteSprite();
        // Met à jour le joueur
        void update();
        int getProj();
        int getProjDamage();
        ~Wadedji();
};

#endif