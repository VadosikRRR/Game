#include <iostream>
#include <vector>
#include "item.hpp"
#include "../main_hero/fighter.hpp"
#pragma once

using namespace std;

class Inventory{
private:
    int max_weight;
    int current_weight;
    vector<Item> stuff;
    ~Inventory();
public:
    Inventory(fighter hero_type);
    void put_item(Item & item);
    void drop_item(int index);
    void use_item(int index);
    void increase_max_weight(int val);
};