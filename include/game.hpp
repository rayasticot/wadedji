#ifndef GAME_HPP
#define GAME_HPP

class Game{
    private:
        Player* player;
        GfxGroup gfx;
        int profile = 0;
        int difficulty = 1;
        int currentLevel = 0;
        uint music;
        uint oldMusic = 22960;
        std::string oldGfx = "N";
        //void update();
        std::string findLevel(std::string fileName, int levelId);
        std::string getGfx(std::string fileName);
        uint getMusic(std::string fileName);
        void loadSave(bool continuer, int profil);
        void resetSave(int profil);
    public:
        Game(bool continuer, int profil);
        ~Game();
};

#endif