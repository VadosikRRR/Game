#include "weapons.hpp"
namespace game{
    Weapons::Weapons(string name, unsigned int weight, char symbol, bool is_thrown,  unsigned int damage, Point pos = Point()): Item(name,weight, symbol, is_thrown, pos), 
        damage_(damage) {}
    Weapons::~Weapons() {}
    unsigned int Weapons::get_damage(){
        return damage_;
    }

    Sword::Sword(string name, unsigned int weight, bool is_thrown, unsigned int damage, Point pos = Point()):
        Weapons(name, weight, '|', is_thrown, damage, pos) {}
    Sword::~Sword() {}

    LongRangeWeapon::LongRangeWeapon(string name, unsigned int weight, bool is_thrown, unsigned int damage, unsigned int range,Point pos = Point()):
        Weapons(name, weight, '|', is_thrown, damage, pos), range_(range) {}
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
