#ifndef LEVEL_HPP
#define LEVEL_HPP

class PoolItem{
    /*
        Objet dans une pool qui peut apparaître
    */
    public:
        int itemId; // ID de l'objet
        int dropRate; // Pourcentage de chance que l'objet apparaisse
        // Créé l'objet
        PoolItem(int id, int rate);
};

class DropPool{
    /*
        Classe gèrant un pool d'objets qui peuvent apparaitre
    */
    private:
        std::vector<PoolItem> items; // Vecteur de chaque objet possible
        bool loaded = false; // Si un fichier pool a été chargé.
    public:
        // Charge un fichier pool
        void loadPoolFile(std::string fileName);
        // Sélectionne un objet à faire apparaître dans sa pool
        int giveItem();
};

class Level{
    /*
        Classe gèrant un seul niveau du jeu.
    */
    private:
        uint id;
        std::array<DropPool, 3> pools = {}; // Objet contenant les drops de chaque ennemis
        DropPool groundItemPool; // Objet contenant les drops qui ne viennent pas d'ennemis
        LevelBackground bg; // Objet pour gérer les arrières-plans
        Player* player; // Pointeur vers le joueur
        ActiveEffect activeEffect; // Objet pour gérer les effets actifs du joueur

        std::vector<std::unique_ptr<Ennemy>> ennemyVector; // Vecteur contenant chacun des ennemis
        std::array<std::unique_ptr<Projectile>, 24> playerProj = {}; // Vecteur contenant les projectiles du joueur
        std::array<std::unique_ptr<Projectile>, 24> ennemyProj = {}; // Vecteur contenant les projectiles des ennemis
        std::array<std::unique_ptr<GroundItem>, 16> groundItems = {}; // Vecteur contenant les objets au sol

        int camX = 0; // Position X de la caméra
	    int camY = 0; // Position Y de la caméra
	    int oldcamX = 0; // Position X précédente de la caméra
	    int oldcamY = 0; // Position Y précédente de la caméra

        int sleep = 0; // Temps à attendre en frame avant de recommencer la partie
        bool boss = false; // Indique si le niveau contient un boss

        // Met en place les arrières-plans
        void setUpBg();
        // Lit un fichier de niveau
        void readLevelFile(std::string fileName);
        // Ajoute un ennemi au vecteur
        void addEnnemy(int type, int positionX, int positionY, int health, int id);
        // Trouve une place vide dans l'array des projectiles ennemis
        int findIdEnnemy();
        // Trouve une place vide dans l'array des objets au sol
        int findIdItem();
        // Trouve une place vide dans l'array des projectiles du joueur
        int findIdPlayer();
        // Met en pause le jeu par la durée indiqué par la variable sleep 
        void freeze();
        // Met à jour les entités
        void updateEntities();
        // Met à jour les sprites et les arrières-plans
        void updateGfx();
        // Vérifie si un projectile ennemi doit être créé
        void checkProj();
        // Vérifie si un projectile joueur doit être créé
        void checkPlayerProj();
        // Vérifie si le joueur a touché un objet au sol
        void checkGroundItem();
        // Vérifie si un ennemi a touché le joueur
        void checkHurtEnnemy();
        // Vérifie si un projectile du joueur a touché quelque chose
        void checkHurtPlayerProj();
        // Vérifie si un projectile ennemi a touché quelque chose
        void checkHurtProj();
        // Raffraichi l'écran
        void screenRefresh();
        // Retire tout les projectiles du joueur et les remplace par des projectiles de sang
        void placeBlood();
    public:
        // Crée le niveau
        Level(Player* play, std::string fileName);
        // Met à jour le niveau
        int update();
};

#endif