#include "creature.hpp"

Creature::Creature(Creature_type type, string name, char designation) : type(type), name(name), designation(designation)
{
    switch (type){
        case goblin:
            health = 25;
            damage = 5;
            protection = 5;
            break;
        case troll:
            health = 150;
            damage = 15;
            protection = 20;
            break;
        case elf_wizard:
            health = 25;
            damage = 15;
            protection = 0;
            break;
        case elf_archer:
            health = 25;
            damage = 10;
            protection = 0;
            break;
        case merchant:
            health = 50;
            damage = 10;
            protection = 10;
            break;
        case villager:
            health = 5;
            damage = 1;
            protection = 0;
            break;
        case boss:
            health = 300;
            damage = 20;
            protection = 25;
            break;
    }
}

Creature::~Creature() {}

string Creature::get_name(){
    return name;
}
Creature_type Creature::get_type(){
    return type;
}
unsigned int Creature::get_health(){
    return health;
}
unsigned int Creature::get_damage(){
    return damage;
}
unsigned int Creature::get_protection(){
    return protection;
}
char Creature::get_designation(){
    return designation;
}
void Creature::reduce_health(unsigned int value){
    health = (health > value) ? (health - value) : 0;
}
