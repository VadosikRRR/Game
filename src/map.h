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

  void GenerateMap();

  bool IsExplored(int x, int y) const;
  bool IsWalkable(int x, int y) const;
  void SetTile(int x, int y, char tile);
  char GetTile(int x, int y) const;
  void TileExplored(int x, int y);

  const std::vector<std::vector<char>> &GetData() const;
  std::shared_ptr<Room> GetRoom(int x, int y) const;
  Room getRandomRoom() const;
  void setData(const std::vector<std::vector<char>> &newData);
  bool IsCellEmpty(int x, int y);
  bool findNearbyPosition(int &x, int &y);

  void addItemsToMap();
  std::shared_ptr<Item> getItemAt(int x, int y);
  void removeItemAt(int x, int y);
  void AddItem(int x, int y, const std::shared_ptr<Item> &item);
  void LoadItem(int x, int y, const std::shared_ptr<Item> &item);
  const std::unordered_map<QPoint, std::shared_ptr<Item>> &getItems() const;
  const std::list<std::shared_ptr<Enemy>> &GetEnemies() const;

  void AddEnemy(std::shared_ptr<Enemy> p_enemy);
  void LoadEnemy(std::shared_ptr<Enemy> p_enemy);
  void AddEnemiesToMap();
  void DeleteEnemy(Enemy &enemy);

  void setGreaterSign(QPoint point);
  QPoint getGreaterSign() const;
  void setLessSign(QPoint point);
  QPoint getLessSign() const;

private:
  int map_width_, map_height_;
  std::vector<std::vector<char>> map_data_;
  std::vector<std::vector<bool>> visible_zone_;
  std::vector<Room> rooms_;
  std::vector<Room> corridors_;
  std::unordered_map<QPoint, std::shared_ptr<Item>> items_;
  std::list<std::shared_ptr<Enemy>> enemies_;

  QPoint greater_sign_;
  QPoint less_sign_;

  void generateRooms(int roomCount, int minSize, int maxSize);
  void connectRooms();
  void addHorizontalCorridor(int x1, int x2, int y);
  void addVerticalCorridor(int y1, int y2, int x);
  void drawRoom(const Room &room);
  void drawHorizontalCorridor(int x1, int x2, int y);
  void drawVerticalCorridor(int y1, int y2, int x);
};

int getRandomInRange(int min, int max);

#endif // MAP_H
