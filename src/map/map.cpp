#include "map.h"

namespace game {

Map::Map()
    : map_(kMapHeight, std::vector<char>(kMapWidth, '#')),
      explored_(kMapHeight, std::vector<bool>(kMapWidth, false)) {
  srand(time(0));
  Generate();
}

void Map::ConnectRooms() {
  size_t index = 1;
  while (index < rooms_.size()) {
    int prevRoomCenterX = rooms_[index - 1].centerX();
    int prevRoomCenterY = rooms_[index - 1].centerY();
    int currRoomCenterX = rooms_[index].centerX();
    int currRoomCenterY = rooms_[index].centerY();
    CreateCorridor(prevRoomCenterX, prevRoomCenterY, currRoomCenterX,
                   currRoomCenterY);
    index++;
  }
}

bool Map::IsExplored(int x, int y) const { return explored_[y][x]; }

void Map::Explore(int x, int y) {
  Room *room = GetRoomAt(x, y);
  if (room != nullptr) {
    ExploreRoom(*room);
    return;
  }

  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      int newX = x + dx;
      int newY = y + dy;
      if (newX >= 0 && newX < kMapWidth && newY >= 0 && newY < kMapHeight) {
        explored_[newY][newX] = true;
      }
    }
  }
}

Room *Map::GetRoomAt(int x, int y) {
  for (Room &room : rooms_) {
    if (IsInsideRoom(x, y, room)) {
      return &room;
    }
  }
  return nullptr;
}

bool Map::IsInsideRoom(int x, int y, const Room &room) const {
  return x >= room.GetX() && x < room.GetX() + room.GetWidth() &&
         y >= room.GetY() && y < room.GetY() + room.GetHeight();
}

void Map::ExploreRoom(const Room &room) {
  int startX = room.GetX() - 1;
  int endX = room.GetX() + room.GetWidth();
  int startY = room.GetY() - 1;
  int endY = room.GetY() + room.GetHeight();

  for (int y = startY; y <= endY; ++y) {
    for (int x = startX; x <= endX; ++x) {
      if (x >= 0 && x < kMapWidth && y >= 0 && y < kMapHeight) {
        explored_[y][x] = true;
      }
    }
  }
}

void Map::CreateCorridor(int x_1, int y_1, int x_2, int y_2) {
  bool horizontalFirst = rand() % 2 == 0;

  if (horizontalFirst) {
    int currentX = x_1;
    while (currentX != x_2) {
      if (map_[y_1][currentX] == '#') {
        map_[y_1][currentX] = '.';
      }
      currentX += (x_2 > x_1) ? 1 : -1;
    }

    int currentY = y_1;
    while (currentY != y_2) {
      if (map_[currentY][x_2] == '#') {
        map_[currentY][x_2] = '.';
      }
      currentY += (y_2 > y_1) ? 1 : -1;
    }
  } else {
    int currentY = y_1;
    while (currentY != y_2) {
      if (map_[currentY][x_1] == '#') {
        map_[currentY][x_1] = '.';
      }
      currentY += (y_2 > y_1) ? 1 : -1;
    }

    int currentX = x_1;
    while (currentX != x_2) {
      if (map_[y_2][currentX] == '#') {
        map_[y_2][currentX] = '.';
      }
      currentX += (x_2 > x_1) ? 1 : -1;
    }
  }
}

void Map::Generate() {
  CreateRooms();
  ConnectRooms();
  PlaceItems();
  PlaceStairs();
}

void Map::CreateRooms() {
  int count = 0;
  while (count < kCountGenerationRooms) {
    int room_width = kMinMapWidth + rand() % kMinMapWidth;
    int room_height = kMinMapHeight + rand() % kMinMapHeight;
    int room_x = rand() % (kMapWidth - room_width - 1);
    int room_y = rand() % (kMapHeight - room_height - 1);

    Room new_room(room_x, room_y, room_width, room_height);

    if (!CanPlaceRoom(new_room)) {
      continue;
    }

    rooms_.push_back(new_room);
    new_room.Draw(map_);

    count++;
  }
}

bool Map::CanPlaceRoom(Room const &room) const {
  for (const Room &other : rooms_) {
    if (room.Intersects(other)) {
      return false;
    }
  }
  return true;
}

void Map::Draw(ssize_t player_x, ssize_t player_y) const {
  for (int y = 0; y < kMapHeight; ++y) {
    for (int x = 0; x < kMapWidth; ++x) {
      if (y == player_y && x == player_x) {
        mvaddch(y, x, '@');
      } else if (IsExplored(x, y)) {
        mvaddch(y, x, map_[y][x]);
      } else {
        mvaddch(y, x, ' ');
      }
    }
  }
}

bool Map::IsStairsUp(ssize_t x, ssize_t y) const {
  return x == stairUp_.first && y == stairUp_.second;
}

bool Map::IsStairsDown(ssize_t x, ssize_t y) const {
  return x == stairDown_.first && y == stairDown_.second;
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

    while (map_[y][x] != '.') {
      x = rand() % kMapWidth;
      y = rand() % kMapHeight;
    }
    map_[y][x] = item.GetChar();
  }
}

bool Map::IsWalkable(int x, int y) const { return map_[y][x] != '#'; }

const Room &Map::GetRandomRoom() const {
  int index = rand() % rooms_.size();
  return rooms_[index];
}

const std::pair<ssize_t, ssize_t> &Map::GetStairUp() const { return stairUp_; }
const std::pair<ssize_t, ssize_t> &Map::GetStairDown() const {
  return stairDown_;
}

}; // namespace game
