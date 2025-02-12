#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>
#include <QPoint>
#include "map.h"
#include "player.h"
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
    void setCurrentLevel(int level);
    void setPlayerPosition(int x, int y);
    void setMapData(const std::vector<std::vector<char>>& data);
    const std::vector<Map>& getAllMaps() const;
    void setAllMaps(const std::vector<Map>& maps);




private:
    std::vector<Map> maps;
    int currentLevel;
    std::vector<QPoint> changedTiles;

    Player player_;
};

#endif // GAMELOGIC_H
