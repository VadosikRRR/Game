#include "item.hpp"
#pragma once

Item::~Item() {



}
const string& Item::get_name() const
{
    return name;
}

int Item::get_weight()const
{
    return weight;
}

char Item::GetChar() const{
    return symbol;
}
void Item::execute() {}
