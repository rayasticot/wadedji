#ifndef ITEM_HPP
#define ITEM_HPP

class ItemInfo{
    /*
        Classe constante qui indique différentes valeurs
        relatives au objets
    */
    public:
        static constexpr std::array<int, 5> effectIndex =
            {0, 0, 2, 2, 3}; // Indique si le type de l'objet
        static constexpr std::array<int, 5> rarityIndex =
            {2, 2, 2, 2, 2}; // Indique la rareté de l'objet
        static constexpr std::array<int, 5> valueIndex =
            {1000, 10000, 10000, 6000, 8000}; // Indique la valeur de l'objet
};

#endif