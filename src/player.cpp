#include "player.h"
#include <QFont>

Player::Player()
    : health(100), attackPower(10) {
}
Player::Player(QString name): Player() {
    this->name = name;
}
