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

GameSaverLoader::GameSaverLoader(const QString &playerName)
    : player_name_(playerName)
{}

QString GameSaverLoader::GetSaveFilePath() const
{
    return QString("saves/%1_save.json").arg(player_name_);
}

bool GameSaverLoader::SaveGame(const GameLogic &gameLogic)
{
    QDir().mkdir("saves");

    QJsonObject json;
    SavePlayerData(json, gameLogic);

    QJsonArray maps_array;
    SaveMapData(maps_array, gameLogic);
    json["maps"] = maps_array;

    QFile file(GetSaveFilePath());
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(QJsonDocument(json).toJson());
    file.close();
    return true;
}

bool GameSaverLoader::LoadGame(GameLogic &gameLogic)
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

    if (!LoadPlayerData(json, gameLogic)) {
        return false;
    }
    if (!LoadMapData(json["maps"].toArray(), gameLogic)) {
        return false;
    }

    return true;
}

void GameSaverLoader::SavePlayerData(QJsonObject &json, const GameLogic &gameLogic)
{
    QJsonObject player_object;
    player_object["name"] = player_name_;
    player_object["health"] = gameLogic.getPlayerHealth();
    player_object["currentLevel"] = gameLogic.GetCurrentLevel();

    const GameStatistics &stats = gameLogic.getGameStatistics();
    player_object["totalStepsTaken"] = stats.getTotalStepsTaken();
    player_object["totalEnemiesKilled"] = stats.getTotalEnemiesKilled();

    QJsonObject position_object;
    position_object["x"] = gameLogic.GetPlayerX();
    position_object["y"] = gameLogic.GetPlayerY();
    player_object["position"] = position_object;

    QJsonArray inventory_array;
    for (const auto &item : gameLogic.GetPlayerItems()) {
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

void GameSaverLoader::SaveMapData(QJsonArray &mapsArray, const GameLogic &gameLogic)
{
    for (const auto &map : gameLogic.GetAllMaps()) {
        QJsonObject map_object;

        QJsonArray data_array;
        for (const auto &row : map.getData()) {
            data_array.append(QString::fromStdString(std::string(row.begin(), row.end())));
        }
        map_object["data"] = data_array;

        SaveItems(map_object, map);
        SaveEnemies(map_object, map);

        mapsArray.append(map_object);
    }
}

void GameSaverLoader::SaveItems(QJsonObject &mapObject, const Map &map)
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
    mapObject["items"] = items_array;
}

void GameSaverLoader::SaveEnemies(QJsonObject &mapObject, const Map &map)
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
    mapObject["enemies"] = enemies_array;
}

bool GameSaverLoader::LoadPlayerData(const QJsonObject &json, GameLogic &gameLogic)
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
    gameLogic.setCurrentLevel(current_level);

    int health = player_object["health"].toInt();
    gameLogic.getPlayer().SetHealth(health);

    GameStatistics &stats = gameLogic.getGameStatistics();
    stats.setCurrentLevel(current_level);
    stats.setStepsTaken(player_object["totalStepsTaken"].toInt());
    stats.setEnemiesKilled(player_object["totalEnemiesKilled"].toInt());

    QJsonObject position_object = player_object["position"].toObject();
    int player_x = position_object["x"].toInt();
    int player_y = position_object["y"].toInt();
    gameLogic.setPlayerPosition(player_x, player_y);

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
            gameLogic.getPlayer().PickUpItem(item);
        }
    }

    return true;
}

bool GameSaverLoader::LoadMapData(const QJsonArray &mapsArray, GameLogic &gameLogic)
{
    std::vector<Map> maps;
    for (const auto &map_value : mapsArray) {
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

    gameLogic.SetAllMaps(maps);
    return true;
}

bool GameSaverLoader::LoadItems(const QJsonArray &itemsArray, Map &map)
{
    for (const auto &item_value : itemsArray) {
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

bool GameSaverLoader::LoadEnemies(const QJsonArray &enemiesArray, Map &map)
{
    for (const auto &enemy_value : enemiesArray) {
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
