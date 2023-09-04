#ifndef PIG_HPP
#define PIG_HPP

class Pig : public Ennemy{
    private:
        bool dirRight = false;
    public:
        Pig(int id, int sprite, int palette, int posx, int posy);
        void update();
};

#endif