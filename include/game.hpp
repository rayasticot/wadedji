#ifndef GAME_HPP
#define GAME_HPP

class Game{
    /*
        Classe principale du jeu. Gère tout une partie du jeu.
        Commence en chargeant une sauvegarde.
    */
    private:
        Player* player; // Pointeur vers l'entité du joueur
        GfxGroup gfx; // Objet pour gérer tout les sprites
        int profile = 0; // Profile sélectionné. (0-2)
        int difficulty = 1; // Difficulté sélectionnée
        int currentLevel = 0; // Indicateur du niveau actuel
        uint music; // Musique actuellement jouée
        uint oldMusic = 22960; // Précedente musique
        std::string oldGfx = "N"; // Précedent arrière-plan
        //void update();

        // Récupère le nom du fichier du niveau à partir du fichier contenant
        // la liste de ceux-ci et le nombre indiquant le niveau actuel.
        std::string findLevel(std::string fileName, int levelId);
        // Récupère le nom du fichier des sprites de ce niveau.
        std::string getGfx(std::string fileName);
        // Récupère la musique d'un certain niveau
        uint getMusic(std::string fileName);
        // Remet la sauvegarde du profil indiqué à zéro si continuer est faux
        // sinon la charge directement
        void loadSave(bool continuer, int profil);
        // Remet une sauvegarde à zéro
        void resetSave(int profil);
    public:
        // Fonction principale de la partie du jeu
        Game(bool continuer, int profil);
        // Détruit tout les éléments de la classe
        ~Game();
};

#endif