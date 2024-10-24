#pragma once
#include "creature_type.hpp"
#include "../basic_classes/point.hpp"
#include "../map/map.h"
#include <iostream>
using namespace std;

class Creature {
private:
  unsigned int health_;
  unsigned int damage_;
  unsigned int protection_;
  unsigned int probability_of_hit;
  string name_;
  char designation_;
  Creature_type type_;
  Point position_;

public:
  Creature(Creature_type type, string name, char designation, Point pos = Point(0,0));
  virtual ~Creature();
  string GetName();
  Creature_type GetType();
  unsigned int GetHealth();
  unsigned int GetDamage();
  unsigned int GetProtection();
  unsigned int GetProbabilityOfHit();
  char GetDesignation();
  Point GetPosition();
  void Move(int add_x, int add_y, const game::Map &map);
  void SetPosition(const Point &point);
  void ReduceHealth(unsigned int value);
};