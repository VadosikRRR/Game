#pragma once
#include "item.hpp"
#include <iostream>

using namespace std;

namespace game {
class Weapons : public Item {
private:
  unsigned int damage_;

public:
  Weapons(string name, unsigned int weight, char symbol, bool is_thrown,
          unsigned int damage, Point pos = Point());
  virtual ~Weapons();
  unsigned int get_damage();
};

class Sword : public Weapons {
public:
  Sword(string name, unsigned int weight, bool is_thrown, unsigned int damage,
        Point pos = Point());
  virtual ~Sword();
};

class LongRangeWeapon : public Weapons {
private:
  unsigned int range_;

public:
  LongRangeWeapon(string name, unsigned int weight, bool is_thrown,
                  unsigned int damage, unsigned int range, Point pos = Point());
  virtual ~LongRangeWeapon();
  unsigned int get_range();
};

class Bow : public LongRangeWeapon {
public:
  Bow(string name, unsigned int weight, bool is_thrown, unsigned int damage,
      unsigned int range, Point pos = Point());
  ~Bow();
};

class Stick : public LongRangeWeapon {
private:
  unsigned int mana_consumption_;

public:
  Stick(string name, unsigned int weight, bool is_thrown, unsigned int damage,
        unsigned int range, unsigned int mana_consumption, Point pos = Point());
  ~Stick();
  unsigned int get_mana_consumption();
};
} // namespace game