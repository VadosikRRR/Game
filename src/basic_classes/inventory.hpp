#pragma once
#include <iostream>
#include <vector>
#include "item.hpp"
#include "../basic_classes/fighter.hpp"

using namespace std;

namespace game{
    class Inventory{
    private:
        unsigned int max_weight;
        unsigned int current_weight;
        vector<Item> stuff;
        ~Inventory();
    public:
        Inventory(fighter hero_type);
        void put_item(Item & item);
        void drop_item(int index);
        void use_item(int index);
        void increase_max_weight(int val);
        unsigned int get_max_weight();
        unsigned int get_current_weight();
    };
}