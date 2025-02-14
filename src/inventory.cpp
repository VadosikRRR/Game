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
    std::shared_ptr<Item> droppedItem = container_[currentIndex_];
    container_.erase(container_.begin() + currentIndex_);
    if (container_.empty()) {
      currentIndex_ = -1;
    } else if (currentIndex_ >= container_.size()) {
      currentIndex_ = container_.size() - 1;
    }
    return droppedItem;
  }
  return nullptr;
}

void Inventory::Next() {
  if (!container_.empty()) {
    if (currentIndex_ == -1) {
      currentIndex_ = 0;
    } else {
      currentIndex_ = (currentIndex_ + 1) % container_.size();
    }
  }
}

void Inventory::Previous() {
  if (!container_.empty()) {
    if (currentIndex_ == -1) {
      currentIndex_ = container_.size() - 1;
    } else {
      currentIndex_ =
          (currentIndex_ - 1 + container_.size()) % container_.size();
    }
  }
}

std::shared_ptr<Item> Inventory::GetCurrItem() {
  if (currentIndex_ != -1 && currentIndex_ < container_.size()) {
    return container_[currentIndex_];
  }
  return nullptr;
}

std::vector<std::shared_ptr<Item>> Inventory::GetItems() const {
  return container_;
}

int Inventory::GetCurrentIndex() const { return currentIndex_; }
