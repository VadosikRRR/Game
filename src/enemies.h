#ifndef ENEMY_H
#define ENEMY_H
#include <QString>


// int SPAWN_PROBABILITY = 50;


class Enemy {
private:
    char _designation;
    int _x;
    int _y;
    QString _name;
public:
Enemy(char designation, int x, int y, QString name);
    char GetDesignation();
    int GetX();
    int GetY();
};


Enemy CreateEnemy(int left_x, int left_y, int width, int height);


#endif
