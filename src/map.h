#ifndef MAP_H
#define MAP_H

#include "item.h"
#include "enemy.h"
#include <QPoint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <list>

namespace std {
template <> struct hash<QPoint> {
  size_t operator()(const QPoint &point) const noexcept {
    size_t h1 = std::hash<int>{}(point.x());
    size_t h2 = std::hash<int>{}(point.y());
    return h1 ^ (h2 << 1);
  }
};
} // namespace std

struct Room {
  int x, y;
  int width, height;
};

class Map {
public:
  Map(int mapWidth, int mapHeight);

  void generateMap();

  bool isWalkable(int x, int y) const;
  void setTile(int x, int y, char tile);
  char getTile(int x, int y) const;

  const std::vector<std::vector<char>> &getData() const;
  Room getRandomRoom() const;
  void setData(const std::vector<std::vector<char>> &newData);
  bool IsCellEmpty(int x, int y);
  bool findNearbyPosition(int &x, int &y);

  void addItemsToMap();
  std::shared_ptr<Item> getItemAt(int x, int y);
  void removeItemAt(int x, int y);
  void AddItem(int x, int y, const std::shared_ptr<Item> &item);
  const std::unordered_map<QPoint, std::shared_ptr<Item>> &getItems() const;
  const std::list<std::shared_ptr<Enemy>> &GetEnemies() const;

  void addEnemiesToMap();
  void DeleteEnemy(Enemy &enemy);

private:
  int mapWidth, mapHeight;
  std::vector<std::vector<char>> mapData;
  std::vector<Room> rooms;
  std::unordered_map<QPoint, std::shared_ptr<Item>> items_;
  std::list<std::shared_ptr<Enemy>> enemies_;

  void generateRooms(int roomCount, int minSize, int maxSize);
  void connectRooms();
  void drawRoom(const Room &room);
  void drawHorizontalCorridor(int x1, int x2, int y);
  void drawVerticalCorridor(int y1, int y2, int x);
};

int getRandomInRange(int min, int max);

#endif // MAP_H
