#include <iostream>


float SPAWN_PROBABILITY = 0.5; 


class Enemy {
private:
    char _designation;
    int _x;
    int _y;
    std::string _name;
public:
    Enemy(char designation, int x, int y, std::string name);
};
