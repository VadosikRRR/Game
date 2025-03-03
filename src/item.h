#ifndef ITEM_H
#define ITEM_H

#include <QString>
const int kMedKitHeal = 20;

class Item {
protected:
  Item() = default;

public:
  virtual ~Item() = default;
  virtual QString GetName() const = 0;
  virtual char GetTile() const = 0;
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
  int GetDamage() const;
  QString GetName() const override;
  char GetTile() const override;

private:
  int damage_;
};

class MedKit : public CollectiblesItem {
public:
  MedKit() = default;
  ~MedKit() = default;
  QString GetName() const override;
  char GetTile() const override;
};

class Armor : public Item {
public:
  Armor(int defense);
  ~Armor() = default;
  int GetDefense() const;
  QString GetName() const override;
  char GetTile() const override;

private:
  int defense_;
};
#endif // ITEM_H
