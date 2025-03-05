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

    QJsonArray visible_zones_array;
    SaveVisibleZoneData(visible_zones_array, game_logic);
    json["visible_zones"] = visible_zones_array;

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
    if (!LoadVisibleZoneData(json["visible_zones"].toArray(), game_logic)) {
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
        } else if (auto medkit = std::dynamic_pointer_cast<MedKit>(item)) {
            item_object["defence"] = medkit->GetCount();
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

        QJsonObject stairs_object;
        QPoint less_sign = map.GetLessSign();
        QPoint greater_sign = map.GetGreaterSign();
        stairs_object["less_x"] = less_sign.x();
        stairs_object["less_y"] = less_sign.y();
        stairs_object["greater_x"] = greater_sign.x();
        stairs_object["greater_y"] = greater_sign.y();
        map_object["stairs"] = stairs_object;

        SaveRooms(map_object, map);
        SaveCorridors(map_object, map);
        SaveItems(map_object, map);
        SaveEnemies(map_object, map);

        maps_array.append(map_object);
    }
}

void GameSaverLoader::SaveRooms(QJsonObject &map_object, const Map &map) {
    QJsonArray rooms_array;
    for (const auto &room : map.GetRooms()) {
        QJsonObject room_object;
        room_object["x"] = room.x;
        room_object["y"] = room.y;
        room_object["width"] = room.width;
        room_object["height"] = room.height;
        rooms_array.push_back(room_object);
    }

    map_object["rooms"] = rooms_array;
}

void GameSaverLoader::SaveCorridors(QJsonObject &map_object, const Map &map) {
    QJsonArray corridors_array;
    for (const auto &corridor : map.GetCorridors()) {
        QJsonObject corridor_object;
        corridor_object["x"] = corridor.x;
        corridor_object["y"] = corridor.y;
        corridor_object["width"] = corridor.width;
        corridor_object["height"] = corridor.height;
        corridors_array.push_back(corridor_object);
    }

    map_object["corridors"] = corridors_array;
}

void GameSaverLoader::SaveItems(QJsonObject &map_object, const Map &map)
{
    QJsonArray items_array;
    for (const auto &[pos, item] : map.GetItems()) {
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

void GameSaverLoader::SaveVisibleZoneData(QJsonArray &visible_zones_array, const GameLogic &game_logic) {
    for (const auto &map : game_logic.GetAllMaps()) {
        QJsonObject map_object;

        QJsonArray data_array;
        for (const auto &row : map.GetVisibleZone()) {
            QJsonArray row_array;
            for (size_t ind = 0; ind < row.size(); ++ind) {
                row_array.push_back(row[ind]);
            }

            data_array.push_back(row_array);
        }

        map_object["visible_zone"] = data_array;
        visible_zones_array.append(map_object);
    }
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
            int count = item_param.toInt();
            item = std::make_shared<MedKit>(count);
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
        map.SetData(map_data);

        QJsonObject stairs_object = map_object["stairs"].toObject();
        QPoint less_sign(stairs_object["less_x"].toInt(), stairs_object["less_y"].toInt());
        QPoint greater_sign(stairs_object["greater_x"].toInt(), stairs_object["greater_y"].toInt());
        map.SetLessSign(less_sign);
        map.SetGreaterSign(greater_sign);

        LoadRooms(map_object["rooms"].toArray(), map);
        LoadCorridors(map_object["corridors"].toArray(), map);
        LoadItems(map_object["items"].toArray(), map);
        LoadEnemies(map_object["enemies"].toArray(), map);

        maps.push_back(map);
    }

    game_logic.SetAllMaps(maps);
    return true;
}

bool GameSaverLoader::LoadRooms(const QJsonArray &rooms_array, Map &map) {
    for (const auto &room_value : rooms_array) {
        QJsonObject room_object = room_value.toObject();
        int x = room_object["x"].toInt();
        int y = room_object["y"].toInt();
        int width = room_object["width"].toInt();
        int height = room_object["height"].toInt();
        Room room = {x, y, width, height};
        map.LoadRoom(room);
    }

    return true;
}

bool GameSaverLoader::LoadCorridors(const QJsonArray &corridors_array, Map &map) {
    for (const auto &corridor_value : corridors_array) {
        QJsonObject corridor_object = corridor_value.toObject();
        int x = corridor_object["x"].toInt();
        int y = corridor_object["y"].toInt();
        int width = corridor_object["width"].toInt();
        int height = corridor_object["height"].toInt();
        Room corridor = {x, y, width, height};
        map.LoadCorridor(corridor);
    }

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

bool GameSaverLoader::LoadVisibleZoneData(const QJsonArray &visible_zones_array, GameLogic &game_logic) {
    std::vector<std::vector<std::vector<bool>>> new_visible_zones;

    for (qsizetype ind1 = 0; ind1 < visible_zones_array.size(); ++ind1) {
        std::vector<std::vector<bool>> new_visible_zone;
        QJsonObject visible_zone_object = visible_zones_array[ind1].toObject();
        QJsonArray visible_zone = visible_zone_object["visible_zone"].toArray();
        for (qsizetype ind2 = 0; ind2 < visible_zone.size(); ++ind2) {
            std::vector<bool> new_row;
            QJsonArray row = visible_zone[ind2].toArray();
            for (qsizetype ind3 = 0; ind3 < row.size(); ++ind3) {
                new_row.push_back(row[ind3].toBool());
            }

            new_visible_zone.push_back(new_row);
        }

        new_visible_zones.push_back(new_visible_zone);
    }

    game_logic.SetVisibleZones(new_visible_zones);

    return true;
}
