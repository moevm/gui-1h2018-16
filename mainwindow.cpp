#include "mainwindow.h"
#include "ui_mainwindow.h"

#define WOLF_LEFT 180
#define WOLF_RIGHT 296
#define WOLF_Y 165

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/bg.jpg"));

    scene = new QGraphicsScene(0, 0, 572, 350, this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(":/img/game-bg.jpg"));

    game = new Game(true);

    /*gameLoop = new QTimer(this);
    connect(gameLoop, SIGNAL(timeout()),
            game, SLOT(Play()));
    gameLoop->start(1000);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    bool wolf_x;
    int basket_pos;

    switch (event->key()) {
    case Qt::Key_A:
        wolf_x = true;
        basket_pos = 1;
        game->tapEvent(true, false);
        break;
    case Qt::Key_Q:
        wolf_x = true;
        basket_pos = 2;
        game->tapEvent(true, true);
        break;
    case Qt::Key_D:
        wolf_x = false;
        basket_pos = 3;
        game->tapEvent(false, false);
        break;
    case Qt::Key_E:
        wolf_x = false;
        basket_pos = 4;
        game->tapEvent(true, true);
        break;
    default:
        return;
        break;
    }

    scene->clear();
    scene->addPixmap(QPixmap(":/img/game-bg.jpg"));

    scene->addItem(new Wolf(wolf_x));
    scene->addItem(new Basket(basket_pos));
}

Wolf::Wolf(bool left) : QGraphicsPixmapItem(0)
{
    if(left){
        setPixmap(QPixmap(":/img/wolf/wolf-p-0.png"));
        setPos(WOLF_LEFT, WOLF_Y);
    }else{
        setPixmap(QPixmap(":/img/wolf/wolf-p-1.png"));
        setPos(WOLF_RIGHT, WOLF_Y);
    }
}

Basket::Basket(int pos) : QGraphicsPixmapItem(0)
{
    switch (pos) {
    case 1:
        setPixmap(QPixmap(":/img/basket/basket-p-0-0.png"));
        setPos(125, 236);
        break;
    case 2:
        setPixmap(QPixmap(":/img/basket/basket-p-0-1.png"));
        setPos(131, 160);
        break;
    case 3:
        setPixmap(QPixmap(":/img/basket/basket-p-1-0.png"));
        setPos(361, 242);
        break;
    case 4:
        setPixmap(QPixmap(":/img/basket/basket-p-1-1.png"));
        setPos(370, 167);
        break;
    default:
        break;
    }
}
