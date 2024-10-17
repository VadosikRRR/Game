#pragma once

#include "../basic_classes/item.hpp"
#include "room.h"
#include <iostream>
#include <ncurses.h>
#include <random>
#include <thread>
#include <vector>
namespace game {
const ssize_t kMapWidth = 80;
const ssize_t kMapHeight = 40;
const int kCountGenerationRooms = 10;
class Map {
private:
  std::vector<Room> rooms_;
  std::vector<std::vector<char>> map_;
  std::vector<Item> items_;
  std::pair<ssize_t, ssize_t> stairUp_;
  std::pair<ssize_t, ssize_t> stairDown_;

  void ConnectRooms(const Room &room_1, const Room &room_2);
  void CreateHorizontalCorridor(int x1, int x2, int y);
  void CreateVerticalCorridor(int y1, int y2, int x);
  void PlaceItems();
  void PlaceStairs();

public:
  Map();
  void Generate();
  void Draw(ssize_t player_x, ssize_t player_y) const;

  const Room &GetRandomRoom() const;
  const std::pair<ssize_t, ssize_t> &GetStairUp() const;
  const std::pair<ssize_t, ssize_t> &GetStairDown() const;

  bool IsStairsUp(ssize_t x, ssize_t y) const;
  bool IsStairsDown(ssize_t x, ssize_t y) const;
  bool IsWalkable(int x, int y) const;
};
} // namespace game