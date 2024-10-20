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
const ssize_t kMinMapWidth = 6;
const ssize_t kMapHeight = 30;
const ssize_t kMinMapHeight = 5;
const int kCountGenerationRooms = 10;
class Map {
private:
  std::vector<Room> rooms_;
  std::vector<std::vector<char>> map_;
  std::vector<std::vector<bool>> explored_;
  std::vector<Item> items_;
  std::pair<ssize_t, ssize_t> stairUp_;
  std::pair<ssize_t, ssize_t> stairDown_;

  void Generate();
  void CreateRooms();
  void ConnectRooms();
  void PlaceItems();
  void PlaceStairs();

  void CreateCorridor(int x_1, int y_1, int x_2, int y_2);

  Room *GetRoomAt(int x, int y);
  void ExploreRoom(const Room &room);

public:
  Map();
  void Explore(int x, int y);
  void Draw(ssize_t player_x, ssize_t player_y) const;

  const Room &GetRandomRoom() const;
  const std::pair<ssize_t, ssize_t> &GetStairUp() const;
  const std::pair<ssize_t, ssize_t> &GetStairDown() const;

  bool IsStairsUp(ssize_t x, ssize_t y) const;
  bool IsStairsDown(ssize_t x, ssize_t y) const;
  bool IsWalkable(int x, int y) const;
  bool CanPlaceRoom(Room const &room) const;
  bool IsExplored(int x, int y) const;
  bool IsInsideRoom(int x, int y, const Room &room) const;
};
} // namespace game