#include "inventory.hpp"
#pragma once

Inventory::Inventory(fighter hero_type) {
    // Добавить в инвентарь начальное оружие каждого класса; TODO: реализовать классы оружия,меча, лука, посоха
};
void Inventory::put_item(Item &item)
{
    if (item.get_weight() + current_weight <= max_weight)
    {
        current_weight += item.get_weight();
        stuff.push_back(item);
    }
    // else что-то пошло не так
}
void Inventory::drop_item(int index)
{
    current_weight -= stuff[index].get_weight();
    stuff.erase(stuff.begin() + index);
}
void Inventory::use_item(int index)
{
    stuff[index].execute();
}
void Inventory::increase_max_weight(int val)
{
    max_weight += val;
}
Inventory::~Inventory()
{
    stuff.clear();
    stuff.shrink_to_fit();
}