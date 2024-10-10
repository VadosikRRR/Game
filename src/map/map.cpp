#include "map.h"

namespace game
{

  Map::Map(ssize_t width, ssize_t height)
  {
    Generate();
    PlaceItems();
    PlaceStairs();
  }
  void Map::ConnectRooms(const Room &room_1, const Room &room_2)
  {
    int x1 = room_1.GetX() + room_1.GetWidth() / 2;
    int y1 = room_1.GetY() + room_1.GetHeight() / 2;
    int x2 = room_2.GetX() + room_2.GetWidth() / 2;
    int y2 = room_2.GetY() + room_2.GetHeight() / 2;

    if (rand() % 2)
    {
      CreateHorizontalCorridor(x1, x2, y1);
      CreateVerticalCorridor(y1, y2, x2);
    }
    else
    {
      CreateVerticalCorridor(y1, y2, x1);
      CreateHorizontalCorridor(x1, x2, y2);
    }
  }
  void Map::CreateHorizontalCorridor(int x1, int x2, int y)
  {
    for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++)
    {
      map_[y][x] = '.';
    }
  }

  void Map::CreateVerticalCorridor(int y1, int y2, int x)
  {
    for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
    {
      map_[y][x] = '.';
    }
  }
  void Map::Generate()
  {
    srand(time(0));
    for (int i = 0; i < 10; ++i)
    {
      int room_width = 6 + rand() % 10;
      int room_height = 4 + rand() % 6;
      int room_x = rand() % (kMapWidth - room_width - 1);
      int room_y = rand() % (kMapHeight - room_height - 1);

      Room new_room(room_x, room_y, room_width, room_height);

      bool intersects = false;
      for (const auto &room : rooms_)
      {
        if (new_room.Intersects(room))
        {
          intersects = true;
          break;
        }
      }

      if (!intersects)
      {
        rooms_.push_back(new_room);
        new_room.Draw(map_);

        if (rooms_.size() > 1)
        {
          ConnectRooms(rooms_[rooms_.size() - 2], new_room);
        }
      }
    }
  }
  void Map::Draw() const
  {
    for (int i = 0; i < kMapHeight; ++i)
    {
      for (int j = 0; j < kMapWidth; ++j)
      {
        mvaddch(i, j, map_[i][j]);
      }
    }
  }

  bool Map::IsStairsUp(ssize_t x, ssize_t y) const
  {
    return x == stairUp_.first && y == stairUp_.second;
  }
  bool Map::IsStairsDown(ssize_t x, ssize_t y) const
  {
    return x == stairDown_.first && y == stairDown_.second;
  }
  void Map::PlaceStairs()
  {
    ssize_t room_index = rand() % rooms_.size();
    stairUp_ = std::make_pair(
        rooms_[room_index].GetX() + rooms_[room_index].GetWidth() / 2,
        rooms_[room_index].GetY() + rooms_[room_index].GetHeight() / 2);
    map_[stairUp_.first][stairUp_.second] = '>';
    room_index = rand() % rooms_.size();
    stairDown_ = std::make_pair(
        rooms_[room_index].GetX() + rooms_[room_index].GetWidth() / 2,
        rooms_[room_index].GetY() + rooms_[room_index].GetHeight() / 2);
    map_[stairDown_.first][stairDown_.second] = '<';
  }

  void Map::PlaceItems() {}

};