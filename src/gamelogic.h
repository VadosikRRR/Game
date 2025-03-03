#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "map.h"
#include "player.h"
#include <QPoint>
#include <vector>
#include <memory>

class GameLogic {
public:
  GameLogic(int mapWidth, int mapHeight, int levels);

  void MovePlayer(int dx, int dy);
  int GetPlayerX() const;
  int GetPlayerY() const;
  void SwitchLevel(int direction);
  const Map &GetCurrentMap() const;
  int GetCurrentLevel() const;
  std::vector<QPoint> GetChangedTiles() const;
  bool isPlayerOnStairs() const;
  void clearChangedTiles();
  void interactWithStairs();
  void setCurrentLevel(int level);
  void setPlayerPosition(int x, int y);
  void setMapData(const std::vector<std::vector<char>> &data);
  const std::vector<Map> &GetAllMaps() const;
  std::vector<std::shared_ptr<Item>> GetPlayerItems() const;
  void SetAllMaps(const std::vector<Map> &maps);
  void PickUpItem();
  void DropItem();
  void UseItem();
  int GetCurrentItemIndex() const;
  void SelectNextItem();
  void SelectPreviousItem();
  int getPlayerHealth() const;
  int GetPlayerMaxHealth() const;
  int getPlayerAttackPower() const;
  Player &getPlayer();

  std::shared_ptr<Enemy> GetAttackedEnemy();

  void HitEnemy(int dx_enemy, int dy_enemy);
  void MoveEnemy(Enemy &enemy, QPoint new_position);
  void UpdateEnemies();

private:
  std::vector<Map> maps;
  int currentLevel;
  std::vector<QPoint> changedTiles;

  Player player_;
  std::shared_ptr<Enemy> attactedEnemy_;
};

#endif // GAMELOGIC_H
