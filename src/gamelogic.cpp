#include "gamelogic.h"
#include <random>
#include<time.h>
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
    playerX = startRoom.x + startRoom.width / 2;
    playerY = startRoom.y + startRoom.height / 2;

    maps[currentLevel].setTile(playerX, playerY, '@');
}

void GameLogic::movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    const Map& map = maps[currentLevel];
    char nextTile = map.getTile(newX, newY);

    if (map.isWalkable(newX, newY)) {
        changedTiles.push_back({playerX, playerY});

        if (nextTile != '<' && nextTile != '>') {
            maps[currentLevel].setTile(playerX, playerY, '.');
        }
        maps[currentLevel].setTile(playerX, playerY, '.');

        playerX = newX;
        playerY = newY;

        maps[currentLevel].setTile(playerX, playerY, '@');

        changedTiles.push_back({playerX, playerY});
    }
}


void GameLogic::switchLevel(int direction) {
    int newLevel = currentLevel + direction;

    if (newLevel >= 0 && newLevel < maps.size()) {
        maps[currentLevel].setTile(playerX, playerY, '.');

        currentLevel = newLevel;
        const Map& newMap = maps[currentLevel];
        for (int y = 0; y < newMap.getData().size(); ++y) {
            for (int x = 0; x < newMap.getData()[y].size(); ++x) {
                if (newMap.getTile(x, y) == ((direction == -1) ? '>' : '<')) {
                    playerX = x;
                    playerY = y;
                }
            }
        }

        maps[currentLevel].setTile(playerX, playerY, '@');
    }
}

const Map& GameLogic::getCurrentMap() const {
    return maps[currentLevel];
}

int GameLogic::getPlayerX() const {
    return playerX;
}

int GameLogic::getPlayerY() const {
    return playerY;
}
std::vector<std::pair<int, int>> GameLogic::getChangedTiles() const {
    return changedTiles;
}

void GameLogic::clearChangedTiles() {
    changedTiles.clear();
}
bool GameLogic::isPlayerOnStairs() const {
    char tile = maps[currentLevel].getTile(playerX, playerY);
    return (tile == '<' || tile == '>');
}
int GameLogic::getCurrentLevel() const{
    return currentLevel;
}
void GameLogic::interactWithStairs() {
    if (isPlayerOnStairs()) {
        char stair = maps[currentLevel].getTile(playerX, playerY);
        int direction = (stair == '<') ? -1 : 1;
        switchLevel(direction);
    }
}
