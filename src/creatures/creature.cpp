#include "creature.hpp"

Creature::Creature(Creature_type type, string name, char designation, Point pos)
    : type_(type), name_(name), designation_(designation), position_(pos) {
  switch (type_) {
  case goblin:
    health_ = 25;
    damage_ = 5;
    protection_ = 5;
    break;
  case troll:
    health_ = 150;
    damage_ = 15;
    protection_ = 20;
    break;
  case elf_wizard:
    health_ = 25;
    damage_ = 15;
    protection_ = 0;
    break;
  case elf_archer:
    health_ = 25;
    damage_ = 10;
    protection_ = 0;
    break;
  case merchant:
    health_ = 50;
    damage_ = 10;
    protection_ = 10;
    break;
  case villager:
    health_ = 5;
    damage_ = 1;
    protection_ = 0;
    break;
  case boss:
    health_ = 300;
    damage_ = 20;
    protection_ = 25;
    break;
  }
}

Creature::~Creature() {}

string Creature::GetName() { return name_; }
Creature_type Creature::GetType() { return type_; }
unsigned int Creature::GetHealth() { return health_; }
unsigned int Creature::GetDamage() { return damage_; }
unsigned int Creature::GetProtection() { return protection_; }
char Creature::GetDesignation() { return designation_; }
void Creature::ReduceHealth(unsigned int value) {
  health_ = (health_ > value) ? (health_ - value) : 0;
}

Point Creature::GetPosition(){ return position_; }

void Creature::Move(int add_x, int add_y, const game::Map & map){
  int new_x = position_.getX() + add_x;
  int new_y = position_.getY() + add_y;

  if (new_x >= 0 && new_x < game::kMapWidth && new_y >= 0 && new_y < game::kMapHeight &&
      map.IsWalkable(new_x, new_y)) {
    position_.changeX(new_x);
    position_.changeY(new_y);
  }
}

void Creature::SetPosition(const Point & point){
  position_.changeX(point.getX());
  position_.changeY(point.getY());
}