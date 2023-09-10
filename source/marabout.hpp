#ifndef MARABOUT_HPP
#define MARABOUT_HPP

class Marabout : public Ennemy{
    private:
        int timeSinceProj = 90;
        int proj = 0;
        int lastHealth = 0;
        void updateVertical();
    public:
        Marabout(int id, int sprite, int palette, int posx, int posy, int hp);
        void update();
        int getProj();
        ~Marabout();
};

#endif