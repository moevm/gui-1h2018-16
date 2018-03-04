#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#define MAX_SPEED 10;

class Game
{
private:
    int speed,
        score,
        life;

    class Wolf : public QGraphicsPixmapItem{
    public:
        bool left;
        Wolf();
    };

    class Basket : public QGraphicsPixmapItem{
    public:
        bool top;
        Basket();
    };

    class Egg : public QGraphicsPixmapItem{
    private:
        int layer,
        pos,
        speed;
    public:
        Egg(int layer, int speed);
        ~Egg();

        void falling();

    };

    void CollectEgg();
    void LostEgg();

    void GameOver();

public:
    Game();

    void Play(int key);

    QVector<Egg> eggs;

    void setPlayerPos(int key);
    int getPlayerPos();

    int getScore();
    int getLife();
};

#endif // GAME_H
