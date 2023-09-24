#ifndef SPRITE_HPP
#define SPRITE_HPP

class Sprite{
    private:
        std::string nameSprite;
        u8 sizeX;
        u8 sizeY;
        u8 screenNumber;
        s8 slotMemory;
        bool loaded = false;
    public:
        Sprite(std::string fileName, u8 xSize, u8 ySize, u8 screen, u8 slot);
        void loadSpr();
        void unloadSpr();
        //~Sprite();

        //std::string getNameSprite(){return nameSprite;}
        u8 getSizeX(){return sizeX;}
        u8 getSizeY(){return sizeY;}
        s8 getSlotMemory(){return slotMemory;}
};

class Palette{
    private:
        std::string namePalette;
        u8 screenNumber;
        s8 slotMemory;
        bool loaded = false;
    public:
        Palette(std::string fileName, u8 screen, u8 slot);
        void loadPal();
        void unloadPal();
        //~Palette();

        //std::string getNamePalette(){return namePalette;}
        s8 getSlotMemory(){return slotMemory;}
};

class GfxGroup{
    private:
        std::vector<Sprite> spriteVector;
        std::vector<Palette> paletteVector;
    public:
        //GfxGroup(std::string fileName, u8 screen, int sprStart, int palStart);
        void readGfxFile(std::string fileName, u8 screen, int sprStart, int palStart);
        void loadSpr(uint id);
        void unloadSpr(uint id);
        void loadPal(uint id);
        void unloadPal(uint id);
};

#endif