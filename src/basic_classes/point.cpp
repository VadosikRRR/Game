#include "point.hpp"

Point::Point(int new_x = 0, int new_y = 0) : x(new_x), y(new_y) {}

int Point::get_x() {
    return x;
}

int Point::get_y() {
    return y;
}

void Point::change_x(int new_x) {
    x = new_x;
}

void Point::change_y(int new_y) {
    y = new_y;
}