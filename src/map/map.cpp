#include "map.h"

namespace game {

Map::Map() : map_(kMapHeight, std::vector<char>(kMapWidth, '#')) {
  srand(time(0));
  Generate();
  PlaceItems();
  PlaceStairs();
}
void Map::ConnectRooms(const Room &room_1, const Room &room_2) {
  int x_1 = room_1.GetX() + rand() % room_1.GetWidth();
  int y_1 = room_1.GetY() + rand() % room_1.GetHeight();
  int x_2 = room_2.GetX() + rand() % room_2.GetWidth();
  int y_2 = room_2.GetY() + rand() % room_2.GetHeight();

  if (rand() % 2) {
    CreateHorizontalCorridor(x_1, x_2, y_1);
    CreateVerticalCorridor(y_1, y_2, x_2);
  } else {
    CreateVerticalCorridor(y_1, y_2, x_1);
    CreateHorizontalCorridor(x_1, x_2, y_2);
  }
}
void Map::CreateHorizontalCorridor(int x_1, int x_2, int y) {
  for (int x = std::min(x_1, x_2); x <= std::max(x_1, x_2); x++) {
    map_[y][x] = '.';
  }
}

void Map::CreateVerticalCorridor(int y_1, int y_2, int x) {
  for (int y = std::min(y_1, y_2); y <= std::max(y_1, y_2); y++) {

    map_[y][x] = '.';
  }
}
void Map::Generate() {
  for (int i = 0; i < kCountGenerationRooms; ++i) {
    int room_width = 6 + rand() % 10;
    int room_height = 4 + rand() % 6;
    int room_x = rand() % (kMapWidth - room_width - 1);
    int room_y = rand() % (kMapHeight - room_height - 1);

    Room new_room(room_x, room_y, room_width, room_height);

    bool intersects = false;
    for (const auto &room : rooms_) {
      if (new_room.Intersects(room)) {
        intersects = true;
        break;
      }
    }

    if (!intersects) {
      rooms_.push_back(new_room);
      new_room.Draw(map_);

      if (rooms_.size() > 1) {
        ConnectRooms(rooms_[rooms_.size() - 2], new_room);
      }
    }
  }
}
void Map::Draw(ssize_t player_x, ssize_t player_y) const {
  for (int i = 0; i < kMapHeight; ++i) {
    for (int j = 0; j < kMapWidth; ++j) {
      if (i == player_x && j == player_y) {
        mvaddch(i, j, '@');
      } else {
        mvaddch(i, j, map_[i][j]);
      }
    }
  }
}

bool Map::IsStairsUp(ssize_t x, ssize_t y) const {
  return x == stairUp_.second && y == stairUp_.first;
}
bool Map::IsStairsDown(ssize_t x, ssize_t y) const {
  return x == stairDown_.second && y == stairDown_.first;
}
void Map::PlaceStairs() {
  Room room = GetRandomRoom();
  stairUp_ = std::make_pair(room.GetX() + rand() % room.GetWidth(),
                            room.GetY() + rand() % room.GetHeight());
  map_[stairUp_.second][stairUp_.first] = '>';
  room = GetRandomRoom();
  stairDown_ = std::make_pair(room.GetX() + rand() % room.GetWidth(),
                              room.GetY() + rand() % room.GetHeight());
  map_[stairDown_.second][stairDown_.first] = '<';
}

void Map::PlaceItems() {
  for (Item &item : items_) {
    int x = rand() % kMapWidth;
    int y = rand() % kMapHeight;

    while (map_[x][y] != '.') {
      x = rand() % kMapWidth;
      y = rand() % kMapHeight;
    }
    map_[x][y] = item.GetChar();
  }
}
bool Map::IsWalkable(int x, int y) const { return map_[x][y] != '#'; }
const Room &Map::GetRandomRoom() const {
  int index = rand() % rooms_.size();
  return rooms_[index];
}

const std::pair<ssize_t, ssize_t> &Map::GetStairUp() const { return stairUp_; }
const std::pair<ssize_t, ssize_t> &Map::GetStairDown() const {
  return stairDown_;
}
}; // namespace game
