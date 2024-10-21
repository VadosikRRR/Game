#pragma once
#include "../basic_classes/fighter.hpp"
#include "item.hpp"
#include <iostream>
#include <vector>

using namespace std;

namespace game {
class Inventory {
private:
  unsigned int max_weight;
  unsigned int current_weight;
  vector<Item> stuff;

public:
  ~Inventory();
  Inventory(fighter hero_type);
  void put_item(Item &item);
  void drop_item(int index);
  void use_item(int index);
  void increase_max_weight(int val);
  unsigned int get_max_weight();
  unsigned int get_current_weight();
};
} // namespace game
