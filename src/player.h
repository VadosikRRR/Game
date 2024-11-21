#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsTextItem>

class Player : public QGraphicsSimpleTextItem {
public:
    Player();

private:
    int health;
    int attackPower;
};

#endif // PLAYER_H
