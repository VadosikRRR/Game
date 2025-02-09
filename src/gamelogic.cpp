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
    playerPoint.setX(startRoom.x + startRoom.width / 2);
    playerPoint.setY(startRoom.y + startRoom.height / 2);

}

void GameLogic::movePlayer(int dx, int dy) {
    int newX = playerPoint.x() + dx;
    int newY = playerPoint.y() + dy;

    const Map& map = maps[currentLevel];
    
    if (map.isWalkable(newX, newY)) {
        changedTiles.push_back({playerPoint.x(), playerPoint.y()});

        playerPoint.setX(newX);
        playerPoint.setY(newY);

        changedTiles.push_back({playerPoint.x(), playerPoint.y()});
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
                    playerPoint.setX(x);
                    playerPoint.setY(y);

                }
            }
        }

    }
}

const Map& GameLogic::getCurrentMap() const {
    return maps[currentLevel];
}

int GameLogic::getPlayerX() const {
    return playerPoint.x();
}

int GameLogic::getPlayerY() const {
    return playerPoint.y();
}
std::vector<QPoint> GameLogic::getChangedTiles() const {
    return changedTiles;
}

void GameLogic::clearChangedTiles() {
    changedTiles.clear();
}
bool GameLogic::isPlayerOnStairs() const {
    char tile = maps[currentLevel].getTile(playerPoint.x(), playerPoint.y());
    return (tile == '<' || tile == '>');
}
int GameLogic::getCurrentLevel() const{
    return currentLevel;
}
void GameLogic::interactWithStairs() {
    if (isPlayerOnStairs()) {
        char stair = maps[currentLevel].getTile(playerPoint.x(), playerPoint.y());
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
    playerPoint.setX(x);
    playerPoint.setY(y);
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
