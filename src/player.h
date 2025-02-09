#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player {
public:
    Player();
    Player(QString name);

private:
    int health;
    QString name;
    int attackPower;
};

#endif // PLAYER_H
