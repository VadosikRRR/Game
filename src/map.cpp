#include "map.h"
#include "item.h"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>

const int kDamage = 10;
const int kRoomcount = 10;
const int kMinsize = 5;
const int kMaxsize = 10;
const int kDefense = 50;

Map::Map(int mapWidth, int mapHeight)
    : map_width_(mapWidth), map_height_(mapHeight) {

  map_data_ = std::vector<std::vector<char>>(map_height_,
                                           std::vector<char>(map_width_, '#'));
  visible_zone_ = std::vector<std::vector<bool>>(map_height_,
                                                 std::vector<bool>(map_width_, false));
}

void Map::GenerateMap() {
    GenerateRooms(kRoomcount, kMinsize, kMaxsize);
    ConnectRooms();
    AddItemsToMap();
    AddEnemiesToMap();
}

void Map::GenerateRooms(int roomCount, int minSize, int maxSize)
{
    for (int i = 0; i < roomCount; ++i) {
        int const width = minSize + std::rand() % (maxSize - minSize + 1);
        int const height = minSize + std::rand() % (maxSize - minSize + 1);
        int const x = std::rand() % (map_width_ - width - 1) + 1;
        int const y = std::rand() % (map_height_ - height - 1) + 1;
        Room const room = {x, y, width, height};

        bool intersects = false;
        for (const auto &existing_room : rooms_) {
            if (x < existing_room.x + existing_room.width &&
                x + width > existing_room.x &&
                y < existing_room.y + existing_room.height &&
                y + height > existing_room.y) {
                intersects = true;
                break;
            }
        }

        if (!intersects) {
            rooms_.push_back(room);
            DrawRoom(room);
        }
    }
}
Room Map::GetRandomRoom() const
{
    if (rooms_.empty()) {
        return {0, 0, 1, 1};
    }
    return rooms_[std::rand() % static_cast<int>(rooms_.size())];
}

void Map::ConnectRooms()
{
    for (size_t i = 1; i < rooms_.size(); ++i) {
        int const x1 = rooms_[i - 1].x + rooms_[i - 1].width / 2;
        int const y1 = rooms_[i - 1].y + rooms_[i - 1].height / 2;

        int const x2 = rooms_[i].x + rooms_[i].width / 2;
        int const y2 = rooms_[i].y + rooms_[i].height / 2;

        if (std::rand() % 2 == 0) {
            AddHorizontalCorridor(x1, x2, y1);
            DrawHorizontalCorridor(x1, x2, y1);
            AddVerticalCorridor(y1, y2, x2);
            DrawVerticalCorridor(y1, y2, x2);
        } else {
            AddVerticalCorridor(y1, y2, x1);
            DrawVerticalCorridor(y1, y2, x1);
            AddHorizontalCorridor(x1, x2, y2);
            DrawHorizontalCorridor(x1, x2, y2);
        }
    }
}

void Map::AddHorizontalCorridor(int x1, int x2, int y)
{
    if (x1 > x2) {
        std::swap(x1, x2);
    }
    Room room = {x1, y, x2 - x1 + 1, 1};
    corridors_.push_back(room);
}

void Map::AddVerticalCorridor(int y1, int y2, int x)
{
    if (y1 > y2) {
        std::swap(y1, y2);
    }

    Room room = {x, y1, 1, y2 - y1 + 1};
    corridors_.push_back(room);
}

void Map::DrawRoom(const Room &room)
{
    for (int y = room.y; y < room.y + room.height; ++y) {
        for (int x = room.x; x < room.x + room.width; ++x) {
            SetTile(x, y, '.');
        }
    }
}

void Map::DrawHorizontalCorridor(int x1, int x2, int y)
{
    if (x1 > x2) {
        std::swap(x1, x2);
    }

    for (int x = x1; x <= x2; ++x) {
        SetTile(x, y, '.');
    }
}

void Map::DrawVerticalCorridor(int y1, int y2, int x)
{
    if (y1 > y2) {
        std::swap(y1, y2);
    }

  for (int y = y1; y <= y2; ++y) {
    SetTile(x, y, '.');
  }
}

bool Map::IsWalkable(int x, int y) const {
  if (x < 0 || x >= map_width_ || y < 0 || y >= map_height_) {
    return false;
  }
  return map_data_[y][x] == '.';
}

void Map::SetTile(int x, int y, char tile) {
  if (x >= 0 && x < map_width_ && y >= 0 && y < map_height_) {
    map_data_[y][x] = tile;
  }
}

char Map::GetTile(int x, int y) const {
  if (x >= 0 && x < map_width_ && y >= 0 && y < map_height_) {
    return map_data_[y][x];
  }
  return '#';
}

const std::vector<std::vector<char>> &Map::GetData() const { return map_data_; }

void Map::SetData(const std::vector<std::vector<char>> &newData)
{
    if (static_cast<int>(newData.size()) == map_height_ && !newData.empty() &&
        static_cast<int>(newData[0].size()) == map_width_) {
    map_data_ = newData;
  } else {
    throw std::invalid_argument("Invalid map data size");
  }
}

int GetRandomInRange(int min, int max)
{
    return min + std::rand() % (max - min + 1);
}

bool Map::IsCellEmpty(int x, int y) {
  return GetTile(x, y) == '.';
}

bool Map::FindNearbyPosition(int &x, int &y)
{
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

void Map::AddItemsToMap()
{
    for (const auto &room : rooms_) {
        int center_x = room.x + room.width / 2;
        int center_y = room.y + room.height / 2;

        if (!IsCellEmpty(center_x, center_y)) {
            if (!FindNearbyPosition(center_x, center_y)) {
                continue;
            }
        }

        int random = std::rand();

        if (random % 5 == 0) {
            SetTile(center_x, center_y, '+');
            items_[QPoint(center_x, center_y)] = std::make_shared<MedKit>();
        } else if (random % 7 == 0) {
            int const damage = GetRandomInRange(kDamage / 2, 3 * kDamage / 2);
            SetTile(center_x, center_y, '!');
            items_[QPoint(center_x, center_y)] = std::make_shared<Sword>(damage);
        } else if (random % 9 == 0) {
            int const defense = GetRandomInRange(kDefense / 2, 3 * kDefense / 2);
            SetTile(center_x, center_y, 'A');
            items_[QPoint(center_x, center_y)] = std::make_shared<Armor>(defense);
        }
    }
}

std::shared_ptr<Item> Map::GetItemAt(int x, int y)
{
    QPoint const pos(x, y);
    if (items_.find(pos) != items_.end()) {
        return items_[pos];
    }
    return nullptr;
}

void Map::RemoveItemAt(int x, int y)
{
    QPoint const pos(x, y);
    items_.erase(pos);
    SetTile(x, y, '.');
}

void Map::LoadItem(int x, int y, const std::shared_ptr<Item> &item) {
    items_[QPoint(x, y)] = item;
}

void Map::LoadEnemy(std::shared_ptr<Enemy> p_enemy) {
    enemies_.push_front(p_enemy);
}

void Map::AddItem(int x, int y, const std::shared_ptr<Item> &item) {
  if (GetTile(x, y) == '.') {
    items_[QPoint(x, y)] = item;
    SetTile(x, y, item->GetTile());
  }
}

void Map::AddEnemy(std::shared_ptr<Enemy> p_enemy) {
    if (IsCellEmpty(p_enemy->GetX(), p_enemy->GetY())) {
        SetTile(p_enemy->GetX(), p_enemy->GetY(), p_enemy->GetSymbol());
        enemies_.push_front(p_enemy);
    }
}

void Map::AddEnemiesToMap() {
    for (const auto &room : rooms_) {

        int center_x = room.x + room.width / 2;
        int center_y = room.y + room.height / 2;

        if (!IsCellEmpty(center_x, center_y)) {
            if (!FindNearbyPosition(center_x, center_y)) {
                continue;
            }
        }

        int random = std::rand();

        if (random % 5 == 0) {
            enemies_.push_front(std::make_shared<Enemy>(Enemy(1, center_x, center_y)));
            SetTile(center_x, center_y, enemies_.front()->GetSymbol());
        } else if (random % 7 == 0) {
            enemies_.push_front(std::make_shared<Enemy>(Enemy(2, center_x, center_y)));
            SetTile(center_x, center_y, enemies_.front()->GetSymbol());
        } else if (random % 9 == 0) {
            enemies_.push_front(std::make_shared<Enemy>(Enemy(3, center_x, center_y)));
            SetTile(center_x, center_y, enemies_.front()->GetSymbol());
        }
    }
}

const std::unordered_map<QPoint, std::shared_ptr<Item>> &Map::GetItems() const
{
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

        SetTile(x_coord, y_coord, '.');
        enemies_.erase(iter);
        return;
    }
}

void Map::SetGreaterSign(QPoint point)
{
    greater_sign_ = point;
}

QPoint Map::GetGreaterSign() const
{
    return greater_sign_;
}

void Map::SetLessSign(QPoint point)
{
    less_sign_ = point;
}

QPoint Map::GetLessSign() const
{
    return less_sign_;
}

bool Map::IsExplored(int x, int y) const {
    return visible_zone_[y][x];
}

std::shared_ptr<Room> Map::GetRoom(int x, int y) const{
    for (size_t ind = 0; ind < rooms_.size(); ++ind) {
        if (rooms_[ind].x <= x && rooms_[ind].x + rooms_[ind].width + 1 > x &&
            rooms_[ind].y <= y && rooms_[ind].y + rooms_[ind].height + 1 > y) {
            return std::make_shared<Room>(rooms_[ind]);
        }
    }

    for (size_t ind = 0; ind < corridors_.size(); ++ind) {
        if (corridors_[ind].x <= x && corridors_[ind].x + corridors_[ind].width + 1 > x &&
            corridors_[ind].y <= y && corridors_[ind].y + corridors_[ind].height + 1 > y) {
            return std::make_shared<Room>(corridors_[ind]);
        }
    }

    return nullptr;
}

void Map::TileExplored(int x, int y) {
    visible_zone_[y][x] = true;
}

const std::vector<std::vector<bool>> & Map::GetVisibleZone() const {
    return visible_zone_;
}

void Map::SetExplored(int x, int y, bool is_explored) {
    visible_zone_[y][x] = is_explored;
}

const std::vector<Room> &Map::GetRooms() const {
    return rooms_;
}

const std::vector<Room> &Map::GetCorridors() const {
    return corridors_;
}

void Map::LoadRoom(Room &room) {
    rooms_.push_back(room);
}

void Map::LoadCorridor(Room &corridor) {
    corridors_.push_back(corridor);
}
