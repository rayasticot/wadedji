#ifndef SINTRAJPROJ_HPP
#define SINTRAJPROJ_HPP

class SinTrajProj : public Projectile{
    /*
        Projectile qui suit une direction en appliquant une fonction sinus
        pour créer une trajectoire différente.
    */
    private:
        int amplitude; // Amplitude de la fonction
        int cycle; // Cycle de la fonction
        int timer = 0; // Temps du projectile
        float sideX; // Composante X normalisé du vecteur côté
        float sideY; // Composante Y normalisé du vecteur côté
    public:
        SinTrajProj(int id, int sprite, int palette, int posx, int posy, int targetX, int targetY, int projSpeed, int projDamage, int ampli, int cyc);
        int update();
        ~SinTrajProj();
};

#endif