#ifndef INTERFACE_HPP
#define INTERFACE_HPP

class ItemPositions{
    /*
        Positions des différents objets sur l'écran du bas
    */
    public:
        static constexpr std::array<int, 6> positions_x = {160, 208, 112, 160, 80, 16};
        static constexpr std::array<int, 6> positions_y = {0, 48, 48, 96, 128, 128};
};

class InterfaceItem{
    /*
        Classe pour un objet de l'interface
    */
    private:
        ItemPositions itemPositions; // Positions des différents objets

        bool started = false; // Si l'objet est créé
        int spriteId; // Identifiant du sprite
        int defaultPositionX; // Position par défaut X
        int defaultPositionY; // Position par défaut Y
    public:
        int itemId; // Identifiant de l'objet
        int positionX; // Position X de l'objet
        int positionY; // Position Y de l'objet

        void start(int posX, int posY, int spriteid, int itemid);
        virtual ~InterfaceItem();
        // Si l'objet est touché par un point
        bool isTouched(int px, int py);
        // Replace l'objet à sa position par défaut
        void resetPos();
        // Met à jour le sprite
        void updateSprite();
};

class Interface{
    /*
        Classe de tout l'inventaire
    */
    private:
        ItemPositions itemPositions; // Positions des différents objets
        ItemInfo itemInfo; // Infos des objets

        std::array<InterfaceItem, 5> items; // Objets de l'inventaire

        int currentHeld = -1; // Objet actuellement en train d'être tenu
        int heldTimer = 0; // Temps depuis que l'objet est touché
        int heldPosX = 0; // Position X de l'objet tenu
        int heldPosY = 0; // Position Y de l'objet tenu

        int lastItem = 0; // Dernier item touché
        std::string itemDesc; // Description de l'objet

        int last_px = -1; // Dernière position X du stylet
        int last_py = -1; // Dernière position Y du stylet
        touchPosition touch; // Structure pour les données du stylet

        // Lis la description d'un objet
        void readItemDesc(std::string fileName);
        // Dessine la description à l'écran
        void drawItemDesc(int item);
        // Desinne la vie à l'écran
        void drawHealth(int health);
        // Desinne la mana à l'écran
        void drawMana(int mana, int maxMana);
        // Dessine l'argent à l'écran
        void drawFcfa(int fcfa, int level);
        // Met à jour le système d'inventaire du bas
        bool updateHolding(std::array<int, 5>* inventory, int *fcfa);
    public:
        void start();
        void destroy();
        bool update(int health, int mana, int maxMana, int *fcfa, std::array<int, 5>* inventory, int level);
        ~Interface();
};

#endif