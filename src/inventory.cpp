#include "inventory.h"
#include <memory>
#include "item.h"
#include <vector>

Inventory::Inventory() : currentIndex_(-1) {
}

void Inventory::Add(const std::shared_ptr<Item>& item) {
    if (item) {
        container_.push_back(item);
        if (currentIndex_ == -1) {
            currentIndex_ = 0;
        }
    }
}

std::shared_ptr<Item> Inventory::Drop()
{
    if (currentIndex_ != -1 && !container_.empty()) {
        std::shared_ptr<Item> droppedItem = container_[currentIndex_];
        container_.erase(container_.begin() + currentIndex_);
        if (container_.empty()) {
            currentIndex_ = -1;
        } else if (currentIndex_ >= container_.size()) {
            currentIndex_ = container_.size() - 1;
        }
        return droppedItem; // Возвращаем выброшенный предмет
    }
    return nullptr; // Если инвентарь пуст, возвращаем nullptr
}

void Inventory::Next() {
    if (!container_.empty()) {
        if (currentIndex_ == -1) {
            currentIndex_ = 0; // Если текущий предмет не выбран, выбираем первый
        } else {
            currentIndex_ = (currentIndex_ + 1) % container_.size(); // Переход к следующему предмету
        }
    }
}

void Inventory::Previous() {
    if (!container_.empty()) {
        if (currentIndex_ == -1) {
            currentIndex_ = container_.size() - 1; // Если текущий предмет не выбран, выбираем последний
        } else {
            currentIndex_ = (currentIndex_ - 1 + container_.size()) % container_.size(); // Переход к предыдущему предмету
        }
    }
}

std::shared_ptr<Item> Inventory::GetCurrItem()
{
    if (currentIndex_ != -1 && currentIndex_ < container_.size()) {
        return container_[currentIndex_];
    }
    return nullptr;
}

std::vector<std::shared_ptr<Item>> Inventory::GetItems() const
{
    return container_;
}

int Inventory::GetCurrentIndex() const
{
    return currentIndex_;
}
