#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include <QPoint>
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
    std::vector<QPoint> getChangedTiles() const;
    bool isPlayerOnStairs() const;
    void clearChangedTiles();
    void interactWithStairs();

private:
    std::vector<Map> maps;
    int currentLevel;
    QPoint playerPoint;
    std::vector<QPoint> changedTiles;
};

#endif // GAMELOGIC_H
