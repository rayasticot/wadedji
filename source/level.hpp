#ifndef LEVEL_HPP
#define LEVEL_HPP

class Level{
    private:
        uint id;
        LevelBackground bg;
        std::unique_ptr<GfxGroup> gfx;
        Player* player;
        std::vector<std::unique_ptr<Ennemy>> ennemyVector;

        void readLevelFile(std::string fileName);
        void update();
    public:
        Level(std::unique_ptr<GfxGroup> gfxGroup, std::string fileName);
};

#endif