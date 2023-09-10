#ifndef LEVEL_HPP
#define LEVEL_HPP

class Level{
    private:
        uint id;
        LevelBackground bg;
        GfxGroup* gfx;
        Player* player;
        std::vector<std::unique_ptr<Ennemy>> ennemyVector;
        std::array<std::unique_ptr<Projectile>, 32> playerProj = {};
        std::array<std::unique_ptr<Projectile>, 32> ennemyProj = {};

        int camX = 0;
	    int camY = 0;
	    int oldcamX = 0;
	    int oldcamY = 0;

        int sleep = 0;

        void setUpBg();
        void readLevelFile(std::string fileName);
        void addEnnemy(int type, int positionX, int positionY, int health, int id);
        int findIdEnnemy();
        void freeze();
        int updateEntities();
        void updateGfx();
        void checkProj();
        void checkHurtEnnemy();
        void checkHurtProj();
        void screenRefresh();
    public:
        Level(GfxGroup* gfxGroup, Player* play, std::string fileName);
        int update();
};

#endif