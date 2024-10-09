#include "item.hpp"


Item::~Item() {}

string Item::get_name() {
    return name;
}

float Item::get_weight() {
    return weight;
}

void Item::execute() {}
