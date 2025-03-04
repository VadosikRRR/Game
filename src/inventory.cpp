#include "inventory.h"
#include "item.h"
#include <memory>
#include <vector>

Inventory::Inventory() : currentIndex_(-1) {}

void Inventory::Add(const std::shared_ptr<Item> &item) {
  if (item) {
    container_.push_back(item);
    if (currentIndex_ == -1) {
      currentIndex_ = 0;
    }
  }
}

std::shared_ptr<Item> Inventory::Drop() {
  if (currentIndex_ != -1 && !container_.empty()) {
    std::shared_ptr<Item> dropped_item = container_[currentIndex_];
    container_.erase(container_.begin() + currentIndex_);
    if (container_.empty()) {
      currentIndex_ = -1;
    } else if (currentIndex_ >= static_cast<int>(container_.size())) {
        currentIndex_ = static_cast<int>(container_.size()) - 1;
    }
    return dropped_item;
  }
  return nullptr;
}

void Inventory::Next() {
  if (!container_.empty()) {
    if (currentIndex_ == -1) {
      currentIndex_ = 0;
    } else {
        currentIndex_ = (currentIndex_ + 1) % static_cast<int>(container_.size());
    }
  }
}

void Inventory::Previous() {
  if (!container_.empty()) {
    if (currentIndex_ == -1) {
          currentIndex_ = static_cast<int>(container_.size()) - 1;
    } else {
      currentIndex_ =
            (currentIndex_ - 1 + static_cast<int>(container_.size())) % static_cast<int>(container_.size());
    }
  }
}

std::shared_ptr<Item> Inventory::GetCurrItem() {
    if (currentIndex_ != -1 && currentIndex_ < static_cast<int>(container_.size())) {
    return container_[currentIndex_];
  }
  return nullptr;
}

std::vector<std::shared_ptr<Item>> Inventory::GetItems() const {
  return container_;
}

int Inventory::GetCurrentIndex() const { return currentIndex_; }
