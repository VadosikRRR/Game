#include "map.h"
#include "item.h"
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <stdexcept>

const int DAMAGE = 10;
const int ROOMCOUNT = 10;
const int MINSIZE = 5;
const int MAXSIZE = 10;

Map::Map(int mapWidth, int mapHeight)
    : mapWidth(mapWidth), mapHeight(mapHeight) {

    mapData = std::vector<std::vector<char>>(mapHeight, std::vector<char>(mapWidth, '#'));
}

void Map::generateMap() {
    generateRooms(ROOMCOUNT, MINSIZE, MAXSIZE);
    connectRooms();
    addItemsToMap();
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
            if (x < existingRoom.x + existingRoom.width && x + width > existingRoom.x &&
                y < existingRoom.y + existingRoom.height && y + height > existingRoom.y) {
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
Room Map::getRandomRoom() const
{
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
    if (x1 > x2) { std::swap(x1, x2);
}
    for (int x = x1; x <= x2; ++x) {
        setTile(x, y, '.');
    }
}

void Map::drawVerticalCorridor(int y1, int y2, int x) {
    if (y1 > y2) { std::swap(y1, y2);
}
    for (int y = y1; y <= y2; ++y) {
        setTile(x, y, '.');
    }
}

bool Map::isWalkable(int x, int y) const
{
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

char Map::getTile(int x, int y) const
{
    if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
        return mapData[y][x];
    }
    return '#';
}

const std::vector<std::vector<char>>& Map::getData() const
{
    return mapData;
}

void Map::setData(const std::vector<std::vector<char>>& newData) {
    if (newData.size() == mapHeight && !newData.empty() && newData[0].size() == mapWidth) {
        mapData = newData;
    } else {
        throw std::invalid_argument("Invalid map data size");
    }
}

int getRandomInRange(int min, int max)
{
    return min + std::rand() % (max - min + 1);
}

bool canPlaceItem(const Map& map, int x, int y)
{
    return map.getTile(x, y) == '.';
}

bool findNearbyPosition(const Map& map, int& x, int& y)
{
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) { continue;
}
            if (canPlaceItem(map, x + dx, y + dy)) {
                x += dx;
                y += dy;
                return true;
            }
        }
    }
    return false;
}

void Map::addItemsToMap() {
    std::srand(time(nullptr));

    for (const auto& room : rooms) {

        int centerX = room.x + room.width / 2;
        int centerY = room.y + room.height / 2;


        if (!canPlaceItem(*this, centerX, centerY)) {

            if (!findNearbyPosition(*this, centerX, centerY)) {
                continue;
            }
        }

        if (std::rand() % 5 == 0) {
            setTile(centerX, centerY, '+');
            items_[QPoint(centerX, centerY)] = std::make_shared<MedKit>();
        }
        else if (std::rand() % 10 == 0) {
            int const damage = getRandomInRange(DAMAGE / 2, 3 * DAMAGE / 2);
            setTile(centerX, centerY, '!');
            items_[QPoint(centerX, centerY)] = std::make_shared<Sword>(damage);
        }
    }
}

void Map::placeItemInRoom(const Room& room, std::shared_ptr<Item> item, char tile) {
    int const x = room.x + 1 + std::rand() % (room.width - 2);
    int const y = room.y + 1 + std::rand() % (room.height - 2);

    if (mapData[y][x] == '.') {
        setTile(x, y, tile);
        items_[QPoint(x, y)] = std::move(item);
    }
}

auto Map::generateRandomItem() -> std::shared_ptr<Item> {
    int const itemType = std::rand() % 2;
    switch (itemType) {
    case 0:
        return std::make_shared<Sword>(DAMAGE + std::rand() % 10);
    case 1:
        return std::make_shared<MedKit>();
    default:
        return nullptr;
    }
}

std::shared_ptr<Item> Map::getItemAt(int x, int y)
{
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

void Map::AddItem(int x, int y, const std::shared_ptr<Item>& item) {
    if (this->getTile(x,y) =='.') {
        items_[QPoint(x, y)] = item;
        setTile(x, y, item->GetTile());
    }
}

const std::unordered_map<QPoint, std::shared_ptr<Item>>& Map::getItems() const
{
    return items_;
}
