#include "room.h"

namespace Game {
Room::Room(ssize_t x, ssize_t y, ssize_t width, ssize_t height)
    : x_(x), y_(y), width_(width), height_(height) {}

bool Room::intersects(const Room &other) const {
  return !(x_ + width_ < other.GetX() || other.GetX() + other.GetWidth() < x_ ||
           y_ + height_ < other.GetY() ||
           other.GetY() + other.GetHeight() < y_);
}
void Room::Draw(std::vector<std::vector<char>> &map) const {
  for (int i = y_; i < y_ + height_; i++) {
    for (int j = x_; j < x_ + width_; j++) {
      map[i][j] = '.';
    }
  }
}
ssize_t Room::GetX() const { return x_; }
ssize_t Room::GetY() const { return y_; }
ssize_t Room::GetWidth() const { return width_; }
ssize_t Room::GetHeight() const { return height_; }
};