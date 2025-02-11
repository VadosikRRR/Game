#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "inventory.h"

class Player {
public:
    Player();
    void EquipSword();
private:
    int health;
    // QString name;
    int attackPower;
    int basePower;
    Inventory inventory_;
    Sword * sword_ = nullptr;
};

#endif // PLAYER_H
