#include "gamesaverloader.h"

#include <utility>
#include "gamelogic.h"
#include <qfiledevice.h>
#include <vector>
#include <qchar.h>

GameSaverLoader::GameSaverLoader(QString  playerName)
    : playerName(std::move(playerName)) {}

QString GameSaverLoader::getSaveFilePath() const
{
    return QString("saves/%1_save.txt").arg(playerName);
}

bool GameSaverLoader::saveGame(const GameLogic& gameLogic)
{
    QDir().mkdir("saves");

    QString const filename = getSaveFilePath();
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);

        out << playerName << "\n";
        out << gameLogic.GetCurrentLevel() << "\n";
        out << gameLogic.GetPlayerX() << " " << gameLogic.GetPlayerY() << "\n";

        for (const auto& map : gameLogic.GetAllMaps()) {
            const auto& mapData = map.getData();
            for (const auto& row : mapData) {
                out << QString::fromStdString(std::string(row.begin(), row.end())) << "\n";
            }
            out << "---\n";
        }

        file.close();
        return true;
    }         return false;
}

bool GameSaverLoader::loadGame(GameLogic& gameLogic)
{
    QString const filename = getSaveFilePath();
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);

        QString const savedPlayerName = in.readLine();
        if (savedPlayerName != playerName) {
            file.close();
            return false;
        }

        int currentLevel = 0;
        in >> currentLevel;
        gameLogic.setCurrentLevel(currentLevel);

        int playerX;
        int playerY;
        in >> playerX >> playerY;
        gameLogic.setPlayerPosition(playerX, playerY);

        in.readLine();

        std::vector<Map> maps;
        std::vector<std::vector<char>> mapData;
        while (!in.atEnd()) {
            QString const line = in.readLine();
            if (line == "---") {
                Map map(mapData[0].size(), mapData.size());
                map.setData(mapData);
                maps.push_back(map);
                mapData.clear();
            } else {
                std::vector<char> row;
                for (QChar const qchar : line) {
                    row.push_back(qchar.toLatin1());
                }
                mapData.push_back(row);
            }
        }
        gameLogic.SetAllMaps(maps);

        file.close();
        return true;
    }         return false;
}
