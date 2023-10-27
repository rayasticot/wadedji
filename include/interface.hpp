#ifndef INTERFACE_HPP
#define INTERFACE_HPP

class ItemPositions{
    public:
        static constexpr std::array<int, 6> positions_x = {160, 208, 112, 160, 80, 16};
        static constexpr std::array<int, 6> positions_y = {0, 48, 48, 96, 128, 128};
};

class InterfaceItem{
    private:
        ItemPositions itemPositions;

        bool started = false;
        int spriteId;
        int defaultPositionX;
        int defaultPositionY;
    public:
        int itemId;
        int positionX;
        int positionY;

        void start(int posX, int posY, int spriteid, int itemid);
        virtual ~InterfaceItem();
        bool isTouched(int px, int py);
        void resetPos();
        void updateSprite();
};

class Interface{
    private:
        ItemPositions itemPositions;
        ItemInfo itemInfo;

        std::array<InterfaceItem, 5> items;

        int currentHeld = -1;
        int heldTimer = 0;
        int heldPosX = 0;
        int heldPosY = 0;

        int lastItem = 0;
        std::string itemDesc;

        int last_px = -1;
        int last_py = -1;
        touchPosition touch;

        void readItemDesc(std::string fileName);
        void drawItemDesc(int item);
        void drawHealth(int health);
        void drawMana(int mana, int maxMana);
        void drawFcfa(int fcfa);
        bool updateHolding(std::array<int, 5>* inventory, int *fcfa);
    public:
        void start();
        bool update(int health, int mana, int maxMana, int *fcfa, std::array<int, 5>* inventory);
};

#endif