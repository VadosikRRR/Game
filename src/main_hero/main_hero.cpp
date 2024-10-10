#include "main_hero.hpp"

void main_hero::check_name(string name_hero) {
    name = (name_hero != "") ? name_hero : NAME_REPLACEMENT_IF_INCORRECT;
}

void main_hero::put_fighter_class_characteristics(fighter fighter_class_hero) {
    if (fighter_class_hero == warrior) {
        mana = START_MAX_MANA_NO_WIZARD;
        max_mana = START_MAX_MANA_NO_WIZARD;
        protection = START_PROTECTION_WARRIOR;
    }
        
    else if (fighter_class_hero == archer) {
        // Тут обязательно будут крутые характеристики, но пока нет
        mana = START_MAX_MANA_NO_WIZARD;
        max_mana = START_MAX_MANA_NO_WIZARD;
        protection = START_PROTECTION_NO_WARRIOR;
    }

    else {
        mana = START_MAX_MANA_WIZARD;
        max_mana = START_MAX_MANA_WIZARD;
        protection = START_PROTECTION_NO_WARRIOR;
    }
}

main_hero::main_hero(string name_hero, fighter fighter_class_hero): designation(DESIGNATION_MAIN_HERO), xp(0), money(0),
        health(START_MAX_HEALTH), max_health(START_MAX_HEALTH), probability_of_hit(START_PROBABILITY_OF_HIT), position(Point(0, 0)), fighter_class(fighter_class_hero) {
    check_name(name_hero);
    put_fighter_class_characteristics(fighter_class_hero);
}

char main_hero::get_designation() {
    return designation;
}

unsigned int main_hero::get_xp() {
    return xp;
}

unsigned int main_hero::get_money() {
    return money;
}

unsigned int main_hero::get_health() {
    return health;
}

unsigned int main_hero::get_max_health() {
    return max_health;
}

unsigned int main_hero::get_mana() {
    return mana;
}

unsigned int main_hero::get_max_mana() {
    return max_mana;
}

unsigned int main_hero::get_protection() {
    return protection;
}

unsigned int main_hero::get_probability_of_hit() {
    return probability_of_hit;
}

Point main_hero::get_position() {
    return position;
}

string main_hero::get_name() {
    return name;
}

fighter main_hero::get_fighter_class() {
    return fighter_class;
}

void main_hero::reduce_xp(unsigned int amount_xp) {
    xp = amount_xp > xp ? 0 : xp - amount_xp;
}

void main_hero::reduce_money(unsigned int amount_money) {
    money = amount_money > money ? 0 : money - amount_money;
}

void main_hero::reduce_health(unsigned int amount_health) {
    health = amount_health > health ? 0 : health - amount_health;
}

void main_hero::reduce_max_health(unsigned int amount_health) {
    max_health = amount_health > max_health ? 0 : max_health - amount_health;
}

void main_hero::reduce_mana(unsigned int amount_mana) {
    mana = amount_mana > mana ? 0 : mana - amount_mana;
}

void main_hero::reduce_max_mana(unsigned int amount_mana) {
    max_mana = amount_mana > max_mana ? 0 : max_mana - amount_mana;
}

void main_hero::reduce_protection(unsigned int amount_protection) {
    protection = amount_protection > protection ? 0 : protection - amount_protection;
}

void main_hero::reduce_probability_of_hit(unsigned int change_in_probability) {
    probability_of_hit = change_in_probability > probability_of_hit ? 0 : probability_of_hit - change_in_probability;
}

void main_hero::increase_xp(unsigned int amount_xp) {
    xp += amount_xp;
}

void main_hero::increase_money(unsigned int amount_money) {
    money += amount_money;
}

void main_hero::increase_health(unsigned int amount_health) {
    health = amount_health + health > max_health ? max_health : amount_health + health;
}

void main_hero::increase_max_health(unsigned int amount_health) {
    max_health += amount_health;
}

void main_hero::increase_mana(unsigned int amount_mana) {
    mana = amount_mana + mana > max_mana ? max_mana : amount_mana + mana;
}

void main_hero::increase_max_mana(unsigned int amount_mana) {
    max_mana += amount_mana;
}

void main_hero::increase_protection(unsigned int amount_protection) {
    protection += amount_protection;
}

void main_hero::increase_probability_of_hit(unsigned int change_in_probability) {
    probability_of_hit = change_in_probability + probability_of_hit > 100 ? 100 : change_in_probability + probability_of_hit;
}

void main_hero::move_up() {
    position.change_y(position.get_y() + 1);
}

void main_hero::move_down() {
    position.change_y(position.get_y() - 1);
}

void main_hero::move_right() {
    position.change_x(position.get_x() + 1);
}

void main_hero::move_up() {
    position.change_x(position.get_x() - 1);
}
