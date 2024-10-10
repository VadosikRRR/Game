#include "room.h"
#include <iostream>
#include <ncurses.h>
#include <random>
#include <vector>
namespace game
{
  const ssize_t kMapWidth = 100;
  const ssize_t kMapHeight = 100;
  class Map
  {
  private:
    std::vector<Room> rooms_;
    std::vector<std::vector<char>> map_;
    std::vector<std::vector<bool>> explored_;
    std::pair<ssize_t, ssize_t> stairUp_;
    std::pair<ssize_t, ssize_t> stairDown_;

    void ConnectRooms(const Room &room_1, const Room &room_2);
    void CreateHorizontalCorridor(int x1, int x2, int y);
    void CreateVerticalCorridor(int y1, int y2, int x);
    void PlaceItems();
    bool IsStairsUp(ssize_t x, ssize_t y) const;
    bool IsStairsDown(ssize_t x, ssize_t y) const;
    void PlaceStairs();

  public:
    Map(ssize_t width, ssize_t height);
    void Generate();
    void Draw() const;
  };
}