#ifndef GAME_H
#define GAME_H

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

class Game
{
private:
    int chance = 10,
        score = 0,
        life = 3;

    bool style;

    bool player_wolf,
         player_basket;

    void CollectEgg();
    void LostEgg();

    void GameOver();

public:
    Game(bool typeA);
    QVector<Egg*> *eggs;

    void newEgg();
    void tapEvent(bool left_wolf, bool top_basket);

    int getPlayerPos();
    int getScore();
    int getLife();
public slots:
    void Play();
};

#endif // GAME_H
