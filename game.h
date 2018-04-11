#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#define MAX_SPEED 2;
#define LAYER_LEN 5;

class Egg
{
public:
    int layer,
        pos,
        speed;

    Egg(int layer, int speed);
    ~Egg();
};

class Game : public QObject
{
    Q_OBJECT
private:
    int chance = 5,
        score = 0,
        life = 3;

    bool style;

    bool player_wolf,
         player_basket;

    bool takeIt(int layer);

    void GameOver();
public:
    explicit Game(bool typeA, QObject *parent = 0);
    virtual ~Game(){};

    QVector<Egg*> *eggs;

    void Play();
    void tapEvent(bool left_wolf, bool top_basket);

    int getScore();
    int getLife();
signals:
    void collectEgg();
};

#endif // GAME_H
