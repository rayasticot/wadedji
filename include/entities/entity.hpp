#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity{
    /*
        Classe mère de toutes les entités dans le monde.
    */
    protected:
        int spriteId; // Identifiant du prite de l'entité
        bool spriteCreated = false; // Si le sprite est créé
        int sprite; // Sprite de l'entité
        int palette; // Palette de l'entité
        float positionX; // Position X
        float positionY; // Position Y
        float speedX; // Vitesse X
        float speedY; // Vitesse Y
        float accelerationX; // Acceleration X
        float accelerationY; // Acceleration Y
        int positionScreenX; // Position X sur l'écran
        int positionScreenY; // Position Y sur l'écran
        int sizeX; // Taille X
        int sizeY; // Taille Y
        int offsetX = 0; // Offset entre la position X et l'endroit où le sprite est réellement affiché
        int shakeX = 0; // Tremblement de la caméra X
        int shakeY = 0; // Tremblement de la caméra Y
        bool flagNotCenterX; // Si la caméra n'est pas au centre sur l'axe X
        bool flagNotCenterY; // Si la caméra n'est pas au centre sur l'axe Y
        bool blink = false; // Si le sprite doit s'afficher ou non

        // Applique la gravité à l'entité
        void updateGravity();
        // Déplace le sprite de l'entité à la position relative à la caméra
        void moveScreenPos(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
        // Détecte si l'entité touche un plafond ou du sol
        bool checkRangeMapCollisionX(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        // Détecte si l'entité touche un mur
        bool checkRangeMapCollisionY(u8 collisionMapSlot, u16 startX, u16 startY, u8 pixelRange);
        // Vérifie la collision d'une autre objet avec l'entité
        bool checkCollision(int posX, int posY, int sizeX, int sizeY);
        // Joue un son à une hauteur aléatoire
        static void playSoundRandomPitch(mm_word sound);
    public:
        int getPosX(){ return positionX; };
        int getPosY(){ return positionY; };
        int getSizeX(){ return sizeX; };
        int getSizeY(){ return sizeY; };
        int getId(){ return spriteId; };
        // Déplace la caméra sur l'entité
        void moveCamToPos(int* camPositionX, int* camPositionY, int screenSizeX, int screenSizeY, int sizeXModif, int sizeYModif);
        // Met à jour le sprite
        void updateSprite(int camPositionX, int camPositionY, int screenSizeX, int screenSizeY);
        // Détruit l'entité
        virtual ~Entity(){};
};

#endif