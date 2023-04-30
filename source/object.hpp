#ifndef OBJECT_HPP
#define OBJECT_HPP
class Object{
    protected:
        float positionX;
        float positionY;
        int positionScreenX;
        int positionScreenY;
        int sizeX;
        int sizeY;
    
        void moveCamToPos();
        bool checkRangeMapCollisionX(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        bool checkRangeMapCollisionY(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
};
#endif