#ifndef PIG_HPP
#define PIG_HPP

class Pig : public Ennemy{
    private:
        bool dirRight = false;
        void updateAnimation();
    public:
        Pig(int id, int sprite, int palette, int posx, int posy, int hp);
        void update();
        int getProj();
        ~Pig();
};

#endif