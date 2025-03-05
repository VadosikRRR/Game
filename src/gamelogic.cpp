#include "gamelogic.h"
#include "enemy.h"
#include "item.h"
#include "map.h"
#include <ctime>

const int kVisibleDistance = 5;
const int kFightDistance = 1;

GameLogic::GameLogic(int map_width, int map_height, int levels, QObject *parent)
    : QObject(parent)
    , current_level_(0)
    , attacked_enemy_(nullptr)
{
    srand(time(nullptr));

    for (int i = 0; i < levels; ++i) {
        Map map(map_width, map_height);
        map.GenerateMap();

        if (i > 0) {
            Room const room = map.GetRandomRoom();
            int x = room.x + room.width / 2;
            int y = room.y + room.height / 2;

            while (map.GetTile(x, y) != '.') {
                x = room.x + 1 + rand() % (room.width - 2);
                y = room.y + 1 + rand() % (room.height - 2);
            }
            int less_x = room.x + room.width / 2;
            int less_y = room.y + room.height / 2;
            if (map.GetTile(less_x, less_y) != '.') {
                map.FindNearbyPosition(less_x, less_y);
            }
            map.SetTile(less_x, less_y, '<');
            map.SetLessSign(QPoint(less_x, less_y));
        }

        if (i < levels - 1) {
            Room const room = map.GetRandomRoom();
            int x = room.x + room.width / 2;
            int y = room.y + room.height / 2;

            while (map.GetTile(x, y) != '.') {
                x = room.x + 1 + rand() % (room.width - 2);
                y = room.y + 1 + rand() % (room.height - 2);
            }
            int greater_x = room.x + room.width / 2;
            int greater_y = room.y + room.height / 2;
            if (map.GetTile(greater_x, greater_y) != '.') {
                map.FindNearbyPosition(greater_x, greater_y);
            }
            map.SetTile(greater_x, greater_y, '>');
            map.SetGreaterSign(QPoint(greater_x, greater_y));
        }

        maps_.push_back(map);
    }

    Room const start_room = maps_[0].GetRandomRoom();
    int x = start_room.x + 1 + rand() % (start_room.width - 2);
    int y = start_room.y + 1 + rand() % (start_room.height - 2);

    while (maps_[0].GetTile(x, y) != '.') {
        x = start_room.x + 1 + rand() % (start_room.width - 2);
        y = start_room.y + 1 + rand() % (start_room.height - 2);
    }
    player_.SetPosition(x, y);
    UpdateVisibleZone();
}

void GameLogic::MovePlayer(int dx, int dy)
{
    int const new_x = player_.GetX() + dx;
    int const new_y = player_.GetY() + dy;

    const Map &map = maps_[current_level_];

    if (map.GetTile(new_x, new_y) == '.' || map.GetTile(new_x, new_y) == '+'
        || map.GetTile(new_x, new_y) == 'A' || map.GetTile(new_x, new_y) == '!'
        || map.GetTile(new_x, new_y) == '>' || map.GetTile(new_x, new_y) == '<') {
        changed_tiles_.emplace_back(player_.GetX(), player_.GetY());

        player_.SetPosition(new_x, new_y);
        UpdateVisibleZone();
        changed_tiles_.emplace_back(player_.GetX(), player_.GetY());
        game_statistics_.IncrementStepsTaken();
        emit StatsUpdated();
    }
}

void GameLogic::UpdateVisibleZone() {
    auto p_rooms_vect = maps_[current_level_].GetRoomsWithPlayer(player_.GetX(), player_.GetY());
    for (const auto & p_room : *p_rooms_vect) {
        if (p_room) {
            RoomExplored(*(p_room));
        }
    }
}

void GameLogic::RoomExplored(Room &room) {
    for (int y = room.y - 1; y <= room.y + room.height; ++y) {
        for (int x = room.x - 1; x <= room.x + room.width; ++x) {
            maps_[current_level_].TileExplored(x, y);
        }
    }
}

void GameLogic::SwitchLevel(int direction)
{
    int const new_level = current_level_ + direction;

    if (new_level >= 0 && new_level < static_cast<int>(maps_.size())) {
        current_level_ = new_level;
        const Map &new_map = maps_[current_level_];
        QPoint point = (direction == 1) ? new_map.GetLessSign() : new_map.GetGreaterSign();
        player_.SetPosition(point.x(), point.y());
        game_statistics_.SetCurrentLevel(current_level_);
        UpdateVisibleZone();
    }
}

const Map &GameLogic::GetCurrentMap() const
{
    return maps_[current_level_];
}

int GameLogic::GetPlayerX() const
{
    return player_.GetX();
}

int GameLogic::GetPlayerY() const
{
    return player_.GetY();
}

std::vector<QPoint> GameLogic::GetChangedTiles() const
{
    return changed_tiles_;
}

void GameLogic::ClearChangedTiles()
{
    changed_tiles_.clear();
}

bool GameLogic::IsPlayerOnStairs() const
{
    char const tile = maps_[current_level_].GetTile(player_.GetX(), player_.GetY());
    return (tile == '<' || tile == '>');
}

int GameLogic::GetCurrentLevel() const
{
    return current_level_;
}

void GameLogic::SetCurrentLevel(int level)
{
    if (level >= 0 && level < static_cast<int>(maps_.size())) {
        current_level_ = level;
    }
}

void GameLogic::InteractWithStairs()
{
    if (IsPlayerOnStairs()) {
        char const stair = maps_[current_level_].GetTile(player_.GetX(), player_.GetY());
        int const direction = (stair == '<') ? -1 : 1;
        SwitchLevel(direction);
    }
}

void GameLogic::SetPlayerPosition(int x, int y)
{
    player_.SetPosition(x, y);
}

void GameLogic::SetMapData(const std::vector<std::vector<char>> &data)
{
    if (current_level_ >= 0 && current_level_ < static_cast<int>(maps_.size())) {
        maps_[current_level_].SetData(data);
    }
}

const std::vector<Map> &GameLogic::GetAllMaps() const
{
    return maps_;
}

void GameLogic::SetAllMaps(const std::vector<Map> &newMaps)
{
    maps_ = newMaps;
}

void GameLogic::PickUpItem()
{
    int const x = player_.GetX();
    int const y = player_.GetY();
    std::shared_ptr<Item> const item = maps_[current_level_].GetItemAt(x, y);
    if (item) {
        player_.PickUpItem(item);
        maps_[current_level_].RemoveItemAt(x, y);
    }
}

void GameLogic::DropItem()
{
    std::shared_ptr<Item> const current_item = player_.GetCurrentItem();
    if (current_item) {
        int const x = player_.GetX();
        int const y = player_.GetY();

        if (maps_[current_level_].GetTile(x, y) == '.') {
            maps_[current_level_].AddItem(x, y, current_item);
            player_.DropItem();
        }
    }
}

void GameLogic::UseItem()
{
    player_.UseItem();
}

std::vector<std::shared_ptr<Item>> GameLogic::GetPlayerItems() const
{
    return player_.GetItems();
}

int GameLogic::GetCurrentItemIndex() const
{
    return player_.GetCurrentItemIndex();
}

void GameLogic::SelectNextItem()
{
    player_.SelectNextItem();
}

void GameLogic::SelectPreviousItem()
{
    player_.SelectPreviousItem();
}

int GameLogic::GetPlayerHealth() const
{
    return player_.GetHealth();
}

int GameLogic::GetPlayerMaxHealth() const
{
    return player_.GetMaxHealth();
}

int GameLogic::GetPlayerAttackPower() const
{
    return player_.GetAttackPower();
}

Player &GameLogic::GetPlayer()
{
    return player_;
}

void GameLogic::UpdateEnemies()
{
    const Map &map = maps_[current_level_];
    for (const auto &p_enemy : map.GetEnemies()) {
        Enemy &enemy = *p_enemy;
        int distance_to_player = enemy.StepsNumberToPlayer(player_.GetX(), player_.GetY());
        if (distance_to_player > kVisibleDistance) {
            enemy.RestEnemy();
            continue;
        }

        int result_probability = GetRandomInRange(0, 100);

        if (result_probability <= enemy.GetAttackProbability()
            && distance_to_player <= kFightDistance && enemy.GetEnergy() >= Constant::energy_for_hit) {
            player_.ReduceHealthForHit(enemy.GetAttackPower());
            continue;
        }

        if (enemy.GetEnergy() < Constant::energy_for_step) {
            enemy.RestEnemy();
            continue;
        }
        QPoint new_enemy_position = enemy.NextStep(player_.GetX(), player_.GetY());
        MoveEnemy(enemy, new_enemy_position);
    }
}

void GameLogic::MoveEnemy(Enemy &enemy, QPoint new_position)
{
    Map &map = maps_[current_level_];
    int new_x = new_position.x();
    int new_y = new_position.y();
    char tile = map.GetTile(new_x, new_y);

    if (tile == '.' || tile == '+' || tile == 'A' || tile == '!') {
        map.SetTile(enemy.GetX(), enemy.GetY(), enemy.GetEatenTile());
        enemy.SetEatenTile(tile);

        enemy.SetPosition(new_x, new_y);
        enemy.ReduceEnergyForStep();
        map.SetTile(new_x, new_y, enemy.GetSymbol());
        return;
    }

    enemy.RestEnemy();
}

GameStatistics &GameLogic::GetGameStatistics()
{
    return game_statistics_;
}

const GameStatistics &GameLogic::GetGameStatistics() const
{
    return game_statistics_;
}

void GameLogic::HitEnemy(int dx, int dy)
{
    int x_enemy = player_.GetX() + dx;
    int y_enemy = player_.GetY() + dy;
    Map &map = maps_[current_level_];
    char symbol = map.GetTile(x_enemy, y_enemy);
    if (symbol != Constant::enemy_symbol_1 && symbol != Constant::enemy_symbol_2 && symbol != Constant::enemy_symbol_3) {
        return;
    }

    for (const auto & p_enemy : map.GetEnemies()) {
        if (p_enemy->GetX() != x_enemy || p_enemy->GetY() != y_enemy) {
            continue;
        }

        attacked_enemy_ = p_enemy;

        int result_probability = GetRandomInRange(0, 100);

        if (result_probability > player_.GetAttackProbability()) {
            return;
        }

        p_enemy->ReduceHealth(player_.GetAttackPower());

        if (p_enemy->GetHealth() <= 0) {
            map.DeleteEnemy(*p_enemy);
            DropWithEnemy(*p_enemy);
            game_statistics_.IncrementEnemiesKilled();
        }

        return;
    }
}

std::shared_ptr<Enemy> GameLogic::GetAttackedEnemy()
{
    return attacked_enemy_;
}

void GameLogic::IncrementEnemiesKilled()
{
    game_statistics_.IncrementEnemiesKilled();
}

void GameLogic::SetVisibleZones(std::vector<std::vector<std::vector<bool>>> &new_visilbe_zones) {
    for (int ind1 = 0; ind1 < static_cast<int>(maps_.size()); ++ind1) {
        Map &map = maps_[ind1];
        std::vector<std::vector<bool>> &new_visible_zone = new_visilbe_zones[ind1];
        for (int y = 0; y < static_cast<int>(new_visible_zone.size()); ++y) {
            std::vector<bool> row = new_visible_zone[y];
            for (int x = 0; x < static_cast<int>(row.size()); ++x) {
                map.SetExplored(x, y, row[x]);
            }
        }
    }
}

void GameLogic::DropWithEnemy(Enemy &enemy) {
    int result_probability = GetRandomInRange(0, 100);

    if (enemy.GetSymbol() == Constant::enemy_symbol_1 && result_probability > Constant::drop_probability_1) {
        return;
    } else if (enemy.GetSymbol() == Constant::enemy_symbol_2 && result_probability > Constant::drop_probability_1) {
        return;
    } else if (enemy.GetSymbol() == Constant::enemy_symbol_3 && result_probability > Constant::drop_probability_1) {
        return;
    }

    std::shared_ptr<Item> p_item = GetRandomItem();
    if (p_item) {
        maps_[current_level_].AddItem(enemy.GetX(), enemy.GetY(), p_item);
    }
}
