#include "gamesaverloader.h"
#include "gamelogic.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <utility>
#include <vector>

GameSaverLoader::GameSaverLoader(QString playerName)
    : playerName(std::move(playerName)) {}

QString GameSaverLoader::getSaveFilePath() const {
  return QString("saves/%1_save.txt").arg(playerName);
}

bool GameSaverLoader::saveGame(const GameLogic &gameLogic) {
  QDir().mkdir("saves");

  QString const filename = getSaveFilePath();
  QFile file(filename);

  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);

    out << playerName << "\n";
    out << gameLogic.GetCurrentLevel() << "\n";
    out << gameLogic.GetPlayerX() << " " << gameLogic.GetPlayerY() << "\n";

    for (const auto &map : gameLogic.GetAllMaps()) {
      const auto &mapData = map.getData();
      for (const auto &row : mapData) {
        out << QString::fromStdString(std::string(row.begin(), row.end()))
            << "\n";
      }

      out << "---\n";

      const auto &items = map.getItems();
      for (const auto &[pos, item] : items) {
        out << "ITEM " << pos.x() << " " << pos.y() << " " << item->GetName()
            << "\n";
      }

      for (const auto &p_enemy : map.GetEnemies()) {
          out << "ENEMY " << p_enemy->GetLevel() << " "
              << p_enemy->GetX() << " " << p_enemy->GetY()
              << "\n";
      }

      out << "END\n";
    }

    const auto &inventory = gameLogic.GetPlayerItems();
    for (const auto &item : inventory) {
      out << "INVENTORY " << item->GetName() << "\n";
    }

    file.close();
    return true;
  }
  return false;
}

bool GameSaverLoader::loadGame(GameLogic &gameLogic) {
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
      } else if (line == "END") {
        mapData.clear();
      } else if (line.startsWith("ENEMY ")) {
          QStringList parts = line.split(" ");
          int enemyLevel = parts[1].toInt();
          int x = parts[2].toInt();
          int y = parts[3].toInt();

          std::shared_ptr<Enemy> p_enemy = std::make_shared<Enemy>(enemyLevel, x, y);
          maps.back().LoadEnemy(p_enemy);
      } else if (line.startsWith("ITEM ")) {
        QStringList parts = line.split(" ");
        int x = parts[1].toInt();
        int y = parts[2].toInt();
        QString itemName = parts[3];

        std::shared_ptr<Item> item;
        if (itemName == "Sword") {
          item = std::make_shared<Sword>(10);
        } else if (itemName == "MedKit") {
          item = std::make_shared<MedKit>();
        }

        if (item) {
          maps.back().LoadItem(x, y, item);
        }
      } else if (line.startsWith("INVENTORY ")) {
        QString itemName = line.section(' ', 1);
        std::shared_ptr<Item> item;
        if (itemName == "Sword") {
          item = std::make_shared<Sword>(10);
        } else if (itemName == "MedKit") {
          item = std::make_shared<MedKit>();
        }

        if (item) {
          gameLogic.getPlayer().PickUpItem(item);
        }
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
  }
  return false;
}
