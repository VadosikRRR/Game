#include "inventory.hpp"
#include "fighter.hpp"
#include "weapons.hpp"
#include "../constants/inventory_constants.hpp"

namespace game{
    Inventory::Inventory(fighter hero_type){
        max_weight = INITIAL_INVENTORY_MAX_WEIGHT;
        stuff.reserve(2);
        switch (hero_type){
            case warrior:
                stuff[0] = Sword(STANDART_WARRIOR_SWORD_NAME, STANDART_WARRIOR_SWORD_WEIGHT, false, STANDART_WARRIOR_SWORD_DAMAGE);
                current_weight += stuff[0].get_weight();
                stuff[1] = Bow(STANDART_WARRIOR_BOW_NAME, STANDART_WARRIOR_BOW_WEIGHT, false, STANDART_WARRIOR_BOW_DAMAGE, STANDART_WARRIOR_BOW_RANGE);
                current_weight += stuff[1].get_weight();
                break;
            case archer:
                stuff[0] = Sword(STANDART_ARCHER_SWORD_NAME, STANDART_ARCHER_SWORD_WEIGHT, false, STANDART_ARCHER_SWORD_DAMAGE);
                current_weight += stuff[0].get_weight();
                stuff[1] = Bow(STANDART_ARCHER_BOW_NAME, STANDART_ARCHER_BOW_WEIGHT, false, STANDART_ARCHER_BOW_DAMAGE, STANDART_ARCHER_BOW_RANGE);
                current_weight += stuff[1].get_weight();
                break;
            case wizard:
                stuff[0] = Sword(STANDART_WIZARD_SWORD_NAME, STANDART_WIZARD_SWORD_WEIGHT, false, STANDART_WIZARD_SWORD_DAMAGE);
                current_weight += stuff[0].get_weight();
                stuff[1] = Stick(STANDART_STICK_NAME, STANDART_STICK_WEIGHT, false, STANDART_STICK_DAMAGE, STANDART_STICK_RANGE, STANDART_STICK_MANA_CONSUMPTION);
                current_weight += stuff[1].get_weight();
                break;
        }
    };
    void Inventory::put_item(Item & item){
        if (item.get_weight() + current_weight <= max_weight){
            current_weight += item.get_weight();
            stuff.push_back(item);
        }
    }
    void Inventory::drop_item(int index){
        current_weight -= stuff[index].get_weight();
        stuff.erase(stuff.begin() + index);
    }
    void Inventory::use_item(int index){
        stuff[index].execute();
    }
    void Inventory::increase_max_weight(int val){
        max_weight += val;
    }
    Inventory::~Inventory(){
        stuff.clear();
        stuff.shrink_to_fit();
    }
    unsigned int Inventory::get_max_weight(){
        return max_weight;
    }
    unsigned int Inventory::get_current_weight(){
        return current_weight;
    }
}
