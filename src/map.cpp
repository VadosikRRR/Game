#include "map.h"
#include "item.h"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

const int DAMAGE = 10;
const int ROOMCOUNT = 10;
const int MINSIZE = 5;
const int MAXSIZE = 10;
const int DEFENSE = 50;

Map::Map(int mapWidth, int mapHeight)
    : mapWidth(mapWidth), mapHeight(mapHeight) {

  mapData = std::vector<std::vector<char>>(mapHeight,
                                           std::vector<char>(mapWidth, '#'));
}

void Map::generateMap() {
  generateRooms(ROOMCOUNT, MINSIZE, MAXSIZE);
  connectRooms();
  addItemsToMap();
  AddEnemiesToMap();
}

void Map::generateRooms(int roomCount, int minSize, int maxSize) {
  for (int i = 0; i < roomCount; ++i) {
    int const width = minSize + std::rand() % (maxSize - minSize + 1);
    int const height = minSize + std::rand() % (maxSize - minSize + 1);
    int const x = std::rand() % (mapWidth - width - 1) + 1;
    int const y = std::rand() % (mapHeight - height - 1) + 1;
    Room const room = {x, y, width, height};

    bool intersects = false;
    for (const auto &existingRoom : rooms) {
      if (x < existingRoom.x + existingRoom.width &&
          x + width > existingRoom.x &&
          y < existingRoom.y + existingRoom.height &&
          y + height > existingRoom.y) {
        intersects = true;
        break;
      }
    }

    if (!intersects) {
      rooms.push_back(room);
      drawRoom(room);
    }
  }
}
Room Map::getRandomRoom() const {
  if (rooms.empty()) {
    return {0, 0, 1, 1};
  }
  return rooms[std::rand() % rooms.size()];
}

void Map::connectRooms() {
  for (size_t i = 1; i < rooms.size(); ++i) {
    int const x1 = rooms[i - 1].x + rooms[i - 1].width / 2;
    int const y1 = rooms[i - 1].y + rooms[i - 1].height / 2;

    int const x2 = rooms[i].x + rooms[i].width / 2;
    int const y2 = rooms[i].y + rooms[i].height / 2;

    if (std::rand() % 2 == 0) {
      drawHorizontalCorridor(x1, x2, y1);
      drawVerticalCorridor(y1, y2, x2);
    } else {
      drawVerticalCorridor(y1, y2, x1);
      drawHorizontalCorridor(x1, x2, y2);
    }
  }
}

void Map::drawRoom(const Room &room) {
  for (int y = room.y; y < room.y + room.height; ++y) {
    for (int x = room.x; x < room.x + room.width; ++x) {
      setTile(x, y, '.');
    }
  }
}

void Map::drawHorizontalCorridor(int x1, int x2, int y) {
  if (x1 > x2) {
    std::swap(x1, x2);
  }
  for (int x = x1; x <= x2; ++x) {
    setTile(x, y, '.');
  }
}

void Map::drawVerticalCorridor(int y1, int y2, int x) {
  if (y1 > y2) {
    std::swap(y1, y2);
  }
  for (int y = y1; y <= y2; ++y) {
    setTile(x, y, '.');
  }
}

bool Map::isWalkable(int x, int y) const {
  if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
    return false;
  }
  return mapData[y][x] == '.';
}

void Map::setTile(int x, int y, char tile) {
  if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
    mapData[y][x] = tile;
  }
}

char Map::getTile(int x, int y) const {
  if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
    return mapData[y][x];
  }
  return '#';
}

const std::vector<std::vector<char>> &Map::getData() const { return mapData; }

void Map::setData(const std::vector<std::vector<char>> &newData) {
  if (newData.size() == mapHeight && !newData.empty() &&
      newData[0].size() == mapWidth) {
    mapData = newData;
  } else {
    throw std::invalid_argument("Invalid map data size");
  }
}

int getRandomInRange(int min, int max) {
  return min + std::rand() % (max - min + 1);
}

bool Map::IsCellEmpty(int x, int y) {
  return getTile(x, y) == '.';
}

bool Map::findNearbyPosition(int &x, int &y) {
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) {
        continue;
      }
      if (IsCellEmpty(x + dx, y + dy)) {
        x += dx;
        y += dy;
        return true;
      }
    }
  }
  return false;
}

void Map::addItemsToMap() {
  for (const auto &room : rooms) {

    int centerX = room.x + room.width / 2;
    int centerY = room.y + room.height / 2;

    if (!IsCellEmpty(centerX, centerY)) {

      if (!findNearbyPosition(centerX, centerY)) {
        continue;
      }
    }

    int random = std::rand();

    if (random % 5 == 0) {
      setTile(centerX, centerY, '+');
      items_[QPoint(centerX, centerY)] = std::make_shared<MedKit>();
    } else if (random % 7 == 0) {
      int const damage = getRandomInRange(DAMAGE / 2, 3 * DAMAGE / 2);
      setTile(centerX, centerY, '!');
      items_[QPoint(centerX, centerY)] = std::make_shared<Sword>(damage);
    } else if (random % 9 == 0) {
      int const defense = getRandomInRange(DEFENSE / 2, 3 * DEFENSE / 2);
      setTile(centerX, centerY, 'A');
      items_[QPoint(centerX, centerY)] = std::make_shared<Armor>(defense);
    }
  }
}

std::shared_ptr<Item> Map::getItemAt(int x, int y) {
  QPoint const pos(x, y);
  if (items_.find(pos) != items_.end()) {
    return items_[pos];
  }
  return nullptr;
}

void Map::removeItemAt(int x, int y) {
  QPoint const pos(x, y);
  items_.erase(pos);
  setTile(x, y, '.');
}

void Map::LoadItem(int x, int y, const std::shared_ptr<Item> &item) {
    items_[QPoint(x, y)] = item;
}

void Map::LoadEnemy(std::shared_ptr<Enemy> p_enemy) {
    enemies_.push_front(p_enemy);
}

void Map::AddItem(int x, int y, const std::shared_ptr<Item> &item) {
  if (getTile(x, y) == '.') {
    items_[QPoint(x, y)] = item;
    setTile(x, y, item->GetTile());
  }
}

void Map::AddEnemy(std::shared_ptr<Enemy> p_enemy) {
    if (IsCellEmpty(p_enemy->GetX(), p_enemy->GetY())) {
        setTile(p_enemy->GetX(), p_enemy->GetY(), p_enemy->GetSymbol());
        enemies_.push_front(p_enemy);
    }
}

void Map::AddEnemiesToMap() {
    for (const auto &room : rooms) {

        int centerX = room.x + room.width / 2;
        int centerY = room.y + room.height / 2;

        if (!IsCellEmpty(centerX, centerY)) {

            if (!findNearbyPosition(centerX, centerY)) {
                continue;
            }
        }

        int random = std::rand();

        if (random % 5 == 0) {
            enemies_.push_front(std::make_shared<Enemy>(Enemy(1, centerX, centerY)));
            setTile(centerX, centerY, enemies_.front()->GetSymbol());
        } else if (random % 7 == 0) {
            enemies_.push_front(std::make_shared<Enemy>(Enemy(2, centerX, centerY)));
            setTile(centerX, centerY, enemies_.front()->GetSymbol());
        } else if (random % 9 == 0) {
            enemies_.push_front(std::make_shared<Enemy>(Enemy(3, centerX, centerY)));
            setTile(centerX, centerY, enemies_.front()->GetSymbol());
        }
    }
}

const std::unordered_map<QPoint, std::shared_ptr<Item>> &Map::getItems() const {
  return items_;
}

const std::list<std::shared_ptr<Enemy>> &Map::GetEnemies() const {
    return enemies_;
}

void Map::DeleteEnemy(Enemy &enemy) {
    int x_coord = enemy.GetX();
    int y_coord = enemy.GetY();

    for (auto iter = enemies_.begin(); iter != enemies_.end(); iter++) {
        Enemy &finder_enemy = *(*iter);
        if (x_coord != finder_enemy.GetX() || y_coord != finder_enemy.GetY()) {
            continue;
        }

        setTile(x_coord, y_coord, '.');
        enemies_.erase(iter);
        return;
    }
}

void Map::setGreaterSign(QPoint point) { greater_sign_ = point; }

QPoint Map::getGreaterSign() const { return greater_sign_; }

void Map::setLessSign(QPoint point) { less_sign_ = point; }

QPoint Map::getLessSign() const { return less_sign_; }

