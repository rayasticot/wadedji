#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object{
    protected:
        int spriteId;
        float positionX;
        float positionY;
        int positionScreenX;
        int positionScreenY;
        int sizeX;
        int sizeY;
        bool flagNotCenterX;
        bool flagNotCenterY;

        void moveScreenPos(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
        bool checkRangeMapCollisionX(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        bool checkRangeMapCollisionY(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
    public:
        void moveCamToPos(int* camPositionX, int* camPositionY, int screenSizeX, int screenSizeY);
        void update();
        void updateSprite(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
};

#endif