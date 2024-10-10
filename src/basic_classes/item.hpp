#include <iostream>
#pragma once

using namespace std;

class Item
{
private:
    string name;
    int weight;
    char symbol;

public:
    const string& get_name() const;
    int get_weight() const;
    char GetChar() const;
    virtual void execute();
    virtual ~Item();
};
