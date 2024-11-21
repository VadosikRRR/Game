#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include "map.h"
class GameLogic {
public:
    GameLogic(int mapWidth, int mapHeight, int levels);

    void movePlayer(int dx, int dy);
    int getPlayerX() const;
    int getPlayerY() const;
    void switchLevel(int direction);
    const Map& getCurrentMap() const;
    int getCurrentLevel() const;
    std::vector<std::pair<int, int>> getChangedTiles() const;
    bool isPlayerOnStairs() const;
    void clearChangedTiles();

private:
    std::vector<Map> maps;
    int currentLevel;
    int playerX, playerY;
    std::vector<std::pair<int, int>> changedTiles;
    void interactWithStairs();
};

#endif // GAMELOGIC_H
