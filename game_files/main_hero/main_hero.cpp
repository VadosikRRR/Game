#include "main_hero.hpp"


void main_hero::check_name(string name_hero) {
    name = (name_hero != "") ? name_hero : "Easy hero";
}

void main_hero::put_fighter_class_characteristics(fighter fighter_class_hero) {
    if (fighter_class_hero == warrior) {
        mana = 50;
        max_mana = 50;
        protection = 10;
    }
        
    else if (fighter_class_hero == archer) {
        // Тут обязательно будут крутые характеристики, но пока нет
        mana = 50;
        max_mana = 50;
        protection = 5;
    }

    else {
        mana = 100;
        max_mana = 100;
        protection = 5;
    }
}

main_hero::main_hero(string name_hero, fighter fighter_class_hero): designation('@'), xp(0), money(0),
        health(100), max_health(100), probability_of_hit(100), fighter_class(fighter_class_hero) {
    check_name(name_hero);
    put_fighter_class_characteristics(fighter_class_hero);
}

int main_hero::get_xp() {
    return xp;
}

int main_hero::get_money() {
    return money;
}

int main_hero::get_health() {
    return health;
}

int main_hero::get_max_health() {
    return max_health;
}

int main_hero::get_mana() {
    return mana;
}

int main_hero::get_max_mana() {
    return max_mana;
}

int main_hero::get_protection() {
    return protection;
}

int main_hero::get_probability_of_hit() {
    return probability_of_hit;
}

string main_hero::get_name() {
    return name;
}

fighter main_hero::get_fighter_class() {
    return fighter_class;
}
