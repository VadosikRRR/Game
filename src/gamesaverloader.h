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
    GameSaverLoader(const QString &playerName);

    bool SaveGame(const GameLogic &gameLogic);
    bool LoadGame(GameLogic &gameLogic);

private:
    QString player_name_;
    QString GetSaveFilePath() const;

    void SavePlayerData(QJsonObject &json, const GameLogic &gameLogic);
    void SaveMapData(QJsonArray &mapsArray, const GameLogic &gameLogic);
    void SaveItems(QJsonObject &mapObject, const Map &map);
    void SaveEnemies(QJsonObject &mapObject, const Map &map);

    bool LoadPlayerData(const QJsonObject &json, GameLogic &gameLogic);
    bool LoadMapData(const QJsonArray &mapsArray, GameLogic &gameLogic);
    bool LoadItems(const QJsonArray &itemsArray, Map &map);
    bool LoadEnemies(const QJsonArray &enemiesArray, Map &map);
};

#endif // GAMESAVERLOADER_H
