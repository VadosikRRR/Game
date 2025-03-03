#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <memory>
#include <vector>

class Inventory {
public:
  Inventory();
  void Add(const std::shared_ptr<Item> &item);
  std::shared_ptr<Item> Drop();
  void EquipSword();
  void Next();
  void Previous();
  std::shared_ptr<Item> GetCurrItem();
  std::vector<std::shared_ptr<Item>> GetItems() const;
  int GetCurrentIndex() const;

private:
  std::vector<std::shared_ptr<Item>> container_;
  int currentIndex_;
};

#endif // INVENTORY_H
