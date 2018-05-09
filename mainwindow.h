#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QMediaPlayer>

#include <QTimer>
#include <QKeyEvent>
#include <QTime>

#include <set>
#include <algorithm>

#include "game.h"

namespace Ui {
    class MainWindow;
}

struct srt
{
    bool operator ()(const std::pair<QString, int> &a, const std::pair<QString, int> &b)
    {
        return a.second > b.second;
    }
};

class Wolf : public QGraphicsPixmapItem{
public:
    Wolf(bool left);
};

class Basket : public QGraphicsPixmapItem{
public:
    Basket(int pos);
};

class G_Egg : public QGraphicsPixmapItem{
public:
    G_Egg(int x, int y);
};

class Chick : public QGraphicsPixmapItem{
public:
    Chick(int x);
};

class Splinter : public QGraphicsPixmapItem{
public:
    Splinter(bool left);
};

class Indicator : public QGraphicsEllipseItem{
public:
   Indicator();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::set<std::pair<QString, int>, srt> *records;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene, *indicator1, *indicator2;

    Game* game;
    QTimer* gameLoop;
    QMediaPlayer *bg_sound, *game_sound, *egg_sound, *lost_egg_sound;

    bool wolf_x = true, play = false;
    int basket_pos = 1, tmp_lost_egg = 0;

    // QWidget interface
protected:
    void newGame(bool type);
    void writeRecord(int r);

    void keyPressEvent(QKeyEvent *event);
    void movePlayer(int key);

    void Render();
private slots:
    void Play();
    void lostEgg(bool left);
    void GameOver();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
};

#endif // MAINWINDOW_H
