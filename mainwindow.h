#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QMediaPlayer>

#include <QTimer>
#include <QKeyEvent>

#include "game.h"

namespace Ui {
    class MainWindow;
}

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    Game* game;
    QTimer* gameLoop;
    QMediaPlayer *bg_sound;
    QMediaPlayer *game_sound;
    QMediaPlayer *egg_sound;

    bool wolf_x;
    int basket_pos;
    bool play;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void movePlayer(int key);

    void Render();
private slots:
    void Play();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
};

#endif // MAINWINDOW_H
