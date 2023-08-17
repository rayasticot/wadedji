#ifndef LEVEL_HPP
#define LEVEL_HPP

class Level{
    private:
        uint id;
        LevelBackground bg;
        GfxGroup* gfx;
        Player* player;
        //std::vector<std::unique_ptr<Ennemy>> ennemyVector;

        int camX = 0;
	    int camY = 0;
	    int oldcamX = 0;
	    int oldcamY = 0;

        void setUpBg();
        void readLevelFile(std::string fileName);
    public:
        Level(GfxGroup* gfxGroup, Player* play, std::string fileName);
        int update();
};

#endif