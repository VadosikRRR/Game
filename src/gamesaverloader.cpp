#include "gamesaverloader.h"
#include <QChar>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "enemy.h"
#include "gamelogic.h"
#include "item.h"
#include "map.h"

GameSaverLoader::GameSaverLoader(const QString &player_name)
    : player_name_(player_name)
{}

QString GameSaverLoader::GetSaveFilePath() const
{
    return QString("saves/%1_save.json").arg(player_name_);
}

bool GameSaverLoader::SaveGame(const GameLogic &game_logic)
{
    QDir().mkdir("saves");

    QJsonObject json;
    SavePlayerData(json, game_logic);

    QJsonArray maps_array;
    SaveMapData(maps_array, game_logic);
    json["maps"] = maps_array;

    QFile file(GetSaveFilePath());
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(QJsonDocument(json).toJson());
    file.close();
    return true;
}

bool GameSaverLoader::LoadGame(GameLogic &game_logic)
{
    QFile file(GetSaveFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument json_document = QJsonDocument::fromJson(data);
    if (json_document.isNull()) {
        return false;
    }

    QJsonObject json = json_document.object();

    if (!LoadPlayerData(json, game_logic)) {
        return false;
    }
    if (!LoadMapData(json["maps"].toArray(), game_logic)) {
        return false;
    }

    return true;
}

void GameSaverLoader::SavePlayerData(QJsonObject &json, const GameLogic &game_logic)
{
    QJsonObject player_object;
    player_object["name"] = player_name_;
    player_object["health"] = game_logic.GetPlayerHealth();
    player_object["currentLevel"] = game_logic.GetCurrentLevel();

    const GameStatistics &stats = game_logic.GetGameStatistics();
    player_object["totalStepsTaken"] = stats.GetTotalStepsTaken();
    player_object["totalEnemiesKilled"] = stats.GetTotalEnemiesKilled();

    QJsonObject position_object;
    position_object["x"] = game_logic.GetPlayerX();
    position_object["y"] = game_logic.GetPlayerY();
    player_object["position"] = position_object;

    QJsonArray inventory_array;
    for (const auto &item : game_logic.GetPlayerItems()) {
        QJsonObject item_object;
        item_object["type"] = item->GetName();
        if (auto sword = std::dynamic_pointer_cast<Sword>(item)) {
            item_object["damage"] = sword->GetDamage();
        } else if (auto armor = std::dynamic_pointer_cast<Armor>(item)) {
            item_object["defence"] = armor->GetDefense();
        }
        inventory_array.append(item_object);
    }
    player_object["inventory"] = inventory_array;

    json["player"] = player_object;
}

void GameSaverLoader::SaveMapData(QJsonArray &maps_array, const GameLogic &game_logic)
{
    for (const auto &map : game_logic.GetAllMaps()) {
        QJsonObject map_object;

        QJsonArray data_array;
        for (const auto &row : map.GetData()) {
            data_array.append(QString::fromStdString(std::string(row.begin(), row.end())));
        }
        map_object["data"] = data_array;

        SaveItems(map_object, map);
        SaveEnemies(map_object, map);

        maps_array.append(map_object);
    }
}

void GameSaverLoader::SaveItems(QJsonObject &map_object, const Map &map)
{
    QJsonArray items_array;
    for (const auto &[pos, item] : map.getItems()) {
        QJsonObject item_object;
        item_object["type"] = item->GetName();
        QJsonObject position_object;
        position_object["x"] = pos.x();
        position_object["y"] = pos.y();
        item_object["position"] = position_object;
        items_array.append(item_object);
    }
    map_object["items"] = items_array;
}

void GameSaverLoader::SaveEnemies(QJsonObject &map_object, const Map &map)
{
    QJsonArray enemies_array;
    for (const auto &enemy : map.GetEnemies()) {
        QJsonObject enemy_object;
        enemy_object["type"] = enemy->GetName();
        enemy_object["level"] = enemy->GetLevel();
        QJsonObject position_object;
        position_object["x"] = enemy->GetX();
        position_object["y"] = enemy->GetY();
        enemy_object["position"] = position_object;
        enemies_array.append(enemy_object);
    }
    map_object["enemies"] = enemies_array;
}

bool GameSaverLoader::LoadPlayerData(const QJsonObject &json, GameLogic &game_logic)
{
    if (!json.contains("player")) {
        return false;
    }

    QJsonObject player_object = json["player"].toObject();
    QString saved_player_name = player_object["name"].toString();
    if (saved_player_name != player_name_) {
        return false;
    }
    int current_level = player_object["currentLevel"].toInt();
    game_logic.SetCurrentLevel(current_level);

    int health = player_object["health"].toInt();
    game_logic.GetPlayer().SetHealth(health);

    GameStatistics &stats = game_logic.GetGameStatistics();
    stats.SetCurrentLevel(current_level);
    stats.SetStepsTaken(player_object["totalStepsTaken"].toInt());
    stats.SetEnemiesKilled(player_object["totalEnemiesKilled"].toInt());

    QJsonObject position_object = player_object["position"].toObject();
    int player_x = position_object["x"].toInt();
    int player_y = position_object["y"].toInt();
    game_logic.SetPlayerPosition(player_x, player_y);

    QJsonArray inventory_array = player_object["inventory"].toArray();
    for (const auto &item_value : inventory_array) {
        QJsonObject item_object = item_value.toObject();

        QString item_type = item_object["type"].toString();
        QString item_name = item_type.section('(', 0, 0).trimmed();
        QString item_param = item_type.section('(', 1).section(')', 0, 0).trimmed();

        std::shared_ptr<Item> item;

        if (item_name == "Sword") {
            int damage = item_param.toInt();
            item = std::make_shared<Sword>(damage);
        } else if (item_name == "MedKit") {
            item = std::make_shared<MedKit>();
        } else if (item_name == "Armor") {
            int defense = item_param.toInt();
            item = std::make_shared<Armor>(defense);
        }

        if (item) {
            game_logic.GetPlayer().PickUpItem(item);
        }
    }

    return true;
}

bool GameSaverLoader::LoadMapData(const QJsonArray &maps_array, GameLogic &game_logic)
{
    std::vector<Map> maps;
    for (const auto &map_value : maps_array) {
        QJsonObject map_object = map_value.toObject();

        QJsonArray data_array = map_object["data"].toArray();
        std::vector<std::vector<char>> map_data;
        for (const auto &row_value : data_array) {
            QString row = row_value.toString();
            std::vector<char> row_data;
            for (QChar qchar : row) {
 row_data.push_back(qchar.toLatin1());
            }
            map_data.push_back(row_data);
        }

        Map map(map_data[0].size(), map_data.size());
        map.setData(map_data);

        LoadItems(map_object["items"].toArray(), map);
        LoadEnemies(map_object["enemies"].toArray(), map);

        maps.push_back(map);
    }

    game_logic.SetAllMaps(maps);
    return true;
}

bool GameSaverLoader::LoadItems(const QJsonArray &items_array, Map &map)
{
    for (const auto &item_value : items_array) {
        QJsonObject item_object = item_value.toObject();
        QString item_type = item_object["type"].toString();
        QJsonObject position_object = item_object["position"].toObject();
        int x = position_object["x"].toInt();
        int y = position_object["y"].toInt();

        std::shared_ptr<Item> item;

        QString item_name = item_type.section('(', 0, 0).trimmed();
        QString item_param = item_type.section('(', 1).section(')', 0, 0).trimmed();

        if (item_name == "Sword") {
            int damage = item_param.toInt();
            item = std::make_shared<Sword>(damage);
        } else if (item_name == "MedKit") {
            item = std::make_shared<MedKit>();
        } else if (item_name == "Armor") {
            int defense = item_param.toInt();
            item = std::make_shared<Armor>(defense);
        }

        if (item) {
            map.LoadItem(x, y, item);
        }
    }
    return true;
}

bool GameSaverLoader::LoadEnemies(const QJsonArray &enemies_array, Map &map)
{
    for (const auto &enemy_value : enemies_array) {
        QJsonObject enemy_object = enemy_value.toObject();
        QString enemy_type = enemy_object["type"].toString();
        int level = enemy_object["level"].toInt();
        QJsonObject position_object = enemy_object["position"].toObject();
        int x = position_object["x"].toInt();
        int y = position_object["y"].toInt();

        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(level, x, y);
        map.LoadEnemy(enemy);
    }
    return true;
}