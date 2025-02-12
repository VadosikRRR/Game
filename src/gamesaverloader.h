#ifndef GAMESAVERLOADER_H
#define GAMESAVERLOADER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include "gamelogic.h"

class GameSaverLoader {
public:
    GameSaverLoader(QString  playerName);

    bool saveGame(const GameLogic& gameLogic);
    bool loadGame(GameLogic& gameLogic);

private:
    QString playerName;
    QString getSaveFilePath() const;
};

#endif // GAMESAVERLOADER_H
