#include "item.h"

Sword::Sword(int damage) : damage_(damage) {}

int Sword::GetDamage() const
{
    return damage_;
}

void CollectiblesItem::Add() {count_++;}

void CollectiblesItem::Drop() {
    if(count_ > 1){
        count_--;
    }
}

int CollectiblesItem::GetCount() const
{
    return count_;
}

QString Sword::GetName() const
{
    return QString("Sword (%1)").arg(damage_) ;
}

QString MedKit::GetName() const
{
    return "MedKit";
}
