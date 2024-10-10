#include "point.hpp"

Point::Point(int new_x, int new_y) : x(new_x), y(new_y) {}

int Point::get_x() const
{
    return x;
}

int Point::get_y() const
{
    return y;
}

void Point::change_x(int new_x)
{
    x = new_x;
}

void Point::change_y(int new_y)
{
    y = new_y;
}
