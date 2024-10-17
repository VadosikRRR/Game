#pragma once

#include <iostream>
#include <vector>

namespace game {
class Room {
private:
  ssize_t x_;
  ssize_t y_;
  ssize_t width_;
  ssize_t height_;

public:
  Room(ssize_t x, ssize_t y, ssize_t width, ssize_t height);
  bool Intersects(const Room &other) const;
  void Draw(std::vector<std::vector<char>> &map) const;
  ssize_t GetX() const;
  ssize_t GetY() const;
  ssize_t GetWidth() const;
  ssize_t GetHeight() const;
};
} // namespace game