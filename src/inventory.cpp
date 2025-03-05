#include "inventory.h"
#include "item.h"
#include <memory>
#include <vector>

Inventory::Inventory() : current_index_(-1) {}

void Inventory::Add(const std::shared_ptr<Item> &item)
{
    if (!item) {
        return;
    }
    std::shared_ptr<CollectiblesItem> collectible = std::dynamic_pointer_cast<CollectiblesItem>(
        item);
    if (collectible) {
        for (auto &existing_item : container_) {
            std::shared_ptr<CollectiblesItem> existing_collectible
                = std::dynamic_pointer_cast<CollectiblesItem>(existing_item);
            if (existing_collectible->GetName().section('(', 0, 0).trimmed()
                == collectible->GetName().section('(', 0, 0).trimmed()) {
                existing_collectible->Add();
                return;
            }
        }
    }
    container_.push_back(item);
    if (current_index_ == -1) {
        current_index_ = 0;
    }
}

std::shared_ptr<Item> Inventory::Drop() {
  if (current_index_ != -1 && !container_.empty()) {
    std::shared_ptr<Item> dropped_item = container_[current_index_];
    container_.erase(container_.begin() + current_index_);
    if (container_.empty()) {
      current_index_ = -1;
    } else if (current_index_ >= static_cast<int>(container_.size())) {
        current_index_ = static_cast<int>(container_.size()) - 1;
    }
    return dropped_item;
  }
  return nullptr;
}

void Inventory::Next() {
  if (!container_.empty()) {
    if (current_index_ == -1) {
      current_index_ = 0;
    } else {
        current_index_ = (current_index_ + 1) % static_cast<int>(container_.size());
    }
  }
}

void Inventory::Previous() {
  if (!container_.empty()) {
    if (current_index_ == -1) {
          current_index_ = static_cast<int>(container_.size()) - 1;
    } else {
      current_index_ =
            (current_index_ - 1 + static_cast<int>(container_.size())) % static_cast<int>(container_.size());
    }
  }
}

std::shared_ptr<Item> Inventory::GetCurrItem() {
    if (current_index_ != -1 && current_index_ < static_cast<int>(container_.size())) {
    return container_[current_index_];
  }
  return nullptr;
}

std::vector<std::shared_ptr<Item>> Inventory::GetItems() const {
  return container_;
}

int Inventory::GetCurrentIndex() const { return current_index_; }
