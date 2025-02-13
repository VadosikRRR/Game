#include "player.h"
#include "item.h"
#include <memory>
#include <vector>

Player::Player(const QString& name)
    : health(100)
    , basePower(10)
    , attackPower(basePower)
    , name(std::move(name))
{}

void Player::EquipSword() {
    std::shared_ptr<Item> const currItem = inventory_.GetCurrItem();
    if (currItem) {
        std::shared_ptr<Sword> const sword = std::dynamic_pointer_cast<Sword>(currItem);
        if (sword) {
            sword_ = sword;
            attackPower = basePower + sword_->GetDamage();
            inventory_.Drop();
        }
    }
}
int Player::GetX() const
{
    return position_.x();
}

int Player::GetY() const
{
    return position_.y();
}

void Player::SetPosition(int x, int y) {
    position_.setX(x);
    position_.setY(y);
}

void Player::PickUpItem(const std::shared_ptr<Item>& item) {
    if (item) {
        inventory_.Add(item);
    }
}

std::shared_ptr<Item> Player::DropItem()
{
    return inventory_.Drop();
}

void Player::UseItem() {
    std::shared_ptr<Item> const currItem = inventory_.GetCurrItem();
    if (currItem) {
        if (currItem->GetName() == "MedKit") {
            health += kMedKitHeal;
            if (health > 100) { health = 100;
}
            inventory_.Drop();
        }
    }
}
std::vector<std::shared_ptr<Item>> Player::GetItems() const
{
    return inventory_.GetItems();
}

int Player::GetCurrentItemIndex() const
{
    return inventory_.GetCurrentIndex();
}

void Player::SelectNextItem() {
    inventory_.Next();
}

void Player::SelectPreviousItem() {
    inventory_.Previous();
}
std::shared_ptr<Item> Player::GetCurrentItem()
{
    return inventory_.GetCurrItem();
}
int Player::GetHealth() const
{
    return health;
}

int Player::GetAttackPower() const
{
    return attackPower;
}
