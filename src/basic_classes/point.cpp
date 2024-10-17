#include "point.hpp"

Point::Point(int new_x, int new_y) : x_(new_x), y_(new_y) {}

int Point::getX() const { return x_; }

int Point::getY() const { return y_; }

void Point::changeX(int new_x) { x_ = new_x; }

void Point::changeY(int new_y) { y_ = new_y; }
