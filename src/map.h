#ifndef MAP_H
#define MAP_H

#include <vector>
#include <unordered_map>
#include "item.h"
#include <memory>
#include <QPoint>
#include <functional>

namespace std {
    template <>
    struct hash<QPoint> {
        size_t operator()(const QPoint& point) const noexcept {
            size_t h1 = std::hash<int>{}(point.x());
            size_t h2 = std::hash<int>{}(point.y());
            return h1 ^ (h2 << 1);
        }
    };
}

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

    const std::vector<std::vector<char>>& getData() const;
    Room getRandomRoom() const;
    void setData(const std::vector<std::vector<char>>& newData);

    void addItemsToMap();

private:
    int mapWidth, mapHeight;
    std::vector<std::vector<char>> mapData;
    std::vector<Room> rooms;
    void generateRooms(int roomCount, int minSize, int maxSize);
    void connectRooms();
    void drawRoom(const Room &room);
    void drawHorizontalCorridor(int x1, int x2, int y);
    void drawVerticalCorridor(int y1, int y2, int x);

    std::unordered_map<QPoint, std::shared_ptr<Item>> items_;
};

#endif // MAP_H
