#include <iostream>

using namespace std;

class Item {
private:
    string name;
    float weight;

public:
    string get_name();
    float get_weight();
    virtual void execute();
    virtual ~Item();
};
