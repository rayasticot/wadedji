#ifndef CINEMATIC_HPP
#define CINEMATIC_HPP

class CinematicFrame{
    private:
        std::string image;
        std::string bgName;
        bool created = false;
        bool loaded = false;
    public:
        int time;
        int scrollEffect;
        int transition;
        int addCalcX(int timer);
        int addCalcY(int timer);
        void create();
        void destroy();
        void load();
        void unLoad();
        CinematicFrame(std::string imag, std::string name, int tim, int scroll, int trans);
        ~CinematicFrame();
};

class Cinematic{
    private:
        std::vector<CinematicFrame> frames;
        int timer = 0;
        int currentFrame = 0;
    public:
        Cinematic(std::string filename);
        void play();
};

#endif