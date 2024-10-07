#include <iostream>
#include "fighter.hpp"

using namespace std;

class main_hero {
    char designation;
    int xp;
    int money;
    int health;
    int max_health;
    int mana;
    int max_mana;
    float probability_of_hit;
    int protection;
    string name;
    fighter fighter_class;

    void check_name(string name_hero);
    void put_fighter_class_characteristics(fighter fighter_class_hero);

    public:
        main_hero(string name_hero, fighter fighter_class_hero);
        int get_xp();
        int get_money();
        int get_health();
        int get_max_health();
        int get_mana();
        int get_max_mana();
        int get_protection();
        int get_probability_of_hit();
        string get_name();
        fighter get_fighter_class();
};
