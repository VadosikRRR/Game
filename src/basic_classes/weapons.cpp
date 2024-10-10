#include "weapon.hpp"
namespace game{
    Weapon::Weapon(string name, unsigned int weight, bool is_thrown,  unsigned int damage, Point pos = Point()): Item(name,weight, is_thrown, pos), 
        damage_(damage) {}
    Weapon::~Weapon() {}
    unsigned int Weapon::get_damage(){
        return damage_;
    }

    Sword::Sword(string name, unsigned int weight, bool is_thrown, unsigned int damage, Point pos = Point()):
        Weapon(name, weight, is_thrown, damage, pos) {}
    Sword::~Sword() {}

    LongRangeWeapon::LongRangeWeapon(string name, unsigned int weight, bool is_thrown, unsigned int damage, unsigned int range,Point pos = Point()):
        Weapon(name, weight, is_thrown, damage, pos), range_(range) {}
    LongRangeWeapon::~LongRangeWeapon() {}
    unsigned int LongRangeWeapon::get_range(){
        return range_;
    }

    Bow::Bow(string name, unsigned int weight, bool is_thrown, unsigned int damage, unsigned int range,Point pos = Point()):
        LongRangeWeapon(name, weight, is_thrown, damage, range, pos) {}
    Bow::~Bow() {}

    Stick::Stick(string name, unsigned int weight, bool is_thrown, unsigned int damage, unsigned int range, unsigned int mana_consumption, Point pos = Point()) :
        LongRangeWeapon(name, weight, is_thrown, damage, range, pos), mana_consumption_(mana_consumption){}
    Stick::~Stick() {}
    unsigned int Stick::get_mana_consumption(){
        return mana_consumption_;
    }
}