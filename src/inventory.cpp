#include "inventory.h"

void Inventory::Add(Item* item) {
    if (item) {
        container_.push_back(*item);
        if (container_.size() == 1) {
            currItem_ = container_.begin();
        }
    }
}


void Inventory::Drop() {
    if (currItem_ != container_.end()) {
        currItem_ = container_.erase(currItem_); 
        if (currItem_ == container_.end() && !container_.empty()) {
            currItem_ = std::prev(container_.end());
        }
    }
}

void Inventory::Next() {
    if (!container_.empty()) {
        ++currItem_;
        if (currItem_ == container_.end()) {
            currItem_ = container_.begin();
        }
    }
}

void Inventory::Previous() {
    if (!container_.empty()) {
        if (currItem_ == container_.begin()) {
            currItem_ = std::prev(container_.end());
        } else {
            --currItem_;
        }
    }
}

Item * Inventory::GetCurrItem(){
    return dynamic_cast<Item*>(&(*currItem_));
}