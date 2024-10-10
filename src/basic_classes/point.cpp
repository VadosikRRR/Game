#include "point.hpp"

Point::Point(int new_x, int new_y) : x(new_x), y(new_y) {}

int Point::get_x() {
    return x;
}

int Point::get_y() {
    return y;
}

int Point::change_x(int new_x) {
    x = new_x;
}

int Point::change_y(int new_y) {
    y = new_y;
}