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
    Wolf();
    bool left = true;
    void advance(int phase);
protected:
    void keyPressEvent(QKeyEvent *event);
};

class Basket : public QGraphicsPixmapItem{
public:
    Basket();
    bool top = true;
    void advance(int phase);
protected:
    void keyPressEvent(QKeyEvent *event);
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

    QTimer* gameLoop;
};

#endif // MAINWINDOW_H
