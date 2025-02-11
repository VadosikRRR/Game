#pragma once
#include <list>
#include "item.h"

using Iter = std::list<Item>::iterator;

class Inventory {
public:
    Inventory() = default;
    void Add(Item * item);
    void Drop();
    void EquipSword();
    void Next();
    void Previous();
    Item * GetCurrItem();
private:
    std::list<Item> container_;
    Iter currItem_;
    Sword * sword_ = nullptr;
};