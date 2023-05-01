#ifndef GFXHANDLER_HPP
#define GFXHANDLER_HPP
class GfxHandler{
    class Sprite{
        private:
            std::string nameSprite;
            u8 sizeX;
            u8 sizeY;
            u8 screenNumber;
            s8 slotMemory;
            u8 arrayIndex;
        public:
            Sprite(std::string fileName, u8 xSize, u8 ySize, u8 screen, u8 index);
            void loadInMemory();
            void unloadInMemory();

            std::string getNameSprite(){return nameSprite;}
            u8 getSizeX(){return sizeX;}
            u8 getSizeY(){return sizeY;}
            s8 getSlotMemory(){return slotMemory;}
    };

    class Palette{
        private:
            std::string namePalette;
            u8 screenNumber;
            s8 slotMemory;
            u8 arrayIndex;
        public:
            Palette(std::string fileName, u8 screen, u8 index);
            void loadInMemory();
            void unloadInMemory();

            std::string getNamePalette(){return namePalette;}
            s8 getSlotMemory(){return slotMemory;}
    };

    public:
        Sprite spriteArray[2] = {Sprite("wade_w", 32, 32, 0, 0), Sprite("kirikou", 16, 32, 0, 1)};
        s16 spriteMemoryMap[128];
        Palette paletteArray[2] = {Palette("wade_w", 0, 0), Palette("kirikou", 0, 1)};
        s16 paletteMemoryMap[16];
};
#endif