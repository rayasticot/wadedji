#ifndef BASICTRAJPROJ_HPP
#define BASICTRAJPROJ_HPP

class BasicTrajProj : public Projectile{
    /*
        Projectile qui suit une direction
    */
    public:
        BasicTrajProj(int id, int sprite, int palette, int posx, int posy, int targetX, int targetY, int projSpeed, int projDamage);
        int update();
        ~BasicTrajProj();
};

#endif