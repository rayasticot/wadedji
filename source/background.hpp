#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

class Background{
    private:
        std::string bgFile;
        std::string bgName;
        float scrollSpeed;
        int sizeX;
        int sizeY;
        u8 bgLayer;
        bool loaded = false;
        bool created = false;
        bool set = false;
    public:
        void setBg(std::string file, std::string name, float speed, int sizex, int sizey, u8 layer);
        void loadBg();
        void unLoadBg();
        void createBg();
        void deleteBg();
        void scrollBg(int positionX, int positionY);
        ~Background();
};

class LevelBackground{
    private:
        Background bg[4];
        bool created[4] = {false, false, false, false};
        std::string colMapName;
        int colMapSizeX;
        int colMapSizeY;
        bool colMapActive;
    public:
        //LevelBackground();
        void readBackgroundFile(std::string bgFile);
        void loadBg(uint id);
        void unLoadBg(uint id);
        void createBg(uint id);
        void deleteBg(uint id);
        void scrollBg(uint id, int positionX, int positionY);
        void loadCol();
        void unLoadCol();
        int getMapSizeX(){return colMapSizeX;};
        int getMapSizeY(){return colMapSizeY;};
        ~LevelBackground();
};

#endif