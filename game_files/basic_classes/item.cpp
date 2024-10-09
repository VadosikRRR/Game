#include "item.hpp"
#pragma once


Item::~Item() {}

string Item::get_name() {
    return name;
}

int Item::get_weight() {
    return weight;
}

void Item::execute() {}
