#include "room.h"

namespace game {
Room::Room(ssize_t x, ssize_t y, ssize_t width, ssize_t height)
    : x_(x), y_(y), width_(width), height_(height) {}

bool Room::Intersects(const Room &other) const {
  return !(x_ + width_ < other.GetX() || other.GetX() + other.GetWidth() < x_ ||
           y_ + height_ < other.GetY() ||
           other.GetY() + other.GetHeight() < y_);
}
void Room::Draw(std::vector<std::vector<char>> &map) const {
  for (int y = y_; y < y_ + height_; y++) {
    for (int x = x_; x < x_ + width_; x++) {
      map[y][x] = '.';
    }
  }
}
ssize_t Room::GetX() const { return x_; }
ssize_t Room::GetY() const { return y_; }
ssize_t Room::GetWidth() const { return width_; }
ssize_t Room::GetHeight() const { return height_; }
size_t Room::centerX() const { return x_ + width_ / 2; }
size_t Room::centerY() const { return y_ + height_ / 2; }
}; // namespace game