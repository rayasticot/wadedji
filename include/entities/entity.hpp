#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity{
    protected:
        int spriteId;
        bool spriteCreated = false;
        int sprite;
        int palette;
        float positionX;
        float positionY;
        float speedX;
        float speedY;
        float accelerationX;
        float accelerationY;
        int positionScreenX;
        int positionScreenY;
        int sizeX;
        int sizeY;
        int shakeX = 0;
        int shakeY = 0;
        bool flagNotCenterX;
        bool flagNotCenterY;
        bool blink = false;

        void updateGravity();
        void moveScreenPos(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
        bool checkRangeMapCollisionX(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        bool checkRangeMapCollisionY(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        bool checkCollision(int posX, int posY, int sizeX, int sizeY);
        static void playSoundRandomPitch(mm_word sound);
    public:
        int getPosX(){ return positionX; };
        int getPosY(){ return positionY; };
        int getSizeX(){ return sizeX; };
        int getSizeY(){ return sizeY; };
        int getId(){ return spriteId; };
        void moveCamToPos(int* camPositionX, int* camPositionY, int screenSizeX, int screenSizeY, int sizeXModif, int sizeYModif);
        void updateSprite(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
        virtual ~Entity(){};
};

#endif