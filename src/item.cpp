#include "item.h"

Sword::Sword(int damage) : damage_(damage) {}

int Sword::GetDamage() const { return damage_; }

void CollectiblesItem::Add()
{
    count_++;
}

void CollectiblesItem::Drop() {
    if (count_ > 0) {
        count_--;
    }
}

int CollectiblesItem::GetCount() const { return count_; }

QString Sword::GetName() const { return QString("Sword (%1)").arg(damage_); }

QString MedKit::GetName() const
{
    return QString("MedKit (%1)").arg(count_);
}

char Sword::GetTile() const { return '!'; }

char MedKit::GetTile() const { return '+'; }

Armor::Armor(int defence) : defense_(defence) {}

int Armor::GetDefense() const { return defense_; }

QString Armor::GetName() const { return QString("Armor (%1)").arg(defense_); }

char Armor::GetTile() const { return 'A'; }
