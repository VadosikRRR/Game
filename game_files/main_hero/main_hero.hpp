#pragma once
#include <iostream>
#include "../basic_classes/fighter.hpp"
#include "../basic_classes/point.hpp"
#include "../constants/main_hero_constants.hpp"

using namespace std;

class main_hero {
private:
    char designation;
    int xp;
    int money;
    int health;
    int max_health;
    int mana;
    int max_mana;
    float probability_of_hit;
    int protection;
    Point position;
    string name;
    fighter fighter_class;

    void check_name(string name_hero);
    void put_fighter_class_characteristics(fighter fighter_class_hero);

public:
    main_hero(string name_hero, fighter fighter_class_hero);

    char get_designation();
    unsigned int get_xp();
    unsigned int get_money();
    unsigned int get_health();
    unsigned int get_max_health();
    unsigned int get_mana();
    unsigned int get_max_mana();
    unsigned int get_protection();
    unsigned int get_probability_of_hit();
    Point get_position();
    string get_name();
    fighter get_fighter_class();

    void reduce_xp(unsigned int amount_xp);
    void reduce_money(unsigned int amount_money);
    void reduce_health(unsigned int amount_health);
    void reduce_max_health(unsigned int amount_health);
    void reduce_mana(unsigned int amount_mana);
    void reduce_max_mana(unsigned int amount_mana);
    void reduce_protection(unsigned int amount_protection);
    void reduce_probability_of_hit(unsigned int change_in_probability);

    void increase_xp(unsigned int amount_xp);
    void increase_money(unsigned int amount_money);
    void increase_health(unsigned int amount_health);
    void increase_max_health(unsigned int amount_health);
    void increase_mana(unsigned int amount_mana);
    void increase_max_mana(unsigned int amount_mana);
    void increase_protection(unsigned int amount_protection);
    void increase_probability_of_hit(unsigned int change_in_probability);

    void move_up();
    void move_down();
    void move_right();
    void move_left();
};
