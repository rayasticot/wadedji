#ifndef ITEM_HPP
#define ITEM_HPP

class ItemInfo{
    public:
        static constexpr std::array<int, 5> effectIndex =
            {0, 0, 2, 2, 3};
        static constexpr std::array<int, 5> rarityIndex =
            {2, 2, 2, 2, 2};
        static constexpr std::array<int, 5> valueIndex =
            {1000, 10000, 10000, 6000, 8000};
};

#endif