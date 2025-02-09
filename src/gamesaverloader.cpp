#include "gamesaverloader.h"

GameSaverLoader::GameSaverLoader(const QString& playerName)
    : playerName(playerName) {}

QString GameSaverLoader::getSaveFilePath() const {
    return QString("saves/%1_save.txt").arg(playerName);
}

bool GameSaverLoader::saveGame(const GameLogic& gameLogic) {
    QDir().mkdir("saves");

    QString filename = getSaveFilePath();
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);

        out << playerName << "\n";
        out << gameLogic.getCurrentLevel() << "\n";
        out << gameLogic.getPlayerX() << " " << gameLogic.getPlayerY() << "\n";

        for (const auto& map : gameLogic.getAllMaps()) {
            const auto& mapData = map.getData();
            for (const auto& row : mapData) {
                out << QString::fromStdString(std::string(row.begin(), row.end())) << "\n";
            }
            out << "---\n";
        }

        file.close();
        return true;
    } else {
        return false;
    }
}

bool GameSaverLoader::loadGame(GameLogic& gameLogic) {
    QString filename = getSaveFilePath();
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);

        QString savedPlayerName = in.readLine();
        if (savedPlayerName != playerName) {
            file.close();
            return false;
        }

        int currentLevel;
        in >> currentLevel;
        gameLogic.setCurrentLevel(currentLevel);

        int playerX, playerY;
        in >> playerX >> playerY;
        gameLogic.setPlayerPosition(playerX, playerY);

        in.readLine();

        std::vector<Map> maps;
        std::vector<std::vector<char>> mapData;
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line == "---") {
                Map map(mapData[0].size(), mapData.size());
                map.setData(mapData);
                maps.push_back(map);
                mapData.clear();
            } else {
                std::vector<char> row;
                for (QChar qchar : line) {
                    row.push_back(qchar.toLatin1());
                }
                mapData.push_back(row);
            }
        }
        gameLogic.setAllMaps(maps);

        file.close();
        return true;
    } else {
        return false;
    }
}
