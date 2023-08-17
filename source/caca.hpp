#ifndef CACA_HPP
#define CACA_HPP

class Caca : public Object{
    public:
        Caca(int id, int sprite, int palette, int posx, int posy);
        int update();
};

#endif