#include "Hero.hpp"

namespace game
{
    void Hero::check_name(string name_hero)
    {
        name = (name_hero != "") ? name_hero : NAME_REPLACEMENT_IF_INCORRECT;
    }

    void Hero::put_fighter_class_characteristics(fighter fighter_class_hero)
    {
        if (fighter_class_hero == warrior)
        {
            mana = START_MAX_MANA_NO_WIZARD;
            max_mana = START_MAX_MANA_NO_WIZARD;
            protection = START_PROTECTION_WARRIOR;
        }

        else if (fighter_class_hero == archer)
        {
            // Тут обязательно будут крутые характеристики, но пока нет
            mana = START_MAX_MANA_NO_WIZARD;
            max_mana = START_MAX_MANA_NO_WIZARD;
            protection = START_PROTECTION_NO_WARRIOR;
        }

        else
        {
            mana = START_MAX_MANA_WIZARD;
            max_mana = START_MAX_MANA_WIZARD;
            protection = START_PROTECTION_NO_WARRIOR;
        }
    }

    Hero::Hero(string name_hero, fighter fighter_class_hero) : designation('@'), xp(0), money(0),
                                                               health(START_MAX_HEALTH), max_health(START_MAX_HEALTH), probability_of_hit(START_PROBABILITY_OF_HIT), position(Point(0, 0)), fighter_class(fighter_class_hero)
    {
        check_name(name_hero);
        put_fighter_class_characteristics(fighter_class_hero);
    }

    char Hero::get_designation()
    {
        return designation;
    }

    unsigned int Hero::get_xp()
    {
        return xp;
    }

    unsigned int Hero::get_money()
    {
        return money;
    }

    unsigned int Hero::get_health()
    {
        return health;
    }

    unsigned int Hero::get_max_health()
    {
        return max_health;
    }

    unsigned int Hero::get_mana()
    {
        return mana;
    }

    unsigned int Hero::get_max_mana()
    {
        return max_mana;
    }

    unsigned int Hero::get_protection()
    {
        return protection;
    }

    unsigned int Hero::get_probability_of_hit()
    {
        return probability_of_hit;
    }

    Point Hero::get_position()
    {
        return position;
    }

    string Hero::get_name()
    {
        return name;
    }

    fighter Hero::get_fighter_class()
    {
        return fighter_class;
    }

    void Hero::reduce_xp(unsigned int amount_xp)
    {
        xp = amount_xp > xp ? 0 : xp - amount_xp;
    }

    void Hero::reduce_money(unsigned int amount_money)
    {
        money = amount_money > money ? 0 : money - amount_money;
    }

    void Hero::reduce_health(unsigned int amount_health)
    {
        health = amount_health > health ? 0 : health - amount_health;
    }

    void Hero::reduce_max_health(unsigned int amount_health)
    {
        max_health = amount_health > max_health ? 0 : max_health - amount_health;
    }

    void Hero::reduce_mana(unsigned int amount_mana)
    {
        mana = amount_mana > mana ? 0 : mana - amount_mana;
    }

    void Hero::reduce_max_mana(unsigned int amount_mana)
    {
        max_mana = amount_mana > max_mana ? 0 : max_mana - amount_mana;
    }

    void Hero::reduce_protection(unsigned int amount_protection)
    {
        protection = amount_protection > protection ? 0 : protection - amount_protection;
    }

    void Hero::reduce_probability_of_hit(unsigned int change_in_probability)
    {
        probability_of_hit = change_in_probability > probability_of_hit ? 0 : probability_of_hit - change_in_probability;
    }

    void Hero::increase_xp(unsigned int amount_xp)
    {
        xp += amount_xp;
    }

    void Hero::increase_money(unsigned int amount_money)
    {
        money += amount_money;
    }

    void Hero::increase_health(unsigned int amount_health)
    {
        health = amount_health + health > max_health ? max_health : amount_health + health;
    }

    void Hero::increase_max_health(unsigned int amount_health)
    {
        max_health += amount_health;
    }

    void Hero::increase_mana(unsigned int amount_mana)
    {
        mana = amount_mana + mana > max_mana ? max_mana : amount_mana + mana;
    }

    void Hero::increase_max_mana(unsigned int amount_mana)
    {
        max_mana += amount_mana;
    }

    void Hero::increase_protection(unsigned int amount_protection)
    {
        protection += amount_protection;
    }

    void Hero::increase_probability_of_hit(unsigned int change_in_probability)
    {
        probability_of_hit = change_in_probability + probability_of_hit > 100 ? 100 : change_in_probability + probability_of_hit;
    }

    void Hero::move(int add_x, int add_y, const game::Map &map)
    {
        int new_x = position.get_x() + add_x;

        int new_y = position.get_y() + add_y;

        if (new_x >= 0 && new_x < kMapHeight && new_y >= 0 && new_y < kMapWidth && map.IsWalkable(new_x, new_y))
        {
            position.change_x(new_x);
            position.change_y(new_y);
        }
    }

    void Hero::SetPositions(const Point &point)
    {
        position.change_x(point.get_x());
        position.change_y(point.get_y());
    }
}
