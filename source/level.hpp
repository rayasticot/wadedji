#ifndef LEVEL_HPP
#define LEVEL_HPP

class Level{
    private:
        uint id;
        LevelBackground bg;
        std::unique_ptr<GfxGroup> gfx;
        std::vector<std::unique_ptr<Object>> objectVector;

        void readLevelFile(std::string fileName);
        void update();
    public:
        Level(std::unique_ptr<GfxGroup> gfxGroup, std::string fileName);
};

#endif