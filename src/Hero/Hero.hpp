#pragma once
#include "../basic_classes/fighter.hpp"
#include "../basic_classes/inventory.hpp"
#include "../basic_classes/point.hpp"
#include "../constants/Hero_constants.hpp"
#include "../map/map.h"
#include <iostream>

using namespace std;

namespace game {
class Hero {
private:
  char designation_;
  unsigned int xp_;
  unsigned int money_;
  unsigned int health_;
  unsigned int max_health_;
  unsigned int mana_;
  unsigned int max_mana_;
  unsigned int probability_of_hit_;
  unsigned int protection_;
  unsigned int damage_;
  Point position_;
  string name_;
  fighter fighter_class_;
  Inventory inventory_;

  void CheckName(string name_hero);
  void PutFighterClassCharacteristics(fighter fighter_class_hero);

public:
  Hero(string name_hero, fighter fighter_class_hero);

  char GetDesignation();
  unsigned int GetXp();
  unsigned int GetMoney();
  unsigned int GetHealth();
  unsigned int GetMaxHealth();
  unsigned int GetMana();
  unsigned int GetMaxMana();
  unsigned int GetProtection();
  unsigned int GetProbabilityOfHit();
  unsigned int GetDamage();
  Point GetPosition();
  string GetName();
  fighter GetFighterClass();
  Inventory &GetInventory();

  void ReduceXp(unsigned int amount_xp);
  void ReduceMoney(unsigned int amount_money);
  void ReduceHealth(unsigned int amount_health);
  void ReduceMaxHealth(unsigned int amount_health);
  void ReduceMana(unsigned int amount_mana);
  void ReduceMaxMana(unsigned int amount_mana);
  void ReduceProtection(unsigned int amount_protection);
  void ReduceProbabilityOfHit(unsigned int change_in_probability);
  void ReduceDamage(unsigned int amount_damage);

  void IncreaseXp(unsigned int amount_xp);
  void IncreaseMoney(unsigned int amount_money);
  void IncreaseHealth(unsigned int amount_health);
  void IncreaseMaxHealth(unsigned int amount_health);
  void IncreaseMana(unsigned int amount_mana);
  void IncreaseMaxMana(unsigned int amount_mana);
  void IncreaseProtection(unsigned int amount_protection);
  void IncreaseProbabilityOfHit(unsigned int change_in_probability);
  void IncreaseDamage(unsigned int amount_damage);

  void Move(int add_x, int add_y, const game::Map &map);
  void SetPositions(const Point &point);
};
} // namespace game
