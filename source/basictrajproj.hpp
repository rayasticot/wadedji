#ifndef BASICTRAJPROJ_HPP
#define BASICTRAJPROJ_HPP

class BasicTrajProj : public Projectile{
    public:
        BasicTrajProj(int id, int sprite, int palette, int posx, int posy, int targetX, int targetY, int projSpeed, int projDamage);
        int update();
        ~BasicTrajProj();
};

#endif