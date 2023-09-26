#ifndef INTERFACE_HPP
#define INTERFACE_HPP

class Interface{
    private:
        void drawHealth(int health);
        void drawMana(int mana, int maxMana);
    public:
        void start();
        void update(int health, int mana, int maxMana);
};

#endif