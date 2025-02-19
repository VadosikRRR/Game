#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsTextItem>

class Player : public QGraphicsSimpleTextItem {
public:
    Player();
    Player(QString name);

private:
    int health;
    QString name;
    int attackPower;
};

#endif // PLAYER_H
