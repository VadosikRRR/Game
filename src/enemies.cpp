#include "enemies.h"
#include "map.h"

Enemy::Enemy(char designation, int x, int y, QString name) : _designation(designation), _x(x), _y(y), _name(name) {}

int Enemy::GetX() {
    return _x;
}

int Enemy::GetY() {
    return _y;
}

char Enemy::GetDesignation() {
    return _designation;
}

Enemy CreateEnemy(int left_x, int left_y, int width, int height) {
    if (std::rand() % 100 > 50) {
        int dx = std::rand() % width;
        int dy = std::rand() % height;
        return Enemy('e', left_x + dx, left_y + dy, QString("1"));
    }
    else {
        return Enemy('!', -1, -1, QString("incorrect"));
    }
}
