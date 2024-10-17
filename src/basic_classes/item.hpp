#pragma once
#include "point.hpp"
#include <iostream>

using namespace std;
namespace game {
class Item {
private:
  string name_;
  unsigned int weight_;
  bool is_thrown_;
  Point position_;
  char symbol_;

public:
  Item(string name, unsigned int weight, char symbol, bool is_trown,
       Point position_ = Point());
  string get_name();
  unsigned int get_weight();
  virtual void execute();
  virtual ~Item();
  void put_item();
  void throw_item(Point pos);
  Point &get_position();
  bool get_is_trown();
  char GetChar() const;
};
} // namespace game