#include <iostream>
#include "creature_type.hpp"
using namespace std;

class Creature
{
private:
    unsigned int health;
    unsigned int damage;
    unsigned int protection;
    string name;
    char designation;
    Creature_type type;

public:
    Creature(Creature_type type, string name, char designation);
    virtual ~Creature();
    string get_name();
    Creature_type get_type();
    unsigned int get_health();
    unsigned int get_damage();
    unsigned int get_protection();
    char get_designation();
    void reduce_health(unsigned int value);
};