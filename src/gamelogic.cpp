#include "gamelogic.h"
#include "item.h"
#include "map.h"
#include <ctime>
GameLogic::GameLogic(int mapWidth, int mapHeight, int levels)
    : currentLevel(0) {
  srand(time(nullptr));

  for (int i = 0; i < levels; ++i) {
    Map map(mapWidth, mapHeight);
    map.generateMap();

    if (i > 0) {
      Room const room = map.getRandomRoom();
      int x = room.x + room.width / 2;
      int y = room.y + room.height / 2;

      while (map.getTile(x, y) != '.') {
        x = room.x + 1 + rand() % (room.width - 2);
        y = room.y + 1 + rand() % (room.height - 2);
      }
      map.setTile(room.x + room.width / 2, room.y + room.height / 2, '<');
    }
    if (i < levels - 1) {
      Room const room = map.getRandomRoom();
      int x = room.x + room.width / 2;
      int y = room.y + room.height / 2;

      while (map.getTile(x, y) != '.') {
        x = room.x + 1 + rand() % (room.width - 2);
        y = room.y + 1 + rand() % (room.height - 2);
      }
      map.setTile(room.x + room.width / 2, room.y + room.height / 2, '>');
    }

    maps.push_back(map);
  }
  Room const startRoom = maps[0].getRandomRoom();

  int x = startRoom.x + 1 + rand() % (startRoom.width - 2);
  int y = startRoom.y + 1 + rand() % (startRoom.height - 2);

  while (maps[0].getTile(x, y) != '.') {
    x = startRoom.x + 1 + rand() % (startRoom.width - 2);
    y = startRoom.y + 1 + rand() % (startRoom.height - 2);
  }
  player_.SetPosition(x, y);
}

void GameLogic::MovePlayer(int dx, int dy) {
  int const newX = player_.GetX() + dx;
  int const newY = player_.GetY() + dy;

  const Map &map = maps[currentLevel];

  if (map.getTile(newX, newY) != '#') {
    changedTiles.emplace_back(player_.GetX(), player_.GetY());

    player_.SetPosition(newX, newY);

    changedTiles.emplace_back(player_.GetX(), player_.GetY());
  }
}

void GameLogic::SwitchLevel(int direction) {
  int const newLevel = currentLevel + direction;

  if (newLevel >= 0 && newLevel < maps.size()) {
    currentLevel = newLevel;
    const Map &newMap = maps[currentLevel];
    for (int y = 0; y < newMap.getData().size(); ++y) {
      for (int x = 0; x < newMap.getData()[y].size(); ++x) {
        if (newMap.getTile(x, y) == ((direction == -1) ? '>' : '<')) {
          player_.SetPosition(x, y);
          break;
        }
      }
    }
  }
}

const Map &GameLogic::GetCurrentMap() const { return maps[currentLevel]; }

int GameLogic::GetPlayerX() const { return player_.GetX(); }

int GameLogic::GetPlayerY() const { return player_.GetY(); }
std::vector<QPoint> GameLogic::GetChangedTiles() const { return changedTiles; }

void GameLogic::clearChangedTiles() { changedTiles.clear(); }
bool GameLogic::isPlayerOnStairs() const {
  char const tile = maps[currentLevel].getTile(player_.GetX(), player_.GetY());
  return (tile == '<' || tile == '>');
}
int GameLogic::GetCurrentLevel() const { return currentLevel; }
void GameLogic::interactWithStairs() {
  if (isPlayerOnStairs()) {
    char const stair =
        maps[currentLevel].getTile(player_.GetX(), player_.GetY());
    int const direction = (stair == '<') ? -1 : 1;
    SwitchLevel(direction);
  }
}
void GameLogic::setCurrentLevel(int level) {
  if (level >= 0 && level < maps.size()) {
    currentLevel = level;
  }
}

void GameLogic::setPlayerPosition(int x, int y) { player_.SetPosition(x, y); }

void GameLogic::setMapData(const std::vector<std::vector<char>> &data) {
  if (currentLevel >= 0 && currentLevel < maps.size()) {
    maps[currentLevel].setData(data);
  }
}
const std::vector<Map> &GameLogic::GetAllMaps() const { return maps; }

void GameLogic::SetAllMaps(const std::vector<Map> &newMaps) { maps = newMaps; }

void GameLogic::PickUpItem() {
  int const x = player_.GetX();
  int const y = player_.GetY();
  std::shared_ptr<Item> const item = maps[currentLevel].getItemAt(x, y);
  if (item) {
    player_.PickUpItem(item);
    maps[currentLevel].removeItemAt(x, y);
  }
}

void GameLogic::DropItem() {
  std::shared_ptr<Item> const currentItem = player_.GetCurrentItem();
  if (currentItem) {
    int const x = player_.GetX();
    int const y = player_.GetY();

    if (maps[currentLevel].getTile(x, y) == '.') {
      maps[currentLevel].AddItem(x, y, currentItem);
      player_.DropItem();
    }
  }
}

void GameLogic::UseItem() { player_.UseItem(); }
std::vector<std::shared_ptr<Item>> GameLogic::GetPlayerItems() const {
  return player_.GetItems();
}
int GameLogic::GetCurrentItemIndex() const {
  return player_.GetCurrentItemIndex();
}

void GameLogic::SelectNextItem() { player_.SelectNextItem(); }

void GameLogic::SelectPreviousItem() { player_.SelectPreviousItem(); }
int GameLogic::getPlayerHealth() const { return player_.GetHealth(); }

int GameLogic::GetPlayerMaxHealth() const { return player_.GetMaxHealth(); }

int GameLogic::getPlayerAttackPower() const { return player_.GetAttackPower(); }
Player &GameLogic::getPlayer() { return player_; }
