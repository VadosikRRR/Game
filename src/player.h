#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QPoint>
#include "inventory.h"

class Player {
public:
    Player();
    void EquipSword();
    int GetX() const;
    int GetY() const;
    void SetPosition(int x, int y);
private:
    int health;
    // QString name;
    QPoint position_;
    int attackPower;
    int basePower;
    Inventory inventory_;
    Sword * sword_ = nullptr;
};

#endif // PLAYER_H
