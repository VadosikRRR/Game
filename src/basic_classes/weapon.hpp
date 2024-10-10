#pragma once
#include <iostream>
#include "item.hpp"

using namespace std;

namespace game{
    class Weapon : public Item{
    private:
        unsigned int damage_;
    public:
        Weapon(string name, unsigned int weight, bool is_thrown, unsigned int damage, Point pos = Point());
        virtual ~Weapon();
        unsigned int get_damage();
    };

    class Sword : public Weapon{
    public: 
        Sword(string name, unsigned int weight, bool is_thrown, unsigned int damage, Point pos = Point());
        virtual ~Sword();
    };

    class LongRangeWeapon : public Weapon{
    private:
        unsigned int range_;
    public:
        LongRangeWeapon(string name, unsigned int weight, bool is_thrown, unsigned int damage, unsigned int range, Point pos = Point());
        virtual ~LongRangeWeapon();
        unsigned int get_range();
    };

    class Bow : public LongRangeWeapon{
    public:
        Bow(string name, unsigned int weight, bool is_thrown, unsigned int damage, unsigned int range,Point pos = Point());
        ~Bow();

    };

    class Stick : public LongRangeWeapon{
    private:
        unsigned int mana_consumption_;
    public:
        Stick(string name,unsigned int weight, bool is_thrown,unsigned int damage,unsigned int range,unsigned int mana_consumption, Point pos = Point());
        ~Stick();
        unsigned int get_mana_consumption();
    };
}
