#include "player.h"
#include <QFont>

Player::Player()
    : health(100), attackPower(10) {

    setText("@");
    QFont font("Courier", 24, QFont::Bold);
    setFont(font);
}
Player::Player(QString name): Player() {
    this->name = name;
}
