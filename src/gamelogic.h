#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include <QPoint>
#include "gamestatistics.h"
#include "map.h"
#include "player.h"
#include <memory>
#include <vector>

class GameLogic : public QObject
{
    Q_OBJECT
signals:
    void StatsUpdated();

public:
    GameLogic(int map_width, int map_height, int levels, QObject *parent = nullptr);

    void MovePlayer(int dx, int dy);
    int GetPlayerX() const;
    int GetPlayerY() const;
    void SwitchLevel(int direction);
    const Map &GetCurrentMap() const;
    int GetCurrentLevel() const;
    std::vector<QPoint> GetChangedTiles() const;
    bool IsPlayerOnStairs() const;
    void ClearChangedTiles();
    void InteractWithStairs();
    void SetCurrentLevel(int level);
    void SetPlayerPosition(int x, int y);
    void SetMapData(const std::vector<std::vector<char>> &data);
    const std::vector<Map> &GetAllMaps() const;
    std::vector<std::shared_ptr<Item>> GetPlayerItems() const;
    void SetAllMaps(const std::vector<Map> &maps);
    void PickUpItem();
    void DropItem();
    void UseItem();
    int GetCurrentItemIndex() const;
    void SelectNextItem();
    void SelectPreviousItem();
    int GetPlayerHealth() const;
    int GetPlayerMaxHealth() const;
    int GetPlayerAttackPower() const;
    Player &GetPlayer();
    GameStatistics &GetGameStatistics();
    const GameStatistics &GetGameStatistics() const;

    void IncrementEnemiesKilled();

    std::shared_ptr<Enemy> GetAttackedEnemy();

    void HitEnemy(int dx_enemy, int dy_enemy);
    void MoveEnemy(Enemy &enemy, QPoint new_position);
    void UpdateEnemies();

private:
    std::vector<Map> maps_;
    int current_level_;
    std::vector<QPoint> changed_tiles_;
    GameStatistics game_statistics_;

    Player player_;
    std::shared_ptr<Enemy> attacked_enemy_;
};

#endif // GAMELOGIC_H