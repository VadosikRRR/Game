#pragma once

const int kMedKitHeal = 20;
const char kSwordTile = '!';
const char kMedKitTile = '+';

class Item {
protected:
    Item() = default;
public:
    virtual ~Item() = default;
};

class CollectiblesItem : public Item {
public:
    void Add();
    void Drop();
    int GetCount() const;
    virtual ~CollectiblesItem() = default;
protected:
    CollectiblesItem() = default;
    int count_ = 1;
};

class Sword : public Item {
public:
    Sword(int damage);
    ~Sword() = default;
    int GetDamage();
private:
    int damage_;
};

class MedKit : public CollectiblesItem {
public:
    MedKit() = default;
    ~MedKit() = default;
};