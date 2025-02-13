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
    std::shared_ptr<Item> getItemAt(int x, int y);
    void removeItemAt(int x, int y);
    void AddItem(int x, int y, const std::shared_ptr<Item>& item);
    const std::unordered_map<QPoint, std::shared_ptr<Item>>& getItems() const;

private:
    int mapWidth, mapHeight;
    std::vector<std::vector<char>> mapData;
    std::vector<Room> rooms;
    std::unordered_map<QPoint, std::shared_ptr<Item>> items_;

    void generateRooms(int roomCount, int minSize, int maxSize);
    void connectRooms();
    void drawRoom(const Room &room);
    void drawHorizontalCorridor(int x1, int x2, int y);
    void drawVerticalCorridor(int y1, int y2, int x);
    void placeItemInRoom(const Room& room, std::shared_ptr<Item> item, char tile);
    static std::shared_ptr<Item> generateRandomItem();
};

#endif // MAP_H
