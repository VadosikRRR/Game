#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QPoint>
#include <memory>
#include "inventory.h"

class Player {
public:
    Player();
    void EquipSword();
    int GetX() const;
    int GetY() const;
    void SetPosition(int x, int y);
    void PickUpItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<Item> DropItem();
    void UseItem();
    std::vector<std::shared_ptr<Item>> GetItems() const;
    int GetCurrentItemIndex() const;
    void SelectNextItem();
    void SelectPreviousItem();
    std::shared_ptr<Item> GetCurrentItem();
private:
    int health;
    // QString name;
    QPoint position_;
    int attackPower;
    int basePower;
    Inventory inventory_;
    std::shared_ptr<Sword> sword_ = nullptr;
};

#endif // PLAYER_H
