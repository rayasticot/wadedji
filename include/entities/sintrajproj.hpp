#ifndef SINTRAJPROJ_HPP
#define SINTRAJPROJ_HPP

class SinTrajProj : public Projectile{
    private:
        int amplitude;
        int cycle;
        int timer = 0;
        float sideX;
        float sideY;
    public:
        SinTrajProj(int id, int sprite, int palette, int posx, int posy, int targetX, int targetY, int projSpeed, int projDamage, int ampli, int cyc);
        int update();
        ~SinTrajProj();
};

#endif