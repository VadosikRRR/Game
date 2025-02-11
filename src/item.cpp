#include "item.h"

Sword::Sword(int damage) : damage_(damage) {}

int Sword::GetDamage() {return damage_;}

void CollectiblesItem::Add() {count_++;}

void CollectiblesItem::Drop() {
    if(count_ > 1){
        count_--;
    }
}

int CollectiblesItem::GetCount() const {return count_;}


