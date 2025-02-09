#ifndef MAP_H
#define MAP_H

#include <vector>

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

private:
    int mapWidth, mapHeight;
    std::vector<std::vector<char>> mapData;
    std::vector<Room> rooms;
    void generateRooms(int roomCount, int minSize, int maxSize);
    void connectRooms();
    void drawRoom(const Room &room);
    void drawHorizontalCorridor(int x1, int x2, int y);
    void drawVerticalCorridor(int y1, int y2, int x);
};

#endif // MAP_H
