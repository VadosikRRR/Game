#include "player.h"
#include "item.h"
#include <memory>
#include <vector>

Player::Player(const QString &name)
    : base_health_(100), health_(100), max_health_(100), base_power_(10),
    attack_power_(10), attack_probability_(PLAYER_ATTACK_PROBABILITY), name_(std::move(name)) {}

void Player::EquipSword() {
    std::shared_ptr<Item> const current_item = inventory_.GetCurrItem();
    if (current_item) {
        std::shared_ptr<Sword> const sword = std::dynamic_pointer_cast<Sword>(current_item);
        if (sword) {
            sword_ = sword;
            attack_power_ = base_power_ + sword_->GetDamage();
            inventory_.Drop();
        }
    }
}

void Player::EquipArmor() {
    std::shared_ptr<Item> const current_item = inventory_.GetCurrItem();
    if (current_item) {
        std::shared_ptr<Armor> const armor = std::dynamic_pointer_cast<Armor>(current_item);
        if (armor) {
            armor_ = armor;
            max_health_ = base_health_ + armor_->GetDefense();
            if (health_ - base_health_ > armor_->GetDefense()) {
                health_ = max_health_;
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
  std::shared_ptr<Item> const curr_item = inventory_.GetCurrItem();
  if (!curr_item) {
      return;
  }
  if (curr_item->GetName().left(6) == "MedKit") {
      std::shared_ptr<CollectiblesItem> medkit = std::dynamic_pointer_cast<CollectiblesItem>(
          curr_item);
      if (!medkit) {
          return;
      }
      health_ += kMedKitHeal;
      if (health_ > max_health_) {
          health_ = max_health_;
      }
      medkit->Drop();
      if (medkit->GetCount() == 0) {
          inventory_.Drop();
      }
  }
  if (curr_item->GetName().left(5) == "Sword") {
      if (sword_) {
          PickUpItem(sword_);
      }
      EquipSword();
  }
  if (curr_item->GetName().left(5) == "Armor") {
      if (armor_) {
          PickUpItem(armor_);
      }
      EquipArmor();
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
int Player::GetHealth() const { return health_; }

int Player::GetMaxHealth() const { return max_health_; }

int Player::GetAttackPower() const { return attack_power_; }

int Player::GetAttackProbability() const { return attack_probability_; }

void Player::SetHealth(int new_health) {
    if(new_health > max_health_) {
        health_ = max_health_;
        return;
    }
    else if (new_health < 0) {
        health_ = 0;
        return;
    }

    health_ = new_health;
}

void Player::ReduceHealthForHit(int d_health) {
    SetHealth(health_ - d_health);
}
