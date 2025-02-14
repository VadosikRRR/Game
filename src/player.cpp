#include "player.h"
#include "item.h"
#include <memory>
#include <vector>

Player::Player(const QString &name)
    : health(100), baseHealth_(100), maxHealth_(100), basePower(10),
      attackPower(10), name(std::move(name)) {}

void Player::EquipSword() {
  std::shared_ptr<Item> const currItem = inventory_.GetCurrItem();
  if (currItem) {
    std::shared_ptr<Sword> const sword =
        std::dynamic_pointer_cast<Sword>(currItem);
    if (sword) {
      sword_ = sword;
      attackPower = basePower + sword_->GetDamage();
      inventory_.Drop();
    }
  }
}

void Player::EquipArmor() {
  std::shared_ptr<Item> const currItem = inventory_.GetCurrItem();
  if (currItem) {
    std::shared_ptr<Armor> const armor =
        std::dynamic_pointer_cast<Armor>(currItem);
    if (armor) {
      armor_ = armor;
      maxHealth_ = baseHealth_ + armor_->GetDefense();
      if (health - baseHealth_ > armor_->GetDefense()) {
        health = maxHealth_;
      }
      inventory_.Drop();
    }
  }
}

int Player::GetX() const { return position_.x(); }

int Player::GetY() const { return position_.y(); }

void Player::SetPosition(int x, int y) {
  position_.setX(x);
  position_.setY(y);
}

void Player::PickUpItem(const std::shared_ptr<Item> &item) {
  if (item) {
    inventory_.Add(item);
  }
}

std::shared_ptr<Item> Player::DropItem() { return inventory_.Drop(); }

void Player::UseItem() {
  std::shared_ptr<Item> const currItem = inventory_.GetCurrItem();
  if (currItem) {
    if (currItem->GetName() == "MedKit") {
      health += kMedKitHeal;
      if (health > maxHealth_) {
        health = maxHealth_;
      }
      inventory_.Drop();
    }
    if (currItem->GetName().left(5) == "Sword") {
      if (sword_) {
        PickUpItem(sword_);
      }
      EquipSword();
    }
    if (currItem->GetName().left(5) == "Armor") {
      if (armor_) {
        PickUpItem(armor_);
      }
      EquipArmor();
    }
  }
}
std::vector<std::shared_ptr<Item>> Player::GetItems() const {
  return inventory_.GetItems();
}

int Player::GetCurrentItemIndex() const { return inventory_.GetCurrentIndex(); }

void Player::SelectNextItem() { inventory_.Next(); }

void Player::SelectPreviousItem() { inventory_.Previous(); }
std::shared_ptr<Item> Player::GetCurrentItem() {
  return inventory_.GetCurrItem();
}
int Player::GetHealth() const { return health; }

int Player::GetMaxHealth() const { return maxHealth_; }

int Player::GetAttackPower() const { return attackPower; }
