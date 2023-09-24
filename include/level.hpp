#ifndef LEVEL_HPP
#define LEVEL_HPP

class PoolItem{
    public:
        int itemId;
        int dropRate;
        PoolItem(int id, int rate);
};

class DropPool{
    private:
        std::vector<PoolItem> items;
        bool loaded = false;
    public:
        void loadPoolFile(std::string fileName);
        int giveItem();
};

class Level{
    private:
        uint id;
        std::array<DropPool, 2> pools = {};
        LevelBackground bg;
        GfxGroup* gfx;
        Player* player;

        std::vector<std::unique_ptr<Ennemy>> ennemyVector;
        std::array<std::unique_ptr<Projectile>, 24> playerProj = {};
        std::array<std::unique_ptr<Projectile>, 24> ennemyProj = {};
        std::array<std::unique_ptr<GroundItem>, 16> groundItems = {};

        int camX = 0;
	    int camY = 0;
	    int oldcamX = 0;
	    int oldcamY = 0;

        int sleep = 0;

        void setUpBg();
        void readLevelFile(std::string fileName);
        void addEnnemy(int type, int positionX, int positionY, int health, int id);
        int findIdEnnemy();
        int findIdItem();
        void freeze();
        void updateEntities();
        void updateGfx();
        void checkProj();
        void checkGroundItem();
        void checkHurtEnnemy();
        void checkHurtProj();
        void screenRefresh();
    public:
        Level(GfxGroup* gfxGroup, Player* play, std::string fileName);
        int update();
};

#endif