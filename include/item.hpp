#ifndef ITEM_HPP
#define ITEM_HPP

class Item{
    private:
        bool updateStatus = false;
    public:
        virtual PlayerParameters start(PlayerParameters param) = 0;
        virtual Player update(Player player) = 0;
};

#endif