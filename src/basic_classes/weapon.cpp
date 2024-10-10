#include "weapon.hpp"
namespace game{
    Weapon::Weapon(string name, int weight, bool is_thrown,  int damage, Point pos = Point()): Item(name,weight, is_thrown, pos), 
        damage_(damage) {}
    Weapon::~Weapon() {}
    int Weapon::get_damage(){
        return damage_;
    }

    Sword::Sword(string name, int weight, bool is_thrown, int damage, Point pos = Point()):
        Weapon(name, weight, is_thrown, damage, pos) {}
    Sword::~Sword() {}

    LongRangeWeapon::LongRangeWeapon(string name, int weight, bool is_thrown, int damage, int range,Point pos = Point()):
        Weapon(name, weight, is_thrown, damage, pos), range_(range) {}
    LongRangeWeapon::~LongRangeWeapon() {}
    int LongRangeWeapon::get_range(){
        return range_;
    }

    Bow::Bow(string name, int weight, bool is_thrown, int damage, int range,Point pos = Point()):
        LongRangeWeapon(name, weight, is_thrown, damage, range, pos) {}
    Bow::~Bow() {}

    Stick::Stick(string name, int weight, bool is_thrown, int damage, int range, int mana_consumption, Point pos = Point()) :
        LongRangeWeapon(name, weight, is_thrown, damage, range, pos), mana_consumption_(mana_consumption){}
    Stick::~Stick() {}
    unsigned int Stick::get_mana_consumption(){
        return mana_consumption_;
    }


    

}