#ifndef GAME_HPP
#define GAME_HPP

class Game{
    private:
        Player* player;
        GfxGroup gfx;
        int currentLevel = 0;
        uint music;
        uint oldMusic = 22960;
        std::string oldGfx = "N";
        //void update();
        std::string findLevel(std::string fileName, int levelId);
        std::string getGfx(std::string fileName);
        uint getMusic(std::string fileName);
    public:
        Game(int levelId);
};

#endif