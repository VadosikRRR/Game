#include <iostream>
#pragma once

using namespace std;

class Item {
private:
    string name;
    int weight;

public:
    string get_name();
    int get_weight();
    virtual void execute();
    virtual ~Item();
};
