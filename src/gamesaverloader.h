#ifndef GAMESAVERLOADER_H
#define GAMESAVERLOADER_H

#include "gamelogic.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

class GameSaverLoader {
public:
  GameSaverLoader(QString playerName);

  bool saveGame(const GameLogic &gameLogic);
  bool loadGame(GameLogic &gameLogic);

private:
  QString playerName;
  QString getSaveFilePath() const;
};

#endif // GAMESAVERLOADER_H
