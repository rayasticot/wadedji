#ifndef BLOODPROJ_HPP
#define BLOODPROJ_HPP

class BloodProj : public Projectile{
    /*
        Projectile de sang qui est affecté par la gravité.
    */
    public:
        BloodProj(int id, int sprite, int palette, int posx, int posy, int angle);
        int update();
        ~BloodProj();
};

#endif