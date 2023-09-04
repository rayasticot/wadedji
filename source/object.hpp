#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object{
    protected:
        int spriteId;
        int sprite;
        int palette;
        float positionX;
        float positionY;
        int positionScreenX;
        int positionScreenY;
        int sizeX;
        int sizeY;
        int shakeX = 0;
        int shakeY = 0;
        bool flagNotCenterX;
        bool flagNotCenterY;
        bool blink = false;

        void moveScreenPos(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
        bool checkRangeMapCollisionX(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        bool checkRangeMapCollisionY(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        bool checkCollision(int posX, int posY, int sizeX, int sizeY);
    public:
        int getPosX(){ return positionX; };
        int getPosY(){ return positionY; };
        int getSizeX(){ return sizeX; };
        int getSizeY(){ return sizeY; };
        void moveCamToPos(int* camPositionX, int* camPositionY, int screenSizeX, int screenSizeY, int sizeXModif, int sizeYModif);
        virtual void update() = 0;
        void updateSprite(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
};

#endif