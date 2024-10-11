#include "Hero.hpp"

namespace game
{
    void Hero::CheckName(string name_hero)
    {
        name_ = (name_hero != "") ? name_hero : NAME_REPLACEMENT_IF_INCORRECT;
    }

    void Hero::PutFighterClassCharacteristics(fighter fighter_class_hero)
    {
        if (fighter_class_hero == warrior)
        {
            damage_ = START_DAMAGE_WARRIOR;
            mana_ = START_MAX_MANA_NO_WIZARD;
            max_mana_ = START_MAX_MANA_NO_WIZARD;
            protection_ = START_PROTECTION_WARRIOR;
        }

        else if (fighter_class_hero == archer)
        {
            damage_ = START_DAMAGE_NO_WARRIOR;
            mana_ = START_MAX_MANA_NO_WIZARD;
            max_mana_ = START_MAX_MANA_NO_WIZARD;
            protection_ = START_PROTECTION_NO_WARRIOR;
        }

        else
        {
            damage_ = START_DAMAGE_NO_WARRIOR;
            mana_ = START_MAX_MANA_WIZARD;
            max_mana_ = START_MAX_MANA_WIZARD;
            protection_ = START_PROTECTION_NO_WARRIOR;
        }
    }

    Hero::Hero(string name_hero, fighter fighter_class_hero) : designation_('@'), xp_(0), money_(0),
                                                               health_(START_MAX_HEALTH), max_health_(START_MAX_HEALTH), 
                                                               probability_of_hit_(START_PROBABILITY_OF_HIT), position_(Point(0, 0)), 
                                                               fighter_class_(fighter_class_hero), inventory_(Inventory(fighter_class_hero))
    {
        CheckName(name_hero);
        PutFighterClassCharacteristics(fighter_class_hero);
    }

    char Hero::GetDesignation()
    {
        return designation_;
    }

    unsigned int Hero::GetXp()
    {
        return xp_;
    }

    unsigned int Hero::GetMoney()
    {
        return money_;
    }

    unsigned int Hero::GetHealth()
    {
        return health_;
    }

    unsigned int Hero::GetMaxHealth()
    {
        return max_health_;
    }

    unsigned int Hero::GetMana()
    {
        return mana_;
    }

    unsigned int Hero::GetMaxMana()
    {
        return max_mana_;
    }

    unsigned int Hero::GetProtection()
    {
        return protection_;
    }

    unsigned int Hero::GetProbabilityOfHit()
    {
        return probability_of_hit_;
    }

    Point Hero::GetPosition()
    {
        return position_;
    }

    unsigned int Hero::GetDamage() 
    {
        return damage_;
    }

    string Hero::GetName()
    {
        return name_;
    }

    fighter Hero::GetFighterClass()
    {
        return fighter_class_;
    }

    Inventory &Hero::GetInventory() 
    {
        return inventory_;
    }

    void Hero::ReduceXp(unsigned int amount_xp)
    {
        xp_ = amount_xp > xp_ ? 0 : xp_ - amount_xp;
    }

    void Hero::ReduceMoney(unsigned int amount_money)
    {
        money_ = amount_money > money_ ? 0 : money_ - amount_money;
    }

    void Hero::ReduceHealth(unsigned int amount_health)
    {
        health_ = amount_health > health_ ? 0 : health_ - amount_health;
    }

    void Hero::ReduceMaxHealth(unsigned int amount_health)
    {
        max_health_ = amount_health > max_health_ ? 0 : max_health_ - amount_health;
    }

    void Hero::ReduceMana(unsigned int amount_mana)
    {
        mana_ = amount_mana > mana_ ? 0 : mana_ - amount_mana;
    }

    void Hero::ReduceMaxMana(unsigned int amount_mana)
    {
        max_mana_ = amount_mana > max_mana_ ? 0 : max_mana_ - amount_mana;
    }

    void Hero::ReduceProtection(unsigned int amount_protection)
    {
        protection_ = amount_protection > protection_ ? 0 : protection_ - amount_protection;
    }

    void Hero::ReduceProbabilityOfHit(unsigned int change_in_probability)
    {
        probability_of_hit_ = change_in_probability > probability_of_hit_ ? 0 : probability_of_hit_ - change_in_probability;
    }

    void Hero::ReduceDamage(unsigned int amount_damage) 
    {
        damage_ = amount_damage > damage_ ? 0 : damage_ - amount_damage;
    }

    void Hero::IncreaseXp(unsigned int amount_xp)
    {
        xp_ += amount_xp;
    }

    void Hero::IncreaseMoney(unsigned int amount_money)
    {
        money_ += amount_money;
    }

    void Hero::IncreaseHealth(unsigned int amount_health)
    {
        health_ = amount_health + health_ > max_health_ ? max_health_ : amount_health + health_;
    }

    void Hero::IncreaseMaxHealth(unsigned int amount_health)
    {
        max_health_ += amount_health;
    }

    void Hero::IncreaseMana(unsigned int amount_mana)
    {
        mana_ = amount_mana + mana_ > max_mana_ ? max_mana_ : amount_mana + mana_;
    }

    void Hero::IncreaseMaxMana(unsigned int amount_mana)
    {
        max_mana_ += amount_mana;
    }

    void Hero::IncreaseProtection(unsigned int amount_protection)
    {
        protection_ += amount_protection;
    }

    void Hero::IncreaseProbabilityOfHit(unsigned int change_in_probability)
    {
        probability_of_hit_ = change_in_probability + probability_of_hit_ > 100 ? 100 : change_in_probability + probability_of_hit_;
    }

    void Hero::IncreaseDamage(unsigned int amount_damage) {
        damage_ += amount_damage;
    }

    void Hero::Move(int add_x, int add_y, const game::Map &map)
    {
        int new_x = position_.getX() + add_x;

        int new_y = position_.getY() + add_y;

        if (new_x >= 0 && new_x < kMapHeight && new_y >= 0 && new_y < kMapWidth && map.IsWalkable(new_x, new_y))
        {
            position_.changeX(new_x);
            position_.changeX(new_y);
        }
    }

    void Hero::SetPositions(const Point &point)
    {
        position_.changeX(point.getX());
        position_.changeX(point.getY());
    }
}
