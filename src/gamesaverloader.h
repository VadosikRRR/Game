#ifndef GAMESAVERLOADER_H
#define GAMESAVERLOADER_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "gamelogic.h"

class GameSaverLoader
{
public:
    GameSaverLoader(const QString &player_name);

    bool SaveGame(const GameLogic &game_logic);
    bool LoadGame(GameLogic &game_logic);

private:
    QString player_name_;
    QString GetSaveFilePath() const;

    void SavePlayerData(QJsonObject &json, const GameLogic &game_logic);
    void SaveMapData(QJsonArray &maps_array, const GameLogic &game_logic);
    void SaveItems(QJsonObject &map_object, const Map &map);
    void SaveEnemies(QJsonObject &map_object, const Map &map);

    bool LoadPlayerData(const QJsonObject &json, GameLogic &game_logic);
    bool LoadMapData(const QJsonArray &maps_array, GameLogic &game_logic);
    bool LoadItems(const QJsonArray &items_array, Map &map);
    bool LoadEnemies(const QJsonArray &enemies_array, Map &map);
};

#endif // GAMESAVERLOADER_H