#include "player.h"
#include <QFont>

Player::Player()
    : health(100), basePower(10), inventory_(), attackPower(basePower) {
}

void Player::EquipSword() {
    Item * currItem = inventory_.GetCurrItem();
    if (currItem) {
        Sword* sword = dynamic_cast<Sword*>(currItem);
        if (sword) {
            sword_ = sword; 
            attackPower = basePower + sword_->GetDamage();
            inventory_.Drop();
        }
    }
}
int Player::GetX() const {
    return position_.x();
}

int Player::GetY() const {
    return position_.y();
}

void Player::SetPosition(int x, int y) {
    position_.setX(x);
    position_.setY(y);
}
