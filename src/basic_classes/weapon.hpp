#pragma once
#include <iostream>
#include "item.hpp"

using namespace std;

namespace game{
    class Weapon : public Item{
    private:
        int damage_;
    public:
        Weapon(string name, int weight, bool is_thrown, int damage, Point pos = Point());
        virtual ~Weapon();
        int get_damage();
    };

    class Sword : public Weapon{
    public: 
        Sword(string name, int weight, bool is_thrown, int damage, Point pos = Point());
        virtual ~Sword();
    };

    class LongRangeWeapon : public Weapon{
    private:
        int range_;
    public:
        LongRangeWeapon(string name, int weight, bool is_thrown, int damage, int range,Point pos = Point());
        virtual ~LongRangeWeapon();
        int get_range();
    };
    
    class Bow : public LongRangeWeapon{
    public:
        Bow(string name, int weight, bool is_thrown, int damage, int range,Point pos = Point());
        ~Bow();

    };

    class Stick : public LongRangeWeapon{
    private:
        unsigned int mana_consumption_;
    public:
        Stick(string name, int weight, bool is_thrown, int damage, int range, int mana_consumption, Point pos = Point());
        ~Stick();
        unsigned int get_mana_consumption();
    };
}
