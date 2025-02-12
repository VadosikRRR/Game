#include "gamelogic.h"
#include <time.h>
GameLogic::GameLogic(int mapWidth, int mapHeight, int levels)
    : currentLevel(0) {
    srand(time(nullptr));


    for (int i = 0; i < levels; ++i) {
        Map map(mapWidth, mapHeight);
        map.generateMap();

        if (i > 0) {
            Room room = map.getRandomRoom();
            map.setTile(room.x + room.width / 2, room.y + room.height / 2, '<');
        }
        if (i < levels - 1) {
            Room room = map.getRandomRoom();
            map.setTile(room.x + room.width / 2, room.y + room.height / 2, '>');
        }

        maps.push_back(map);
    }
    Room startRoom = maps[0].getRandomRoom();
    player_.SetPosition(startRoom.x + startRoom.width / 2,startRoom.y + startRoom.height / 2);

}

void GameLogic::movePlayer(int dx, int dy) {
    int newX = player_.GetX() + dx;
    int newY = player_.GetY() + dy;

    const Map& map = maps[currentLevel];
    
    if (map.isWalkable(newX, newY)) {
        changedTiles.push_back({player_.GetX(), player_.GetY()});

        player_.SetPosition(newX, newY);

        changedTiles.push_back({player_.GetX(), player_.GetY()});
    }
}


void GameLogic::switchLevel(int direction) {
    int newLevel = currentLevel + direction;

    if (newLevel >= 0 && newLevel < maps.size()) {
        currentLevel = newLevel;
        const Map& newMap = maps[currentLevel];
        for (int y = 0; y < newMap.getData().size(); ++y) {
            for (int x = 0; x < newMap.getData()[y].size(); ++x) {
                if (newMap.getTile(x, y) == ((direction == -1) ? '>' : '<')) {
                    player_.SetPosition(x, y);

                }
            }
        }

    }
}

const Map& GameLogic::getCurrentMap() const {
    return maps[currentLevel];
}

int GameLogic::getPlayerX() const {
    return player_.GetX();
}

int GameLogic::getPlayerY() const {
    return player_.GetY();
}
std::vector<QPoint> GameLogic::getChangedTiles() const {
    return changedTiles;
}

void GameLogic::clearChangedTiles() {
    changedTiles.clear();
}
bool GameLogic::isPlayerOnStairs() const {
    char tile = maps[currentLevel].getTile(player_.GetX(), player_.GetY());
    return (tile == '<' || tile == '>');
}
int GameLogic::getCurrentLevel() const{
    return currentLevel;
}
void GameLogic::interactWithStairs() {
    if (isPlayerOnStairs()) {
        char stair = maps[currentLevel].getTile(player_.GetX(), player_.GetY());
        int direction = (stair == '<') ? -1 : 1;
        switchLevel(direction);
    }
}
void GameLogic::setCurrentLevel(int level) {
    if (level >= 0 && level < maps.size()) {
        currentLevel = level;
    }
}

void GameLogic::setPlayerPosition(int x, int y) {
    player_.SetPosition(x, y);
}

void GameLogic::setMapData(const std::vector<std::vector<char>>& data) {
    if (currentLevel >= 0 && currentLevel < maps.size()) {
        maps[currentLevel].setData(data);
    }
}
const std::vector<Map>& GameLogic::getAllMaps() const {
    return maps;
}

void GameLogic::setAllMaps(const std::vector<Map>& newMaps) {
    maps = newMaps;
}


