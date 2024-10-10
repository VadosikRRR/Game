#pragma once
#include <iostream>
#include "item.hpp"

using namespace std;

namespace game{
    class Weapon : Item{
    private:
        int damage_;
    public:
        Weapon(string name, int weight, bool is_thrown, int damage, Point pos = Point());
        virtual ~Weapon();
        int get_damage();
    };

    class Sword : Weapon{
    public: 
        Sword(string name, int weight, bool is_thrown, int damage, Point pos = Point());
        virtual ~Sword();
    };

    class LongRangeWeapon : Weapon{
    private:
        int range_;
    public:
        LongRangeWeapon(string name, int weight, bool is_thrown, int damage, int range,Point pos = Point());
        virtual ~LongRangeWeapon();
        int get_range();
    };
    class Bow : LongRangeWeapon{
    public:
        Bow(string name, int weight, bool is_thrown, int damage, int range,Point pos = Point());
        ~Bow();

    };
    class Stick : LongRangeWeapon{
    public:
        Stick(string name, int weight, bool is_thrown, int damage, int range, Point pos = Point());
        ~Stick();
    };
}
