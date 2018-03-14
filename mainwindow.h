#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

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

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
