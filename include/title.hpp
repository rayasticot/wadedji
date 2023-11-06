#ifndef TITLE_HPP
#define TITLE_HPP

class Title{
    private:
        int frame = 0;
        int cursor = 0;
        int profile = 0;
        int action = 0;
        std::array<int, 3> started = {-1, -1, -1};
        std::array<int, 3> alive = {-1, -1, -1};
        std::array<int, 3> level = {-1, -1, -1};
        static constexpr std::array<int, 5> cursorPositionsX = {72, 72, 72, 24, 64};
        static constexpr std::array<int, 5> cursorPositionsY = {64, 96, 128, 32, 64};

        void loadProfileInfo();
        int startScreen(bool fade);
        int profileScreen();
        int menuScreen();
        void loadSprites();
        void update();
        void end();
        void introNul();
    public:
        bool getAction();
        bool getProfil(){ return profile; };
        Title();
};

#endif