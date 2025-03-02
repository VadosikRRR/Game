#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"
#include <QPoint>
#include <QString>
#include <memory>

#define PLAYER_ATTACK_PROBABILITY 75

class Player {
public:
  explicit Player(const QString &name = "Олег");

  int GetX() const;
  int GetY() const;
  int GetHealth() const;
  int GetMaxHealth() const;
  int GetAttackPower() const;
  int GetAttackProbability() const;
  int GetCurrentItemIndex() const;
  std::vector<std::shared_ptr<Item>> GetItems() const;
  std::shared_ptr<Item> GetCurrentItem();

  void SetPosition(int x, int y);

  void EquipSword();
  void EquipArmor();
  void PickUpItem(const std::shared_ptr<Item> &item);
  std::shared_ptr<Item> DropItem();
  void UseItem();
  void SelectNextItem();
  void SelectPreviousItem();

  void ReduceHealthForHit(int d_health);

private:
  int baseHealth_;
  int health_;
  int maxHealth_;
  QString name;
  QPoint position_;
  int attackPower;
  int basePower;
  int attackProbability_;
  Inventory inventory_;
  std::shared_ptr<Sword> sword_ = nullptr;
  std::shared_ptr<Armor> armor_ = nullptr;

  void SetHealth(int new_health);
};

#endif // PLAYER_H
